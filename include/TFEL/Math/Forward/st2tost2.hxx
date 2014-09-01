/*! 
 * \file  include/TFEL/Math/Forward/st2tost2.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 03 janv. 2012
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_TFEL_MATH_FORWARD_ST2TOST2_H_
#define _LIB_TFEL_MATH_FORWARD_ST2TOST2_H_ 

namespace tfel{
  
  namespace math {

    /*
     * \class st2tost2
     * \brief finite size linear function on symmetric tensor.
     * \param N, the spatial dimension, see StensorDimeToSize for details. 
     * \param T, numerical type used, by default, double
     * \pre   This class is only defined for N=1u,2u and 3u.
     * \see   StensorDimeToSize and StensorSizeToDime.
     */
    template<unsigned short N,
	     typename T = double>
    struct st2tost2;

  } // end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_MATH_FORWARD_ST2TOST2_H */

