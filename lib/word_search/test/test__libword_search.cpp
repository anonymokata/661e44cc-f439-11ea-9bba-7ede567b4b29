// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

#include "kirke/system_allocator.h"

// Internal Includes
#include "word_search/word_search.h"
#include "word_search/solution.h"

class WordSearch__TestFixture {

    protected:

        WordSearch__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );

            String* entries = string__clone( &ENTRIES, system_allocator.allocator );

            word_search__grid__initialize( 
                &grid,
                system_allocator.allocator,
                GRID_DIM,
                GRID_DIM,
                entries
            );

            allocator__free( system_allocator.allocator, entries );

            array__string__initialize( &words, system_allocator.allocator, 8 );
            
            AutoArray__String words__auto_array = {
                .array__string = &words,
                .allocator = system_allocator.allocator
            };

            auto_array__string__append_elements( &words__auto_array, 9, WORDS );
        }

        ~WordSearch__TestFixture(){
            array__string__clear( &words, system_allocator.allocator );
            word_search__grid__clear( &grid, system_allocator.allocator );

            system_allocator__deinitialize( &system_allocator );
        }

        const long GRID_DIM = 15;

        String ENTRIES = {
            .data = (char[]) {
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

        String WORDS[ 10 ] = {
            string__literal( "SCOTTY" ),
            string__literal( "SPOCK" ),
            string__literal( "BONES" ),
            string__literal( "UHURA" ),
            string__literal( "KIRK" ),
            string__literal( "SULU" ),
            string__literal( "KHAN" ),
            string__literal( "RIKER" ),
            string__literal( "WORF" ),
            string__literal( "ABCDEFG" )
        };

        Array__String words;

        WordSearch__Grid grid;
        SystemAllocator system_allocator;
};

TEST_CASE_METHOD( WordSearch__TestFixture, "word_search__find_word_in_direction__brute_force", "[word_search]" ){
    String scotty = string__literal( "SCOTTY" );
    
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
        word_search__find_word_in_direction__brute_force( 
            &grid,
            &scotty,
            WordSearch__Direction__East,
            &sequence
        )
    );

    REQUIRE( word_search__grid_sequence__equals( &sequence, &expected_sequence ) );

    String does_not_exist = string__literal( "ABCDEFG" );
    REQUIRE_FALSE(
        word_search__find_word_in_direction__brute_force( 
            &grid,
            &does_not_exist,
            WordSearch__Direction__East,
            &sequence
        )
    );
}

TEST_CASE_METHOD( WordSearch__TestFixture, "word_search__search_in_direction__brute_force__east", "[word_search]" ){
    unsigned long word_index;

    WordSearch__Solution expected_solutions[] = {
        {
            .word = string__literal( "SCOTTY" ),
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
            .word = string__literal( "SPOCK" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "BONES" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "UHURA" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "KIRK" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "SULU" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "KHAN" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "RIKER" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "WORF" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        },
        {
            .word = string__literal( "ABCDEFG" ),
            .disposition = WordSearch__Solution__Disposition__NotFound,
        }
    };

    Array__WordSearch__Solution solutions;
    array__word_search__solution__initialize( &solutions, system_allocator.allocator, words.length );

    // Test whether expected solution is found
    REQUIRE( 
        word_search__search_in_direction__brute_force( 
            &words,
            &grid,
            WordSearch__Direction__East,
            &solutions
        )
    );

    REQUIRE( solutions.length == words.length );

    for( word_index = 0; word_index < words.length; word_index++ ){
        REQUIRE( 
            word_search__solution__equals( 
                &solutions.data[ word_index ], 
                &expected_solutions[ word_index ] 
            )
        );
    }

    // Test whether parameter out_solutions->length <= words->length returns 0

    array__word_search__solution__clear( &solutions, system_allocator.allocator );
    array__word_search__solution__initialize( &solutions, system_allocator.allocator, 1 );

    REQUIRE_FALSE( 
        word_search__search_in_direction__brute_force( 
            &words,
            &grid,
            WordSearch__Direction__East,
            &solutions
        )
    );

    // Test whether parameter solutions == NULL returns 0
    REQUIRE_FALSE(
        word_search__search_in_direction__brute_force( 
            &words,
            &grid,
            WordSearch__Direction__East,
            NULL
        )
    );

    array__word_search__solution__clear( &solutions, system_allocator.allocator );
}

TEST_CASE_METHOD( WordSearch__TestFixture, "word_search__find_word", "[word_search]" ){
    String word;
    WordSearch__Solution expected_solution;
    WordSearch__Solution found_solution;

    word = string__literal( "SCOTTY" );
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

    found_solution = word_search__find_word( &grid, &word );

    REQUIRE( word_search__solution__equals( &found_solution, &expected_solution ) );

    word = string__literal( "SPOCK" );
    expected_solution = (WordSearch__Solution) {
        .word = string__literal( "SPOCK" ),
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

    found_solution = word_search__find_word( &grid, &word );
    REQUIRE( word_search__solution__equals( &found_solution, &expected_solution ) );

    word = string__literal( "ABCDEFG" );
    expected_solution = {
        .word = string__literal( "ABCDEFG" ),
        .disposition = WordSearch__Solution__Disposition__NotFound
    };

    found_solution = word_search__find_word( &grid, &word );
    REQUIRE( word_search__solution__equals( &found_solution, &expected_solution ) );
}


TEST_CASE_METHOD( WordSearch__TestFixture, "word_search__search", "[word_search]" ){
    WordSearch__Solution expected_solutions[] = {
        {
            .word = string__literal( "SCOTTY" ),
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
            .word = string__literal( "SPOCK" ),
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
            .word = string__literal( "BONES" ),
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
            .word = string__literal( "UHURA" ),
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
            .word = string__literal( "KIRK" ),
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
            .word = string__literal( "SULU" ),
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
            .word = string__literal( "KHAN" ),
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
            .word = string__literal( "RIKER" ),
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
            .word = string__literal( "WORF" ),
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
            .word = string__literal( "ABCDEFG" ),
            .disposition = WordSearch__Solution__Disposition__NotFound
        }
    };

    Array__WordSearch__Solution solutions;
    array__word_search__solution__initialize( &solutions, system_allocator.allocator, words.length );

    REQUIRE( word_search__search( &words, &grid, &solutions ) );

    for( unsigned long solution_index = 0; solution_index < words.length; solution_index++ ){
        REQUIRE( 
            word_search__solution__equals( 
                &solutions.data[ solution_index ],
                &expected_solutions[ solution_index ]
            )
        );
    }

    array__word_search__solution__clear( &solutions, system_allocator.allocator );
}
