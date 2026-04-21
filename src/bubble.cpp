#include "bubble.h"
#include <cmath>

Bubble::Bubble() {
    position = {100.0f, 100.0f};
    velocity = {2.0f, 2.0f};
    radius = 30.0f;
    color = SKYBLUE;
    scoreValue = 10;
}

Bubble::Bubble(float x, float y, float r, Color c, int score) {
    position = {x, y};
    velocity = {2.0f, 2.0f};
    radius = r;
    color = c;
    scoreValue = score;
}

void Bubble::update(int screenWidth, int screenHeight) {
    position.x += velocity.x;
    position.y += velocity.y;

    // 撞牆反彈
    if (position.x - radius <= 0 || position.x + radius >= screenWidth) {
        velocity.x *= -1;
    }

    if (position.y - radius <= 80 || position.y + radius >= screenHeight) {
        velocity.y *= -1;
    }
}

void Bubble::draw() const {
    // 外圈柔和光暈
    DrawCircleV(position, radius + 6, Fade(WHITE, 0.15f));

    // 主泡泡
    DrawCircleV(position, radius, color);

    // 外框
    DrawCircleLines((int)position.x, (int)position.y, radius, Fade(WHITE, 0.8f));

    // 高光，讓泡泡看起來比較立體
    Vector2 highlight1 = { position.x - radius * 0.35f, position.y - radius * 0.35f };
    Vector2 highlight2 = { position.x - radius * 0.15f, position.y - radius * 0.15f };

    DrawCircleV(highlight1, radius * 0.22f, Fade(WHITE, 0.55f));
    DrawCircleV(highlight2, radius * 0.10f, Fade(WHITE, 0.80f));
}

bool Bubble::isClicked(Vector2 mousePos) const {
    return CheckCollisionPointCircle(mousePos, position, radius);
}

void Bubble::reset(int screenWidth, int screenHeight) {
    radius = (float)GetRandomValue(25, 55);

    position.x = (float)GetRandomValue((int)radius, screenWidth - (int)radius);
    position.y = (float)GetRandomValue((int)radius + 90, screenHeight - (int)radius);

    velocity.x = (float)GetRandomValue(-3, 3);
    velocity.y = (float)GetRandomValue(-3, 3);

    // 避免速度變成 0
    if (velocity.x == 0) velocity.x = 2.0f;
    if (velocity.y == 0) velocity.y = -2.0f;

    // 小泡泡分數比較高
    scoreValue = 70 - (int)radius;

    Color colors[6] = {
        SKYBLUE, PINK, GREEN, ORANGE, PURPLE, GOLD
    };
    color = colors[GetRandomValue(0, 5)];
}

int Bubble::getScore() const {
    return scoreValue;
}