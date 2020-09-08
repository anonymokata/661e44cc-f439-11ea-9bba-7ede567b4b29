// 3rdParty Includes
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/catch.hpp"

// 3rdParty Includes
#include "kirke/string.h"
#include "kirke/system_allocator.h"

// Internal Includes
#include "word_search/word_search.h"

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

TEST_CASE_METHOD( WordSearch__TestFixture, "word_search__search__benchmark", "[word_search]" ){
    Array__WordSearch__Solution solutions;
    array__word_search__solution__initialize( &solutions, system_allocator.allocator, words.length );

    BENCHMARK( "word_search__search" ) {
        return word_search__search( &words, &grid, &solutions );
    };

    BENCHMARK( "word_search__search__bruteforce" ) {
        return word_search__search__brute_force( &words, &grid, &solutions );
    };

    array__word_search__solution__clear( &solutions, system_allocator.allocator );
}
