#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>

#include "binnumvis.h"

uint64_t num = 0;

int main(int argc, char **argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "BINNUMVIS");
    SetExitKey(KEY_Q);
    
    Buttons buttons = (Buttons){
        calloc(64, sizeof(Button)),
        63,
        64
    };

    for (int i = 0; i < num_bits; i++) {
        buttons.data[i] = (Button){
            { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
            "0",
            RED,
            i
        };
    }

    char num_text[24];

    while (!WindowShouldClose()) {
        for (int i = 0; i < num_bits; i++) {
            buttons.data[i].rec = (Rectangle){
                16 + i * (GetScreenWidth() / button_x_divide),
                GetScreenHeight() / button_y_divide,
                GetScreenWidth() / button_height_divide,
                GetScreenHeight() / button_width_divide
            };
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawFPS(10, 10);
        
        sprintf(num_text, signed_print, num);
        DrawText("i64:", GetScreenWidth() / 40, GetScreenHeight() / 5, GetScreenWidth() / 40, LIGHTGRAY);
        DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 4, GetScreenWidth() / 40, WHITE);

        sprintf(num_text, unsigned_print, num);
        DrawText("u64:", GetScreenWidth() / 2, GetScreenHeight() / 5, GetScreenWidth() / 40, LIGHTGRAY);
        DrawText(num_text, GetScreenWidth() / 2, GetScreenHeight() / 4, GetScreenWidth() / 40, WHITE);

        sprintf(num_text, "0x%16llX", num);
        DrawText("hex:", GetScreenWidth() / 40, GetScreenHeight() / 3, GetScreenWidth() / 40, LIGHTGRAY);
        DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 2.5, GetScreenWidth() / 40, WHITE);

        for (int i = 0; i < num_bits; i++) {
            Button b = buttons.data[i];
            DrawRectangleRounded(b.rec, 0.5, 3, b.color);
            
            DrawText(b.text, b.rec.x + bit_text_offset, b.rec.y, GetScreenWidth() / bit_text_width_divide, WHITE);
            
            if (i % 8 == 0) {
                char x[4];
                sprintf(x, "%d", i);
                DrawText(x, b.rec.x + bit_text_offset, b.rec.y + GetScreenHeight() / text_height_divide, GetScreenWidth() / text_width_divide, LIGHTGRAY);
            }

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
