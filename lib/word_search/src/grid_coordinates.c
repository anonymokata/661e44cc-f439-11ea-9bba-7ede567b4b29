// Internal Includes
#include "word_search/grid_coordinates.h"

char word_search__grid_coordinates__equals( 
    WordSearch__GridCoordinates const *first,
    WordSearch__GridCoordinates const *second
){
    if( 
        first->row == second->row &&
        first->column == second->column 
    ){
        return 1;
    }

    return 0;
}