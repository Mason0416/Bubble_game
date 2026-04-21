#ifndef BUBBLE_H
#define BUBBLE_H

#include "raylib.h"

class Bubble {
private:
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    int scoreValue;

public:
    Bubble();
    Bubble(float x, float y, float r, Color c, int score);

    void update(int screenWidth, int screenHeight);
    void draw() const;
    bool isClicked(Vector2 mousePos) const;
    void reset(int screenWidth, int screenHeight);

    int getScore() const;
    Vector2 getPosition() const;
};

#endif