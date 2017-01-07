#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(600, 395), "SFML Welcome to Davos window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("Davos.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("ChangaOne-Regular.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Welcome to Davos", font, 60);
    text.setPosition(30, -5);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("sound.ogg"))
        return EXIT_FAILURE;

    // Play the music
    music.play();
    music.setLoop(true);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
