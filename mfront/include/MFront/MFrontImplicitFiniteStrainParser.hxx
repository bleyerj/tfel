/*! 
 * \file  mfront/include/MFront/MFrontImplicitFiniteStrainParser.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 18 févr. 2013
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_MFRONT_IMPLICITFINITESTRAINPARSER_H_
#define _LIB_MFRONT_IMPLICITFINITESTRAINPARSER_H_ 

#include"MFront/MFrontImplicitParserBase.hxx"

namespace mfront
{

  /*!
   *
   */
  struct MFrontImplicitFiniteStrainParser
    : public MFrontImplicitParserBase
  {

    MFrontImplicitFiniteStrainParser();

    static std::string 
    getName(void);

    static std::string 
    getDescription(void);

  }; // end of struct MFrontImplicitFiniteStrainParser

} // end of namespace mfront

#endif /* _LIB_MFRONT_IMPLICITFINITESTRAINPARSER_H */

