#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;

const int size = 16; // size of each grid
const int N = 30;  // grid width
const int M = 20;  // grid height
const int W = size * N; // window width
const int H = size * M; // window height

struct Snake {
    int x, y;
} snake[N * M];

int num = 4; // snake length
int dir = 2; // direction snake is facing

void Tick() {
    // move body segments
    for (int i = num; i > 0; --i) {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }

    // move head based on direction
    if (dir == 0) snake[0].y += 1; // down
    if (dir == 1) snake[0].x -= 1; // left
    if (dir == 2) snake[0].x += 1; // right
    if (dir == 3) snake[0].y -= 1; // up

    // simple wrapping
    if (snake[0].x >= N) snake[0].x = 0;
    if (snake[0].x < 0) snake[0].x = N - 1;
    if (snake[0].y >= M) snake[0].y = 0;
    if (snake[0].y < 0) snake[0].y = M - 1;
}


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

    // initial snake position
    snake[0].x = 10; snake[0].y = 10;
    snake[1].x = 9;  snake[1].y = 10;
    snake[2].x = 8;  snake[2].y = 10;
    snake[3].x = 7;  snake[3].y = 10;

    // timer for movement
    Clock clock;
    float timer = 0;
    const float delay = 0.2f; // movement speed


    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        while (std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        // handling keyboard input, and preventing opposite direction inputs
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && dir != 2) { dir = 1; }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && dir != 1) { dir = 2; }
        if (Keyboard::isKeyPressed(Keyboard::Key::Up) && dir != 0) { dir = 3; }
        if (Keyboard::isKeyPressed(Keyboard::Key::Down) && dir != 3) { dir = 0; }

        // updating game logic
        if (timer > delay) {
            timer = 0;
            Tick();
        }

        // clearing screen
        window.clear(Color::Black);

        // drawing background grid
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                backgroundSprite.setPosition(Vector2f(i * size, j * size));
                window.draw(backgroundSprite);
            }
        }

        // drawing snake
        for (int i = 0; i < num; i++) {
            snakeSprite.setPosition(Vector2f(snake[i].x * size, snake[i].y * size));
            window.draw(snakeSprite);
        }

        window.display();
    }

    return 0;
}