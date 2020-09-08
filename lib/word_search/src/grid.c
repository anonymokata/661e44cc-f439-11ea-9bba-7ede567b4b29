// System Includes
#include <limits.h>

// Internal Includes
#include "word_search/grid.h"

/* 
 * Only valid for characters A-Z, case-sensitive 
 */
static unsigned char word_search__grid__character_to_index( int value ){
    return value - 65;
}

void word_search__grid__initialize( WordSearch__Grid *grid, Allocator* allocator, long width, long height, String *entries ){
    grid->width = width;
    grid->height = height;
    grid->entries = *entries;
    memset( &grid->entry_coordinates_by_value, 0, sizeof( grid->entry_coordinates_by_value ) );

    for( long row_index = 0; row_index < height; row_index++ ){
        for( long column_index = 0; column_index < width; column_index++ ){
            unsigned char array_index = word_search__grid__character_to_index( entries->data[ row_index * width + column_index ] );

            if( grid->entry_coordinates_by_value[ array_index ] == NULL ){
                grid->entry_coordinates_by_value[ array_index ] = allocator__alloc( allocator, sizeof( Array__WordSearch__GridCoordinates ) );
                array__word_search__grid_coordinates__initialize( grid->entry_coordinates_by_value[ array_index ], allocator, 0 );
            }

            AutoArray__WordSearch__GridCoordinates lut_auto_array = {
                .array__word_search__grid_coordinates = grid->entry_coordinates_by_value[ array_index ],
                .allocator = allocator
            };

            auto_array__word_search__grid_coordinates__append_element( &lut_auto_array, (WordSearch__GridCoordinates) { .row = row_index, .column = column_index } );
        }
    }
}

void word_search__grid__clear( WordSearch__Grid *grid, Allocator *allocator ){
    grid->width = 0;
    grid->height = 0;

    if( grid->entries.data != NULL ){
        string__clear( &grid->entries, allocator );
    }

    for( unsigned long array_index = 0; array_index < ELEMENT_COUNT( grid->entry_coordinates_by_value ); array_index++ ){
        if( grid->entry_coordinates_by_value[ array_index ] != NULL ){
            array__word_search__grid_coordinates__clear( grid->entry_coordinates_by_value[ array_index ], allocator );
        }
    }
}

bool word_search__grid__contains( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates ){
    if( 
        coordinates->row >= 0 &&
        coordinates->row < grid->height &&
        coordinates->column >= 0 &&
        coordinates->column < grid->width
    ){
        return true;
    }

    return false;
}

char word_search__grid__entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridCoordinates const *coordinates
){
    if( word_search__grid__contains( grid, coordinates ) ){
        return grid->entries.data[ ( coordinates->row * grid->width ) + coordinates->column ];
    }

    return '\0';
}

bool word_search__grid__lookup_sequence_entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const* sequence,
    unsigned long index,
    char* out_entry
){
    if( index >= sequence->span.magnitude ){
        return false;
    }

    WordSearch__GridCoordinates current_coordinates = word_search__grid_coordinates__translate(
        sequence->start,
        (WordSearch__GridVector) { 
            .magnitude = index,
            .direction = sequence->span.direction
        }
    );

    if( word_search__grid__contains( grid, &current_coordinates ) == 0 ){
        return false;
    }

    *out_entry = word_search__grid__entry( grid, &current_coordinates );
    return true;
}

bool word_search__grid__sequence_matches_word(
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const *sequence,
    String const *word
){
    if( sequence->span.magnitude != word->length ){
        return false;
    }

    for( unsigned long character_index = 0; character_index < word->length; character_index++ ){
        char entry;
        if( word_search__grid__lookup_sequence_entry( grid, sequence, character_index, &entry ) == 0 ){
            return false;
        }

        char letter = word->data[ character_index ];

        if( entry != letter ){
            return false;
        }
    }

    return true;
}

void word_search__grid__get_candidate_coordinates( 
    WordSearch__Grid const *grid, 
    String const *word, 
    Array__WordSearch__GridCoordinates **candidates, 
    unsigned long *candidate_character_index 
){
    *candidates = grid->entry_coordinates_by_value[ word_search__grid__character_to_index( word->data[ 0 ] ) ];
    *candidate_character_index = 0;

    for( unsigned long character_index = 1; character_index < word->length; character_index++ ){
        Array__WordSearch__GridCoordinates *array = grid->entry_coordinates_by_value[ word_search__grid__character_to_index( word->data[ character_index ] ) ];       
        if( array->length < (*candidates)->length ){
            *candidates = array;
            *candidate_character_index = character_index;
        }
    }
}