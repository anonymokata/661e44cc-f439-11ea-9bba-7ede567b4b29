// Internal Includes
#include "kata_word_search/solution.h"

char kata_word_search__solution__equals( KataWordSearch__Solution const *first, KataWordSearch__Solution const *second ){
    // The two solutions are equal iff fields word and disposition are equal
    if( 
        slice__equals( &first->word, &second->word ) == 0 || 
        first->disposition != second->disposition 
    ){
        return 0;
    }

    // If the word was found, then the sequence fields must also be equal.
    if( first->disposition == WordSearch__Solution__Disposition__Found ){
        return word_search__grid_sequence__equals( &first->sequence, &second->sequence );
    }
    
    // The word was not found in either case, so the solutions are equal.
    return 1;
}