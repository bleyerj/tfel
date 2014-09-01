/*!
 * \file   include/TFEL/Math/Parser/EvaluatorBase.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   02 oct 2007
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_TFEL_PARSERBASE_HXX_
#define _LIB_TFEL_PARSERBASE_HXX_ 

#include<vector>
#include<string>

#include"TFEL/Config/TFELConfig.hxx"

namespace tfel
{
  namespace math
  {

    namespace parser
    {

      struct TFELMATHPARSER_VISIBILITY_EXPORT EvaluatorBase
      {
      protected:
	void
	analyse(const std::string&);
	std::vector<std::string> tokens;
      private:
	static TFEL_VISIBILITY_LOCAL void
	splitAtTokenSeperator(std::vector<std::string>&);
	static TFEL_VISIBILITY_LOCAL
	std::string
	readNumber(std::string::iterator&,const std::string::iterator);
      }; // end of struct EvaluatorBase

    } // end of namespace parser

  } // end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_PARSERBASE_HXX */

