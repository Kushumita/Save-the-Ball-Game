#include "Ball.h"

Ball::Ball(float startX, float startY, float radius) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(radius);
    m_Shape.setPosition(m_Position);
    m_InitialPosition = m_Position;
}
Vector2f     Ball::getPosition() { return m_Position; }
FloatRect    Ball::getBounds() {return m_Shape.getLocalBounds();}
CircleShape &Ball::getShape() { return m_Shape; }
void         Ball::bounceSides() { m_DirectionX = -m_DirectionX; }
void         Ball::bounceByBat() { m_DirectionY = -m_DirectionY; }
void         Ball::bounceTop() { m_DirectionY = -m_DirectionY; }
void         Ball::bounceBottom() { m_Position = m_InitialPosition; }
void         Ball::update(Time dt) {
    m_Position.x+= m_DirectionX * m_Speed*dt.asSeconds();
    m_Position.y+= m_DirectionY * m_Speed*dt.asSeconds();
    m_Shape.setPosition(m_Position);
}