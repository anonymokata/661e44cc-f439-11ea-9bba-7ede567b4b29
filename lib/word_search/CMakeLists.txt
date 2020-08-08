set( word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    word_search
    ${word_search__DIR}/src/grid.c
    ${word_search__DIR}/src/grid_coordinates.c
    ${word_search__DIR}/src/grid_sequence.c
    ${word_search__DIR}/src/grid_vector.c
)

target_include_directories(
    word_search
    PUBLIC
    ${word_search__DIR}/include
)

target_link_libraries(
    word_search
    PUBLIC
    kirke
)

if( BUILD_TESTS )

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
        NAME test__word_search__grid
        SOURCES "${word_search__DIR}/test/test__word_search__grid.cpp"
        LINK_LIBRARIES word_search
    )

    catch2__add_test(
        NAME test__word_search__grid_coordinates
        SOURCES "${word_search__DIR}/test/test__word_search__grid_coordinates.cpp"
        LINK_LIBRARIES word_search
    )

    catch2__add_test(
        NAME test__word_search__grid_sequence
        SOURCES "${word_search__DIR}/test/test__word_search__grid_sequence.cpp"
        LINK_LIBRARIES word_search
    )
    
    catch2__add_test(
        NAME test__word_search__grid_vector
        SOURCES "${word_search__DIR}/test/test__word_search__grid_vector.cpp"
        LINK_LIBRARIES word_search
    )

endif( BUILD_TESTS )