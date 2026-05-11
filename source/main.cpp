
#include <main.hpp>
#include <TileGrid.hpp>
#include <PaintBrush.hpp>

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               

    TileGrid tilegrid(4,4,{100.0f,100.0f});
    PaintBrush paintbrush(tilegrid);

    while (!WindowShouldClose())    
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        tilegrid.draw();
        paintbrush.update();
        EndDrawing();
    }

    CloseWindow();       

    return 0;
}