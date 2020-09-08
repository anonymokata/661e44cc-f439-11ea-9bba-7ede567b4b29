# Word Search
# Author: Justin Kirkegaard

### This document gives a brief overview of the word search project.  Detailed documentation is hosted by Github Pages [here](https://this-kirke.github.io/kata-word-search-docs/index.html).

## About

This project is a word search puzzle solver. This was completed as part of an employment application to Accenture, located in Des Moines, IA. All internal source was written by Justin Kirkegaard. 

This project relies heavily on open source software and tools. Acknowledgements to 

* Build system using [CMake](https://cmake.org "CMake")
* Unit testing using [Catch2](https://github.com/catchorg/Catch2/ "Catch2")
* Code coverage reports using [LCOV](http://ltp.sourceforge.net/coverage/lcov.php "LCOV")
* Documentation using [Doxygen](http://www.doxygen.nl "Doxygen")
* [doxygen_dark_theme]( https://github.com/MaJerle/doxygen-dark-theme "doxygen_dark_theme" ) written by MaJerle 
* Continuous Integration using [Travis.CI](https://travis-ci.org/ "Travis.CI" )

It is likely that other open source software was used in this project but not acknowledged. If your work was used but not acknowledged and you would like it to be, or if you notice another's work which was not acknowledged, please open an issue on the [project's GitHub page]( https://github.com/this-kirke/kata-word-search "project's GitHub page" ) and I will address it as soon as possible.

## Building

Building this project requires CMake version >= 3.12. Optional documentation generation requires Doxygen and dot. Code coverage requires and lcov and genhtml. Follow the following steps to build:

1. Clone the repository:   `<project_root>$git clone https://github.com/this-kirke/kata-word-search.git`
2. Update submodules:      `<project_root>$git submodule update --init --recursive`
3. Generate the build:     `<project_root>$cmake -B build`
4. Start the build:        `<project_root>$cmake --build build`
5. Run the executable:     `<project_root>$build/exec/kata_word_search/kata_word_search data/sample_input.txt`

Several build options are available, as defined in `<project_root>/CMakeLists.txt`. To enable these options, add -D<OPTION_NAME>=ON for each desired option in step 3.  For example the command `<project_root>$cmake -B build -DBUILD_TESTS=ON -DBUILD_COVERAGE_REPORT=ON -DBUILD_DOCUMENTATION=ON` will enable all options.

By default, a static library will be built for libword_search. To produce a shared library, add `-DCMAKE_BUILD_TYPE=Shared` to the generate command (step 3).

For convenience, there are tasks defined `<project_root>/.vscode`, which allow different configurations to be built as VSCode tasks. 

## Usage

This project creates the executable target kata_word_search, located in <project_root>/build/exec/kata_word_search. This application accepts a word search puzzle in the format described below. This puzzle can either be piped to the application through stdin, or can be specified by the path to a file containing the puzzle as the first positional argument.  Try `kata_word_search --help` for more information.

Additionally, this project creates the library target libword_search, located in <project_root>/build/lib/word_search.

## Testing

Testing is accomplished using the Catch2 testing framework, which is included with the project source as a submodule. To enable testing, pass the -DBUILD_TESTS=ON option to the generate command (step 3) above. This will create the executable <project_root>/build/test__all, which will run all of the project's tests. This executable has many options, to see them run `<project_root>/build/test__all --help`.

## Instructions

The instructions provided by Pillar are as follows:

Word Search Kata
================
In this exercise you will build a program to complete a [word search](https://en.wikipedia.org/wiki/Word_search) problem.

Given a text file consisting of a list of words, and a series of rows of single-character lists representing the word search grid, this program should search for the words in the grid and return a set of x,y coordinates for each word found.

The point of this kata to to provide a larger than trivial exercise that can be used to practice TDD. A significant portion of the effort will be in determining what tests should be written and, more importantly, written next.

## Input ##

The first line of the text file will consist of the list of words to be found.  The following lines will consist of a list of single characters, A-Z. All lines in the file except the first will have the same length, and the number of rows will match the number of characters in a line.  This input represents the square grid of the word search.

The grid will always be square, and all words in the list will always be present in the grid. Words may be located horizontally, vertically, diagonally, and both forwards and backwards.  Words will never "wrap" around the edges of the grid.

The following is an example of the format of the input file:

<pre>
BONES,KHAN,KIRK,SCOTTY,SPOCK,SULU,UHURA
U,M,K,H,U,L,K,I,N,V,J,O,C,W,E
L,L,S,H,K,Z,Z,W,Z,C,G,J,U,Y,G
H,S,U,P,J,P,R,J,D,H,S,B,X,T,G
B,R,J,S,O,E,Q,E,T,I,K,K,G,L,E
A,Y,O,A,G,C,I,R,D,Q,H,R,T,C,D
S,C,O,T,T,Y,K,Z,R,E,P,P,X,P,F
B,L,Q,S,L,N,E,E,E,V,U,L,F,M,Z
O,K,R,I,K,A,M,M,R,M,F,B,A,P,P
N,U,I,I,Y,H,Q,M,E,M,Q,R,Y,F,S
E,Y,Z,Y,G,K,Q,J,P,C,Q,W,Y,A,K
S,J,F,Z,M,Q,I,B,D,B,E,M,K,W,D
T,G,L,B,H,C,B,E,C,H,T,O,Y,I,K
O,J,Y,E,U,L,N,C,C,L,Y,B,Z,U,H
W,Z,M,I,S,U,K,U,R,B,I,D,U,X,S
K,Y,L,B,Q,Q,P,M,D,F,C,K,E,A,B
</pre>

## Output ##
The output of the program is the location of each word found, each on a separate line.  The location will be represented as a series of x,y coordinates, where both x and y start at zero at the top-left of the grid.  From this position both x and y will increase, i.e. they will never be negative.  

Given the example input above, the following output would be expected:

<pre>
BONES: (0,6),(0,7),(0,8),(0,9),(0,10)
KHAN: (5,9),(5,8),(5,7),(5,6)
KIRK: (4,7),(3,7),(2,7),(1,7)
SCOTTY: (0,5),(1,5),(2,5),(3,5),(4,5),(5,5)
SPOCK: (2,1),(3,2),(4,3),(5,4),(6,5)
SULU: (3,3),(2,2),(1,1),(0,0)
UHURA: (4,0),(3,1),(2,2),(1,3),(0,4)
</pre>

## User Stories ##
*As the Puzzle Solver*<br />
*I want to search horizontally*<br />
*So that I can find words on the X axis*<br />

*As the Puzzle Solver*<br />
*I want to search vertically*<br />
*So that I can find words on the Y axis*<br />

*As the Puzzle Solver*<br />
*I want to search diagonally descending*<br />
*So that I can find words the descend along the X axis*<br />

*As the Puzzle Solver*<br />
*I want to search diagonally ascending*<br />
*So that I can find words that ascend along the X axis*<br />

*As the Puzzle Solver*<br />
*I want to search backwards*<br />
*So that I can find words in reverse along all axes*<br />

## FAQ ##

*It looks hard to generate test data.  How can do do this easily?*<br />
* If you need to generate test data there are many sites which will generate puzzles for you, such as [this one](http://puzzlemaker.discoveryeducation.com/WordSearchSetupForm.asp?campaign=flyout_teachers_puzzle_wordcross).

*How large can the grid be?*<br />
* Big or small, this is really up to you as long as you remember that the grid will always be square and that your solution should meet the requirements described above. This question is really outside the scope of the kata; the point is to focus on Test-Driving and software craftsmanship.

*How long or short can the words be?*<br />
* Words will be a minimum of two letters long, and will always fit within the grid along the axis on which it can be located.
