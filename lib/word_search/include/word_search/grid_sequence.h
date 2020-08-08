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
 *  \brief This method calculates and returns the coordinates corresponding to the given position of a WordSearch__GridSequence.
 *  \param sequence A pointer to the WordSearch__GridSequence
 *  \param index The index of the entry in the sequence for which the coordinates will be returned. 
 *  \param out_coordinates An out parameter, this will be filled with the coordinates of the entry at the specified index.
 *  \returns 1 if the lookup was successful, and 0 if it was not. This operation can fail if the supplied index is greater than
 *  or equal to sequence->span.magnitude. 
 */
char word_search__grid_sequence__coordinates_of( WordSearch__GridSequence* sequence, unsigned long index, WordSearch__GridCoordinates* out_coordinates );

/**
 *  @} // group word_search__grid_coordinates
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID_SEQUENCE__H