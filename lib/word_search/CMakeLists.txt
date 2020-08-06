set( word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    word_search
    ${word_search__DIR}/src/math.c
)

target_include_directories(
    word_search
    PUBLIC
    ${word_search__DIR}/include
)

if( BUILD_TESTS )

    # So local/static methods can be tested
    target_include_directories( 
        word_search
        PUBLIC
        ${word_search__DIR}/src/
    )

    target_link_libraries(
        word_search
        PRIVATE
        gcov
    )

    set_target_properties(
        word_search
        PROPERTIES
        COMPILE_FLAGS "--coverage"
    )

    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
    catch2__add_test(
        NAME test__word_search
        SOURCES "${word_search__DIR}/test/test__word_search.cpp"
        LINK_LIBRARIES word_search
    )

endif( BUILD_TESTS )