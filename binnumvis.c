#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>

#include "binnumvis.h"

int main(int argc, char **argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "BINNUMVIS");
    SetExitKey(KEY_Q);
    
    bit_buttons = (Buttons) {
        calloc(64, sizeof(Button)),
        63,
        64
    };

    for (int i = 0; i < num_bits; i++) {
        bit_buttons.data[i] = (Button){
            { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
            "0",
            RED,
            i
        };
    }

    Buttons bit_selection_buttons = (Buttons) {
        calloc(64, sizeof(Button)),
        2,
        3
    };

    bit_selection_buttons.data[0] = (Button) {
        (Rectangle){GetScreenWidth() / 2.5 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        "8 bit",
        LIGHTGRAY,
        0
    };
    bit_selection_buttons.data[1] = (Button) {
        (Rectangle){GetScreenWidth() / 2 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        "32 bit",
        LIGHTGRAY,
        1
    };
    bit_selection_buttons.data[2] = (Button) {
        (Rectangle){GetScreenWidth() / 1.6666667 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        "64 bit",
        LIGHTGRAY,
        2
    };

    char num_text[24];

    while (!WindowShouldClose()) {

        for (int i = 0; i < num_bits; i++) {
            bit_buttons.data[i].rec = (Rectangle){
                16 + i * (GetScreenWidth() / button_x_divide),
                GetScreenHeight() / button_y_divide,
                GetScreenWidth() / button_height_divide,
                GetScreenHeight() / button_width_divide
            };
        }
        bit_selection_buttons.data[2].rec = (Rectangle)(Rectangle){GetScreenWidth() / 1.6666667 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        bit_selection_buttons.data[1].rec = (Rectangle)(Rectangle){GetScreenWidth() / 2 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        bit_selection_buttons.data[0].rec = (Rectangle){GetScreenWidth() / 2.5 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},


        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawFPS(10, 10);
    
        float xoffset = GetScreenWidth() / 60;
        float yoffset = GetScreenHeight() / 65;
        DrawRectangleRounded(bit_selection_buttons.data[0].rec, 0.5, 3, LIGHTGRAY);
        DrawText("8 bit", bit_selection_buttons.data[0].rec.x + xoffset, bit_selection_buttons.data[0].rec.y + yoffset, 50, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), bit_selection_buttons.data[0].rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            set_8_bit_settings();
        }
        DrawRectangleRounded(bit_selection_buttons.data[1].rec, 0.5, 3, LIGHTGRAY);
        DrawText("32 bit", bit_selection_buttons.data[1].rec.x + xoffset, bit_selection_buttons.data[1].rec.y + yoffset, 50, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), bit_selection_buttons.data[1].rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            set_32_bit_settings();
        }
        DrawRectangleRounded(bit_selection_buttons.data[2].rec, 0.5, 3, LIGHTGRAY);
        DrawText("64 bit", bit_selection_buttons.data[2].rec.x + xoffset, bit_selection_buttons.data[2].rec.y + yoffset, 50, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), bit_selection_buttons.data[2].rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            set_64_bit_settings();
        }

        sprintf(num_text, signed_print, num);
        DrawText("signed:", GetScreenWidth() / 40, GetScreenHeight() / 5, GetScreenWidth() / 40, LIGHTGRAY);
        DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 4, GetScreenWidth() / 40, WHITE);

        sprintf(num_text, unsigned_print, num);
        DrawText("unsigned:", GetScreenWidth() / 2, GetScreenHeight() / 5, GetScreenWidth() / 40, LIGHTGRAY);
        DrawText(num_text, GetScreenWidth() / 2, GetScreenHeight() / 4, GetScreenWidth() / 40, WHITE);

        sprintf(num_text, "0x%16llX", num);
        DrawText("hex:", GetScreenWidth() / 40, GetScreenHeight() / 3, GetScreenWidth() / 40, LIGHTGRAY);
        DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 2.5, GetScreenWidth() / 40, WHITE);
        printf("%d\n", num_bits);
        for (int i = 0; i < num_bits; i++) {
            Button b = bit_buttons.data[i];
            DrawRectangleRounded(b.rec, 0.5, 3, b.color);
            
            DrawText(b.text, b.rec.x + bit_text_offset, b.rec.y, GetScreenWidth() / bit_text_width_divide, WHITE);
            
            if (i % 8 == 0 && num_bits > 8) {
                char x[4];
                sprintf(x, "%d", i);
                DrawText(x, b.rec.x + bit_text_offset, b.rec.y + GetScreenHeight() / text_height_divide, GetScreenWidth() / text_width_divide, LIGHTGRAY);
            }

            if (CheckCollisionPointRec(GetMousePosition(), b.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                uint64_t mask = (uint64_t)1 << i;
                if (raylib_color_equals(b.color, RED)) {
                    num |= mask;
                    bit_buttons.data[i].color = GREEN;
                    bit_buttons.data[i].text = "1";
                } else {
                    num &= ~mask;
                    bit_buttons.data[i].color = RED;
                    bit_buttons.data[i].text = "0";
                }
            }
        }

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
