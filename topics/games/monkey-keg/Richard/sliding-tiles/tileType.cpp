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
            return "Unknown Type";
    }
}
