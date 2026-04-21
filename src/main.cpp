#include "raylib.h"
#include "bubble.h"

Color GetBackgroundColorByScore(int score) {
    if (score < 100) {
        return (Color){220, 240, 255, 255};   // 淺藍
    } else if (score < 250) {
        return (Color){200, 255, 220, 255};   // 淺綠
    } else if (score < 450) {
        return (Color){255, 240, 200, 255};   // 淺橘
    } else if (score < 700) {
        return (Color){255, 210, 230, 255};   // 粉色
    } else {
        return (Color){210, 200, 255, 255};   // 紫色
    }
}

void DrawBackgroundDecor(int score, int screenWidth, int screenHeight) {
    // 背景圓形裝飾，分數越高越多
    DrawCircle(120, 120, 70, Fade(WHITE, 0.10f));
    DrawCircle(screenWidth - 150, 150, 90, Fade(WHITE, 0.08f));

    if (score >= 250) {
        DrawCircle(250, screenHeight - 100, 60, Fade(WHITE, 0.08f));
    }

    if (score >= 450) {
        DrawCircle(screenWidth - 300, screenHeight - 120, 75, Fade(WHITE, 0.10f));
    }

    if (score >= 700) {
        DrawCircle(screenWidth / 2, screenHeight / 2, 100, Fade(WHITE, 0.05f));
    }
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;
    const int bubbleCount = 6;

    InitWindow(screenWidth, screenHeight, "EX06 - Click the Bubble");
    SetTargetFPS(60);

    Bubble bubbles[bubbleCount];
    int score = 0;

    for (int i = 0; i < bubbleCount; i++) {
        bubbles[i].reset(screenWidth, screenHeight);
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        // 更新泡泡移動
        for (int i = 0; i < bubbleCount; i++) {
            bubbles[i].update(screenWidth, screenHeight);
        }

        // 滑鼠點擊
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < bubbleCount; i++) {
                if (bubbles[i].isClicked(mousePos)) {
                    score += bubbles[i].getScore();
                    bubbles[i].reset(screenWidth, screenHeight);
                }
            }
        }

        Color bgColor = GetBackgroundColorByScore(score);

        BeginDrawing();
        ClearBackground(bgColor);

        DrawBackgroundDecor(score, screenWidth, screenHeight);

        DrawText("Click the Bubble!", 20, 20, 36, DARKBLUE);
        DrawText(TextFormat("Score: %d", score), 20, 65, 30, MAROON);
        DrawText("Left click bubbles to get points", 20, 105, 22, DARKGRAY);

        for (int i = 0; i < bubbleCount; i++) {
            bubbles[i].draw();
        }

        // 分數階段提示
        if (score < 100) {
            DrawText("Background Level 1", 760, 20, 20, DARKGRAY);
        } else if (score < 250) {
            DrawText("Background Level 2", 760, 20, 20, DARKGREEN);
        } else if (score < 450) {
            DrawText("Background Level 3", 760, 20, 20, BROWN);
        } else if (score < 700) {
            DrawText("Background Level 4", 760, 20, 20, MAGENTA);
        } else {
            DrawText("Background Level MAX", 740, 20, 20, PURPLE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}