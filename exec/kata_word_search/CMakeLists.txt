set( kata_word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_executable(
    kata_word_search_executable
    ${kata_word_search__DIR}/src/kata_word_search.c
)

target_link_libraries(
    kata_word_search_executable
    PRIVATE
    kirke
    word_search
)