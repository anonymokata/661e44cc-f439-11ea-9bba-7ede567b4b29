#ifndef WORD_SEARCH__GRID_VECTOR__H
#define WORD_SEARCH__GRID_VECTOR__H

// 3rdParty Includes
#include "kirke/macros.h"

// Internal Includes
#include "word_search/direction.h"

BEGIN_DECLARATIONS

/**
 *  \file word_search/grid_vector.h
 *  \addtogroup word_search Word Search
 *  @{
 *  \defgroup word_search__grid_vector WordSearch__GridVector
 *  @{
 */

/**
 *  A structure representing a vector on a word search puzzle grid.
 */
typedef struct WordSearch__GridVector{
    /** The magnitude, in entries of the vector */
    unsigned long magnitude;
    /** The direction in which the vector is oriented. */
    WordSearch__Direction direction;
} WordSearch__GridVector;

/**
 *  \brief Compares two WordSearch__GridVectors for equality
 *  This is accomplished by comparing each of the WordSearch__GridVector's constituent fields.
 *  \param first A pointer to the first WordSearch__GridVector to be compared
 *  \param second A pointer to the second WordSearch__GridVector to be compared 
 *  \returns 1 if the WordSearch__GridVectors are equal, and 0 if they are not.
 */
char word_search__grid_vector__equals(
    WordSearch__GridVector const *first,
    WordSearch__GridVector const *second
);

/**
 *  @} // group word_search__grid_vector
 *  @} // group word_search
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID_VECTOR__H