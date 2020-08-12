// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kata_word_search/solution.h"

TEST_CASE( "kata_word_search__solution__equals", "[kata_word_search__solution]" ){
    KataWordSearch__Solution first = {
        .word = slice__string_literal( "Word1" ),
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

    KataWordSearch__Solution second = {
        .word = slice__string_literal( "Word2" ),
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

    REQUIRE( kata_word_search__solution__equals( &first, &first ) == 1 );
    REQUIRE( kata_word_search__solution__equals( &first, &second ) == 0 );
}