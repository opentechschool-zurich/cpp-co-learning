#include "tileType.h"

std::string tileTypeToString(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            return "Empty";
        case TileType::Horizontal:
            return "Horizontal";
        case TileType::Vertical:
            return "Vertical";
        case TileType::StartTop:
            return "StartTop";
        case TileType::StartBottom:
            return "StartBottom";
        case TileType::StartLeft:
            return "StartLeft";
        case TileType::StartRight:
            return "StartRight";
        case TileType::EndTop:
            return "EndTop";
        case TileType::EndBottom:
            return "EndBottom";
        case TileType::EndRight:
            return "EndRight";
        case TileType::EndLeft:
            return "EndLeft";
        case TileType::LeftTop:
            return "LeftTop";
        case TileType::LeftBottom:
            return "LeftBottom";
        case TileType::TopRight:
            return "TopRight";
        case TileType::BottomRight:
            return "BottomRight";
        default:
            return "Unknown Type";
    }
}

std::string tileTypeToChar(const TileType & t) {
    switch (t) {
        case TileType::Empty:
            return " ";
        case TileType::Horizontal:
            return "-";
        case TileType::Vertical:
            return "|";
        case TileType::StartTop:
            return "┴";
        case TileType::StartBottom:
            return "┬";
        case TileType::StartLeft:
            return "┤";
        case TileType::StartRight:
            return "├";
        case TileType::EndTop:
            return "┻";
        case TileType::EndBottom:
            return "┳";
        case TileType::EndRight:
            return "┣";
        case TileType::EndLeft:
            return "┫";
        case TileType::LeftTop:
            return "┘";
        case TileType::LeftBottom:
            return "┐";
        case TileType::TopRight:
            return "└";
        case TileType::BottomRight:
            return "┌";
        default:
            return "?";
    }
}

/**
 * @brief Returns if a TileType is a start tile 
 */
bool isStartTileType(const TileType & t) {
    switch (t) {
        case TileType::StartTop:
            return true;
        case TileType::StartBottom:
            return true;
        case TileType::StartLeft:
            return true;
        case TileType::StartRight:
            return true;
    }
    return false;
}

/**
 * @brief Returns if a random start TileType
 */
TileType randomStartTileType() {
    TileType startTileType{TileType::Empty};
    switch (rand() % 4) {
        case 0: startTileType = TileType::StartTop;
            break;
        case 1: startTileType = TileType::StartBottom;
            break;
        case 2: startTileType = TileType::StartLeft;
            break;
        case 3: startTileType = TileType::StartRight;
            break;
    }
    return startTileType;
}

/**
 * @brief Returns if a TileType is an end tile 
 */
bool isEndTileType(const TileType & t) {
    switch (t) {
        case TileType::EndTop:
            return true;
        case TileType::EndBottom:
            return true;
        case TileType::EndLeft:
            return true;
        case TileType::EndRight:
            return true;
    }
    return false;
}

/**
 * @brief Returns if a random end TileType
 */
TileType randomEndTileType() {
    TileType endTileType{TileType::Empty};
    switch (rand() % 4) {
        case 0: endTileType = TileType::EndTop;
            break;
        case 1: endTileType = TileType::EndBottom;
            break;
        case 2: endTileType = TileType::EndLeft;
            break;
        case 3: endTileType = TileType::EndRight;
            break;
    }
    return endTileType;
}

bool isGameTileType(const TileType & t) {
    switch (t) {
        case TileType::Horizontal:
            return true;
        case TileType::Vertical:
            return true;
        case TileType::LeftTop:
            return true;
        case TileType::LeftBottom:
            return true;
        case TileType::TopRight:
            return true;
        case TileType::BottomRight:
            return true;
    }
    return false;
}

TileType randomGameTileType() {
    TileType gameTileType{TileType::Empty};
    switch (rand() % 6) {
        case 0: gameTileType = TileType::Horizontal;
            break;
        case 1: gameTileType = TileType::Vertical;
            break;
        case 2: gameTileType = TileType::LeftTop;
            break;
        case 3: gameTileType = TileType::LeftBottom;
            break;
        case 4: gameTileType = TileType::TopRight;
            break;
        case 5: gameTileType = TileType::BottomRight;
            break;
    }

    return gameTileType;
}