/**
 *  \file word_search/word_search__solution.h
 */

#ifndef WORD_SEARCH__SOLUTION__H
#define WORD_SEARCH__SOLUTION__H

// System Includes
#include <stdbool.h>

// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/string.h"

// Internal Includes
#include "word_search/grid_sequence.h"

/**
 *  \defgroup word_search__solution WordSearch__Solution
 *  @{
 */

BEGIN_DECLARATIONS

typedef struct Allocator Allocator;

/**
 *  \brief An enumerator type describing the disposition of a word after the puzzle grid has been searched.
 */
typedef enum WordSearch__Solution__Disposition{
    /** 
     *  Indicates that an exhaustive search of the grid did not find a given word. 
     */
    WordSearch__Solution__Disposition__NotFound,
    /*
     *  Indicates that a given word was successfully found.
     */
    WordSearch__Solution__Disposition__Found
} WordSearch__Solution__Disposition;

/** 
 * A structure containing fields which describe the solution for a single word found on the word search grid. 
 */
typedef struct WordSearch__Solution{
    /** 
     * A String containing the word which was searched for.
     */
    String word;
    /**
     *  Indicates whether the word was found in the word search grid.
     */
    WordSearch__Solution__Disposition disposition;
    /** 
     * If the word was found, this field represents the sequence of grid entries occupied by the found word.
     */ 
    WordSearch__GridSequence sequence;
} WordSearch__Solution;

/*
 * Array type for WordSearch__Solution
 */
ARRAY__DECLARE( Array__WordSearch__Solution, array__word_search__solution, WordSearch__Solution )

/**
 *  \brief Tests two WordSearch__Solution structures for equality
 *  \param first The first WordSearch__Solution to be compared.
 *  \param second The second WordSearch__Solution to be compared.
 *  \returns 1 if the two structures are equal, and 0 otherwise.
 */
bool word_search__solution__equals( WordSearch__Solution const *first, WordSearch__Solution const *second );

/*
 *  @} // group word_search__solution
 */

END_DECLARATIONS

#endif // WORD_SEARCH__SOLUTION__H