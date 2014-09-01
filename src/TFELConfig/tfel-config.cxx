/*!
 * \file   src/TFELConfig/tfel-config.cxx
 * \brief  
 * \author Helfer Thomas
 * \date   27 ao� 2007
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include<map>
#include<string>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<stdexcept>

#include"tfel-config.hxx"

#if defined _WIN32 || defined _WIN64
#include<windows.h>
#endif

typedef void (*FuncPtr)(void);
typedef std::map<std::string,std::pair<FuncPtr,std::string> > CallBacksContainer;

static std::string
handleSpace(const std::string& p)
{
  using namespace std;
  if(find(p.begin(),p.end(),' ')!=p.end()){
    return '"'+p+'"';
  }
  return p;
}

std::string
libDir(void);

std::string
includeDir(void);

static void
registerCallBack(const std::string&,
		 const FuncPtr&,
		 const std::string&);

static void
treatOFlags(void);

static void
treatOFlags2(void);

#ifdef HAVE_CASTEM
static void
treatCastem(void);
#endif /* HAVE_CASTEM */

#ifdef HAVE_ZMAT
static void
treatZMAT(void);
#endif /* HAVE_ZMAT */

static void
treatExceptions(void);

static void
treatMath(void);

static void
treatMathCubicSpline(void);

static void
treatMathKriging(void);

static void
treatMathParser(void);

static void
treatMathInterpreter(void);

static void
treatUtilities(void);

static void
treatGlossary(void);

static void
treatFiniteElement(void);

static void
treatAll(void);

static void
treatCppFlags(void);

static void
treatIncludes(void);

static void
treatLibs(void);

static void
listOptions(std::ostream&);

static void
treatUnknownOption(const std::string&);

static void
treatHelp(void);

static CallBacksContainer callBacksContainer;
static bool oflags          = false;
static bool oflags2         = false;
static bool warning         = false;
static bool incs            = false;
static bool cppflags        = false;
static bool libs            = false;
static bool exceptions      = false;
static bool math            = false;
static bool mathCubicSpline = false;
static bool mathKriging     = false;
static bool mathParser      = false;
static bool mathInterpreter = false;
static bool utilities       = false;
static bool glossary        = false;
static bool finiteElement   = false;
static bool material        = false;
static bool tests           = false;
static bool mfront_profiling    = false;
#ifdef HAVE_CASTEM
static bool castem          = false;
#endif /* HAVE_CASTEM */
#ifdef HAVE_ZMAT
static bool zmat          = false;
#endif /* HAVE_ZMAT */
static bool lsystem         = false;

#if defined _WIN32 || defined _WIN64
static bool
getValueInRegistry(std::string &value,
		   const std::string& path,
		   const std::string &name)
{
  HKEY  hKey;
  char  szBuffer[512];
  DWORD dwBufferSize = sizeof(szBuffer);
  LONG  nError;
  LONG  lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE,path.c_str(),0,KEY_READ,&hKey);
  if(ERROR_SUCCESS != lRes){
    return false;
  }
  nError = RegQueryValueEx(hKey, name.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
  RegCloseKey(hKey);
  if (ERROR_SUCCESS == nError){
    value = szBuffer;
    return true;
  }
  return false;
}
#endif

std::string
libDir(void)
{
  using namespace std;
  static const string prefix(PREFIXDIR);
  static const string execPrefix(EXECPREFIXDIR);
  string lib(LIBDIR);

#if defined _WIN32 || defined _WIN64 ||defined __CYGWIN__
  string ldir("/bin");
#else 
  string ldir("/lib");
#endif

#if defined _WIN32 || defined _WIN64
  // check in the registry (installation through NSIS)
  string rpath;
  if(getValueInRegistry(rpath,string("Software\\CEA\\tfel-")+VERSION,"")){
    return rpath+ldir;
  }
#endif

  const char * const path = getenv("TFELHOME");
  if(path!=0){
    return handleSpace(string(path)+ldir);
  }
  
  if(lib.substr(0,14)=="${exec_prefix}"){
    if(execPrefix=="${prefix}"){
      lib = prefix + ldir;
    } else {
      lib = execPrefix + ldir;
    }
  }
  return handleSpace(lib);
} // end of libDir

std::string
includeDir(void)
{
  using namespace std;
  static const string prefix(PREFIXDIR);
  string inc(INCLUDEDIR);
#if defined _WIN32 || defined _WIN64
  // check in the registry (installation through NSIS)
  string rpath;
  if(getValueInRegistry(rpath,string("Software\\CEA\\tfel-")+VERSION,"")){
    inc = handleSpace(rpath+"/include");
#ifdef COMPILER_SPECIFIC_OPTIONS
    inc += ' ';
    inc += COMPILER_SPECIFIC_OPTIONS;
#endif
    return inc;
  }
#endif
  const char * const path = getenv("TFELHOME");
  if(path!=0){
    inc =  handleSpace(string(path)+"/include");
  } else {
    if(inc.substr(0,9)=="${prefix}"){
      inc = handleSpace(prefix + "/include");
    }
  }
#ifdef COMPILER_SPECIFIC_OPTIONS
  inc += ' ';
  inc += COMPILER_SPECIFIC_OPTIONS;
#endif
  return inc;
} // end of libDir

static void
registerCallBack(const std::string& key,
		 const FuncPtr& f,
		 const std::string& description)
{
  using namespace std;
  callBacksContainer.insert(make_pair(key,make_pair(f,description)));
} // end of registerNewCallBack

static void
treatOFlags(void)
{
  oflags = true;
} // end of treatOFlags

static void
treatOFlags2(void)
{
  oflags2 = true;
} // end of treatOFlags2

static void
treatWarning(void)
{
  warning = true;
} // end of treatWarning

#ifdef HAVE_CASTEM
static void
treatCastem(void)
{
  castem = true;
} // end of treatCastem
#endif /* HAVE_CASTEM */

#ifdef HAVE_ZMAT
static void
treatZMAT(void)
{
  zmat = true;
} // end of treatZMAT
#endif /* HAVE_ZMAT */

static void
treatExceptions(void)
{
  exceptions = true;
} // end of treatExceptions

static void
treatMath(void)
{
  exceptions = true;
  math       = true;
} // end of treatMath

static void
treatMathKriging(void)
{
  exceptions = true;
  math       = true;
  mathKriging = true;
} // end of treatMathKriging

static void
treatMathCubicSpline(void)
{
  exceptions = true;
  math       = true;
  mathCubicSpline = true;
} // end of treatMathCubicSpline

static void
treatMathParser(void)
{
  exceptions  = true;
  math        = true;
  mathKriging = true;
  mathParser  = true;
} // end of treatMathParser

static void
treatMathInterpreter(void)
{
  exceptions      = true;
  math            = true;
  mathKriging     = true;
  mathParser      = true;
  mathInterpreter = true;
} // end of treatMathInterpreter

static void
treatUtilities(void)
{
  utilities = true;
} // end of treatUtilities

static void
treatGlossary(void)
{
  glossary = true;
} // end of treatGlossary

static void
treatFiniteElement(void)
{
  exceptions    = true;
  math          = true;
  finiteElement = true;
} // end of treatFiniteElement

static void
treatSystem(void)
{
  exceptions    = true;
  lsystem        = true;
} // end of treatFiniteElement

static void
treatMaterial(void)
{
  exceptions  = true;
  math        = true;
  material    = true;
} // end of treatMaterial

static void
treatMFrontProfiling(void)
{
  mfront_profiling  = true;
} // end of treatMFrontProfiling

static void
treatTests(void)
{
  tests  = true;
} // end of treatTests

static void
treatAll(void)
{
  exceptions   = true;
  math         = true;
  material     = true;
  utilities    = true;
  glossary     = true;
  lsystem      = true;
  tests        = true;
  mfront_profiling = true;
} // end of treatAll

static void
treatCppFlags(void)
{
  cppflags = true;
} // end of treatCppFlags

static void
treatIncludes(void)
{
  incs = true;
} // end of treatIncludes


static void
treatLibs(void)
{
  libs = true;
} // end of treatLibs

static void
listOptions(std::ostream& os)
{
  using namespace std;
  CallBacksContainer::const_iterator p;
  os << "Valid options are : " << endl;
  for(p  = callBacksContainer.begin();
      p != callBacksContainer.end(); ++p){ 
    string options(p->first);
    if(options.size()<=18){
      options.insert(options.size(),18-options.size(),' ');
    }
    os << options << " : " <<  p->second.second << endl;
  }
} // end of listOptions

static void
treatVersion(void)
{
  using namespace std;
  cout << "tfel-config " << VERSION 
       << " (svn revision : " << TFEL_SVN_REVISION 
       << ")" << endl;
  exit(EXIT_SUCCESS);
} // end of treatHelp

static void
treatHelp(void)
{
  using namespace std;
  cout << "usage : tfel-config [options]" << endl;
  listOptions(cout);
  exit(EXIT_SUCCESS);
} // end of treatHelp

static void
treatUnknownOption(const std::string& o)
{
  using namespace std;
  cerr << "unknown option " << o << endl;
  listOptions(cerr);
  exit(EXIT_FAILURE);
} // end of treatUnknownOption

int
main(const int argc,
     const char *const *const argv)
{
  using namespace std;
  CallBacksContainer::const_iterator p;
  const char * const * p2;

  registerCallBack("--oflags",&treatOFlags,"return tfel recommended optimisation flags.");
  registerCallBack("--oflags2",&treatOFlags2,"return some aggressive optimisation flags, possibly at the expense of precision.");
  registerCallBack("--warning",&treatWarning,"return tfel recommended warnings.");
  registerCallBack("--includes",&treatIncludes,"return tfel include path.");
  registerCallBack("--cppflags",&treatCppFlags,"return preprocessor flags.");
  registerCallBack("--libs",&treatLibs,"return linking flags.");
  registerCallBack("--help",&treatHelp,"print this help message.");
#ifdef HAVE_CASTEM
  registerCallBack("--castem",&treatCastem,"request flags for castem.");
#endif /* HAVE_CASTEM */
#ifdef HAVE_ZMAT
  registerCallBack("--zmat",&treatZMAT,"request flags for zmat.");
#endif /* HAVE_ZMAT */
  registerCallBack("--exceptions",&treatExceptions,"request flags for libTFELException.");
  registerCallBack("--math-kriging",&treatMathKriging,"request flags for libTFELMathKriging.");
  registerCallBack("--math-cubic-spline",&treatMathCubicSpline,"request flags for libTFELMathCubicSpline.");
  registerCallBack("--math",&treatMath,"request flags for libTFELMath.");
  registerCallBack("--math-parser",&treatMathParser,"request flags for libTFELMathParser.");
  registerCallBack("--math-interpreter",&treatMathInterpreter,
		   "request flags for libTFELMathInterpreter.");
  registerCallBack("--tests",&treatTests,"request flags for libTFELTests.");
  registerCallBack("--system",&treatSystem,"request flags for libTFELSystem.");
  registerCallBack("--utilities",&treatUtilities,
		   "request flags for libTFELUtilities.");
  registerCallBack("--glossary",&treatGlossary,
		   "request flags for libTFELGlossary.");
  registerCallBack("--material",&treatMaterial,
		   "request flags for libTFELMaterial.");
  registerCallBack("--mfront-profiling",&treatMFrontProfiling,
		   "request flags for libMFrontProfiling.");
  registerCallBack("--finiteElement",&treatFiniteElement,
		   "request flags for libTFELFiniteElement.");
  registerCallBack("--all",&treatAll,"request flags for all librairies.");
  registerCallBack("--version",&treatVersion,"print tfel version and svn revision.");
  for(p2=argv+1;p2!=argv+argc;++p2){
    p = callBacksContainer.find(*p2);
    if(p==callBacksContainer.end()){
      treatUnknownOption(*p2);
    }
    (*(p->second.first))();
  }

  if(cppflags){
#ifdef TFEL_ARCH32
    cout << "-DTFEL_ARCH32" << " ";
#endif
#ifdef TFEL_ARCH64
    cout << "-DTFEL_ARCH64" << " ";
#endif
  }

  if(incs){
    cout << "-I" << includeDir() << " ";
  }

#ifdef HAVE_CASTEM
#ifdef LOCAL_CASTEM_HEADER
  if(castem){
    if(!incs){
      cout << "-I" << includeDir() << " ";
      cout << CASTEMFLAGS1 << " ";
    }
  }
#else  /* LOCAL_CASTEM_HEADER */
  if(castem){
    if(!incs){
      cout << CASTEMFLAGS1 << " ";
    }
    const char * const castempath = getenv("CASTEM_ROOT");
    if(castempath!=0){
      cout << "-I" << castempath << "/include ";
    } else {
      cout << CASTEMFLAGS2 << " ";
    }
  }
#endif /* LOCAL_CASTEM_HEADER */
#endif /* HAVE_CASTEM */

#ifdef HAVE_ZMAT
  if(zmat){
    if(!incs){
      cout << ZMATFLAGS1 << " ";
    }
    const char * const zmatpath = getenv("ZSET_ROOT");
    if(zmatpath!=0){
      cout << "-I" << zmatpath << "/include ";
    } else {
#ifndef ZSET_ROOT
      string msg("tfel-config : no installation path to the ZSET softwares.\n"
		 "Please define the 'ZSET_ROOT' variable environnement");
      throw(runtime_error(msg));
#else
      cout << ZMATFLAGS2 << " ";
#endif
    }
  }
#endif /* HAVE_ZMAT */

  if(libs){
    cout << "-L" << libDir() << " ";
    if(mfront_profiling){
      cout << "-lMFrontProfiling ";
    }
    if(material){
      cout << "-lTFELMaterial ";
    }
    if(finiteElement){
      cout << "-lTFELFiniteElement ";
    }
    if(mathInterpreter){
      cout << "-lTFELMathInterpreter ";
    }
    if(mathParser){
      cout << "-lTFELMathParser ";
    }
    if(mathCubicSpline){
      cout << "-lTFELMathCubicSpline ";
    }
    if(mathKriging){
      cout << "-lTFELMathKriging ";
    }
    if(math){
      cout << "-lTFELMath ";
    }
    if(lsystem){
      cout << "-lTFELSystem ";
    }
    if(utilities){
      cout << "-lTFELUtilities ";
    }
    if(glossary){
      cout << "-lTFELGlossary ";
    }
    if(exceptions){
      cout << "-lTFELException ";
    }
    if(tests){
      cout << "-lTFELTests ";
    }
  }

  if(oflags){
    cout << OPTIMISATION_FLAGS << " ";
  }

  if(oflags2){
    cout << OPTIMISATION_FLAGS2 << " ";
  }

  if(warning){
    cout << COMPILER_WARNINGS << " ";
  }

#ifdef HAVE_CASTEM
  if(cppflags||incs||libs||oflags||warning||castem){
    cout << endl;
  }
#else
  if(cppflags||incs||libs||oflags||warning){
    cout << endl;
  }
#endif /* HAVE_CASTEM */

  return EXIT_SUCCESS;
}
