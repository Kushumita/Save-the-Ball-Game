#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

class Ball{
    private:
        Vector2f m_Position;
        Vector2f m_InitialPosition;
        CircleShape m_Shape;
        float m_Speed =1000;
        float m_DirectionX = 0.5f;
        float m_DirectionY = 0.5f;

    public:
        Ball(float startX,float startY,float radius);
        CircleShape& getShape();
        Vector2f& getPosition();
        FloatRect getBounds();
        void reboundTop();
        void reboundBottom();
        void reboundSides(Vector2i resolution);
        void reboundbyBat(int batPos);
        void reset();

        void update(Time dt);
};
