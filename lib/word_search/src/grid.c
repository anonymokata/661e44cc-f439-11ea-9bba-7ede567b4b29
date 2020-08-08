// Internal Includes
#include "word_search/grid.h"

char word_search__grid__contains( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates ){
    if( 
        coordinates->row >= 0 &&
        coordinates->row < grid->height &&
        coordinates->column >= 0 &&
        coordinates->column < grid->width
    ){
        return 1;
    }

    return 0;
}

char word_search__grid__entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridCoordinates const *coordinates
){
    if( word_search__grid__contains( grid, coordinates ) ){
        return slice__index( &grid->entries, char, coordinates->row * grid->width + coordinates->column );
    }

    return '\0';
}