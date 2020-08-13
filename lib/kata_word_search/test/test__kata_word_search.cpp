// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

#include "kirke/system_allocator.h"
#include "kirke/auto_slice.h"

// Internal Includes
#include "kata_word_search/kata_word_search.h"
#include "kata_word_search/solution.h"

class KataWordSearch__TestFixture {

    protected:

        KataWordSearch__TestFixture(){
            system_allocator__init( &system_allocator, NULL );
        
            auto_slice__init( &words, system_allocator.allocator, sizeof( Slice ), WORDS.size() );

            for( size_t word_index = 0; word_index < WORDS.size(); word_index++ ){
                Slice word;
                slice__init( &word, system_allocator.allocator, sizeof( char ), WORDS[ word_index ].length() );
                memcpy( slice__data( &word, char ), WORDS[ word_index ].c_str(), WORDS[ word_index ].length() );
                word.length = WORDS[ word_index ].length();                
               
                auto_slice__append_element( &words, word );
            }
        
            word_search__grid__init( &grid, system_allocator.allocator, GRID_DIM, GRID_DIM );
            memcpy( slice__data( &grid.entries, char ), GRID.data(), GRID.size() );
 
        }

        ~KataWordSearch__TestFixture(){
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
            'S', 'J', 'F', 'Z', 'M', 'Q', 'I', 'B', 'D', 'B', 'R', 'M', 'K', 'W', 'D',
            'T', 'G', 'L', 'B', 'H', 'C', 'B', 'E', 'C', 'E', 'T', 'O', 'Y', 'I', 'F',
            'O', 'J', 'Y', 'E', 'U', 'L', 'N', 'C', 'K', 'L', 'Y', 'B', 'Z', 'R', 'H',
            'W', 'Z', 'M', 'I', 'S', 'U', 'K', 'I', 'R', 'B', 'I', 'D', 'O', 'X', 'S',
            'K', 'Y', 'L', 'B', 'Q', 'Q', 'R', 'M', 'D', 'F', 'C', 'W', 'E', 'A', 'B'
        };

        const std::vector<std::string> WORDS = {
            "SCOTTY",
            "SPOCK",
            "BONES",
            "UHURA",
            "KIRK",
            "SULU",
            "KHAN",
            "RIKER",
            "WORF",
            "ABCDEFG"
        };

        SystemAllocator system_allocator;
        AutoSlice words;
        WordSearch__Grid grid;
};

TEST_CASE_METHOD( KataWordSearch__TestFixture, "kata_word_search__find_word_in_direction", "[kata_word_search]" ){
    Slice scotty = slice__string_literal( "SCOTTY" );
    
    WordSearch__GridSequence expected_sequence = {
        .start = {
            .row = 5,
            .column = 0
        },
        .span = {
            .magnitude = 6,
            .direction = WordSearch__Direction__East
        }
    };

    WordSearch__GridSequence sequence;
    REQUIRE( 
        kata_word_search__find_word_in_direction( 
            &grid,
            &scotty,
            WordSearch__Direction__East,
            &sequence
        )
    );

    REQUIRE( word_search__grid_sequence__equals( &sequence, &expected_sequence ) );

    Slice does_not_exist = slice__string_literal( "ABCDEFG" );
    REQUIRE_FALSE(
        kata_word_search__find_word_in_direction( 
            &grid,
            &does_not_exist,
            WordSearch__Direction__East,
            &sequence
        )
    );
}

TEST_CASE_METHOD( KataWordSearch__TestFixture, "kata_word_search__search_in_direction__east", "[kata_word_search]" ){
    unsigned long word_index;

    KataWordSearch__Solution expected_solutions[] = {
        {
            .word = slice__string_literal( "SCOTTY" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 5,
                    .column = 0
                },
                .span = {
                    .magnitude = 6,
                    .direction = WordSearch__Direction__East
                }
            }
        },
        {
            .word = slice__string_literal( "SPOCK" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "BONES" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "UHURA" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "KIRK" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "SULU" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "KHAN" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "RIKER" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },      
        {
            .word = slice__string_literal( "WORF" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = slice__string_literal( "ABCDEFG" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        }
    };

    Slice solutions;
    slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), words.slice.length );

    // Test whether expected solution is found
    REQUIRE( 
        kata_word_search__search_in_direction( 
            &words.slice,
            &grid,
            WordSearch__Direction__East,
            &solutions
        )
    );

    REQUIRE( solutions.length == words.slice.length );

    for( word_index = 0; word_index < words.slice.length; word_index++ ){
        REQUIRE( 
            kata_word_search__solution__equals( 
                &slice__index( &solutions, KataWordSearch__Solution, word_index ), 
                &expected_solutions[ word_index ] 
            )
        );
    }

    // Test whether parameter out_solutions->length <= words->length returns 0

    slice__clear( &solutions, system_allocator.allocator );
    slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

    REQUIRE_FALSE( 
        kata_word_search__search_in_direction( 
            &words.slice,
            &grid,
            WordSearch__Direction__East,
            &solutions
        )
    );

    // Test whether parameter solutions == NULL returns 0
    REQUIRE_FALSE(
        kata_word_search__search_in_direction( 
            &words.slice,
            &grid,
            WordSearch__Direction__East,
            NULL
        )
    );

    slice__clear( &solutions, system_allocator.allocator );
}

TEST_CASE_METHOD( KataWordSearch__TestFixture, "kata_word_search__find_word", "[kata_word_search]" ){
    Slice word;
    KataWordSearch__Solution expected_solution;
    KataWordSearch__Solution found_solution;

    word = slice__string_literal( "SCOTTY" );
    expected_solution = {
        .word = word,
        .disposition = WordSearch__Solution__Disposition__Found,
        .sequence = {
            .start = {
                .row = 5,
                .column = 0
            },
            .span = {
                .magnitude = 6,
                .direction = WordSearch__Direction__East
            }
        }
    };

    found_solution = kata_word_search__find_word( &grid, &word );

    REQUIRE( kata_word_search__solution__equals( &found_solution, &expected_solution ) );

    word = slice__string_literal( "SPOCK" );
    expected_solution = (KataWordSearch__Solution) {
        .word = slice__string_literal( "SPOCK" ),
        .disposition = WordSearch__Solution__Disposition__Found,
        .sequence = {
            .start = {
                .row = 1,
                .column = 2
            },
            .span = {
                .magnitude = 5,
                .direction = WordSearch__Direction__SouthEast
            }
        }
    };

    found_solution = kata_word_search__find_word( &grid, &word );
    REQUIRE( kata_word_search__solution__equals( &found_solution, &expected_solution ) );

    word = slice__string_literal( "ABCDEFG" );
    expected_solution = {
        .word = slice__string_literal( "ABCDEFG" ),
        .disposition = WordSearch__Solution__Disposition__NotFound
    };

    found_solution = kata_word_search__find_word( &grid, &word );
    REQUIRE( kata_word_search__solution__equals( &found_solution, &expected_solution ) );
}


TEST_CASE_METHOD( KataWordSearch__TestFixture, "kata_word_search__search", "[kata_word_search]" ){
    KataWordSearch__Solution expected_solutions[] = {
        {
            .word = slice__string_literal( "SCOTTY" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 5,
                    .column = 0
                },
                .span = {
                    .magnitude = 6,
                    .direction = WordSearch__Direction__East
                }
            }
        },
        {
            .word = slice__string_literal( "SPOCK" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 1,
                    .column = 2
                },
                .span = {
                    .magnitude = 5,
                    .direction = WordSearch__Direction__SouthEast
                }
            }
        },
        {
            .word = slice__string_literal( "BONES" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 6,
                    .column = 0
                },
                .span = {
                    .magnitude = 5,
                    .direction = WordSearch__Direction__South
                }
            }
        },
        {
            .word = slice__string_literal( "UHURA" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 0,
                    .column = 4
                },
                .span = {
                    .magnitude = 5,
                    .direction = WordSearch__Direction__SouthWest
                }
            }
        },
        {
            .word = slice__string_literal( "KIRK" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 7,
                    .column = 4
                },
                .span = {
                    .magnitude = 4,
                    .direction = WordSearch__Direction__West
                }
            }
        },
        {
            .word = slice__string_literal( "SULU" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 3,
                    .column = 3
                },
                .span = {
                    .magnitude = 4,
                    .direction = WordSearch__Direction__NorthWest
                }
            }
        },
        {
            .word = slice__string_literal( "KHAN" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 9,
                    .column = 5
                },
                .span = {
                    .magnitude = 4,
                    .direction = WordSearch__Direction__North
                }
            }
        },
        {
            .word = slice__string_literal( "RIKER" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 14,
                    .column = 6
                },
                .span = {
                    .magnitude = 5,
                    .direction = WordSearch__Direction__NorthEast
                }
            }
        },
        {
            .word = slice__string_literal( "WORF" ),
            .disposition = WordSearch__Solution__Disposition__Found,
            .sequence = {
                .start = {
                    .row = 14,
                    .column = 11
                },
                .span = {
                    .magnitude = 4,
                    .direction = WordSearch__Direction__NorthEast
                }
            }
        },
        {
            .word = slice__string_literal( "ABCDEFG" ),
            .disposition = WordSearch__Solution__Disposition__NotFound
        }
    };

    Slice solutions;
    slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution), words.slice.length );

    REQUIRE( kata_word_search__search( &words.slice, &grid, &solutions ) );

    for( unsigned long solution_index = 0; solution_index < words.slice.length; solution_index++ ){
        REQUIRE( 
            kata_word_search__solution__equals( 
                &slice__index( &solutions, KataWordSearch__Solution, solution_index ),
                &expected_solutions[ solution_index ]
            )
        );
    }
}