/**
 *  \file word_search/direction.h
 */
#ifndef WORD_SEARCH__DIRECTION__H
#define WORD_SEARCH__DIRECTION__H

// Internal Includes
#include "kirke/macros.h"

BEGIN_DECLARATIONS

/**
 *  \defgroup word_search__direction WordSearch__Direction
 *  @{
 */

/** 
 *  \brief An enumeration type describing all of the directions in which a word can be
 *  oriented on the word search grid. 
 */
typedef enum WordSearch__Direction {
    /** Signifies an invalid grid direction. */
    WordSearch__Direction__Invalid = -1,
    /** A direction on the grid moving from left to right. */
    WordSearch__Direction__East,
    /** A direction on the grid moving from top-left to bottom-right. */
    WordSearch__Direction__SouthEast,
    /** A direction on the grid moving from top to bottom. */
    WordSearch__Direction__South,
    /** A direction on the grid moving from top-right to bottom-left. */
    WordSearch__Direction__SouthWest,
    /** A direction on the grid moving from right to left. */
    WordSearch__Direction__West,
    /** A direction on the grid moving from bottom-right to top-left. */
    WordSearch__Direction__NorthWest,
    /** A direction on the grid moving from bottom to top. */
    WordSearch__Direction__North,
    /** A direction on the grid moving from bottom-left to top-right. */
    WordSearch__Direction__NorthEast,
    /** 
     * The total number of defined directions. 
     * \note This is not a valid direction.
     */
    WordSearch__Direction__COUNT
} WordSearch__Direction;

/**
 *  \brief This method returns the WordSearch__Direction opposite to the specified direction.
 *  \param direction The direction for which the opposite direction is desired.
 *  \returns the WordSearch__Direction opposite to \p direction.
 */
WordSearch__Direction word_search__direction__opposite( WordSearch__Direction direction );

/*
 *  @} group word_search__direction
 *  @} // group word_search
 */

END_DECLARATIONS

#endif // WORD_SEARCH__DIRECTION__H
