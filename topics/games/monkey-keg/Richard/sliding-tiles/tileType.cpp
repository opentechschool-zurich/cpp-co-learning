#include "tileType.h"

std::string tileTypeToString( TileType t) {
    switch( t ) {
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
