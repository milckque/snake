#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(Vector2u(800, 600)), "Snake");

    Texture white, green, red;
    // background texture, white
    if (!white.loadFromFile("images/white.png")) {
        // error handling, create a white texture programmatically
        Image whiteImage(Vector2u(20, 20), Color::White);
        if (!white.loadFromImage(whiteImage)) {}
    }
    // snake texture, green
    if (!green.loadFromFile("images/green.png")) {
        Image greenImage(Vector2u(20, 20), Color::Green);
        if (!green.loadFromImage(greenImage)) {}
    }
    // apple texture, red
    if (!red.loadFromFile("images/red.png")) {
        Image redImage(Vector2u(20, 20), Color::Red);
        if (!red.loadFromImage(redImage)) {}
    }

    Sprite sprite1(white);
    sprite1.setPosition(Vector2f(100, 100));
    Sprite sprite2(green);
    sprite2.setPosition(Vector2f(140, 140));
    Sprite sprite3(red);
    sprite3.setPosition(Vector2f(180, 180));

    while (window.isOpen()) {
        while (std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        window.draw(sprite1);
        window.draw(sprite2);
        window.draw(sprite3);

        window.display();
    }

    return 0;
}