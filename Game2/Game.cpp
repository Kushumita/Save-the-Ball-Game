#include "Ball.cpp"
#include "Bat.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>
using namespace std;
using namespace sf;

int main() {
#pragma region VM
    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    VideoMode    vm(resolution.x, resolution.y);
    RenderWindow window(vm, "Pong Game", Style::Fullscreen);
    View         view(FloatRect(0, 0, resolution.x, resolution.y));
    window.setView(view);
#pragma endregion

#pragma region VariableDeclaration
    bool  gamePaused = true;
    bool  gameOver   = true;
    int   batWidth   = 150;
    int   batHeight  = 10;
    int   ballRadius = 15;
    int   score      = 0;
    int   lives      = 3;
    Clock clock;
    Time  dt;
    Ball  ball(resolution.x / 2, 40, ballRadius);
    Bat   bat((resolution.x - batWidth) / 2, resolution.y - batHeight - 10, batWidth, batHeight);
// ball.getShape().setFillColor(Color::Red);
#pragma endregion

#pragma region Load_Assets
    Font font;
    font.loadFromFile("fonts/Chicago.ttf");

    Text messageText;
    messageText.setFont(font);
    messageText.setFillColor(Color::Cyan);
    messageText.setCharacterSize(50);
    messageText.setString("Press 'Enter' to start");
    messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2);
    messageText.setPosition(resolution.x / 2, resolution.y / 2);

    Text scoreLivesText;
    scoreLivesText.setFont(font);
    scoreLivesText.setFillColor(Color::Cyan);
    scoreLivesText.setCharacterSize(25);
    scoreLivesText.setString("Score: 0 Lives: 3");
    scoreLivesText.setPosition(10,10);

#pragma endregion
    while (window.isOpen()) {
        Event event;
        dt = clock.restart();
        while (window.pollEvent(event)) { // pollevent is for single event
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == Keyboard::Enter) {
                    gameOver   = false;
                    gamePaused = false;
                    score = 0;
                    lives = 3;
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            bat.movingLeft();
        } else {
            bat.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            bat.movingRight();
        } else {
            bat.stopRight();
        }
        if (!gamePaused) {
            // cout<<"X:"<<ball.getPosition().x<<", y: "<<ball.getPosition().y<<endl;
            if (ball.getPosition().x <= 0) {
                // Left boundary
                ball.reboundSides(resolution);
            }
            if (ball.getPosition().x + ball.getBounds().width >= resolution.x) {
                // Right boundary
                ball.reboundSides(resolution);
            }
            if (ball.getPosition().y <= 0) {
                // Top boundary
                ball.reboundTop();
                score++;
            }
            if (ball.getPosition().y >= resolution.y) {
                // Bottom boundary
                lives--;
                ball.reset();
                if(lives==0){
                    gameOver=true;
                    gamePaused = true;
                }
            }

            if (bat.getBounds().intersects(ball.getBounds())) {
                ball.reboundbyBat(resolution.y - batHeight - 10);
            }

            ball.update(dt);
            bat.update(dt, resolution);

            std::stringstream ss;
            ss<<"Score: "<<score<<" Lives: "<<lives;
            scoreLivesText.setString(ss.str());
        }
        window.clear();
        window.draw(ball.getShape());
        window.draw(bat.getShape());
        window.draw(scoreLivesText);
        if (gameOver)
            window.draw(messageText);
        window.display();
    }
}
