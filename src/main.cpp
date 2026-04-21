#include "raylib.h"
#include "Bubble.h"
#include "ScorePopup.h"

Color GetBackgroundColorByScore(int score) {
    if (score < 100) return (Color){220, 240, 255, 255};
    if (score < 250) return (Color){200, 255, 220, 255};
    if (score < 450) return (Color){255, 240, 200, 255};
    if (score < 700) return (Color){255, 210, 230, 255};
    return (Color){210, 200, 255, 255};
}

void DrawBackgroundDecor(int score, int screenWidth, int screenHeight) {
    DrawCircle(120, 140, 80, Fade(WHITE, 0.10f));
    DrawCircle(screenWidth - 120, 180, 100, Fade(WHITE, 0.08f));
    DrawCircle(screenWidth / 2, screenHeight - 80, 120, Fade(WHITE, 0.05f));

    if (score >= 200) {
        DrawCircle(250, screenHeight - 120, 70, Fade(WHITE, 0.08f));
    }
    if (score >= 400) {
        DrawCircle(screenWidth - 280, screenHeight - 150, 90, Fade(WHITE, 0.08f));
    }
    if (score >= 700) {
        DrawCircle(screenWidth / 2, screenHeight / 2, 130, Fade(WHITE, 0.06f));
    }
}

void DrawTopPanel(int score, int highLevel) {
    DrawRectangleRounded((Rectangle){15, 15, 970, 90}, 0.25f, 20, Fade(WHITE, 0.45f));
    DrawRectangleRoundedLinesEx((Rectangle){15, 15, 970, 90}, 0.25f, 20, 2, Fade(WHITE, 0.85f));

    DrawText("Bubble Clicker", 35, 28, 34, DARKBLUE);
    DrawText("Click moving bubbles to earn points", 38, 64, 20, DARKGRAY);

    DrawRectangleRounded((Rectangle){760, 25, 200, 55}, 0.3f, 20, Fade(SKYBLUE, 0.35f));
    DrawText(TextFormat("SCORE: %d", score), 785, 40, 28, MAROON);

    DrawText(TextFormat("Level %d", highLevel), 650, 42, 26, DARKPURPLE);
}

void DrawCustomCursor() {
    Vector2 mouse = GetMousePosition();
    DrawCircleLines((int)mouse.x, (int)mouse.y, 14, DARKBLUE);
    DrawCircleLines((int)mouse.x, (int)mouse.y, 22, Fade(DARKBLUE, 0.45f));
    DrawCircle((int)mouse.x, (int)mouse.y, 3, RED);
}

int GetLevelByScore(int score) {
    if (score < 100) return 1;
    if (score < 250) return 2;
    if (score < 450) return 3;
    if (score < 700) return 4;
    return 5;
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;
    const int bubbleCount = 6;
    const int popupCount = 12;

    InitWindow(screenWidth, screenHeight, "EX06 - Click the Bubble");
    SetTargetFPS(60);
    HideCursor();

    Bubble bubbles[bubbleCount];
    ScorePopup popups[popupCount];

    int score = 0;

    for (int i = 0; i < bubbleCount; i++) {
        bubbles[i].reset(screenWidth, screenHeight);
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < bubbleCount; i++) {
            bubbles[i].update(screenWidth, screenHeight);
        }

        for (int i = 0; i < popupCount; i++) {
            popups[i].update();
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < bubbleCount; i++) {
                if (bubbles[i].isClicked(mousePos)) {
                    int gained = bubbles[i].getScore();
                    score += gained;

                    for (int j = 0; j < popupCount; j++) {
                        if (!popups[j].isActive()) {
                            Vector2 pos = bubbles[i].getPosition();
                            popups[j].activate({pos.x - 10, pos.y - 10}, gained);
                            break;
                        }
                    }

                    bubbles[i].reset(screenWidth, screenHeight);
                }
            }
        }

        Color bgColor = GetBackgroundColorByScore(score);
        int level = GetLevelByScore(score);

        BeginDrawing();
        ClearBackground(bgColor);

        DrawBackgroundDecor(score, screenWidth, screenHeight);

        for (int i = 0; i < bubbleCount; i++) {
            bubbles[i].draw();
        }

        for (int i = 0; i < popupCount; i++) {
            popups[i].draw();
        }

        DrawTopPanel(score, level);
        DrawCustomCursor();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}