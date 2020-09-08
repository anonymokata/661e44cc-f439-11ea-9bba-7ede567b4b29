/**
 *  \file word_search/word_search__grid.h
 */

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

    /**
     * 
     */
    Array__WordSearch__GridCoordinates *entry_coordinates_by_value[ 26 ];
} WordSearch__Grid;

/**
 *  \brief This method initializes a WordSearch__Grid structure.
 *  \param grid A pointer to the WordSearch__Grid structure to be initialized.
 *  \param allocator A pointer to the allocator which will be used to allocate memory used by the WordSearch__Grid structure.
 *  \param width The width of the grid, in entries
 *  \param height The height of the grid, in entries
 *  \param A pointer to a String containing the grid entries. The underlying data of this string is now owned by the WordSearch__Grid
 *  structure; this will be freed upon calling word_search__grid__clear. 
 */
void word_search__grid__initialize( WordSearch__Grid *grid, Allocator* allocator, long width, long height, String *entries );

/**
 *  \brief This method clears a previously initialized WordSearch__Grid structure.
 *  \param grid A pointer to the WordSearch__Grid structure to be cleared.
 *  \param allocator A pointer to the allocator which was used to initialize the WordSearch__Grid structure; this will also be used
 *  to free memory controlled by the grid. 
 */
void word_search__grid__clear( WordSearch__Grid *grid, Allocator *allocator );

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

/**
 *  \brief This method returns an array of candidate coordinates which can be used to search the grid for the given word.
 *  These coordinates are pulled from grid->entry_coordinates_by_value, and represent the grid coordinates of all occurrences 
 *  of the least common character in the desired word.
 *  \param grid A pointer to the grid which is to be searched for \p word.
 *  \param word A pointer to a String containing the desired word.
 *  \param candidates An out parameter, the address of a pointer to an Array__WordSearch__GridCoordinates. Upon completion, 
 *  this will store a pointer to an array containing the grid coordinates of all occurrences of the least common character 
 *  in \p word.
 *  \param character_index An out parameter. Upon completion, this will store the index into \p word of the character value
 *  corresponding to the array stored in \p out_candidates. The grid entry of all coordinates contained in \p out_coordinates 
 *  have this value. 
 */
void word_search__grid__get_candidate_coordinates( 
    WordSearch__Grid const *grid, 
    String const *word, 
    Array__WordSearch__GridCoordinates **out_candidates, 
    unsigned long *out_candidate_character_index 
);

/*
 *  @} // group word_search__grid
 */

END_DECLARATIONS

#endif // WORD_SEARCH__GRID__H