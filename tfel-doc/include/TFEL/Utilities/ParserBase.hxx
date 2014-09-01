/*! 
 * \file  tfel-doc/include/TFEL/Utilities/ParserBase.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 03 mai 2011
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_TFEL_UTILITIES_PARSERBASE_H_
#define _LIB_TFEL_UTILITIES_PARSERBASE_H_ 

#include"TFEL/Utilities/CxxTokenizer.hxx"

namespace tfel
{

  namespace utilities
  {

    /*!
     * This class defines some helper function for parsing
     * configuration files
     */
    struct ParserBase
      : public tfel::utilities::CxxTokenizer
    {
    protected:
      
      /*!
       * check if the end of file has not been reached
       * \param p : current location in file
       */
      void
      checkNotEndOfFile(const_iterator);
      
      /*!
       * check if the specified word is at the specified location
       * \param v : word to be read
       * \param p : current location in file
       */
      void
      readSpecifiedToken(const std::string&,
			 const_iterator&);
      
      /*!
       * extract the value of a string
       * \param s : string to be read
       * \param p : current location in file
       */
      void
      readString(std::string&,
		 const_iterator&);
      
      /*!
       * \return the value of the string at the specified location
       * \param p : current location in file
       */
      std::string
      readString(const_iterator&);
      
    };

  } // end of namespace utilities

} // end of namespace tfel

#endif /* _LIB_PARSERBASE_H */

