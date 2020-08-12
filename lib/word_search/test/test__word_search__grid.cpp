// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

#include "kirke/auto_slice.h"
#include "kirke/slice.h"
#include "kirke/system_allocator.h"

// Internal Includes
#include "word_search/grid.h"

TEST_CASE( "word_search__grid__init_and_clear", "[word_search__grid]" ){
    const unsigned long GRID_WIDTH = 5;
    const unsigned long GRID_HEIGHT = 10;

    SystemAllocator system_allocator;
    system_allocator__init( &system_allocator, NULL );

    WordSearch__Grid grid;
    word_search__grid__init( &grid, system_allocator.allocator, GRID_WIDTH, GRID_HEIGHT );

    REQUIRE( grid.width == GRID_WIDTH ); 
    REQUIRE( grid.height == GRID_HEIGHT );

    REQUIRE( grid.entries.data != NULL ); 
    REQUIRE( grid.entries.length == 0 );
    REQUIRE( grid.entries.element_size == sizeof( char ) ); 
    REQUIRE( grid.entries.capacity == GRID_WIDTH * GRID_HEIGHT );  

    word_search__grid__clear( &grid, system_allocator.allocator );

    REQUIRE( grid.width == 0 ); 
    REQUIRE( grid.height == 0 );

    REQUIRE( grid.entries.data == NULL ); 
    REQUIRE( grid.entries.length == 0 );
    REQUIRE( grid.entries.element_size == 0 ); 
    REQUIRE( grid.entries.capacity == 0 );  

    system_allocator__deinit( &system_allocator );
}


class WordSearch__Grid__TestFixture {
    protected:

        WordSearch__Grid__TestFixture(){
            
            system_allocator__init( &system_allocator, NULL );

            word_search__grid__init( &grid, system_allocator.allocator, GRID_DIM, GRID_DIM );
            memcpy( slice__data( &grid.entries, char ), GRID.data(), GRID.size() );
 
            auto_slice__init( &words, system_allocator.allocator, sizeof( Slice ), WORDS.size() );

            for( size_t word_index = 0; word_index < WORDS.size(); word_index++ ){
                Slice word;
                slice__init( &word, system_allocator.allocator, sizeof( char ), WORDS[ word_index ].length() );
                memcpy( slice__data( &word, char ), WORDS[ word_index ].c_str(), WORDS[ word_index ].length() );
                word.length = WORDS[ word_index ].length();                
               
                auto_slice__append_element( &words, word );
            }
        }

        ~WordSearch__Grid__TestFixture(){
            word_search__grid__clear( &grid, system_allocator.allocator );

            for( unsigned long word_index = 0; word_index < words.slice.length; word_index++ ){
                slice__clear( 
                    &slice__index( &words.slice, Slice, word_index ),
                    system_allocator.allocator
                );
            }

            auto_slice__clear( &words );

            system_allocator__deinit( &system_allocator );
        }

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

        const std::vector<std::string> WORDS = {
            "BONES",
            "KHAN",
            "KIRK",
            "SCOTTY",
            "SPOCK",
            "SULU",
            "UHURA"
        };

        WordSearch__Grid grid;

        SystemAllocator system_allocator;
        AutoSlice words;
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
    REQUIRE( word_search__grid__entry( &grid, &current_coordinates ) == '\0' );
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
        REQUIRE( entry == GRID[ entry_index * GRID_DIM + entry_index ] );
    }

    // Test whether index >= sequence.span.magnitude returns 0.
    REQUIRE_FALSE( word_search__grid__lookup_sequence_entry( &grid, &sequence, GRID_DIM + 1, &entry ) );
    
    // Test whether off-grid entries return 0.
    sequence.start = (WordSearch__GridCoordinates) { -1, -1 };
    REQUIRE_FALSE( word_search__grid__lookup_sequence_entry( &grid, &sequence, 0, &entry ) );

    // Just for fun, make sure that even if part of the sequence is off the grid, if the entry we want is on the grid, 
    // we still get the desired value.
    REQUIRE( word_search__grid__lookup_sequence_entry( &grid, &sequence, 1, &entry ) );
    REQUIRE( entry == GRID[ 0 ] );
}


TEST_CASE_METHOD( WordSearch__Grid__TestFixture, "word_search__grid__sequence_matches_word", "[word_search__grid]" ){
    WordSearch__GridSequence sequences[] = {
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
        }
    };

    for( unsigned long word_index = 0; word_index < words.slice.length; word_index++ ){
        REQUIRE( 
            word_search__grid__sequence_matches_word( 
                &grid,
                &sequences[ word_index ],
                &slice__index( &words.slice, Slice, word_index )
            ) == 1
        );
    }
}