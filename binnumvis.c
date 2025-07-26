#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>

int main(int argc, char **argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "BINNUMVIS");
    SetExitKey(KEY_Q);


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawFPS(10, 10);

        for (int i = 0; i < 64; i++) {
            DrawText("0", 16 + i * (GetScreenWidth() / 64), 200, GetScreenWidth() / 44, PINK);
        }


        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
