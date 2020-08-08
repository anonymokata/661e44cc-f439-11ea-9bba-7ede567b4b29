#ifndef WORD_SEARCH__GRID__H
#define WORD_SEARCH__GRID__H

// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/auto_slice.h"

// Internal Includes
#include "word_search/grid_coordinates.h"

BEGIN_DECLARATIONS

/**
 *  \file word_search/word_search__grid.h
 *  \addtogroup word_search
 *  @{
 *  \defgroup word_search__grid WordSearch__Grid
 *  @{
 */

/** 
 *  A structure defining a word search puzzle grid.
 *  \brief This structure contains metadata describing the grid, such as its width and height, 
 *  as well as a pointer to a Slice containing all of the grid's entries.  
 * 
 *  Grid entries are arranged in flattened row-major format. That is, rows are placed end to 
 *  end in memory, packed so that we can calculate the location of each grid coordinate 
 *  (row, column) by its offset from the start of the entry data.
 */
typedef struct WordSearch__Grid {
    /** The width of the grid, in entries */
    unsigned long width;
    /** The height of the grid, in entries */
    unsigned long height;
    /** 
     *  A pointer to a Slice containing an array of characters. Slice length should always be 
     *  width * height. The grid is laid out in row-major format, that is entries are 0-indexed 
     *  from the top-left corner of the grid, and can be accessed by (row, column) coordinate pair. 
     *  Accessing individual entries by (row, column) coordinate pair can be acheived by calling 
     *      slice__index( entries, char, ( row * width  ) + column )
     *  or by calling the convenience method word_search__grid__entry.
     */
    Slice entries;
} WordSearch__Grid;

char word_search__grid__contains( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates );

/**
 *  \brief Convenience method to retrieve the value of the WordSearch__Grid at the specified (row, column)
 *  coordinate pair.
 *  \param grid A pointer to WordSearch__Grid from which the entry should be retrieved.
 *  \param coordinates The WordSearch__GridLocation at which the entry to be retrieved resides.
 *  \returns The character value stored at the specified WordSearch__GridCoordinates in the specified
 *  WordSearch__Grid
 */
char word_search__grid__entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridCoordinates const *coordinates
);

/*
 *  @} // group word_search__grid
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID__H