// System Includes
#include <stdio.h>
#include <stdlib.h>

// 3rdParty Includes
#include "kirke/auto_slice.h"
// #include "kirke/io.h"
#include "kirke/system_allocator.h"

// Internal Includes
#include "kata_word_search/kata_word_search.h"
#include "kata_word_search/solution.h"

const unsigned long GRID_DIM = 15;

const char GRID[] = {
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

void print_solutions( Slice* solutions ){
    for( unsigned long solution_index = 0; solution_index < solutions->length; solution_index++ ){
        KataWordSearch__Solution current_solution = slice__index( solutions, KataWordSearch__Solution, solution_index );
        printf( "%s: ", slice__data( &current_solution.word, char ) );

        if( current_solution.disposition == WordSearch__Solution__Disposition__Found ){
            for( unsigned long entry_index = 0; entry_index < current_solution.word.length; entry_index++ ){
                WordSearch__GridCoordinates entry_coordinates;
                word_search__grid_sequence__coordinates_of( &current_solution.sequence, entry_index, &entry_coordinates );

                printf( "( %ld, %ld )", entry_coordinates.column, entry_coordinates.row );
                if( entry_index < current_solution.word.length - 1 ){
                    printf( ", " );
                }
            }
            printf( "\n" );
        }
        else{
            printf( "NOT FOUND\n" );
        }
    }
}

void out_of_memory( void ){
    printf( "Out of memory. Exiting" );
    exit( EXIT_FAILURE );
}

void print_usage(){
    printf( "kata_word_search\n" );
    printf( "Solves a word search puzzle by searching for each word in the word list in the grid.\n" );
    printf( "Words can be oriented vertically, horizontally and diagonally, in both forward and reverse.\n" );
    printf( "Usage:\n" ); 
    printf( "\tkata_word_search <input_file>" );
    printf( "OR" );
    printf( "<input_contents> | kata_word_search" );
}

int main( int argc, char* argv[] ){
/*
    Slice puzzle_input;
    if( argc > 1 ){
        if( io__read_file( argv[ 1 ], system_allocator.allocator, &puzzle_input ) == 0 ){
            print_usage();
        }
    }
    else{
        io__read_stdin( system_allocator.allocator, &puzzle_input );
    }
*/

    SystemAllocator system_allocator;
    system_allocator__init( &system_allocator, out_of_memory );

    AutoSlice words;
    auto_slice__init( &words, system_allocator.allocator, sizeof( Slice ), 0 );

    auto_slice__append_element( &words, slice__string_literal( "SCOTTY" ) );
    auto_slice__append_element( &words, slice__string_literal( "SPOCK" ) );
    auto_slice__append_element( &words, slice__string_literal( "BONES" ) );
    auto_slice__append_element( &words, slice__string_literal( "UHURA" ) );
    auto_slice__append_element( &words, slice__string_literal( "KIRK" ) );
    auto_slice__append_element( &words, slice__string_literal( "SULU" ) );
    auto_slice__append_element( &words, slice__string_literal( "KHAN" ) );
    auto_slice__append_element( &words, slice__string_literal( "RIKER" ) );
    auto_slice__append_element( &words, slice__string_literal( "WORF" ) );
    auto_slice__append_element( &words, slice__string_literal( "ABCDEFG" ) );

    WordSearch__Grid grid;
    word_search__grid__init( &grid, system_allocator.allocator, GRID_DIM, GRID_DIM );
    for( unsigned long entry_index = 0; entry_index < sizeof( GRID ); entry_index++ ){
        slice__index( &grid.entries, char, entry_index ) = GRID[ entry_index ];
    }

    Slice solutions;
    slice__init( &solutions, system_allocator.allocator, sizeof( KataWordSearch__Solution ), words.slice.length );

    if( kata_word_search__search( &words.slice, &grid, &solutions ) ){
        print_solutions( &solutions );
    }
    else{
        printf( "Search failed." );
    }

    word_search__grid__clear( &grid, system_allocator.allocator );
    auto_slice__clear( &words );
    system_allocator__deinit( &system_allocator );
}