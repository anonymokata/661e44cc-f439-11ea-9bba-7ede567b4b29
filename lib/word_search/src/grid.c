// Internal Includes
#include "word_search/grid.h"

void word_search__grid__init( WordSearch__Grid* grid, Allocator* allocator, unsigned long width, unsigned long height ){
    grid->width = width;
    grid->height = height;
    slice__init( &grid->entries, allocator, sizeof( char ), width * height );
}

void word_search__grid__clear( WordSearch__Grid* grid, Allocator* allocator ){
    grid->width = 0;
    grid->height = 0;
    slice__clear( &grid->entries, allocator );
}

char word_search__grid__contains( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates ){
    if( 
        coordinates->row >= 0 &&
        coordinates->row < grid->height &&
        coordinates->column >= 0 &&
        coordinates->column < grid->width
    ){
        return 1;
    }

    return 0;
}

char word_search__grid__entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridCoordinates const *coordinates
){
    if( word_search__grid__contains( grid, coordinates ) ){
        return slice__index( &grid->entries, char, coordinates->row * grid->width + coordinates->column );
    }

    return '\0';
}

char word_search__grid__lookup_sequence_entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const* sequence,
    unsigned long index,
    char* out_entry
){
    if( index >= sequence->span.magnitude ){
        return 0;
    }

    WordSearch__GridCoordinates current_coordinates = word_search__grid_coordinates__translate(
        sequence->start,
        (WordSearch__GridVector) { 
            .magnitude = index,
            .direction = sequence->span.direction
        }
    );

    if( word_search__grid__contains( grid, &current_coordinates ) == 0 ){
        return 0;
    }

    *out_entry = word_search__grid__entry( grid, &current_coordinates );
    return 1;
}

char word_search__grid__sequence_matches_word(
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const *sequence,
    Slice const *word
){
    return 0;
}