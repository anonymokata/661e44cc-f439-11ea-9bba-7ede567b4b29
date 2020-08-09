// Internal Includes
#include "word_search/grid.h"
#include "word_search/grid_sequence.h"

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