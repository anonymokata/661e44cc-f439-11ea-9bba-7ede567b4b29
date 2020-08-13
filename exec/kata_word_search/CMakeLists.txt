set( kata_word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_executable(
    kata_word_search_executable
    ${kata_word_search__DIR}/src/main.c
)

target_link_libraries(
    kata_word_search_executable
    PRIVATE
    kata_word_search
)