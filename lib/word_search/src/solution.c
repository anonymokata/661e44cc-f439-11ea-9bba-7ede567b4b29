// 3rdParty Includes
#include "kirke/allocator.h"

// Internal Includes
#include "word_search/solution.h"

ARRAY__DEFINE( Array__WordSearch__Solution, array__word_search__solution, WordSearch__Solution, word_search__solution__equals )

bool word_search__solution__equals( WordSearch__Solution const *first, WordSearch__Solution const *second ){
    // The two solutions are equal iff fields word and disposition are equal
    if( 
        string__equals( &first->word, &second->word ) == 0 || 
        first->disposition != second->disposition 
    ){
        return false;
    }

    // If the word was found, then the sequence fields must also be equal.
    if( first->disposition == WordSearch__Solution__Disposition__Found ){
        return word_search__grid_sequence__equals( &first->sequence, &second->sequence );
    }
    
    // The word was not found in either case, so the solutions are equal.
    return true;
}