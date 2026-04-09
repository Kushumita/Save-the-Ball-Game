#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bat {
  private:
    Vector2f       m_Position;
    Vector2f       m_InitialPosition;
    RectangleShape m_Shape;
    float          m_Speed       = 1000;
    bool           m_MovingLeft  = false;
    bool           m_MovingRight = false;

  public:
    Bat(float startX, float startY, float width, float height);
    RectangleShape &getShape();
    Vector2f       &getPosition();
    FloatRect       getBounds();
    void            movingLeft();
    void            movingRight();
    void            stopLeft();
    void            stopRight();

    void update(Time dt,Vector2i resolution);
};

Bat::Bat(float startX, float startY, float width, float height) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setPosition(m_Position);
    m_InitialPosition = m_Position;
    m_Shape.setSize(Vector2f(width, height));
}
RectangleShape &Bat::getShape() { return m_Shape; }
Vector2f       &Bat::getPosition() { return m_Position; }
FloatRect       Bat::getBounds() { return m_Shape.getGlobalBounds(); }
void            Bat::movingLeft() { m_MovingLeft = true; }
void            Bat::movingRight() { m_MovingRight = true; }
void            Bat::stopLeft() { m_MovingLeft = false; }
void            Bat::stopRight() { m_MovingRight = false; }

void Bat::update(Time dt,Vector2i resolution) {
    if (m_MovingLeft && m_Position.x>0)
        m_Position.x -= m_Speed * dt.asSeconds();
    if (m_MovingRight && (m_Position.x+m_Shape.getLocalBounds().width)<resolution.x)
        m_Position.x += m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}