// 3rdParty Includes
#include "kirke/log.h"

// Internal Includes
#include "word_search/direction.h"

WordSearch__Direction word_search__direction__opposite( WordSearch__Direction direction ){
    switch( direction ){
        case WordSearch__Direction__East:
            return WordSearch__Direction__West;
        case WordSearch__Direction__SouthEast:
            return WordSearch__Direction__NorthWest;
        case WordSearch__Direction__South:
            return WordSearch__Direction__North;
        case WordSearch__Direction__SouthWest:
            return WordSearch__Direction__NorthEast;
        case WordSearch__Direction__West:
            return WordSearch__Direction__East;
        case WordSearch__Direction__NorthWest:
            return WordSearch__Direction__SouthEast;
        case WordSearch__Direction__North:
            return WordSearch__Direction__South;
        case WordSearch__Direction__NorthEast:
            return WordSearch__Direction__SouthWest;
        default:
            log__error( "word_search__direction__opposite: Invalid direction received. Direction: %d", direction );
            return WordSearch__Direction__COUNT;
    }
}
