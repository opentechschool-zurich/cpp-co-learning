#include "tileType.h"
#include <gmock/gmock.h>
#include "gameBoardSingleton.h"

using namespace SlidingTiles;

TEST(TileType, Empty) {
    TileType t = TileType::Empty;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("Empty", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ(" ", single);
}

TEST(TileType, Horizontal) {
    TileType t = TileType::Horizontal;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("Horizontal", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("-", single);
}

TEST(TileType, Vertical) {
    TileType t = TileType::Vertical;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("Vertical", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("|", single);
}

TEST(TileType, StartTop) {
    TileType t = TileType::StartTop;
    ASSERT_TRUE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("StartTop", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┴", single);
}

TEST(TileType, StartBottom) {
    TileType t = TileType::StartBottom;
    ASSERT_TRUE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("StartBottom", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┬", single);
}

TEST(TileType, StartLeft) {
    TileType t = TileType::StartLeft;
    ASSERT_TRUE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("StartLeft", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┤", single);
}

TEST(TileType, StartRight) {
    TileType t = TileType::StartRight;
    ASSERT_TRUE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("StartRight", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("├", single);
}

TEST(TileType, EndTop) {
    TileType t = TileType::EndTop;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_TRUE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("EndTop", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┻", single);
}

TEST(TileType, EndBottom) {
    TileType t = TileType::EndBottom;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_TRUE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("EndBottom", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┳", single);
}

TEST(TileType, EndRight) {
    TileType t = TileType::EndRight;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_TRUE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("EndRight", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┣", single);
}

TEST(TileType, EndLeft) {
    TileType t = TileType::EndLeft;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_TRUE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("EndLeft", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┫", single);
}

TEST(TileType, LeftTop) {
    TileType t = TileType::LeftTop;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("LeftTop", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┘", single);
}

TEST(TileType, LeftBottom) {
    TileType t = TileType::LeftBottom;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("LeftBottom", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┐", single);
}

TEST(TileType, TopRight) {
    TileType t = TileType::TopRight;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("TopRight", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("└", single);
}

TEST(TileType, BottomRight) {
    TileType t = TileType::BottomRight;
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("BottomRight", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("┌", single);
}

TEST(TileType, Unknown) {
    TileType t = static_cast<TileType> (65536);
    ASSERT_FALSE(isStartTileType(t));
    ASSERT_FALSE(isEndTileType(t));
    std::string s = tileTypeToString(t);
    ASSERT_EQ("Unknown Type", s);
    std::string single = tileTypeToChar(t);
    ASSERT_EQ("?", single);
}

TEST(TileType, randomStartTileType) {
    // non deterministic test !! Can this be improved?
    int StartTop{0};
    int StartBottom{0};
    int StartLeft{0};
    int StartRight{0};
    int Unexpected{0};
    for (int i = 0; i < 100; ++i) {
        TileType t = randomStartTileType();
        ASSERT_TRUE(isStartTileType(t));
        switch (t) {
            case TileType::StartTop:
                ++StartTop;
                break;
            case TileType::StartBottom:
                ++StartBottom;
                break;
            case TileType::StartLeft:
                ++StartLeft;
                break;
            case TileType::StartRight:
                ++StartRight;
                break;
            default:
                ++Unexpected;
        }
    }
    EXPECT_GT(StartTop, 0) << "After 100 random start tiles we should have returned more than 0 StartTop tiles";
    EXPECT_GT(StartBottom, 0) << "After 100 random start tiles we should have returned more than 0 StartBottom tiles";
    EXPECT_GT(StartLeft, 0) << "After 100 random start tiles we should have returned more than 0 StartLeft tiles";
    EXPECT_GT(StartRight, 0) << "After 100 random start tiles we should have returned more than 0 StartRight tiles";
    ASSERT_EQ(Unexpected, 0) << "After 100 random start tiles we must not have unexpected tiles";
}

TEST(TileType, randomEndTileType) {
    // non deterministic test !! Can this be improved?
    int EndTop{0};
    int EndBottom{0};
    int EndLeft{0};
    int EndRight{0};
    int Unexpected{0};
    for (int i = 0; i < 100; ++i) {
        TileType t = randomEndTileType();
        ASSERT_TRUE(isEndTileType(t));
        switch (t) {
            case TileType::EndTop:
                ++EndTop;
                break;
            case TileType::EndBottom:
                ++EndBottom;
                break;
            case TileType::EndLeft:
                ++EndLeft;
                break;
            case TileType::EndRight:
                ++EndRight;
                break;
            default:
                ++Unexpected;
        }
    }
    EXPECT_GT(EndTop, 0) << "After 100 random end tiles we should have returned more than 0 EndTop tiles";
    EXPECT_GT(EndBottom, 0) << "After 100 random end tiles we should have returned more than 0 EndBottom tiles";
    EXPECT_GT(EndLeft, 0) << "After 100 random end tiles we should have returned more than 0 EndLeft tiles";
    EXPECT_GT(EndRight, 0) << "After 100 random end tiles we should have returned more than 0 EndRight tiles";
    ASSERT_EQ(Unexpected, 0) << "After 100 random end tiles we must not have unexpected tiles";
}

TEST(TileType, isGameTileType) {
    // non deterministic test !! Can this be improved?
    int Horizontal{0};
    int Vertical{0};
    int LeftTop{0};
    int LeftBottom{0};
    int TopRight{0};
    int BottomRight{0};
    int Unexpected{0};
    for (int i = 0; i < 100; ++i) {
        TileType t = randomGameTileType();
        switch (t) {
            case TileType::Horizontal:
                ++Horizontal;
                break;
            case TileType::Vertical:
                ++Vertical;
                break;
            case TileType::LeftTop:
                ++LeftTop;
                break;
            case TileType::LeftBottom:
                ++LeftBottom;
                break;
            case TileType::TopRight:
                ++TopRight;
                break;
            case TileType::BottomRight:
                ++BottomRight;
                break;
            default:
                ++Unexpected;
        }
    }
    EXPECT_GT(Horizontal, 0) << "After 100 random game tiles we should have returned more than 0 Horizontal tiles";
    EXPECT_GT(Vertical, 0) << "After 100 random game tiles we should have returned more than 0 Vertical tiles";
    EXPECT_GT(LeftTop, 0) << "After 100 random game tiles we should have returned more than 0 LeftTop tiles";
    EXPECT_GT(LeftBottom, 0) << "After 100 random game tiles we should have returned more than 0 LeftBottom tiles";
    EXPECT_GT(TopRight, 0) << "After 100 random game tiles we should have returned more than 0 TopRight tiles";
    ASSERT_EQ(Unexpected, 0) << "After 100 random game tiles we must not have unexpected tiles";
}
