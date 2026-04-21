#ifndef SCOREPOPUP_H
#define SCOREPOPUP_H

#include "raylib.h"

class ScorePopup {
private:
    Vector2 position;
    int value;
    float life;
    bool active;

public:
    ScorePopup();

    void activate(Vector2 startPos, int score);
    void update();
    void draw() const;
    bool isActive() const;
};

#endif