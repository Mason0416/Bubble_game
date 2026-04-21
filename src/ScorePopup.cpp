#include "ScorePopup.h"

ScorePopup::ScorePopup() {
    position = {0.0f, 0.0f};
    value = 0;
    life = 0.0f;
    active = false;
}

void ScorePopup::activate(Vector2 startPos, int score) {
    position = startPos;
    value = score;
    life = 1.2f;
    active = true;
}

void ScorePopup::update() {
    if (!active) return;

    position.y -= 1.6f;
    life -= 0.018f;

    if (life <= 0.0f) {
        active = false;
    }
}

void ScorePopup::draw() const {
    if (!active) return;

    int alpha = (int)(255 * (life / 1.2f));
    if (alpha < 0) alpha = 0;
    if (alpha > 255) alpha = 255;

    const char* text = TextFormat("+%d", value);

    // 高分泡泡特效更明顯
    int fontSize = (value >= 35) ? 42 : 34;

    Color shadowColor = {35, 35, 50, (unsigned char)(alpha * 0.80f)};
    Color glowColor   = {255, 255, 255, (unsigned char)(alpha * 0.45f)};
    Color textColor   = (value >= 35)
        ? Color{255, 130, 130, (unsigned char)alpha}
        : Color{255, 210, 60, (unsigned char)alpha};

    // 外圈發光
    DrawText(text, (int)position.x - 2, (int)position.y - 2, fontSize, glowColor);
    DrawText(text, (int)position.x + 2, (int)position.y - 2, fontSize, glowColor);
    DrawText(text, (int)position.x - 2, (int)position.y + 2, fontSize, glowColor);
    DrawText(text, (int)position.x + 2, (int)position.y + 2, fontSize, glowColor);

    // 陰影
    DrawText(text, (int)position.x + 3, (int)position.y + 3, fontSize, shadowColor);

    // 主文字
    DrawText(text, (int)position.x, (int)position.y, fontSize, textColor);
}

bool ScorePopup::isActive() const {
    return active;
}