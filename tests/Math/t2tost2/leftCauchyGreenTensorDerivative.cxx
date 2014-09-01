/*! 
 * \file  tests/Math/t2tost2/leftCauchyGreenTensorDerivative.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 04 juin 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifdef NDEBUG
#undef NDEBUG
#endif /* NDEBUG */

#include<cmath>
#include<cstdlib>
#include<cassert>

#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/tensor.hxx"
#include"TFEL/Math/t2tost2.hxx"
#include"TFEL/Utilities/ToString.hxx"

#include"TFEL/Tests/TestCase.hxx"
#include"TFEL/Tests/TestProxy.hxx"
#include"TFEL/Tests/TestManager.hxx"

template<unsigned short N>
struct LeftCauchyGreenTensorDerivative
  : public tfel::tests::TestCase
{
  LeftCauchyGreenTensorDerivative()
    : tfel::tests::TestCase("TFEL/Math",
			    "LeftCauchyGreenTensorDerivative"+
			    tfel::utilities::ToString(N))
  {} // end of LeftCauchyGreenTensorDerivative
  tfel::tests::TestResult
  execute()
  {
    using namespace std;
    using namespace tfel::math;
    const double eps  = 1.e-7;
    const double prec = 1.e-8;
    tensor<N> F;
    for(typename tensor<N>::size_type i=0;i!=F.size();++i){
      if(i<3){
	F[i] = 1+0.03*i*i;
      } else {
	F[i] = 0.03*i;
      }
    }
    stensor<N> B  = computeLeftCauchyGreenTensor(F);
    t2tost2<N> dB = t2tost2<N>::dBdF(F);
    t2tost2<N> ndB;
    for(typename tensor<N>::size_type i=0;i!=F.size();++i){
      tensor<N> Fe(F);
      Fe[i] += eps;
      stensor<N> Bfe=computeLeftCauchyGreenTensor(Fe);
      Fe[i] -= 2*eps;
      stensor<N> Bbe=computeLeftCauchyGreenTensor(Fe);
      for(typename tensor<N>::size_type j=0;j!=B.size();++j){
	ndB(j,i) = (Bfe(j)-Bbe(j))/(2*eps);
      }
    }
    for(typename tensor<N>::size_type i=0;i!=B.size();++i){
      for(typename tensor<N>::size_type j=0;j!=F.size();++j){
	TFEL_TESTS_ASSERT(abs(ndB(i,j)-dB(i,j))<prec);
	if(abs(ndB(i,j)-dB(i,j))>prec){
	  cout << "error (" << N << "): " << i << " " << j << " " << ndB(i,j) << " " << dB(i,j) << " " << abs(ndB(i,j)-dB(i,j)) << endl;
	}
      }
    }
    return this->result;
  } // end of execute
};

typedef LeftCauchyGreenTensorDerivative<1u> LeftCauchyGreenTensorDerivative_1D;
typedef LeftCauchyGreenTensorDerivative<2u> LeftCauchyGreenTensorDerivative_2D;
typedef LeftCauchyGreenTensorDerivative<3u> LeftCauchyGreenTensorDerivative_3D;
TFEL_TESTS_GENERATE_PROXY(LeftCauchyGreenTensorDerivative_1D,"LeftCauchyGreenTensorDerivative-1D");
TFEL_TESTS_GENERATE_PROXY(LeftCauchyGreenTensorDerivative_2D,"LeftCauchyGreenTensorDerivative-2D");
TFEL_TESTS_GENERATE_PROXY(LeftCauchyGreenTensorDerivative_3D,"LeftCauchyGreenTensorDerivative-3D");

int main(void){
  using namespace std;
  using namespace std;
  using namespace tfel::tests;
  using namespace tfel::utilities;
  TestManager& manager = TestManager::getTestManager();
  manager.addTestOutput(cout);
  manager.addXMLTestOutput("LeftCauchyGreenTensorDerivative.xml");
  TestResult r = manager.execute();
  if(!r.success()){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
