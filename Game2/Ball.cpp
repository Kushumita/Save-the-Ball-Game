#include "Ball.h"

Ball::Ball(float startX, float startY, float radius) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setPosition(m_Position);
    m_InitialPosition = m_Position;
    m_Shape.setRadius(radius);
}
CircleShape &Ball::getShape() { return m_Shape; }
Vector2f    &Ball::getPosition() { return m_Position; }
FloatRect    Ball::getBounds() { return m_Shape.getGlobalBounds(); }

void Ball::reboundTop() {
    m_Position.y = 1;
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
}
void Ball::reboundBottom() { m_DirectionY = -m_DirectionY; }
void Ball::reboundSides(Vector2i resolution) { 
    if(m_DirectionX<0){
        m_Position.x = 1;
    }else{
        m_Position.x = resolution.x-m_Shape.getLocalBounds().width -1;
    }
    m_Shape.setPosition(m_Position);
    m_DirectionX = -m_DirectionX; 
}
void Ball::reboundbyBat(int batPosY) {
    m_Position.y = batPosY - 1 - m_Shape.getLocalBounds().height;
    m_Shape.setPosition(m_Position);
    m_DirectionY = -m_DirectionY;
}

void Ball::update(Time dt) {
    m_Position.x = m_Shape.getPosition().x + m_DirectionX * dt.asSeconds() * m_Speed;
    m_Position.y = m_Shape.getPosition().y + m_DirectionY * dt.asSeconds() * m_Speed;
    m_Shape.setPosition(m_Position);
}

        void Ball::reset(){
            m_Position = m_InitialPosition;
            m_Shape.setPosition(m_Position);
        }
