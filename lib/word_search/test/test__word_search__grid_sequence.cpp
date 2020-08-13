// 3rdParty Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "word_search/grid_sequence.h"

TEST_CASE( "word_search__grid_sequence__equals", "[word_search__grid_sequence]" ){
    WordSearch__GridSequence first = {
        .start = {
            .row = 11,
            .column = 4 
        },
        .span = {
            .magnitude = 42,
            .direction = WordSearch__Direction__East,
        }
    };

    WordSearch__GridSequence second = {
        .start = {
            .row = 11,
            .column = 11
        },
        .span = {
            .magnitude = 42,
            .direction = WordSearch__Direction__East,
        }
    };

    REQUIRE( word_search__grid_sequence__equals( &first, &first ) == 1 );
    REQUIRE( word_search__grid_sequence__equals( &first, &second ) == 0 );
}

TEST_CASE( "word_search__grid_sequence__coordinates_of", "[grid_sequence]" ){
    WordSearch__GridSequence sequence = {
        .start = { .row = 0, .column = 0 },
        .span = { .magnitude = 2, .direction = WordSearch__Direction__East }
    };

    WordSearch__GridCoordinates coordinates;
    WordSearch__GridCoordinates expected_coordinates;

    REQUIRE( word_search__grid_sequence__coordinates_of( &sequence, 0, &coordinates ) );
    REQUIRE( word_search__grid_coordinates__equals( &sequence.start, &coordinates ) );

    expected_coordinates = { .row = 0, .column = 1 };
    REQUIRE( word_search__grid_sequence__coordinates_of( &sequence, 1, &coordinates ) );
    REQUIRE( word_search__grid_coordinates__equals( &coordinates, &expected_coordinates ) );

    sequence.span.direction = WordSearch__Direction__SouthEast;
    expected_coordinates = (WordSearch__GridCoordinates) { .row = 1, .column = 1 };
    REQUIRE( word_search__grid_sequence__coordinates_of( &sequence, 1, &coordinates ) );
    REQUIRE( word_search__grid_coordinates__equals( &coordinates, &expected_coordinates ) );

    sequence.span.direction = WordSearch__Direction__South;
    expected_coordinates = (WordSearch__GridCoordinates) { .row = 1, .column = 0 };
    REQUIRE( word_search__grid_sequence__coordinates_of( &sequence, 1, &coordinates ) );
    REQUIRE( word_search__grid_coordinates__equals( &coordinates, &expected_coordinates ) );

    sequence.span.direction = WordSearch__Direction__SouthWest;
    expected_coordinates = (WordSearch__GridCoordinates) { .row = 1, .column = -1 };
    REQUIRE( word_search__grid_sequence__coordinates_of( &sequence, 1, &coordinates ) );

    REQUIRE_FALSE( word_search__grid_sequence__coordinates_of( &sequence, 2, &coordinates ) );
} 