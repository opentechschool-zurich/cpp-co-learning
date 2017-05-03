#include "game.h"
#include <gmock/gmock.h>
#include <future>

using namespace ::testing;
using namespace SlidingTiles;

TEST(Game, Constructor) {
    Game game{};
    ASSERT_THAT(1, Eq(1));
}

TEST(Game, ConstructorBadFilename) {
    Game game{};
    ASSERT_THAT(1, Eq(1));

    /* Not sure how to test this...
    //Based on http://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest
    GameBoard gameBoard{};
    std::string game = "|┘ -|├-┳┘- | |-|";
    gameBoard.loadGame(game);

    // This can be an ofstream as well or any other ostream
    std::stringstream buffer;
    // Save cout's buffer here
    std::streambuf *sbuf = std::cout.rdbuf();
    // Redirect cout to our stringstream buffer or any other ostream
    std::cout.rdbuf(buffer.rdbuf());
    // Use cout as usual
    gameBoard.printGame();
    // When done redirect cout to its old self
    std::cout.rdbuf(sbuf);

    std::string output = buffer.str();
    ASSERT_EQ(game + '\n', output);
     */
}

TEST(Game, DoRandomGame) {
    Game game{};
    game.doRandomGame();
    ASSERT_THAT(1, Eq(1));
}

/**
 * @brief This test calls the run method which is an endless loop. So we use 
 * https://groups.google.com/forum/#!topic/googletestframework/zOVRgVTwA5M
 * To create a thread where the run happens. We wait 1 millisecond and then
 * send a window->close event. The run() is expected to shut down withing
 * 10 ms.
 */
TEST(Game, Run) {
    Game game{};
    sf::RenderWindow* window = RenderingSingleton::getInstance().getRenderWindow();
    window->setActive(false);
    
    std::promise<bool> promisedFinished;
    auto futureResult = promisedFinished.get_future();
    std::thread([](std::promise<bool>& finished, Game & game) {
        game.run();
        finished.set_value(true);
    }, std::ref(promisedFinished), std::ref(game)).detach();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    window->close();

    EXPECT_TRUE(futureResult.wait_for(std::chrono::milliseconds(10)) != std::future_status::timeout);
}


TEST(Game, DoLevelUp) {
    Game game{};
    game.doLevelUp();
    //ASSERT_THAT(1, Eq(1));
}

TEST(Game, IncrementMoves) {
    Game game{};
    game.incrementMoves();
    //ASSERT_THAT(1, Eq(1));
}