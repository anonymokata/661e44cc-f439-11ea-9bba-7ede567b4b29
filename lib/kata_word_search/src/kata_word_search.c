// Internal Includes
#include "kata_word_search/kata_word_search.h"

char kata_word_search__find_word( 
    WordSearch__Grid* grid, Slice* word, 
    WordSearch__Direction direction, 
    WordSearch__GridSequence* out_sequence 
){
    if( out_sequence == NULL ){
        return 0;
    }

    for( unsigned long row_index = 0; row_index < grid->height; row_index++ ){

        for( unsigned long column_index = 0; column_index < grid->width; column_index++ ){

            WordSearch__GridSequence current_sequence = {
                .start = {
                    .row = row_index,
                    .column = column_index
                },
                .span = {
                    .magnitude = word->length,
                    .direction = direction
                }
            };

            if( word_search__grid__sequence_matches_word( grid, &current_sequence, word ) ){
                *out_sequence = current_sequence;
                return 1;
            }
        }        
    }

    return 0;
}
