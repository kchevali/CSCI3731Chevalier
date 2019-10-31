cmake_minimum_required(VERSION 3.0)
project(main.exe)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
set (CMAKE_CXX_STANDARD 11)

set(SOURCE ../main.cpp
    ../main.h
    ../image.h
    ../image.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE})

FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
  INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${JPEG_LIBRARIES})
ENDIF()
