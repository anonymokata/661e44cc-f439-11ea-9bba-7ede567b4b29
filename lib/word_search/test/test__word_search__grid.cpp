// 3rdParty Includes
#include "catch2/catch.hpp"
#include "kirke/slice.h"

// Internal Includes
#include "word_search/grid.h"

class WordSearch__Grid__TestFixture {
    protected:
        WordSearch__Grid__TestFixture(){
            grid = {
                .width = GRID_DIM,
                .height = GRID_DIM,
                .entries = slice__init( GRID.data(), GRID.size(), sizeof( char ) )
            };
        }

        ~WordSearch__Grid__TestFixture(){}

        const unsigned long GRID_DIM = 15;

        const std::vector<char> GRID = {
            'U', 'M', 'K', 'H', 'U', 'L', 'K', 'I', 'N', 'V', 'J', 'O', 'C', 'W', 'E',
            'L', 'L', 'S', 'H', 'K', 'Z', 'Z', 'W', 'Z', 'C', 'G', 'J', 'U', 'Y', 'G',
            'H', 'S', 'U', 'P', 'J', 'P', 'R', 'J', 'D', 'H', 'S', 'B', 'X', 'T', 'G',
            'B', 'R', 'J', 'S', 'O', 'E', 'Q', 'E', 'T', 'I', 'K', 'K', 'G', 'L', 'E',
            'A', 'Y', 'O', 'A', 'G', 'C', 'I', 'R', 'D', 'Q', 'H', 'R', 'T', 'C', 'D',
            'S', 'C', 'O', 'T', 'T', 'Y', 'K', 'Z', 'R', 'E', 'P', 'P', 'X', 'P', 'F',
            'B', 'L', 'Q', 'S', 'L', 'N', 'E', 'E', 'E', 'V', 'U', 'L', 'F', 'M', 'Z',
            'O', 'K', 'R', 'I', 'K', 'A', 'M', 'M', 'R', 'M', 'F', 'B', 'A', 'P', 'P',
            'N', 'U', 'I', 'I', 'Y', 'H', 'Q', 'M', 'E', 'M', 'Q', 'R', 'Y', 'F', 'S',
            'E', 'Y', 'Z', 'Y', 'G', 'K', 'Q', 'J', 'P', 'C', 'Q', 'W', 'Y', 'A', 'K',
            'S', 'J', 'F', 'Z', 'M', 'Q', 'I', 'B', 'D', 'B', 'E', 'M', 'K', 'W', 'D',
            'T', 'G', 'L', 'B', 'H', 'C', 'B', 'E', 'C', 'H', 'T', 'O', 'Y', 'I', 'K',
            'O', 'J', 'Y', 'E', 'U', 'L', 'N', 'C', 'C', 'L', 'Y', 'B', 'Z', 'U', 'H',
            'W', 'Z', 'M', 'I', 'S', 'U', 'K', 'U', 'R', 'B', 'I', 'D', 'U', 'X', 'S',
            'K', 'Y', 'L', 'B', 'Q', 'Q', 'P', 'M', 'D', 'F', 'C', 'K', 'E', 'A', 'B'
        };

        WordSearch__Grid grid;
};

TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__contains", "[word_search]" ){
    WordSearch__GridCoordinates current_coordinates;

    current_coordinates = { .row = 0, .column = 0 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 1 );

    current_coordinates = { .row = 0, .column = 1 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 1 );

    current_coordinates = { .row = 1, .column = 0 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 1 );

    current_coordinates = { .row = 1, .column = 1 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 1 );

    current_coordinates = { .row = -1, .column =  0 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 0 );

    current_coordinates = { .row = 0, .column =  -1 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 0 );

    current_coordinates = { .row = 15, .column = 0 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 0 );

    current_coordinates = { .row =  0, .column =  15 };
    REQUIRE( word_search__grid__contains( &grid, &current_coordinates ) == 0 );
}

TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__entry", "[word_search]" ){
    WordSearch__GridCoordinates current_coordinates;

    current_coordinates = { .row = 0, .column = 0 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'a' );

    current_coordinates = { .row = 0, .column = 1 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'b' );

    current_coordinates = { .row = 1, .column = 0 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'c' );

    current_coordinates = { .row = 1, .column = 1 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'd' );
}