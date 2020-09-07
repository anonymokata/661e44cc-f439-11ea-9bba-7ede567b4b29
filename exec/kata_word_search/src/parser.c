// System Includes
#include <stdbool.h>

// 3rdParty Includes
#include "kirke/allocator.h"
#include "kirke/error.h"
#include "kirke/split_iterator.h"
#include "kirke/string.h"

// Internal Includes
#include "word_search/grid.h"
#include "parser.h"

/*
 * Define some common delimiters for convenience
 */
String comma = string__literal( "," );
String newline = string__literal( "\n" );

static bool parse_words( String *words_input, Allocator *allocator, Array__String *out_words, Error **error ){
    (void) ( error );

    /*
     * Initialize the out_words array and create an AutoArray for easy appending
     */
    array__string__initialize( out_words, allocator, 0 );
    AutoArray__String words__auto_array = {
        .array__string = out_words,
        .allocator = allocator
    };

    /*
     * Initialize a SplitIterator to separate words in the input
     */
    SplitIterator word_iterator;
    split_iterator__initialize( &word_iterator, words_input, &comma );

    /*
     *  Append each word to words_autoslice; internally this will append to out_words.
     */
    String word;
    while( split_iterator__next( &word_iterator, &word ) ){
        auto_array__string__append_element( &words__auto_array, word );
    }

    return true;
}

static bool parse_grid( String *grid_input, Allocator *allocator, WordSearch__Grid *grid, Error **error ){

    /*****************************
     * Calculate Grid Dimensions *
     *****************************/
    SplitIterator line_iterator;
    split_iterator__initialize( &line_iterator, grid_input, &newline );

    /*
     *  The height of the grid will be the number of tokens found which are separated by a newline.
     */
    unsigned long height = split_iterator__count( &line_iterator );

    String line;
    split_iterator__next( &line_iterator, &line );

    SplitIterator entry_iterator;
    split_iterator__initialize( &entry_iterator, &line, &comma );

    /*
     *  The width of the grid will be the number of tokens found within a line, which are separated by a comma.
     */
    unsigned long width = split_iterator__count( &entry_iterator );

    if( width != height ){
        error__set( allocator, error, "Parser", 0, "Invalid grid dimensions, only square grids are accepted.  Grid dimensions are: %lu, %lu.", width, height );
        return false;
    }

    /*****************************
     *       Parse Entries       *
     *****************************/

    /*
     * Initialize the entries String and create an AutoString for easy appending
     */
    String entries;
    string__initialize( &entries, allocator, 0 );

    AutoString entries__auto_string = {
        .string = &entries,
        .allocator = allocator
    };

    /*
     *  We've already initialized the line iterator and called split_iterator__next on it once, so line has the first line of
     *  input in it - hence, the do/while.
     */
    do{
        // Initialize the entry iterator with the new contents of line
        split_iterator__initialize( &entry_iterator, &line, &comma );
        
        // Append each token in line to the entries string. 
        String entry;
        while( split_iterator__next( &entry_iterator, &entry ) ){
            auto_string__append_element( &entries__auto_string, entry.data[ 0 ] );
        }
    } while( split_iterator__next( &line_iterator, &line ) );

    *grid = (WordSearch__Grid) {
        .width = width,
        .height = height,
        .entries = entries
    };

    return true;
}

bool parse_input( String *puzzle_input, Allocator* allocator, Array__String *out_words, WordSearch__Grid *out_grid, Error** error ){
    SplitIterator input_iterator;
    split_iterator__initialize( &input_iterator, puzzle_input, &newline );

    String words_input;
    split_iterator__next( &input_iterator, &words_input );

    if( !parse_words( &words_input, allocator, out_words, error ) ){
        return false;
    }

    String grid_input;
    split_iterator__rest( &input_iterator, &grid_input );

    if( !parse_grid( &grid_input, allocator, out_grid, error ) ){
        return false;
    }

    return true;
}
