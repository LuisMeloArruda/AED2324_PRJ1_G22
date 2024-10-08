cmake_minimum_required(VERSION 3.24)
project(AED2324_PRJ1_G22)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED2324_PRJ1_G22 main.cpp
        Classes/Class.h
        Classes/Lesson.h
        Classes/Schedule.h
        Classes/Student.h
        Classes/Student.cpp
        Classes/Schedule.cpp
        Classes/Lesson.cpp
        Classes/Class.cpp
        Classes/Extractor.cpp
        Classes/Extractor.h
        Classes/Request.h
        Classes/Request.cpp Classes/App.h Classes/App.cpp)
