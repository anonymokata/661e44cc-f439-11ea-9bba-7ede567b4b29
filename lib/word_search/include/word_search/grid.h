#ifndef WORD_SEARCH__GRID__H
#define WORD_SEARCH__GRID__H

// System Includes
#include <stdbool.h>

// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/string.h"

// Internal Includes
#include "word_search/grid_coordinates.h"
#include "word_search/grid_sequence.h"

BEGIN_DECLARATIONS

/**
 *  \file word_search/word_search__grid.h
 *  \addtogroup word_search Word Search
 *  @{
 *  \defgroup word_search__grid WordSearch__Grid
 *  @{
 */

// Forward Declarations
typedef struct Allocator Allocator;

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
    long width;
    /** The height of the grid, in entries */
    long height;
    /** 
     *  A pointer to a String containing the grid's entries. The length of this field should always be 
     *  width * height. The grid is laid out in row-major format, that is entries are 0-indexed 
     *  from the top-left corner of the grid, and can be accessed by (row, column) coordinate pair, as in
     *      char entry = grid->entries.data[ ( row * width ) + column ], OR
     *  by calling the convenience method word_search__grid__entry.
     */
    String entries;
} WordSearch__Grid;

/**
 *  \brief This method determines whether the given WordSearch__GridCoordinates reside within the grid.
 *  \param grid The grid upon which the supplied WordSearch__GridCoordinates will be tested.
 *  \param coordinates The WordSearch__GridCoordinates which will be tested.
 *  \returns true if \p coordinates does reside within the grid. That is, coordinates->row < grid->height and 
 *  coordinates->column < grid->width.  Returns false otherwise.
 */
bool word_search__grid__contains( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates );

/**
 *  \brief Convenience method to retrieve the value of the WordSearch__Grid at the specified (row, column)
 *  coordinate pair.
 *  \param grid A pointer to WordSearch__Grid from which the entry should be retrieved.
 *  \param coordinates The WordSearch__GridLocation at which the entry to be retrieved resides.
 *  \returns The character value stored at the specified WordSearch__GridCoordinates in the specified
 *  WordSearch__Grid.  If the grid coordinates are not on the grid, then returns the NULL character, '\0'.
 */
char word_search__grid__entry( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates );

/**
 *  \brief Given a sequence and an index into that sequence, this method looks up the value of the value of 
 *  the corresponding grid entry.
 *  \param grid A pointer to the WordSearch__Grid containing the desired entry.
 *  \param sequence A pointer to the WordSearch__GridSequence describing desired entry sequence.  
 *  \param index The index into the sequence of the desired entry.
 *  \param out_entry An out parameter. Upon successful completion, this will be assigned to the value of the
 *  desired entry.
 *  \returns true if the lookup was successful, and false otherwise. The lookup can fail if either the index is
 *  greater than or equal to sequence->span.magnitude, or if the corresponding entry is not contained by the
 *  grid.
 */
bool word_search__grid__lookup_sequence_entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const* sequence,
    unsigned long index,
    char* out_entry
);

/**
 *  \brief This method determines whether the supplied sequence of grid entries represents the supplied word.
 *  \param grid A pointer to the WordSearch__Grid containing the entries described by \p sequence.
 *  \param sequence A pointer to the WordSearch__GridSequence describing the entries of interest on the grid.
 *  \param word A pointer a String containing the word which will be matched to the grid sequence.
 *  \returns true if the entries described by \p sequence exactly match the supplied word, and false if they do not match.
 */
bool word_search__grid__sequence_matches_word( 
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const *sequence,
    String const *word
);

/*
 *  @} // group word_search__grid
 *  @} // group word_search
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID__H