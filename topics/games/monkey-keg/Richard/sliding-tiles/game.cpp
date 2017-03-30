#include "game.h"
#include "gameBoard.h"
#include <cmath>
#include "puzzleSolver.h"
#include <fstream>
#include <random> // random_shuffle, std::default_random_engine
#include <chrono> // std::chrono::system_clock



using namespace SlidingTiles;
using json = nlohmann::json;

namespace SlidingTiles {

    Game::Game() {
        std::string game3[GameBoard::boardSize][GameBoard::boardSize]{" ", " ", "-", "┬",
            " ", " ", " ", "|",
            " ", " ", "|", " ",
            " ", " ", " ", "┻"};

        std::string game1[GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
            "┣", "┐", " ", "|",
            "┌", "┘", " ", "|",
            "└", "-", "-", "┘"};

        std::string game2[GameBoard::boardSize][GameBoard::boardSize]{
            " ", " ", " ", " ",
            " ", " ", " ", " ",
            " ", " ", "-", " ",
            //" "," ","├",""
            " ", " ", "├", "┐"
        };

        std::string game4[GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", "┬",
            " ", "|", " ", " ",
            " ", " ", " ", "┻",
            " ", " ", " ", " "};

        std::wstring game5{L"   ┬ |     ┻    "};
        std::wstring game6{L"└┘| ├┐┘-┳┘ ┐| ┘┌"};
        std::wstring game7{L"┻ └|┌|┘└ |||├┘ ┌"};
        std::wstring game8{L"┻|└|┌|┘└ | |├┘ ┌"};


        // read a JSON file
        std::ifstream i("assets/sliding-tiles.json");
        json j;
        i >> j;
        levelsArray = j["levels"];
        loadLevel();

        gameView.setGameBoard(&gameBoard);

        json winnerSoundBitesArray = j["winnerSoundBites"];
        for (auto& element : winnerSoundBitesArray) {
            const std::string filename = "assets/" + element["File"].get<std::string>();
            std::cout << filename << '\n';
            sf::SoundBuffer sb{};
            sb.loadFromFile(filename);
            winnerSoundBites.push_back(sb);
        }

        json attitudeSoundBitesArray = j["attitudeSoundBites"];
        for (auto& element : attitudeSoundBitesArray) {
            std::string filename = "assets/" + element["File"].get<std::string>();
            std::cout << filename << '\n';
            sf::SoundBuffer sb{};
            sb.loadFromFile(filename);
            attitudeSoundBites.push_back(sb);
        }

    }

    void Game::update(const float & dt) {
        // send update event to all the tiles
        for (int x = 0; x < GameBoard::boardSize; ++x)
            for (int y = 0; y < GameBoard::boardSize; ++y) {
                gameBoard.tiles[x][y].tileView.update(dt);
            }

        if (gameState == GameState::Playing) {
            std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
            if (solutionPath.size() > 0) {
                gameBoard.setWinnerTiles(solutionPath);
                gameState = GameState::VictoryRolling;
                playWinnerSoundBite();
            } else {
                gameBoard.clearWinnerTiles();
            }
        }
    }

    void Game::OnButtonClick() {
        levelLabel->SetText("Hello SFGUI, pleased to meet you!");
    }

    void Game::run() {

        // Create the label.
        levelLabel = sfg::Label::Create("Level");

        // Create a simple button and connect the click signal.
        auto button = sfg::Button::Create("Greet SFGUI!");
        button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::OnButtonClick, this));

        // Create a vertical box layouter with 5 pixels spacing and add the label
        // and button to it.
        auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
        //box->Pack(m_label);
        box->Pack(button, false);

        // Create a window and add the box layouter to it. Also set the window's title.
        auto sfgwindow = sfg::Window::Create();
        sfgwindow->SetTitle("SFG Window");
        sfgwindow->Add(levelLabel);

        // Create a desktop and add the window to it.
        sfg::Desktop desktop;
        //desktop.Add(sfgwindow);
        desktop.Add(levelLabel);
        levelLabel->SetPosition( sf::Vector2f{400,150});
        levelLabel->SetId("levelLabel");
        

        sf::RenderWindow* window = RenderingSingleton::getInstance().getRenderWindow();
        //window->resetGLStates();
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                desktop.HandleEvent( event );
                if (event.type == sf::Event::Closed)
                    window->close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    doMousePressed(sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doMouseReleased(sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 114) { //r
                        doRandomGame();
                    } else if (event.text.unicode == 112) { //p 
                        gameBoard.printGame();
                    } else if (event.text.unicode == 110) { //n
                        doLevelUp();
                    } else if (event.text.unicode == 97) { //a
                        playAttitudeSoundBite();
                    } else if (event.text.unicode == 119) { //w
                        playWinnerSoundBite();
                    } else
                        std::cout << "ASCII character typed: " << event.text.unicode << " --> " << static_cast<char> (event.text.unicode) << std::endl;
                }
            }

            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            desktop.Update( dt.asSeconds() );
            gameView.render();
            m_sfgui.Display(*window);
            window->display();
        }
    }

    void Game::doRandomGame() {
        int count{0};
        do {
            gameBoard.randomGame(1);
            PuzzleSolver puzzleSolver;
            MoveNode rootNode = puzzleSolver.getTree(gameBoard.serialiseGame(), 3);

            std::cout << "trying a game: " << ++count << "\n";
            int solutionDepth = puzzleSolver.hasASolution(rootNode);
            if (solutionDepth > -1) {
                std::cout << "Solution Depth: " << solutionDepth << "\n";
                count = -1;
            }
        } while (count > -1);
    }

    void Game::doMousePressed(const sf::Vector2i & mousePosition) {
        mousePositionPressed = mousePosition;
    }

    void Game::doMouseReleased(const sf::Vector2i & mousePosition) {
        sf::Vector2i movingTilePosition = RenderingSingleton::getInstance().findTile(mousePositionPressed);
        if (movingTilePosition.x == -1 || movingTilePosition.y == -1)
            return; // out of grid
        int deltaX = mousePosition.x - mousePositionPressed.x;
        int deltaY = mousePosition.y - mousePositionPressed.y;
        if (abs(deltaX) > 2 || abs(deltaY) > 2) {
            SlidingTiles::Tile movingTile = gameBoard.tiles[movingTilePosition.x][movingTilePosition.y];
            if (abs(deltaX) > abs(deltaY)) {
                // horizontal movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x + copysign(1, deltaX), movingTilePosition.y);
                if (deltaX > 0) {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoRight});
                } else {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoLeft});
                }
            } else {
                // vertical movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY));
                //gameBoard.slideTile(movingTilePosition, newPosition);
                if (deltaY > 0) {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoDown});
                } else {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoUp});
                }

            }
        }
    }

    void Game::loadLevel() {
        std::cout << "Loading Level: " << level << std::endl;
        json jsonLevel = levelsArray[level];
        std::string serializedGame = jsonLevel["SerializedGame"].get<std::string>();
        gameBoard.loadGame(serializedGame);
        gameState = GameState::Playing;
    }

    sf::Sound sound;

    void Game::playWinnerSoundBite() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::size_t index = rand() % winnerSoundBites.size();
        sound.setBuffer(winnerSoundBites.at(index));
        sound.play();
    }

    void Game::playAttitudeSoundBite() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::size_t index = rand() % attitudeSoundBites.size();
        sound.setBuffer(attitudeSoundBites.at(index));
        sound.play();
    }

    void Game::doLevelUp() {
        ++level;
        if (level >= levelsArray.size()) {
            level = 0;
        }
        loadLevel();
    }

}
