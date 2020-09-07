// Internal Includes
#include "word_search/grid_vector.h"

bool word_search__grid_vector__equals(
    WordSearch__GridVector const *first,
    WordSearch__GridVector const *second
){
    if( 
        first->direction == second->direction &&
        first->magnitude == second->magnitude
    ){
        return true;
    }

    return false;
}
