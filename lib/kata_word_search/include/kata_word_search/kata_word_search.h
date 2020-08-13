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
 *  \param word A pointer a Slice containing the word to search for. Type is Slice<char>.
 *  \param direction The direction in which to search
 *  \param out_sequence An out parameter. If the desired word is located, this will store
 *  the sequence whose entries match the letters of \p word.  
 *  \returns 1 if the word was found, and 0 otherwise.
 */
char kata_word_search__find_word_in_direction( 
    WordSearch__Grid const *grid, 
    Slice const *word, 
    WordSearch__Direction direction, 
    WordSearch__GridSequence* out_sequence 
);

/**
 *  \brief This method searches the grid for the given word.
 *  \param grid A pointer to the WordSearch__Grid in which to search.
 *  \param word A pointer to a Slice containing the word to search for. Type is Slice<char>.
 *  \returns The solution to the search.
 */
KataWordSearch__Solution kata_word_search__find_word(
    WordSearch__Grid const *grid,
    Slice const *word
);

/**
 *  \brief Searches the given grid for the given words in the given direction.
 *  \param words A list of the words to be found in the \p grid. This is a pointer to a Slice<Slice<char>>
 *  \param grid The grid in which to search for the words contained in \p words.
 *  \param direction The direction in which to search.
 *  \param out_solutions A pointer to a pre-allocated Slice<KataWordSearch__Solution>. The capacity should be equal to 
 *  the length of \p words.
 *  \returns 1 if the search was completed successfully, 0 otherwise.  The search can fail if \p out_solutions is NULL or
 *  lacks the required capacity to hold solutions for every word.
 */
char kata_word_search__search_in_direction( 
    Slice const *words, 
    WordSearch__Grid const *grid,
    WordSearch__Direction direction,
    Slice* out_solutions
);

/**
 *  @} // group kata_word_search
 */

END_DECLARATIONS

#endif // KATA_WORD_SEARCH__H