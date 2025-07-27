#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>

#define define_array(_name, _type) \
    typedef struct _name {         \
        _type *data;               \
        int64_t index;             \
        int64_t capacity;          \
    } _name                        \

#include "buttons.h"

uint64_t num = 0;

bool raylib_color_equals(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int main(int argc, char **argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "BINNUMVIS");
    SetExitKey(KEY_Q);

    Buttons buttons = (Buttons){
        calloc(64, sizeof(Button)),
        63,
        64
    };

    for (int i = 0; i < 64; i++) {
        buttons.data[i] = (Button){
            { 16 + i * (GetScreenWidth() / 64), GetScreenHeight() / 10, GetScreenWidth() / 100, GetScreenHeight() / 38 },
            "0",
            RED,
            i
        };
    }

    char num_text[24];

    while (!WindowShouldClose()) {
        for (int i = 0; i < 64; i++) {
            buttons.data[i].rec = (Rectangle){
                16 + i * (GetScreenWidth() / 64),
                GetScreenHeight() / 10,
                GetScreenWidth() / 100,
                GetScreenHeight() / 38
            };
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawFPS(10, 10);
        
        sprintf(num_text, "%llu", num);

        DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 28, GetScreenWidth() / 40, WHITE);

        for (int i = 0; i < 64; i++) {
            Button b = buttons.data[i];
            DrawRectangleRounded(b.rec, 0.5, 3, b.color);
            
            DrawText(b.text, b.rec.x + 2, b.rec.y, GetScreenWidth() / 56, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), b.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                uint64_t mask = (uint64_t)1 << i;
                if (raylib_color_equals(b.color, RED)) {
                    num |= mask;
                    buttons.data[i].color = GREEN;
                    buttons.data[i].text = "1";
                } else {
                    num &= ~mask;
                    buttons.data[i].color = RED;
                    buttons.data[i].text = "0";
                }
            }
        }

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
