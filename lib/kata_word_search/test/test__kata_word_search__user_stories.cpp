// System Includes
#include <string.h>

// 3rdParty Includes
#include "catch2/catch.hpp"

#include "kirke/auto_slice.h"
#include "kirke/system_allocator.h"

// Internal Includes
#include "kata_word_search/kata_word_search.h"
#include "kata_word_search/solution.h"

class KataWordSearch__UserStories__TestFixture{

    protected:

        KataWordSearch__UserStories__TestFixture(){
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

        ~KataWordSearch__UserStories__TestFixture(){
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
            "WORF",
            "RIKER",
        };

        SystemAllocator system_allocator;
        AutoSlice words;
        WordSearch__Grid grid;
};

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search Eastward "
    "so that I can find forward-facing horizontal words.",
    "[user_stories]"
){
    GIVEN( "The word \"SCOTTY\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "SCOTTY" );
        words.length = 1;

        WHEN( "I search the grid Eastward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__East,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"SCOTTY\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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
                };

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search South-Eastward "
    "so that I can find forward-facing, diagonally-descending words.",
    "[user_stories]"
){
    GIVEN( "The word \"SPOCK\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "SPOCK" );
        words.length = 1;

        WHEN( "I search the grid South-Eastward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__SouthEast,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"SPOCK\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search Southward "
    "so that I can find vertically-descending words.",
    "[user_stories]"
){
    GIVEN( "The word \"BONES\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "BONES" );
        words.length = 1;

        WHEN( "I search the grid Southward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__South,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"BONES\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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
                };

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search South-Westward "
    "so that I can find backward-facing, vertically-ascending words.",
    "[user_stories]"
){
    GIVEN( "The word \"UHURA\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "UHURA" );
        words.length = 1;

        WHEN( "I search the grid South-Westward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__SouthWest,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"UHURA\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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
                };

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search Westward "
    "so that I can find backward-facing horizontal words.",
    "[user_stories]"
){
    GIVEN( "The word \"KIRK\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "KIRK" );
        words.length = 1;

        WHEN( "I search the grid Westward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__West,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"KIRK\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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
                };

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search North-Westward "
    "so that I can find backward-facing, diagonally descending words.",
    "[user_stories]"
){
    GIVEN( "The word \"SULU\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "SULU" );
        words.length = 1;

        WHEN( "I search the grid North-Westward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__NorthWest,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"SULU\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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
                };

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search Northward "
    "so that I can find vertically-ascending words.",
    "[user_stories]"
){
    GIVEN( "The word \"KHAN\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 1 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "KHAN" );
        words.length = 1;

        WHEN( "I search the grid Northward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 1 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__North,
                &solutions
            );

            THEN( "The search successfully returns the location of the word \"KHAN\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solution = {
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
                };

                REQUIRE( 
                    kata_word_search__solution__equals(
                        &slice__index( &solutions, KataWordSearch__Solution, 0 ),
                        &expected_solution
                    )
                );
            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}

SCENARIO_METHOD( 
    KataWordSearch__UserStories__TestFixture,  
    "As the Puzzle Solver, "
    "I want to search North-Eastward "
    "so that I can find forward-facing, diagonally-ascending words.",
    "[user_stories]"
){
    GIVEN( "The words \"RIKER\" and \"WORF\"" ){

        Slice words;
        slice__init( &words, system_allocator.allocator, sizeof( Slice ), 2 );

        slice__index( &words, Slice, 0 ) = slice__string_literal( "RIKER" );
        slice__index( &words, Slice, 1 ) = slice__string_literal( "WORF" );
        words.length = 2;

        WHEN( "I search the grid North-Eastward" ){

            Slice solutions;
            slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), 2 );

            char success = kata_word_search__search_in_direction(
                &words,
                &grid,
                WordSearch__Direction__NorthEast,
                &solutions
            );

            THEN( "The search successfully returns the location of the words \"RIKER\" and \"WORF\" on the grid." ){
                REQUIRE( success );

                KataWordSearch__Solution expected_solutions[ 2 ] = {
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
                    }
                };

                for( unsigned long solution_index = 0; solution_index < solutions.length; solution_index++ ){
                    REQUIRE( 
                        kata_word_search__solution__equals(
                            &slice__index( &solutions, KataWordSearch__Solution, solution_index ),
                            &expected_solutions[ solution_index ]
                        )
                    );
                }

            }

            slice__clear( &solutions, system_allocator.allocator );
        }

        slice__clear( &words, system_allocator.allocator );
    }
}