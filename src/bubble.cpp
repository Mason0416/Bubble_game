#include "Bubble.h"

Bubble::Bubble() {
    position = {100.0f, 100.0f};
    velocity = {2.0f, 2.0f};
    radius = 30.0f;
    color = (Color){150, 200, 235, 220};
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

    if (position.x - radius <= 0 || position.x + radius >= screenWidth) {
        velocity.x *= -1;
    }

    if (position.y - radius <= 100 || position.y + radius >= screenHeight) {
        velocity.y *= -1;
    }
}

void Bubble::draw() const {
    // 最外層淡淡光暈
    DrawCircleV(position, radius + 10, Fade(WHITE, 0.06f));
    DrawCircleV(position, radius + 6, Fade(WHITE, 0.10f));

    // 主體泡泡
    DrawCircleV(position, radius, color);

    // 內層柔和疊色，讓泡泡更有層次
    DrawCircleV(
        { position.x - radius * 0.08f, position.y - radius * 0.08f },
        radius * 0.82f,
        Fade(WHITE, 0.08f)
    );

    // 外框，改淡一點
    DrawCircleLines((int)position.x, (int)position.y, radius, Fade(WHITE, 0.65f));

    // 左上大高光
    DrawCircleV(
        { position.x - radius * 0.32f, position.y - radius * 0.35f },
        radius * 0.24f,
        Fade(WHITE, 0.42f)
    );

    // 左上小高光
    DrawCircleV(
        { position.x - radius * 0.12f, position.y - radius * 0.15f },
        radius * 0.10f,
        Fade(WHITE, 0.75f)
    );

    // 右下淡反光
    DrawCircleLines(
        (int)(position.x + radius * 0.15f),
        (int)(position.y + radius * 0.18f),
        radius * 0.28f,
        Fade(WHITE, 0.18f)
    );
}

bool Bubble::isClicked(Vector2 mousePos) const {
    return CheckCollisionPointCircle(mousePos, position, radius);
}

void Bubble::reset(int screenWidth, int screenHeight) {
    radius = (float)GetRandomValue(25, 55);

    position.x = (float)GetRandomValue((int)radius + 20, screenWidth - (int)radius - 20);
    position.y = (float)GetRandomValue((int)radius + 120, screenHeight - (int)radius - 20);

    velocity.x = (float)GetRandomValue(-3, 3);
    velocity.y = (float)GetRandomValue(-3, 3);

    if (velocity.x == 0) velocity.x = 2.0f;
    if (velocity.y == 0) velocity.y = -2.0f;

    scoreValue = 70 - (int)radius;

    // 降低飽和度：改成比較柔和的馬卡龍色
    Color colors[6] = {
        (Color){149, 204, 255, 220}, // soft blue
        (Color){255, 182, 193, 220}, // soft pink
        (Color){170, 220, 190, 220}, // soft green
        (Color){255, 210, 170, 220}, // soft orange
        (Color){205, 180, 255, 220}, // soft purple
        (Color){255, 225, 150, 220}  // soft gold
    };

    color = colors[GetRandomValue(0, 5)];
}

int Bubble::getScore() const {
    return scoreValue;
}

Vector2 Bubble::getPosition() const {
    return position;
}