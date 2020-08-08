// Internal Includes
#include "word_search/grid_vector.h"

char word_search__grid_vector__equals(
    WordSearch__GridVector const *first,
    WordSearch__GridVector const *second
){
    if( 
        first->direction == second->direction &&
        first->magnitude == second->magnitude
    ){
        return 1;
    }

    return 0;
}
