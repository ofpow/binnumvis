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
    
    init_buttons();

    while (!WindowShouldClose()) {

        update_button_sizes();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawFPS(10, 10);
    
        draw_bit_selection_buttons();

        for (int i = 0; i < num_bits; i++) {
            update_button(i);
        }

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
