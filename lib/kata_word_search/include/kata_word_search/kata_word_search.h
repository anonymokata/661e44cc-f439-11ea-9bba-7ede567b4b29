#ifndef KATA_WORD_SEARCH__H
#define KATA_WORD_SEARCH__H


// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/slice.h"

// Internal Includes
#include "word_search/direction.h"
#include "word_search/grid.h"

#include "kata_word_search/solution.h"
BEGIN_DECLARATIONS

// Forward Declarations
typedef struct Allocator Allocator;

/**
 *  \file kata_word_search/kata_word_search.h
 *  \defgroup kata_word_search Kata Word Search
 *  @{
 */

/**
 *  \brief This method searches the grid in the given direction for the given word.
 *  \param grid A pointer to the WordSearch__Grid in which to search.
 *  \param word A pointer a Slice containing the word to search for. Type Slice<char>
 *  \param direction The direction in which to search
 *  \param out_sequence An out parameter. If the desired word is located, this will store
 *  the sequence whose entries match the letters of \p word.  
 *  \returns 1 if the word was found, and 0 otherwise.
 */
char kata_word_search__find_word( 
    WordSearch__Grid* grid, 
    Slice* word, 
    WordSearch__Direction direction, 
    WordSearch__GridSequence* out_sequence 
);

/**
 *  @} // group kata_word_search
 */

END_DECLARATIONS

#endif // KATA_WORD_SEARCH__H