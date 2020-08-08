// Internal Includes
#include "word_search/grid_sequence.h"

char word_search__grid_sequence__coordinates_of( WordSearch__GridSequence* sequence, unsigned long index, WordSearch__GridCoordinates* out_coordinates ){
    return 0;
}

char word_search__grid_sequence__equals( 
    WordSearch__GridSequence const *first,
    WordSearch__GridSequence const *second
){
    if( 
        word_search__grid_coordinates__equals( &first->start, &second->start ) &&
        word_search__grid_vector__equals( &first->span, &second->span ) 
    ){
        return 1;
    }

    return 0;
}