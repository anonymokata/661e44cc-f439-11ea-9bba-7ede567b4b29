// Internal Includes
#include "word_search/grid.h"

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