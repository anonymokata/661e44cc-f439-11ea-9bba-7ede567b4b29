/**
 *  \file word_search/word_search.h
 */

#ifndef WORD_SEARCH__H
#define WORD_SEARCH__H

// System Includes
#include <stdbool.h>

// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/string.h"

// Internal Includes
#include "word_search/direction.h"
#include "word_search/grid.h"

#include "word_search/solution.h"

BEGIN_DECLARATIONS

// Forward Declarations
typedef struct Allocator Allocator;
typedef struct String String;

/*
 *  \defgroup word_search Word Search
 *  @{
 */

/**
 *  \brief This method searches the grid for the given word.
 *  \param grid A pointer to the WordSearch__Grid in which to search.
 *  \param word A pointer to a String containing the word to search for.
 *  \returns The solution to the search.
 */
WordSearch__Solution word_search__find_word(
    WordSearch__Grid const *grid,
    String const *word
);

/**
 *  \brief This method searches the grid in the given direction for the given word.
 *  \param grid A pointer to the WordSearch__Grid in which to search.
 *  \param word A pointer a String containing the word to search for.
 *  \param direction The direction in which to search
 *  \param out_sequence An out parameter. If the desired word is located, this will store
 *  the sequence whose entries match the letters of \p word.  
 *  \returns true if the word was found, and false otherwise.
 */
bool word_search__find_word_in_direction( 
    WordSearch__Grid const *grid, 
    String const *word, 
    WordSearch__Direction direction, 
    WordSearch__GridSequence* out_sequence 
);

/**
 *  \brief Searches the given grid for the given words in the given direction.
 *  \param words A pointer to an Array__String containing the list of the words to be found in the \p grid.
 *  \param grid The grid in which to search for the words contained in \p words.
 *  \param direction The direction in which to search.
 *  \param out_solutions A pointer to a pre-allocated Array__WordSearch__Solution. The capacity should be equal to 
 *  the length of \p words.
 *  \returns true if the search was completed successfully, false otherwise.  The search can fail if \p out_solutions is NULL or
 *  lacks the required capacity to hold solutions for every word.
 */
bool word_search__search_in_direction( 
    Array__String const *words, 
    WordSearch__Grid const *grid,
    WordSearch__Direction direction,
    Array__WordSearch__Solution* out_solutions
);

/**
 *  \brief This method searches the grid for the given words, and returns a solution for each.
 *  \param words A pointer to an Array__String containing the list of the words to be found in the \p grid.
 *  \param grid The grid in which to search for the words contained in \p words.
 *  \param out_solutions A pointer to a pre-allocated Array__WordSearch__Solution. The capacity should be equal to
 *  the length of \p words.
 *  \returns true if the search was completed successfully, and false otherwise. The search can fail if \p out_solutions is NULL,
 *  or if it lacks the required capacity to hold solutions for every word.  
 */
bool word_search__search(
    Array__String const *words,
    WordSearch__Grid const *grid,
    Array__WordSearch__Solution* out_solutions
);

/**
 *  @} // group word_search
 */

END_DECLARATIONS

#endif // WORD_SEARCH__H