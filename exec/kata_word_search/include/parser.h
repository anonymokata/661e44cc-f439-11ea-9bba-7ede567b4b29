#ifndef WORD_SEARCH__PARSER__H
#define WORD_SEARCH__PARSER__H

// System Includes
#include <stdbool.h>

// 3rdParty Includes
#include "kirke/macros.h"

BEGIN_DECLARATIONS

bool parse_input( String *puzzle_input, Allocator* allocator, Array__String *out_words, WordSearch__Grid *out_grid, Error** error );

END_DECLARATIONS

#endif // WORD_SEARCH__PARSER__H
