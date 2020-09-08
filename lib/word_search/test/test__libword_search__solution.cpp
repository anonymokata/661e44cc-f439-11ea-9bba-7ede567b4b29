// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "word_search/solution.h"

TEST_CASE( "word_search__solution__equals", "[word_search__solution]" ){
    WordSearch__Solution first = {
        .word = string__literal( "Word1" ),
        .disposition = WordSearch__Solution__Disposition__Found,
        .sequence = {
            .start = {
                .row = 5,
                .column = 3
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__North
            }
        }
    };

    WordSearch__Solution second = {
        .word = string__literal( "Word2" ),
        .disposition = WordSearch__Solution__Disposition__NotFound,
        .sequence = {
            .start = {
                .row = 3,
                .column = 5
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__West
            }
        }
    };

    REQUIRE( word_search__solution__equals( &first, &first ) == 1 );
    REQUIRE( word_search__solution__equals( &first, &second ) == 0 );
}
