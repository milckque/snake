#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;

const int size = 16; // size of each grid
const int N = 30;  // grid width
const int M = 20;  // grid height
const int W = size * N; // window width
const int H = size * M; // window height

int main() {
    RenderWindow window(VideoMode(Vector2u(W, H)), "Snake");

    Texture backgroundTexture, snakeTexture, appleTexture;
    // background texture, white
    if (!backgroundTexture.loadFromFile("images/white.png")) {
        // error handling, create a white texture programmatically
        Image whiteImage(Vector2u(size, size), Color::White);
        if (!backgroundTexture.loadFromImage(whiteImage)) {}
    }
    // snake texture, green
    if (!snakeTexture.loadFromFile("images/green.png")) {
        Image greenImage(Vector2u(size, size), Color::Green);
        if (!snakeTexture.loadFromImage(greenImage)) {}
    }
    // apple texture, red
    if (!appleTexture.loadFromFile("images/red.png")) {
        Image redImage(Vector2u(size, size), Color::Red);
        if (!appleTexture.loadFromImage(redImage)) {}
    }

    Sprite backgroundSprite(backgroundTexture);
    Sprite snakeSprite(snakeTexture);
    Sprite appleSprite(appleTexture);

    while (window.isOpen()) {
        while (std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        // drawing background grid
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                backgroundSprite.setPosition(Vector2f(i * size, j * size));
                window.draw(backgroundSprite);
            }
        }

        window.display();
    }

    return 0;
}