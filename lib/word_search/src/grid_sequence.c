// Internal Includes
#include "word_search/grid.h"
#include "word_search/grid_sequence.h"

bool word_search__grid_sequence__equals( 
    WordSearch__GridSequence const *first,
    WordSearch__GridSequence const *second
){
    if( 
        word_search__grid_coordinates__equals( &first->start, &second->start ) &&
        word_search__grid_vector__equals( &first->span, &second->span ) 
    ){
        return true;
    }

    return false;
}

bool word_search__grid_sequence__coordinates_of( WordSearch__GridSequence const *sequence, unsigned long index, WordSearch__GridCoordinates* out_coordinates ){
    if( index >= sequence->span.magnitude ){
        return false;
    }

    switch( sequence->span.direction ){
        case WordSearch__Direction__East:
            out_coordinates->row = sequence->start.row;
            out_coordinates->column = sequence->start.column + index;
            break;
        case WordSearch__Direction__SouthEast:
            out_coordinates->row = sequence->start.row + index;
            out_coordinates->column = sequence->start.column + index;
            break;
        case WordSearch__Direction__South:
            out_coordinates->row = sequence->start.row + index;
            out_coordinates->column = sequence->start.column;
            break;
        case WordSearch__Direction__SouthWest:
            out_coordinates->row = sequence->start.row + index;
            out_coordinates->column = sequence->start.column - index;
            break;
        case WordSearch__Direction__West:
            out_coordinates->row = sequence->start.row;
            out_coordinates->column = sequence->start.column - index;
            break;
        case WordSearch__Direction__NorthWest:
            out_coordinates->row = sequence->start.row - index;
            out_coordinates->column = sequence->start.column - index;
            break;
        case WordSearch__Direction__North:
            out_coordinates->row = sequence->start.row - index;
            out_coordinates->column = sequence->start.column;
            break;
        case WordSearch__Direction__NorthEast:
            out_coordinates->row = sequence->start.row - index;
            out_coordinates->column = sequence->start.column + index;
            break;
        default:
            return false;
    }

    return true;
}