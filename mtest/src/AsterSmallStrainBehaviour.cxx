/*!
 * \file   mtest/src/AsterSmallStrainBehaviour.cxx
 * \brief
 * \author Thomas Helfer
 * \brief  07 avril 2013
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#include <cmath>
#include <ostream>
#include <algorithm>

#include "TFEL/Raise.hxx"
#include "TFEL/Math/tmatrix.hxx"
#include "TFEL/Math/stensor.hxx"
#include "TFEL/Math/st2tost2.hxx"
#include "MFront/MFrontLogStream.hxx"
#include "MFront/Aster/Aster.hxx"
#include "MFront/Aster/AsterComputeStiffnessTensor.hxx"

#include "MTest/CurrentState.hxx"
#include "MTest/BehaviourWorkSpace.hxx"
#include "MTest/UmatNormaliseTangentOperator.hxx"
#include "MTest/AsterSmallStrainBehaviour.hxx"

namespace mtest {

  AsterSmallStrainBehaviour::AsterSmallStrainBehaviour(const Hypothesis h,
                                                       const std::string& l,
                                                       const std::string& b)
      : AsterStandardBehaviour(h, l, b) {
  }  // end of AsterSmallStrainBehaviour::AsterSmallStrainBehaviour

  void AsterSmallStrainBehaviour::getGradientsDefaultInitialValues(
      tfel::math::vector<real>& v) const {
    std::fill(v.begin(), v.end(), real(0));
  }

  std::pair<bool, real> AsterSmallStrainBehaviour::call_behaviour(
      tfel::math::matrix<real>& Kt,
      CurrentState& s,
      BehaviourWorkSpace& wk,
      const real dt,
      const StiffnessMatrixType ktype,
      const bool b) const {
    using namespace tfel::math;
    using namespace aster;
    using tfel::math::vector;
    constexpr auto sqrt2 = Cste<real>::sqrt2;
    unsigned short dimension;
    AsterInt ntens;
    AsterInt nprops =
        s.mprops1.size() == 0 ? 1 : static_cast<AsterInt>(s.mprops1.size());
    AsterInt nstatv;
    AsterInt nummod;
    const auto h = this->getHypothesis();
    if (h == ModellingHypothesis::AXISYMMETRICAL) {
      ntens = 4;
      dimension = 2u;
      nummod = 4u;
    } else if (h == ModellingHypothesis::PLANESTRESS) {
      ntens = 4;
      dimension = 2u;
      nummod = 5u;
    } else if (h == ModellingHypothesis::PLANESTRAIN) {
      ntens = 4;
      dimension = 2u;
      nummod = 6u;
    } else if (h == ModellingHypothesis::TRIDIMENSIONAL) {
      ntens = 6;
      dimension = 3u;
      nummod = 3u;
    } else {
      tfel::raise(
          "AsterSmallStrainBehaviour::call_behaviour: "
          "unsupported hypothesis");
    }
    std::fill(wk.D.begin(), wk.D.end(), 0.);
    // choosing the type of stiffness matrix
    StandardBehaviourBase::initializeTangentOperator(wk.D, ktype, b);
    // using a local copy of material properties to handle the
    // case where s.mprops1 is empty
    std::copy(s.mprops1.begin(), s.mprops1.end(), wk.mps.begin());
    if (s.mprops1.empty()) {
      wk.mps[0] = real(0);
    }
    // using a local copy of internal state variables to handle the
    // case where iv0 is empty
    std::copy(s.iv0.begin(), s.iv0.end(), wk.ivs.begin());
    if (s.iv0.empty()) {
      wk.ivs[0] = real(0);
    }
    nstatv = static_cast<AsterInt>(wk.ivs.size());
    // rotation matrix
    tmatrix<3u, 3u, real> drot = transpose(s.r);
    stensor<3u, real> ue0(real(0));
    stensor<3u, real> ude(real(0));
    std::copy(s.e0.begin(), s.e0.end(), ue0.begin());
    for (decltype(s.e1.size()) i = 0; i != s.e1.size(); ++i) {
      ude(i) = s.e1(i) - s.e0(i);
    }
    std::copy(s.s0.begin(), s.s0.end(), s.s1.begin());
    // thermal strain
    for (AsterInt i = 0; i != static_cast<unsigned short>(ntens); ++i) {
      ue0(i) -= s.e_th0(i);
      ude(i) -= s.e_th1(i) - s.e_th0(i);
    }
    // aster conventions
    for (AsterInt i = 3; i != static_cast<unsigned short>(ntens); ++i) {
      s.s1(i) /= sqrt2;
      ue0(i) *= sqrt2;
      ude(i) *= sqrt2;
    }
    AsterReal ndt(1.);
    (this->fct)(&(s.s1(0)), &(wk.ivs(0)), &(wk.D(0, 0)), &ue0(0), &ude(0), &dt,
                &(s.esv0(0)), &(s.desv(0)), &(s.esv0(0)) + 1, &(s.desv(0)) + 1,
                &ntens, &nstatv, &(wk.mps(0)), &nprops, &drot(0, 0), &ndt,
                &nummod);
    if (ndt < 1) {
      if (mfront::getVerboseMode() >= mfront::VERBOSE_LEVEL1) {
        if (this->emsg != nullptr) {
          mfront::getLogStream() << this->emsg() << std::endl;
        }
      }
      return {false, ndt};
    }
    if (ktype != StiffnessMatrixType::NOSTIFFNESS) {
      UmatNormaliseTangentOperator::exe(&Kt(0, 0), wk.D, dimension);
    }
    if (b) {
      if (!s.iv0.empty()) {
        std::copy_n(wk.ivs.begin(), s.iv1.size(), s.iv1.begin());
      }
      // turning things in standard conventions
      for (AsterInt i = 3; i != static_cast<unsigned short>(ntens); ++i) {
        s.s1(i) *= sqrt2;
      }
    }
    return {true, ndt};
  }

  AsterSmallStrainBehaviour::~AsterSmallStrainBehaviour() = default;

}  // end of namespace mtest
