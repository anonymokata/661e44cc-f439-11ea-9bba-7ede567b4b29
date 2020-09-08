/**
 *  \file word_search/grid_coordinates.h
 */

#ifndef WORD_SEARCH__GRID_COORDINATES__H
#define WORD_SEARCH__GRID_COORDINATES__H

// System Includes
#include <stdbool.h>

// 3rdParty Includes
#include "kirke/array.h"
#include "kirke/macros.h"

// Internal Includes
#include "word_search/grid_vector.h"

BEGIN_DECLARATIONS

/**
 *  \defgroup word_search__grid_coordinates WordSearch__GridCoordinates
 *  @{
 */

/** 
 *  \brief A structure which defines a location on the word search puzzle grid.
 *  Coordinates are zero-indexed from the top-left, or NorthWest corner of the grid.  
 */ 
typedef struct WordSearch__GridCoordinates {
    /** 
     *  The zero-indexed row of the puzzle grid location described by this structure
     */
    long row;
    /** 
     * The zero-indexed column of the puzzle grid location described by this structure 
     */
    long column;
} WordSearch__GridCoordinates;

ARRAY__DECLARE( Array__WordSearch__GridCoordinates, array__word_search__grid_coordinates, WordSearch__GridCoordinates )

/**
 *  \brief Compares two WordSearch__GridCoordinates for equality
 *  This is accomplished by comparing each of the WordSearch__GridCoordinates's constituent fields.
 *  \param first A pointer to the first WordSearch__GridCoordinates to be compared
 *  \param second A pointer to the second WordSearch__GridCoordinates to be compared 
 *  \returns 1 if the WordSearch__GridCoordinates are equal, and 0 if they are not.
 */
bool word_search__grid_coordinates__equals(
    WordSearch__GridCoordinates const *first,
    WordSearch__GridCoordinates const *second
);

/**
 *  \brief Translates the specified coordinates by the specified vector, returning the translated coordinates.
 *  \param coordinates The coordinates which will be translated
 *  \param vector The WordSearch__GridVector describing the translation operation
 *  \returns The translated coordinates.
 */
WordSearch__GridCoordinates word_search__grid_coordinates__translate( 
    WordSearch__GridCoordinates coordinates,
    WordSearch__GridVector vector
);

/**
 *  @} // group word_search__grid_coordinates
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID_COORDINATES__H
