set( libkata_word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    libkata_word_search
    ${libkata_word_search__DIR}/src/solution.c
    ${libkata_word_search__DIR}/src/kata_word_search.c
)

target_include_directories(
    libkata_word_search
    PUBLIC
    ${libkata_word_search__DIR}/include
)

target_link_libraries(
    libkata_word_search
    PUBLIC
    kirke
    libword_search
)

if( BUILD_TESTS )

    target_link_libraries(
        libkata_word_search
        PRIVATE
        gcov
    )

    set_target_properties(
        libkata_word_search
        PROPERTIES
        COMPILE_FLAGS "--coverage"
    )

    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt

    catch2__add_test(
        NAME test__libkata_word_search__solution
        SOURCES "${libkata_word_search__DIR}/test/test__libkata_word_search__solution.cpp"
        LINK_LIBRARIES libkata_word_search
    )

    catch2__add_test(
        NAME test__libkata_word_search
        SOURCES "${libkata_word_search__DIR}/test/test__libkata_word_search.cpp"
        LINK_LIBRARIES libkata_word_search
    )

    catch2__add_test(
        NAME test__libkata_word_search__user_stories
        SOURCES "${libkata_word_search__DIR}/test/test__libkata_word_search__user_stories.cpp"
        LINK_LIBRARIES libkata_word_search
    )

endif( BUILD_TESTS )