/*! 
 * \file  mfront/src/MaterialPropertyDescription.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 03 mars 2014
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include"MFront/MaterialPropertyDescription.hxx"

namespace mfront
{

  std::vector<std::string>
  MaterialPropertyDescription::getInputVariableGlossaryNames(void)
  {
    return this->inputs.getGlossaryNames(this->glossaryNames,
					 this->entryNames);
  } // end of MaterialPropertyDescription::getInputVariableGlossaryNames

} // end of namespace mfront
