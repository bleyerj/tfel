/*!
 * \file   src/Utilities/GenTypeCastError.cxx
 * \brief  This file implements the GenTypeCastError class
 * \see    GenTypeBase
 * \author Helfer Thomas
 * \date   29 Jan. 2009
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include<string>

#include"TFEL/Utilities/GenTypeCastError.hxx"

namespace tfel
{
  
  namespace utilities
  {

    GenTypeCastError::GenTypeCastError()
      : std::runtime_error(std::string("GenTypeCastError : bad cast"))
    {} // end of GenTypeCastError::GenTypeCastError

  } // end of namespace utilities

} // end of namespace tfel
