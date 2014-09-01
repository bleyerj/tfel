/*!
 * \file   mfront/include/MFront/MFrontModelInterfaceFactory.hxx
 * \brief  
 * \author Helfer Thomas
 * \date   09 nov 2006
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_MFRONMODELTINTERFACEFACTORY_HXX_
#define _LIB_MFRONMODELTINTERFACEFACTORY_HXX_ 

#include<vector>
#include<string>
#include<map>

#include"TFEL/Config/TFELConfig.hxx"
#include"MFront/MFrontModelVirtualInterface.hxx"

namespace mfront{

  struct TFEL_VISIBILITY_EXPORT MFrontModelInterfaceFactory
  {
    typedef MFrontModelVirtualInterface* (*InterfaceCreator)(void);
    
    static MFrontModelInterfaceFactory&
    getMFrontModelInterfaceFactory();

    std::vector<std::string>
    getRegistredInterfaces(void);

    void registerInterfaceCreator(const std::string&,
				  InterfaceCreator);
    
    MFrontModelVirtualInterface* 
    getInterfacePtr(const std::string&);
    
    void
    reset(void);

    void
    clear(void);

    ~MFrontModelInterfaceFactory();
    
  private:

    typedef std::map<std::string,InterfaceCreator> InterfaceCreatorsContainer;
    typedef std::map<std::string,MFrontModelVirtualInterface *> InterfaceContainer;

    TFEL_VISIBILITY_LOCAL
    MFrontModelInterfaceFactory();

    TFEL_VISIBILITY_LOCAL
    InterfaceCreatorsContainer&
    getInterfaceCreatorsMap(void);

    TFEL_VISIBILITY_LOCAL
    InterfaceContainer&
    getInterfacesMap(void);

  };

} // end of namespace mfront  

#endif /* _LIB_MFRONTMODELINTERFACEFACTORY_HXX */

