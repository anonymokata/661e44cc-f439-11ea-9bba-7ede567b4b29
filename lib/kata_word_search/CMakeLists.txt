set( kata_word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    kata_word_search
    ${kata_word_search__DIR}/src/solution.c
    ${kata_word_search__DIR}/src/kata_word_search.c
)

target_include_directories(
    kata_word_search
    PUBLIC
    ${kata_word_search__DIR}/include
)

target_link_libraries(
    kata_word_search
    PUBLIC
    kirke
    word_search
)

if( BUILD_TESTS )

    target_link_libraries(
        kata_word_search
        PRIVATE
        gcov
    )

    set_target_properties(
        kata_word_search
        PROPERTIES
        COMPILE_FLAGS "--coverage"
    )

    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt

    catch2__add_test(
        NAME test__kata_word_search__solution
        SOURCES "${kata_word_search__DIR}/test/test__kata_word_search__solution.cpp"
        LINK_LIBRARIES kata_word_search
    )

    catch2__add_test(
        NAME test__kata_word_search
        SOURCES "${kata_word_search__DIR}/test/test__kata_word_search.cpp"
        LINK_LIBRARIES kata_word_search
    )

endif( BUILD_TESTS )