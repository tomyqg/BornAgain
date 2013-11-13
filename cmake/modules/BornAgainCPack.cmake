# BornAgain packaging

include(InstallRequiredSystemLibraries)

set(BORNAGAIN_VERSION "${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR}.${BornAgain_VERSION_PATCH}")

set(CPACK_PACKAGE_NAME "BornAgain")
set(CPACK_PACKAGE_DESCRIPTION "BornAgain: simulate and fit scattering at grazing incidence.")
set(CPACK_PACKAGE_VENDOR "Sceintific Computing at MLZ")
set(CPACK_PACKAGE_VERSION ${BORNAGAIN_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${BornAgain_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${BornAgain_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${BornAgain_VERSION_PATCH})

configure_file(COPYING LICENSE.txt COPYONLY)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/LICENSE.txt")

# binary package setup
set(CPACK_PACKAGE_RELOCATABLE True)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}-${BORNAGAIN_ARCHITECTURE}")
else()
    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}-${BORNAGAIN_ARCHITECTURE}-${CMAKE_BUILD_TYPE}")
endif()

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}")


if(WIN32)
    include(CPackWindows)
elseif(APPLE)
    include(CPackApple)
elseif(UNIX AND BUILD_DEBIAN) # one can build debian package only on UNIX system
    include(CPackDebian)
else()
  set(CPACK_GENERATOR "STGZ;TGZ")
endif()


# Generating the source package
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

# Specify which files do not include into the source package generated by make package_source
set(CPACK_SOURCE_IGNORE_FILES
    ${CPACK_SOURCE_IGNORE_FILES} # first take the default parameters
    "/Doc/UserManual/"
    "/dev-tools/edit-scripts/"
    "/dev-tools/packaging/"
    "/dev-tools/tmp-examples/"
    "/dev-tools/tmp-unsorted/"
    "/GUI/"
    "/XCode_BornAgain.xcodeproj/"
    "~$"
    "/.git/"
    "/\\\\.git/"
    "/\\\\\\\\.git/"  # more screeneng symbols is neccesary because of double file processing by cmake and cpack
    "\\\\\\\\.swp$"
    "\\\\.swp$"
    "/.metadata/"
    "/.settings/"
    "\\\\.cproject"
    "\\\\.project"
    "/\\\\.idea/"
    "\\\\.lssrc"
    "\\\\.gitignore"
    "\\\\.DS_Store"
    "\\\\.obj"
    "CMakeLists.txt.user"
    "/bin/release.sh.in" # user will not need it
    "/cmake/modules/UseLATEX.cmake" # user will not need it
    "/dev-tools/git-utils/cl_lines_of_code.py"
    "/dev-tools/git-utils/qqq.png" # remove this line when unneeded
    ".pro$"
    ".pro.user$"
    ".pri$"
)
    
include(CPack)

set(CPACK_COMPONENTS_ALL Libraries Headers Examples)

