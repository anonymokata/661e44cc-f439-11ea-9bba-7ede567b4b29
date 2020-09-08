set( kata_word_search__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_executable(
    kata_word_search
    ${kata_word_search__DIR}/src/parser.c
    ${kata_word_search__DIR}/src/main.c
)

target_include_directories(
    kata_word_search
    PRIVATE
    ${kata_word_search__DIR}/include
)

target_link_libraries(
    kata_word_search
    PRIVATE
    libword_search
    libkirke
)

target_compile_options( 
    kata_word_search
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Werror -Wall -Wextra -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
