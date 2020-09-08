// System Includes
#include <printf.h>     // register_printf_specifier
#include <stdio.h>      // printf
#include <stdlib.h>     // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>     // strcmp

// 3rdParty Includes
#include "kirke/error.h"
#include "kirke/io.h"
#include "kirke/string.h"
#include "kirke/system_allocator.h"

// Internal Includes
#include "word_search/word_search.h"
#include "word_search/solution.h"

#include "parser.h"
#include "printf_specializations.h"

// Ignore Warning: unknown conversion type character which is thrown because of our printf specializations
#pragma GCC diagnostic ignored "-Wformat"

// Ignore Warning: too many arguments for format which is thrown because of our printf specializations
#pragma GCC diagnostic ignored "-Wformat-extra-args"

/**
 *  These are all of the declarations which will hold dynamic memory
 */
SystemAllocator system_allocator = {0};
String* puzzle_input = NULL;
Error* error = NULL;
Array__String words = {0};
WordSearch__Grid grid = {0};
Array__WordSearch__Solution solutions = {0};

static void cleanup(){
    /*
     *  Clean up allocated memory
     */
    if( puzzle_input != NULL ){
        string__clear( puzzle_input, system_allocator.allocator );
        allocator__free( system_allocator.allocator, puzzle_input );
    }

    if( words.data != NULL ){
        array__string__clear( &words, system_allocator.allocator );
    }

    if( grid.entries.data != NULL ){
        word_search__grid__clear( &grid, system_allocator.allocator );
    }

    if( solutions.data != NULL ){
        array__word_search__solution__clear( &solutions, system_allocator.allocator );
    }

    system_allocator__deinitialize( &system_allocator );
}

static void out_of_memory( void ){
    printf( "Out of memory, exiting." );
    cleanup();
    exit( EXIT_FAILURE );
}

static void print_usage(){
    printf( 
        "word_search\n"
        "Solves a word search puzzle by searching for each word in the word list in the grid.\n"
        "Words can be oriented vertically, horizontally and diagonally, in both forward and reverse.\n"
        "Usage:\n"
        "\tword_search <input_file> OR <input_contents> | word_search\n"
    );
    cleanup();
    exit( EXIT_SUCCESS );
}

int main( int argc, char* argv[] ){
    //log__set_log_level( Log__Level__Debug );
    log__set_log_level( Log__Level__Warning );
    
    printf_specializations__register();

    system_allocator__initialize( &system_allocator, out_of_memory );

    if( argc > 1 ){
        if( strcmp( argv[ 1 ], "-h" ) == 0 || strcmp( argv[ 1 ], "--help" ) == 0 ){
            print_usage();
            exit( EXIT_SUCCESS );
        }

        log__debug( "Reading input from specified input file: %s", argv[ 1 ] );
        String input_file_path = string__literal( argv[ 1 ] ); 
        puzzle_input = io__read_text_file( system_allocator.allocator, &input_file_path, &error );

        if( error != NULL ){
            log__error( "%R,\n", error );
            exit( EXIT_FAILURE );
        }
    }
    else{
        log__debug( "Reading input from stdin." );
        puzzle_input = io__read_stdin( system_allocator.allocator );
    }

    /*
     *  Parse the received input
     */
    if( !parse_input( puzzle_input, system_allocator.allocator, &words, &grid, &error ) ){
        log__error( "%R\n", error );
        exit( EXIT_FAILURE );
    }

    log__debug( "Parsed words:\t%A", &words );
    log__debug( "Parsed grid:\n%G", &grid );

    /*
     *  Actually run the search!
     */
    array__word_search__solution__initialize( &solutions, system_allocator.allocator, words.length );

    if( word_search__search( &words, &grid, &solutions ) ){
        /*
         *  Print results of the search
         */
        for( unsigned long solution_index = 0; solution_index < solutions.length; solution_index++ ){
            printf( "%K\n", &solutions.data[ solution_index ] );
        }
    }

    cleanup();

    exit( EXIT_SUCCESS );
}