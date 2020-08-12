#ifndef WORD_SEARCH__GRID_SEQUENCE__H
#define WORD_SEARCH__GRID_SEQUENCE__H

// 3rdParty Includes
#include "kirke/macros.h"

// Internal Includes
#include "word_search/grid_coordinates.h"
#include "word_search/grid_vector.h"

BEGIN_DECLARATIONS

/**
 *  \file word_search/grid_sequence.h
 *  \addtogroup word_search Word Search
 *  @{
 *  \defgroup word_search__grid_sequence WordSearch__GridSequence
 *  @{
 */

/**
 *  A structure describing a sequence of entries.
 */
typedef struct WordSearch__GridSequence{
    /** 
     *  The WordSearch__GridCoordinates where this sequence of entries begins
     */
    WordSearch__GridCoordinates start;
    /** 
     *  A WordSearch__GridVector describing the span of the sequence. That is, the entries.
     *  occupied by this sequence relative to the start position.
     */
    WordSearch__GridVector span;
} WordSearch__GridSequence;

/**
 *  \brief Compares two WordSearch__GridSequences for equality
 *  This is accomplished by comparing each of the WordSearch__GridSequence's constituent fields.
 *  \param first A pointer to the first WordSearch__GridSequence to be compared
 *  \param second A pointer to the second WordSearch__GridSequence to be compared 
 *  \returns 1 if the WordSearch__GridSequence are equal, and 0 if they are not.
 */
char word_search__grid_sequence__equals( 
    WordSearch__GridSequence const *first,
    WordSearch__GridSequence const *second
);

/**
 *  @} // group word_search__grid_coordinates
 *  @} // group word_search
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID_SEQUENCE__H