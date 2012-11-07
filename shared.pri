# common configuration for all packages

# -----------------------------------------------------------------------------
# checking common prerequisites
# -----------------------------------------------------------------------------
lessThan(QT_VERSION, 4.5) {
    error("GISASFW requires Qt 4.5 or greater")
}

!macx:!unix {
  error("Unknown operation system")
}


# -----------------------------------------------------------------------------
# to compile in debug mode
# 'export GISASFW_DEBUG=yes' to have automatic compilation in debug mode
# -----------------------------------------------------------------------------
env_debug_variable = $$(GISASFW_DEBUG)
isEqual(env_debug_variable, "yes") {
  #message("Compiling with DEBUG option")
  CONFIG += debug
}

# -----------------------------------------------------------------------------
# general external libraries
# -----------------------------------------------------------------------------

# --- checking gsl header ---
GSL_HEADERFILE = gsl/gsl_sf_bessel.h
GSL_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
for(dir, GSL_HEADER_LOCATIONS): isEmpty(GSL_INCLUDE): exists($${dir}/$${GSL_HEADERFILE}): GSL_INCLUDE = $${dir}
isEmpty(GSL_INCLUDE): message("Can't find" $${GSL_HEADERFILE} "in" $${GSL_HEADER_LOCATIONS})
GSL_LIB = $$replace(GSL_INCLUDE,"include","lib")
INCLUDEPATH *=  $${GSL_INCLUDE}
LIBS *= -L$${GSL_LIB}
LIBS += -lgsl -lgslcblas

# --- checking fftw3 ---
FFTW3_HEADERFILE = fftw3.h
FFTW3_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
for(dir, FFTW3_HEADER_LOCATIONS): isEmpty(FFTW3_INCLUDE): exists($${dir}/$${FFTW3_HEADERFILE}): FFTW3_INCLUDE = $${dir}
isEmpty(FFTW3_INCLUDE): message("Can't find" $${FFTW3_HEADERFILE} "in" $${FFTW3_HEADER_LOCATIONS)
FFTW3_LIB = $$replace(FFTW3_INCLUDE,"include","lib")
INCLUDEPATH *=  $${FFTW3_INCLUDE}
LIBS *= -L$${FFTW3_LIB}
LIBS += -lfftw3

# --- checking boost ---
BOOST_HEADERFILE = boost/version.hpp
BOOST_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
for(dir, BOOST_HEADER_LOCATIONS): isEmpty(BOOST_INCLUDE): exists($${dir}/$${BOOST_HEADERFILE}): BOOST_INCLUDE = $${dir}
isEmpty(BOOST_INCLUDE): message("Can't find" $${BOOST_HEADERFILE} "in" $${BOOST_HEADER_LOCATIONS)
BOOST_LIBFILES = libboost*
BOOST_LIB_LOCATIONS = /opt/local/lib /usr/local/lib /usr/lib64 /usr/lib
for(dir, BOOST_LIB_LOCATIONS): isEmpty(BOOST_LIB) {
  NumberOfSuchFiles=$$system(ls $${dir}/$${BOOST_LIBFILES} 2> /dev/null | wc -l)
  !isEqual(NumberOfSuchFiles, 0): BOOST_LIB = $${dir}
}
isEmpty(BOOST_LIB): message("Can't find" $${BOOST_LIBFILES} "in" $${BOOST_LIB_LOCATIONS})
INCLUDEPATH *=  $${BOOST_INCLUDE}
LIBS *= -L$${BOOST_LIB}
LIBS += -lboost_program_options -lboost_iostreams -lboost_system -lboost_filesystem -lboost_regex -lboost_thread
# checking special case when system doesn't have libboost_thread library but have libbost_thread-mt
NumberOfSuchFiles=$$system(ls $${BOOST_LIB}/libboost_thread-mt* 2> /dev/null | wc -l)
!isEqual(NumberOfSuchFiles, 0) {
  # library libboost_thread-mt exists
  LIBS = $$replace(LIBS, "-lboost_thread", "-lboost_thread-mt")
}



#message($${FFTW3_HEADERFILE}" found in "$${FFTW3_INCLUDE})
#message($${BOOST_HEADERFILE}" found in "$${BOOST_INCLUDE})
#message($${BOOST_LIBFILE}" found in "$${BOOST_LIB})
#message($${GSL_HEADERFILE}" found in "$${GSL_INCLUDE})
isEmpty(GSL_INCLUDE): error("missed dependency")
isEmpty(FFTW3_INCLUDE): error("missed dependency")
isEmpty(BOOST_INCLUDE): error("missed dependency")
isEmpty(BOOST_LIB): error("missed dependency")


#INCLUDEPATH =  $${GSL_HEADER} $${FFTW3_HEADER} $${BOOST_HEADER}
#LIBS = -L$${GSL_LIB} $${FFTW3_LIB} $${BOOST_LIB}

# adding libs we are depending on
#LIBS += -lgsl -lgslcblas -lfftw3 -lboost_program_options -lboost_iostreams -lboost_system -lboost_filesystem -lboost_regex -lboost_thread

# here is workaround since JCNS /usr/local doesn't have shared fftw3 (run with 'qmake CONFIG+=JCNS')
env_jcns_variable = $$(GISASFW_JCNS)
isEqual(env_jcns_variable, "yes") {
  #message("Compiling with DEBUG option")
  CONFIG += JCNS
}
CONFIG(JCNS) {
  LIBS = -L/usr/users/jcns/pospelov/software/lib -L/usr/local/lib -L/usr/lib64 -lgsl -lgslcblas -lfftw3 -lboost_program_options -lboost_iostreams -lboost_system -lboost_filesystem -lboost_regex -lboost_thread
}



# -----------------------------------------------------------------------------
# options testing and performance issues
# -----------------------------------------------------------------------------

# optimization flag used in release builds (the -O2 is the default used by qmake)
QMAKE_CXXFLAGS_DEBUG += -fdiagnostics-show-option # to find out in gcc which option control warning
#QMAKE_CXXFLAGS_RELEASE += -O3 -ffast-math -msse3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -g -O3 -ffast-math
# uncommenting line below produces non-stripped (very large) libraries
#QMAKE_STRIP=:

# to compile with GPERFTOOLS support for code profiling
#CONFIG+=GPERFTOOLS
CONFIG(GPERFTOOLS) {
  QMAKE_CXXFLAGS += -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
  LIBS += -L/opt/local/lib -lprofiler -ltcmalloc
}



# hints
# $${VAR} to access .pro variables, $$(VAR) to access environment variables



