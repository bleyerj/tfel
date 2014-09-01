/*!
 * \file   mfront/include/MFront/Cyrano/CyranoException.hxx
 * 
 * \brief    
 * \author Helfer Thomas
 * \date   21 fév 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_MFRONT_CYRANOEXCEPTION_H_
#define _LIB_MFRONT_CYRANOEXCEPTION_H_ 

#include<string>
#include<exception>

#include"MFront/Cyrano/CyranoConfig.hxx"

namespace cyrano {

  struct MFRONT_CYRANO_VISIBILITY_EXPORT CyranoException
    : public std::exception
  {

    CyranoException(const std::string&);

    CyranoException(const CyranoException&);

    const char* 
    what (void) const throw();

    std::string 
    getMsg(void) const throw();
    
    virtual ~CyranoException() throw();

  private:
    
    CyranoException();

    CyranoException&
    operator=(const CyranoException&);

    const std::string msg;
    
  }; // end of struct CyranoException

  struct MFRONT_CYRANO_VISIBILITY_EXPORT CyranoIntegrationFailed
    : public CyranoException
  {
    CyranoIntegrationFailed();
    CyranoIntegrationFailed(const std::string&);
    CyranoIntegrationFailed(const CyranoIntegrationFailed&);
    virtual ~CyranoIntegrationFailed() throw();
  private:
    CyranoIntegrationFailed&
    operator=(const CyranoIntegrationFailed&);
  }; // end of struct CyranoIntegrationFailed

  struct MFRONT_CYRANO_VISIBILITY_EXPORT CyranoInvalidNTENSValue
    : public CyranoException
  {
    CyranoInvalidNTENSValue(const unsigned short);
    CyranoInvalidNTENSValue(const CyranoInvalidNTENSValue&);
    virtual ~CyranoInvalidNTENSValue() throw();
  private:
    CyranoInvalidNTENSValue();
    CyranoInvalidNTENSValue&
    operator=(const CyranoInvalidNTENSValue&);
  }; // end of struct CyranoInvalidNTENSValue

  struct MFRONT_CYRANO_VISIBILITY_EXPORT CyranoInvalidDimension
    : public CyranoException
  {
    CyranoInvalidDimension(const std::string&,
			 const unsigned short);
    CyranoInvalidDimension(const CyranoInvalidDimension&);
    virtual ~CyranoInvalidDimension() throw();
  private:
    CyranoInvalidDimension();
    CyranoInvalidDimension&
    operator=(const CyranoInvalidDimension&);
  }; // end of struct CyranoInvalidDimension
  
} // end of namespace cyrano

#endif /* _LIB_MFRONT_CYRANOEXCEPTION_H */

