// Internal Includes
#include "word_search/grid_coordinates.h"

ARRAY__DEFINE( Array__WordSearch__GridCoordinates, array__word_search__grid_coordinates, WordSearch__GridCoordinates, word_search__grid_coordinates__equals )

WordSearch__GridCoordinates word_search__grid_coordinates__translate( WordSearch__GridCoordinates coordinates, WordSearch__GridVector vector ){
    switch( vector.direction ){
        case WordSearch__Direction__East:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row,
                .column = coordinates.column + vector.magnitude
            };
        case WordSearch__Direction__SouthEast:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row + vector.magnitude,
                .column = coordinates.column + vector.magnitude
            };
        case WordSearch__Direction__South:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row + vector.magnitude,
                .column = coordinates.column
            };
        case WordSearch__Direction__SouthWest:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row + vector.magnitude,
                .column = coordinates.column - vector.magnitude
            };
        case WordSearch__Direction__West:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row,
                .column = coordinates.column - vector.magnitude
            };
        case WordSearch__Direction__NorthWest:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row - vector.magnitude,
                .column = coordinates.column - vector.magnitude
            };
        case WordSearch__Direction__North:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row - vector.magnitude,
                .column = coordinates.column
            };
        case WordSearch__Direction__NorthEast:
            return (WordSearch__GridCoordinates) {
                .row = coordinates.row - vector.magnitude,
                .column = coordinates.column + vector.magnitude
            };
        default:
            return coordinates;
    }
}

bool word_search__grid_coordinates__equals( 
    WordSearch__GridCoordinates const *first,
    WordSearch__GridCoordinates const *second
){
    if( 
        first->row == second->row &&
        first->column == second->column 
    ){
        return true;
    }

    return false;
}
