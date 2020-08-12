#ifndef KATA_WORD_SEARCH__SOLUTION__H
#define KATA_WORD_SEARCH__SOLUTION__H

// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/slice.h"

// Internal Includes
#include "word_search/grid_sequence.h"

/**
 *  \file word_search/word_search__word_solution.h
 *  \addtogroup kata_word_search
 *  @{
 *  \defgroup kata_word_search__solution KataWordSearch__Solution
 *  @{
 */

BEGIN_DECLARATIONS

typedef enum KataWordSearch__Solution__Disposition{
    WordSearch__Solution__Disposition__NotFound,
    WordSearch__Solution__Disposition__Found
} KataWordSearch__Solution__Disposition;

/** A structure containing fields which describe the solution for a single word found on the word search grid. */ 
typedef struct KataWordSearch__Solution{
    /** 
     * A pointer to a slice containing the word whose location is represented by this structure.
     */
    Slice word;
    /**
     *  Indicates whether the word was found in the word search grid.
     */
    KataWordSearch__Solution__Disposition disposition;
    /** 
     * The sequence of grid entries occupied by the found word. 
     */ 
    WordSearch__GridSequence sequence;
} KataWordSearch__Solution;

/**
 *  \brief Tests two KataWordSearch__Solution structures for equality
 *  \param first The first KataWordSearch__Solution to be compared.
 *  \param second The second KataWordSearch__Solution to be compared.
 *  \returns 1 if the two structures are equal, and 0 otherwise.
 */
char kata_word_search__solution__equals( KataWordSearch__Solution const *first, KataWordSearch__Solution const *second );

/*
 *  @} // group word_search__word_solution
 *  @} // group word_search
 */

END_DECLARATIONS

#endif // KATA_WORD_SEARCH__SOLUTION__H