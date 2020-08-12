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

KataWordSearch__Solution* kata_word_search__search( 
    Allocator* allocator, 
    Slice* words, 
    WordSearch__Grid* grid,
    WordSearch__Direction direction
);

/**
 *  @} // group kata_word_search
 */

END_DECLARATIONS

#endif // KATA_WORD_SEARCH__H