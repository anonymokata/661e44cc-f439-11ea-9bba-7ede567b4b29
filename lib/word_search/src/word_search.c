// Internal Includes
#include "word_search/direction.h"
#include "word_search/word_search.h"
#include "word_search/solution.h"

bool word_search__find_word_in_direction__brute_force(
    WordSearch__Grid const *grid, 
    String const *word, 
    WordSearch__Direction direction, 
    WordSearch__GridSequence *out_sequence 
){
    if( out_sequence == NULL ){
        return false;
    }

    for( long row_index = 0; row_index < grid->height; row_index++ ){

        for( long column_index = 0; column_index < grid->width; column_index++ ){

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
                return true;
            }
        }        
    }

    return false;
}

WordSearch__Solution word_search__find_word__brute_force(
    WordSearch__Grid const *grid,
    String const *word
){
    WordSearch__GridSequence sequence;
    for( unsigned long direction_index = 0; direction_index < WordSearch__Direction__COUNT; direction_index++ ){
        if( word_search__find_word_in_direction__brute_force( grid, word, direction_index, &sequence ) ){
            return (WordSearch__Solution) {
                .word = *word,
                .disposition = WordSearch__Solution__Disposition__Found,
                .sequence = sequence
            };
        }
    }

    return (WordSearch__Solution) {
        .word = *word,
        .disposition = WordSearch__Solution__Disposition__NotFound
    };
}

bool word_search__search_in_direction__brute_force( 
    Array__String const *words, 
    WordSearch__Grid const *grid,
    WordSearch__Direction direction,
    Array__WordSearch__Solution* out_solutions
){
    if( out_solutions == NULL || out_solutions->capacity < words->length ){
        return false;
    }

    out_solutions->length = 0;

    for( unsigned long word_index = 0; word_index < words->length; word_index++ ){

        String word = words->data[ word_index ]; 

        WordSearch__GridSequence matching_sequence;
        WordSearch__Solution solution;
        
        if( word_search__find_word_in_direction__brute_force( grid, &word, direction, &matching_sequence ) ){
            solution = (WordSearch__Solution) {
                .word = words->data[ word_index ],
                .disposition = WordSearch__Solution__Disposition__Found,
                .sequence = matching_sequence
            };
        }
        else{
            solution = (WordSearch__Solution) {
                .word = words->data[ word_index ],
                .disposition = WordSearch__Solution__Disposition__NotFound
            };
        }

        memcpy( out_solutions->data + word_index, &solution, sizeof( WordSearch__Solution ) );
        out_solutions->length += 1;
    }

    return true;
}

bool word_search__search__brute_force(
    Array__String const *words,
    WordSearch__Grid const *grid,
    Array__WordSearch__Solution* out_solutions
){
    if( out_solutions == NULL || out_solutions->capacity < words->length ){
        return false;
    }

    out_solutions->length = 0;

    for( unsigned long word_index = 0; word_index < words->length; word_index++ ){
        out_solutions->data[ word_index ] = word_search__find_word__brute_force(
            grid,
            &words->data[ word_index ]
        );

        out_solutions->length += 1;
    }

    return true;
}

WordSearch__Solution word_search__find_word(
    WordSearch__Grid const *grid,
    String const *word
){
    unsigned long candidate_character_index;
    Array__WordSearch__GridCoordinates *candidates;

    word_search__grid__get_candidate_coordinates( grid, word, &candidates, &candidate_character_index );

    for( unsigned long candidate_index = 0; candidate_index < candidates->length; candidate_index++ ){
        for( 
            WordSearch__Direction direction = WordSearch__Direction__East;
            direction < WordSearch__Direction__COUNT; 
            direction++ 
        ){
            WordSearch__GridSequence sequence = {
                .start = word_search__grid_coordinates__translate( 
                    candidates->data[ candidate_index ],
                    (WordSearch__GridVector) {
                        .magnitude = candidate_character_index,
                        .direction = word_search__direction__opposite( direction ),
                    }
                ),
                .span = {
                    .magnitude = word->length,
                    .direction = direction
                }
            };

            if( word_search__grid__sequence_matches_word( grid, &sequence, word ) ){
                return (WordSearch__Solution) {
                    .word = *word,
                    .disposition = WordSearch__Solution__Disposition__Found,
                    .sequence = sequence
                };
            }
        }
    }

    return (WordSearch__Solution) {
        .word = *word,
        .disposition = WordSearch__Solution__Disposition__NotFound
    };
}

bool word_search__search(
    Array__String const *words,
    WordSearch__Grid const *grid,
    Array__WordSearch__Solution* out_solutions
){
    if( out_solutions == NULL || out_solutions->capacity < words->length ){
        return false;
    }

    out_solutions->length = 0;

    for( unsigned long word_index = 0; word_index < words->length; word_index++ ){
        out_solutions->data[ word_index ] = word_search__find_word(
            grid,
            &words->data[ word_index ]
        );

        out_solutions->length += 1;
    }

    return true;
}