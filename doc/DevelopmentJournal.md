\page development_journal Development Journal

---

### Thursday August 6, 2020
### 17:25

Now it's time to begin development on libword_search. This library will define the structures required to represent a word search puzzle and its solution.  I'm going to start small, defining the structures and new/free/equals for each.

Added type WordSearch__Direction. This is an enumerator, defining the cardinal and intermediate directions. These are each of the directions in which a word can be oriented on the grid.

Added type WordSearch__GridCoordinates. This is a structure containing row and column fields, zero-indexed from the top-left or NorthWest corner of the word search puzzle grid. 

* The method word_search__grid_coordinates__equals tests two WordSearch__GridCoordinates structures for equality
* The method word_search__grid_coordinates__translate translates a pair of coordinates by a vector

Added type WordSearch__GridVector. This is a structure containing magnitude and direction fields.

* The method word_search__grid_vector__equals tests two WordSearch__GridVector structures for equality.

Added type WordSearch__GridSequence. This is a structure containing a start field of type WordSearch__GridCoordinates and a span field of type WordSearch__GridVector. Together these fields identify a linear sequence of entries in the word search grid. 

* The method word_search__grid_sequence__equals tests two WordSearch__GridSequence structures for equality.

Added type WordSearch__Grid. This is a structure containing fields for width, height, and entries.  Entries is Slice containing (width * height) character values, packed and arranged in row-major order.

* The methods word_search__grid__init/clear initialize and clear a structure of type WordSearch__Grid
* The method word_search__grid__contains tests whether a pair of coordinates are contained by a grid.
* The method word_search__grid__entry retrieves an entry from the grid at the coordinates.
* The method word_search__grid__lookup_sequence_entry retrieves an entry in the grid according to its index into a sequence.
* The method word_search__grid__sequence_matches_word determines whether the entries in the grid corresponding to a sequence exactly match the letters of a word. This method is going to do most of the heavy lifting in the word search solver.

---
### Thursday August 6, 2020
### 15:13 CDT

Ok, everything seems to be consolidated. We have all the dependencies we need with Catch2 and libkirke, and we have a project structure which builds all the local targets including tests. Going to push the current state, and then begin working on libword_search.

---

### Wednesday August 5, 2020
### 12:21 CDT

Ok, I've spent some time working on libkirke, and it's in fairly decent shape to support the needs of the word search project.
We have Allocator, an abstraction for managing allocation and free; Slice, which is a generic array structure; AutoSlice, which is a wrapper around slice that provides automatic memory management and convenience methods such as append, prepend, insert, and remove; and some general-purpose macro definitions.

There are a few things that I would like to add to round out libkirke, such as error handling, logging functions, and file I/O. These will probably be necessary to complete this project, but I'm going to hold off on adding them to libkirke until I have to.

---

### Saturday, August 1, 2020
### 11:03 CDT

I've created a repository for a library project, which I've called [libkirke](https://github.com/this-kirke/kirke). This project will contain general-purpose functionality, includineg commonly-used macros, generic types such as containers and generic math functions, for example. The idea here is to keep generic code separate as I work through the project, which will allow me to reuse this code in future projects.

This project has been brought in as a dependency to the word search project as a submodule. It will have its own tests and commit history, but since I'm building it to facilitate this project I will also document its development in this journal.

---

### Friday, July 31, 2020
### 11:03 CDT

Filled in the build system targets for the project. We have libword_search, libkata_word_search, and the kata-word-search executable.

The target libword_search will contain definitions and methods for general types used when dealing with word search puzzles. The goal here is to provide the utilities needed to work with word search puzzles, but not to enforce any particular system. For example, there may be multiple approaches to solving a word search puzzle, or there may be different problems to solve regarding word searches - generation and solution, for example. Each of these will require different operations, but they should share many of the same basic types. These types will be defined in libword_search so that each specific target can simply link to libword_search, and utilize those types.

The target libkata_word_search will be a specific target, whose purpose is to solve word search puzzles. It will have a specific solution implementation. As a library target, consumers will be able to link to it in their own applications, and use its functionality to solve word search puzzles.

Finally, the target kata-word-search will be a command-line executable which accepts a string representation of a word search puzzle as input, and outputs the solution to the terminal.

---

### Monday, June 29, 2020
### 23:51 am CDT

Project skeleton created:
    * CMake build system
    * Catch2 for testing
    * gcov with lcov and genhtml for code coverage reporting
    * Doxygen for documentation generation
    * doxygen_dark_theme for pretty documentation.
    * Travis.CI build on push