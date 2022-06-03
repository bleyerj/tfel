tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Weverything")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-c++98-compat-pedantic")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-padded")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-documentation")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-documentation-unknown-command")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-exit-time-destructors")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-global-constructors")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-missing-braces")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wrange-loop-analysis")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wmove")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Winfinite-recursion")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-return-std-move-in-c++11")
if(enable-developer-warnings)
  tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS "Wno-missing-variable-declarations")
else(enable-developer-warnings)
  tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS "Wno-missing-variable-declarations")
endif(enable-developer-warnings)
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wcomma")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wmicrosoft")
tfel_add_cxx_compiler_flag_if_available(COMPILER_WARNINGS  "Wno-inconsistent-missing-destructor-override")
tfel_add_cxx_compiler_flag_if_available2(COMPILER_WARNINGS "Wno-c++98-compat" "Wno_c__98_compat_AVAILABLE")
include(cmake/modules/common-compiler-flags.cmake)

tfel_add_cxx_compiler_flag_if_available(OPTIMISATION_FLAGS_MARCH "march=native")
if(enable-fast-math)
  tfel_add_cxx_compiler_flag_if_available(OPTIMISATION_FLAGS  "ffast-math")
else(enable-fast-math)
  tfel_add_cxx_compiler_flag_if_available(OPTIMISATION_FLAGS2 "ffast-math")
endif(enable-fast-math)

tfel_add_cxx_compiler_flag_if_available(VISIBILITY_FLAGS "fvisibility=hidden")
tfel_add_cxx_compiler_flag_if_available(VISIBILITY_FLAGS "fvisibility-inlines-hidden")

set(OPTIMISATION_FLAGS "-DTFEL_NO_RUNTIME_CHECK_BOUNDS ${OPTIMISATION_FLAGS}")

if((NOT CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(OPTIMISATION_FLAGS "-O2 -DNDEBUG ${OPTIMISATION_FLAGS}")
endif((NOT CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL "Release"))

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions("-g")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

if(HAVE_FORTRAN)
  # we associate clang with the gnu fortran compiler
  include(cmake/modules/gnu-fortran-compiler.cmake)
endif(HAVE_FORTRAN)

option(enable-libcxx "use LLVM C++ Standard library" OFF)
if(enable-libcxx)
  tfel_add_cxx_compiler_flag_if_available(COMPILER_CXXFLAGS "stdlib=libc++")
endif(enable-libcxx)

option(enable-sanitize-options "enable various clang sanitize options (undefined, address,...)" OFF)

if(enable-sanitize-options)
  tfel_add_cxx_compiler_flag_if_available(COMPILER_FLAGS "fsanitize=address")
  tfel_add_cxx_compiler_flag_if_available(COMPILER_FLAGS "fsanitize=thread")
  tfel_add_cxx_compiler_flag_if_available(COMPILER_FLAGS "fsanitize=memory")
  # tfel_add_cxx_compiler_flag_if_available(COMPILER_FLAGS "fsanitize=undefined")
  tfel_add_cxx_compiler_flag_if_available(COMPILER_FLAGS "fsanitize=cfi")
  tfel_add_cxx_compiler_flag_if_available(COMPILER_FLAGS "fsanitize=safe-stack")
endif(enable-sanitize-options)

