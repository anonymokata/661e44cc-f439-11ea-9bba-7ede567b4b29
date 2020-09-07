cmake_minimum_required( VERSION 3.12 )

set( CMAKE_VERBOSE_MAKEFILE OFF )

option( BUILD_TESTS "Build tests with project." OFF )
option( BUILD_COVERAGE_REPORT "Build test coverage report with project and tests." OFF )
option( BUILD_DOCUMENTATION "Build project documentation." OFF )

project( kata_word_search )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_STANDARD_REQUIRED ON )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory( 3rdParty/Catch2 )
add_subdirectory( 3rdParty/kirke )

add_subdirectory( lib/word_search )
add_subdirectory( exec/kata_word_search )

if( BUILD_TESTS )
    if( BUILD_COVERAGE_REPORT )
        # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
        catch2__build_test_executable( 
            GENERATE_COVERAGE_REPORT
            COVERAGE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs/coverage 
        )
    else( BUILD_COVERAGE_REPORT )
        catch2__build_test_executable()
    endif( BUILD_COVERAGE_REPORT )

endif( BUILD_TESTS )

if( BUILD_DOCUMENTATION )

    find_package( Doxygen )
        
    if( DOXYGEN_FOUND )

        set( DOXYGEN_PROJECT_NAME "Word Search Kata" )
        set( DOXYGEN_PROJECT_BRIEF "A word search puzzle solver.  Given a text file consisting of a list of words, and a series of rows of single-character lists representing the word search grid, this program searches for the words in the grid and return a set of x,y coordinates for each word found." )
        set( DOXYGEN_STRIP_FROM_PATH "${CMAKE_CURRENT_LIST_DIR}/.." )
        set( DOXYGEN_LAYOUT_FILE "${CMAKE_CURRENT_LIST_DIR}/doc/DoxygenLayout.xml" )
        set( DOXYGEN_DISABLE_INDEX YES )
        set( DOXYGEN_GENERATE_TREEVIEW YES )

        set( DOXYGEN_TYPEDEF_HIDES_STRUCT YES )
        set( DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/docs" )
        set( DOXYGEN_HTML_OUTPUT "." )
        set( DOXYGEN_HTML_EXTRA_STYLESHEET "${CMAKE_CURRENT_LIST_DIR}/3rdParty/doxygen_dark_theme/custom_dark_theme.css" "${CMAKE_CURRENT_LIST_DIR}/3rdParty/doxygen_dark_theme/custom.css" )

        set( DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES )
        set( DOXYGEN_EXCLUDE_PATTERNS "*/test/*" )

        doxygen_add_docs(
            docs
            lib
            exec
            doc
            ALL
        )

    endif( DOXYGEN_FOUND )

endif( BUILD_DOCUMENTATION )