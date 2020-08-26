set( libword_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    libword_search
    ${libword_search__DIR}/src/grid.c
    ${libword_search__DIR}/src/grid_coordinates.c
    ${libword_search__DIR}/src/grid_sequence.c
    ${libword_search__DIR}/src/grid_vector.c
)

target_include_directories(
    libword_search
    PUBLIC
    ${libword_search__DIR}/include
)

target_link_libraries(
    libword_search
    PUBLIC
    kirke
)

if( BUILD_TESTS )

    target_link_libraries(
        libword_search
        PRIVATE
        gcov
    )

    set_target_properties(
        libword_search
        PROPERTIES
        COMPILE_FLAGS "--coverage"
    )

    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt

    catch2__add_test(
        NAME test__libword_search__grid
        SOURCES "${libword_search__DIR}/test/test__libword_search__grid.cpp"
        LINK_LIBRARIES libword_search
    )

    catch2__add_test(
        NAME test__libword_search__grid_coordinates
        SOURCES "${libword_search__DIR}/test/test__libword_search__grid_coordinates.cpp"
        LINK_LIBRARIES libword_search
    )

    catch2__add_test(
        NAME test__libword_search__grid_sequence
        SOURCES "${libword_search__DIR}/test/test__libword_search__grid_sequence.cpp"
        LINK_LIBRARIES libword_search
    )
    
    catch2__add_test(
        NAME test__libword_search__grid_vector
        SOURCES "${libword_search__DIR}/test/test__libword_search__grid_vector.cpp"
        LINK_LIBRARIES libword_search
    )

endif( BUILD_TESTS )