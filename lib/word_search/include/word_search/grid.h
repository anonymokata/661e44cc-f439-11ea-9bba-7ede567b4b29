#ifndef WORD_SEARCH__GRID__H
#define WORD_SEARCH__GRID__H

// 3rdParty Includes
#include "kirke/macros.h"
#include "kirke/slice.h"

// Internal Includes
#include "word_search/grid_coordinates.h"
#include "word_search/grid_sequence.h"

BEGIN_DECLARATIONS

/**
 *  \file word_search/word_search__grid.h
 *  \addtogroup word_search
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

/**
 *  \brief This method initializes a WordSearch__Grid structure. After initialization, memory is allocated for storage of
 *  entries in the grid, but no entries have been added.  To add entries to the grid, call 
 *      auto_slice__append_element( &grid->entries, <entry_value> );
 *  \param grid A pointer to the WordSearch__Grid to be initialized.
 *  \param allocator The allocator which will be used for managing memory controlled by the grid.
 *  \param width The width of the grid, in entries.
 *  \param height The height of the grid, in entries.
 */
void word_search__grid__init( WordSearch__Grid* grid, Allocator* allocator, unsigned long width, unsigned long height );

/** 
 *  \brief This method clears a previously-initialized WordSearch__Grid structure. All memory controlled by the grid will be 
 *  released, but the grid structure itself will not be freed.
 *  \param grid A pointer to the WordSearch__Grid to be cleared.
 *  \param allocator A pointer to the allocator used to manage memory controlled by the grid.
 */
void word_search__grid__clear( WordSearch__Grid* grid, Allocator* allocator );

/**
 *  \brief This method determines whether the given WordSearch__GridCoordinates reside within the grid.
 *  \param grid The grid upon which the supplied WordSearch__GridCoordinates will be tested.
 *  \param coordinates The WordSearch__GridCoordinates which will be tested.
 *  \returns 1 if \p coordinates does reside within the grid. That is, coordinates->row < grid->height and 
 *  coordinates->column < grid->width.  Returns 0 otherwise.
 */
char word_search__grid__contains( WordSearch__Grid const *grid, WordSearch__GridCoordinates const *coordinates );

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
 *  \returns 1 if the lookup was successful, and 0 otherwise. The lookup can fail if either the index is
 *  greater than or equal to sequence->span.magnitude, or if the corresponding entry is not contained by the
 *  grid.
 */
char word_search__grid__lookup_sequence_entry( 
    WordSearch__Grid const *grid,
    WordSearch__GridSequence const* sequence,
    unsigned long index,
    char* out_entry
);

/*
 *  @} // group word_search__grid
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID__H