/*!
 * \file   src/Tests/TestSuite.cxx
 * \author Helfer Thomas
 * \date   10 Apr 10
 * \brief  
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */


#include<chrono>
#include<iostream>
#include<stdexcept>

#include"TFEL/Tests/TestSuite.hxx"

namespace tfel
{

  namespace tests
  {
    
    TestSuite::TestSuite()
      : tests(),
	sname()
    {} // end of TestSuite::TestSuite

    TestSuite::TestSuite(const std::string& n)
      : tests(),
	sname(n)
    {} // end of TestSuite::TestSuite

    TestSuite::TestSuite(const char * const n)
      : tests(),
	sname(n)
    {} // end of TestSuite::TestSuite

    std::string
    TestSuite::name(void) const
    {
      return this->sname;
    } // end of TestSuite::name

    void
    TestSuite::add(const TestSuite::TestPtr& t)
    {
      this->tests.push_back(t);
    } // end of TestSuite::execute

    TestResult
    TestSuite::execute(void)
    {
      using namespace std;
      using namespace std::chrono;
      vector<TestPtr>::iterator p;
      TestResult r;
      for(p=this->tests.begin();p!=tests.end();++p){
	TestResult r1;
	const auto start = high_resolution_clock::now();
	try{
	  r1 = (*p)->execute();
	} catch(exception& e){
	  string msg("test '"+(*p)->name());
	  msg += "' has thrown an exception (";
	  msg += e.what();
	  msg += ")";
	  cerr << msg << endl;
	  r1 = TestResult(false,msg);
	} catch(...){
	  string msg("test '"+(*p)->name());
	  msg += "' has thrown an unknown exception";
	  cerr << msg << endl;
	  r1 = TestResult(false,msg);
	}
	const auto stop = high_resolution_clock::now();
	const auto nsec = duration_cast<nanoseconds>(stop-start).count();
	r1.setTestDuration(1.e-9*nsec);
	r.append(r1);
      }	
      return r;
    } // end of TestSuite::execute

    TestResult
    TestSuite::execute(TestOutput& o)
    {
      using namespace std;
      using namespace std::chrono;
      vector<TestPtr>::iterator p;
      o.beginTestSuite(this->name());
      TestResult r;
      bool success =true;
      for(p=this->tests.begin();p!=tests.end();++p){
	TestResult r1;
	const auto start = high_resolution_clock::now();
	try{
	  r1 = (*p)->execute();
	  if(!r1.success()){
	    success = false;
	  }
	} catch(exception& e){
	  string msg("test '"+(*p)->name());
	  msg += "' has thrown an exception (";
	  msg += e.what();
	  msg += ")";
	  cerr << msg << endl;
	  r1 = TestResult(false,msg);
	  success = false;
	} catch(...){
	  string msg("test '"+(*p)->name());
	  msg += "' has thrown an unknown exception";
	  cerr << msg << endl;
	  r1 = TestResult(false,msg);
	  success = false;
	}
	const auto stop = high_resolution_clock::now();
	const auto nsec = duration_cast<nanoseconds>(stop-start).count();
	r1.setTestDuration(1.e-9*nsec);
	o.addTest((*p)->classname(),(*p)->name(),r1);
	r.append(r1);
      }
      o.endTestSuite(TestResult(success));
      return r;
    } // end of TestSuite::execute

    TestSuite::~TestSuite()
    {} // end of TestSuite::~TestSuite()

  } // end of namespace tests

} // end of namespace tfel
