// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

#include "kirke/string.h"
#include "kirke/system_allocator.h"

// Internal Includes
#include "word_search/grid.h"

class WordSearch__Grid__TestFixture {
    protected:

        WordSearch__Grid__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );

            word_search__grid__initialize( 
                &grid,
                system_allocator.allocator,
                GRID_DIM,
                GRID_DIM,
                string__clone( &ENTRIES, system_allocator.allocator ) 
            );
        }

        ~WordSearch__Grid__TestFixture(){
            word_search__grid__clear( &grid, system_allocator.allocator );
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;

        const long GRID_DIM = 15;

        String ENTRIES = {
            .data = (char[ 225 ]) {
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
                'S', 'J', 'F', 'Z', 'M', 'Q', 'I', 'B', 'D', 'B', 'R', 'M', 'K', 'W', 'D',
                'T', 'G', 'L', 'B', 'H', 'C', 'B', 'E', 'C', 'E', 'T', 'O', 'Y', 'I', 'F',
                'O', 'J', 'Y', 'E', 'U', 'L', 'N', 'C', 'K', 'L', 'Y', 'B', 'Z', 'R', 'H',
                'W', 'Z', 'M', 'I', 'S', 'U', 'K', 'I', 'R', 'B', 'I', 'D', 'O', 'X', 'S',
                'K', 'Y', 'L', 'B', 'Q', 'Q', 'R', 'M', 'D', 'F', 'C', 'W', 'E', 'A', 'B'
            },
            .length = 225,
            .capacity = 225,
            .element_size = 1
        };

        Array__String words = {
            .data = (String*) (const String[]) {
                string__literal( "SCOTTY" ),
                string__literal( "SPOCK" ),
                string__literal( "BONES" ),
                string__literal( "UHURA" ),
                string__literal( "KIRK" ),
                string__literal( "SULU" ),
                string__literal( "KHAN" ),
                string__literal( "WORF" )
            },
            .length = 8,
            .capacity = 8,
            .element_size = sizeof( String )
        };

        WordSearch__Grid grid;
};

TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__contains", "[word_search__grid]" ){
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

TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__entry", "[word_search__grid]" ){
    WordSearch__GridCoordinates current_coordinates;

    current_coordinates = { .row = 0, .column = 0 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'U' );

    current_coordinates = { .row = 0, .column = 1 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'M' );

    current_coordinates = { .row = 1, .column = 0 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'L' );

    current_coordinates = { .row = 1, .column = 1 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'L' );

    current_coordinates = { .row = 14, .column = 14 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 'B' );

    current_coordinates = { .row = 15, .column = 15 };
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == 0 );
}

TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__lookup_sequence_entry", "[word_search__grid]" ){
    WordSearch__GridSequence sequence = {
        .start = {
            .row = 0,
            .column = 0
        },
        .span = {
            .magnitude = 15,
            .direction = WordSearch__Direction__SouthEast
        }
    };

    char entry;
    for( unsigned long entry_index = 0; entry_index < GRID_DIM; entry_index++ ){
        REQUIRE( word_search__grid__lookup_sequence_entry( &grid, &sequence, entry_index, &entry ) );
        REQUIRE( entry == ENTRIES.data[ entry_index * GRID_DIM + entry_index ] );
    }

    // Test whether index >= sequence.span.magnitude returns 0.
    REQUIRE_FALSE( word_search__grid__lookup_sequence_entry( &grid, &sequence, GRID_DIM + 1, &entry ) );
    
    // Test whether off-grid entries return 0.
    sequence.start = (WordSearch__GridCoordinates) { -1, -1 };
    REQUIRE_FALSE( word_search__grid__lookup_sequence_entry( &grid, &sequence, 0, &entry ) );

    // Just for fun, make sure that even if part of the sequence is off the grid, if the entry we want is on the grid, 
    // we still get the desired value.
    REQUIRE( word_search__grid__lookup_sequence_entry( &grid, &sequence, 1, &entry ) );
    REQUIRE( entry == ENTRIES.data[ 0 ] );
}

TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__sequence_matches_word", "[word_search__grid]" ){
    WordSearch__GridSequence sequences[] = {
        // SCOTTY
        {
            .start = {
                .row = 5,
                .column = 0
            },
            .span = {
                .magnitude = 6,
                .direction = WordSearch__Direction__East
            }
        },
        // SPOCK
        {
            .start = {
                .row = 1,
                .column = 2
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__SouthEast
            }
        },
        // BONES
        {
            .start = {
                .row = 6,
                .column = 0
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__South
            }
        },
        // UHURA
        {
            .start = {
                .row = 0,
                .column = 4
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__SouthWest
            }
        },
        // KIRK
        {
            .start = {
                .row = 7,
                .column = 4
            },
            .span = {
                .magnitude = 4,
                .direction = WordSearch__Direction__West
            }
        },
        // SULU
        {
            .start = {
                .row = 3,
                .column = 3
            },
            .span = {
                .magnitude = 4,
                .direction = WordSearch__Direction__NorthWest
            }
        },
        // KHAN
        {
            .start = {
                .row = 9,
                .column = 5
            },
            .span = {
                .magnitude = 4,
                .direction = WordSearch__Direction__North
            }
        },
        // WORF
        {
            .start = {
                .row = 14,
                .column = 11
            },
            .span = {
                .magnitude = 4,
                .direction = WordSearch__Direction__NorthEast
            }
        },
        // RIKER
        {
            .start = {
                .row = 14,
                .column = 6
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__NorthEast
            } 
        }
    };

    for( unsigned long word_index = 0; word_index < words.length; word_index++ ){
        REQUIRE( 
            word_search__grid__sequence_matches_word( 
                &grid,
                &sequences[ word_index ],
                &words.data[ word_index ]
            ) == 1
        );
    }
}