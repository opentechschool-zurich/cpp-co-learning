#include "gameView.h"

namespace SlidingTiles {

void GameView::init() {
    if (!font.loadFromFile("assets/ChangaOne-Regular.ttf"))
        std::cout << "Can't load font ./assets/ChangaOne-Regular.ttf" << std::endl;

    bannerText.setFont(font);
    bannerText.setCharacterSize(30);
    bannerText.setStyle(sf::Text::Bold);
    bannerText.setColor(sf::Color::Black);
    bannerText.setString("Move the tiles with the mouse");
    bannerText.setPosition(30, 10);
}

void GameView::render()
{
    RenderingSingleton::getInstance().getRenderWindow()->clear(sf::Color::White);

    RenderingSingleton::getInstance().getRenderWindow()->draw(bannerText);

    // render the board after the clear
    sf::Sprite emptyTileSprite;
    sf::Texture emptyTexture{};
    emptyTexture = TexturesSingleton::getInstance().getTexturesMap()[TileType::Empty];
    emptyTileSprite.setTexture(emptyTexture);
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            sf::Vector2i position = RenderingSingleton::getInstance().calculateCoordinates(x,y);
            emptyTileSprite.setPosition(position.x, position.y);
            RenderingSingleton::getInstance().getRenderWindow()->draw(emptyTileSprite);
        }

    // first render the tiles that are static
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y) {
            Tile t = GameBoardSingleton::getInstance().tiles[x][y];
            if ( ( ! t.tileView.transitioning ) && ( t.getTileType() != TileType::Empty ) )
                GameBoardSingleton::getInstance().tiles[x][y].tileView.render();
        }

    // then render the tiles that are transitioning so that they are on top
    for (int x = 0; x < GameBoardSingleton::boardSize; ++x)
        for (int y = 0; y < GameBoardSingleton::boardSize; ++y)
            if ( GameBoardSingleton::getInstance().tiles[x][y].tileView.transitioning )
                GameBoardSingleton::getInstance().tiles[x][y].tileView.render();

    RenderingSingleton::getInstance().getRenderWindow()->display();
}
}
