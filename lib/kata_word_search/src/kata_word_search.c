// Internal Includes
#include "kata_word_search/kata_word_search.h"
#include "kata_word_search/solution.h"

KataWordSearch__Solution kata_word_search__find_word(
    WordSearch__Grid const *grid,
    Slice const *word
){
    return (KataWordSearch__Solution) {
        .word = *word,
        .disposition = WordSearch__Solution__Disposition__NotFound
    };
}

char kata_word_search__find_word_in_direction(
    WordSearch__Grid const *grid, 
    Slice const *word, 
    WordSearch__Direction direction, 
    WordSearch__GridSequence *out_sequence 
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

char kata_word_search__search_in_direction( 
    Slice const *words, 
    WordSearch__Grid const *grid,
    WordSearch__Direction direction,
    Slice* out_solutions
){
    if( out_solutions == NULL || out_solutions->capacity < words->length ){
        return 0;
    }

    out_solutions->length = 0;
    for( unsigned long word_index = 0; word_index < words->length; word_index++ ){

        Slice word = slice__index( words, Slice, word_index ); 

        WordSearch__GridSequence matching_sequence;
        if( kata_word_search__find_word_in_direction( grid, &word, direction, &matching_sequence ) ){
            slice__index( out_solutions, KataWordSearch__Solution, word_index ) = (KataWordSearch__Solution) {
                .word = word,
                .disposition = WordSearch__Solution__Disposition__Found,
                .sequence = matching_sequence
            };
        }
        else{
            slice__index( out_solutions, KataWordSearch__Solution, word_index ) = (KataWordSearch__Solution) {
                .word = word,
                .disposition = WordSearch__Solution__Disposition__NotFound,
            };
        }

        out_solutions->length += 1;
    }

    return 1;
}