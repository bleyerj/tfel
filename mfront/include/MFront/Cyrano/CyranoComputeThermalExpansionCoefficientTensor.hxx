/*!
 * \file   mfront/include/MFront/Cyrano/CyranoComputeThermalExpansionCoefficientTensor.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   21 fév 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_MFRONT_CYRANOCOMPUTETHERMALEXPANSIONTENSOR_HXX_
#define _LIB_MFRONT_CYRANOCOMPUTETHERMALEXPANSIONTENSOR_HXX_ 

#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#include"MFront/Cyrano/Cyrano.hxx"
#include"MFront/Cyrano/CyranoConfig.hxx"
#include"MFront/Cyrano/CyranoTraits.hxx"

namespace cyrano
{

  template<tfel::material::ModellingHypothesis::Hypothesis H,
	   CyranoSymmetryType>
  struct CyranoComputeThermalExpansionCoefficientTensor;

  template<>
  struct MFRONT_CYRANO_VISIBILITY_EXPORT
  CyranoComputeThermalExpansionCoefficientTensor<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN,ISOTROPIC>
  {
    static void
      exe(const CyranoReal* const,
	  tfel::config::Types<1u,CyranoReal,false>::ThermalExpansionCoefficientTensor&);
  }; // end of struct CyranoComputeThermalExpansionCoefficientTensor

  template<>
  struct MFRONT_CYRANO_VISIBILITY_EXPORT
  CyranoComputeThermalExpansionCoefficientTensor<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN,ORTHOTROPIC>
  {
    static void
      exe(const CyranoReal* const,
	  tfel::config::Types<1u,CyranoReal,false>::ThermalExpansionCoefficientTensor&);
  }; // end of struct CyranoComputeThermalExpansionCoefficientTensor

  template<>
  struct MFRONT_CYRANO_VISIBILITY_EXPORT
  CyranoComputeThermalExpansionCoefficientTensor<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS,ISOTROPIC>
  {
    static void
      exe(const CyranoReal* const,
	  tfel::config::Types<1u,CyranoReal,false>::ThermalExpansionCoefficientTensor&);
  }; // end of struct CyranoComputeThermalExpansionCoefficientTensor

  template<>
  struct MFRONT_CYRANO_VISIBILITY_EXPORT
  CyranoComputeThermalExpansionCoefficientTensor<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS,ORTHOTROPIC>
  {
    static void
      exe(const CyranoReal* const,
	  tfel::config::Types<1u,CyranoReal,false>::ThermalExpansionCoefficientTensor&);
  }; // end of struct CyranoComputeThermalExpansionCoefficientTensor

} // end of namespace cyrano

#endif /* _LIB_MFRONT_CYRANOCOMPUTETHERMALEXPANSIONTENSOR_HXX */

