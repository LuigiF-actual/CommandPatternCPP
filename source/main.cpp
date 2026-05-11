
#include <main.hpp>
#include <TileGrid.hpp>
#include <PaintBrush.hpp>

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               

    TileRenderer tileRenderer;
    TileGrid tilegrid(4,4,{100.0f,100.0f});
    TileGrid colorPallete(4, 1,{1000.f, 400.f});
    PaintBrush paintbrush(tilegrid,colorPallete);

    while (!WindowShouldClose())    
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        tileRenderer.draw(tilegrid);
        tileRenderer.draw(tilegrid);
        paintbrush.update();

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}