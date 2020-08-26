// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "word_search/grid_vector.h"

TEST_CASE( "word_search__grid_vector__equals", "[word_search__grid_vector]" ){
    WordSearch__GridVector first = {
        .magnitude = 42,
        .direction = WordSearch__Direction__East,
    };

    WordSearch__GridVector second = {
        .magnitude = 43,
        .direction = WordSearch__Direction__East,
     };

    REQUIRE( word_search__grid_vector__equals( &first, &first ) == 1 );
    REQUIRE( word_search__grid_vector__equals( &first, &second ) == 0 );
}