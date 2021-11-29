/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    float gameTimer = 0.0f;

    InitWindow(screenWidth, screenHeight, "Vostok");
    HideCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    struct Vector2 newGameLoc = {.x = 300.0f, .y = 300.0f};
    struct Rectangle newGameRect = {.x = newGameLoc.x - 4, .y = newGameLoc.y - 2, .width = 102, .height = 24};
    
    RenderTexture2D screenCapture = LoadRenderTexture(screenWidth/2, screenHeight/2);
    
    
    bool doneMagic = false;
    
    
   
        
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        float dt = GetFrameTime();
        
        gameTimer += dt;
        
        struct Color ngRectColor = DARKGRAY;
        struct Vector2 mousePos = {.x = GetMouseX(), .y = GetMouseY()};
        bool doMagic = false;
        
        if (CheckCollisionPointRec(mousePos, newGameRect)) {
            ngRectColor = LIGHTGRAY;
            if (IsMouseButtonPressed(0)) {
                doMagic = true;
            }
        }
        
        if (doMagic) {
            ngRectColor = RED;
            
        }

        // Draw
        //----------------------------------------------------------------------------------
     
        BeginDrawing();
        if (doMagic) {
            BeginTextureMode(screenCapture);
        }
        ClearBackground(BLUE);
        
        DrawRectangle(0.0f, 0.0f, screenWidth, screenHeight, BLUE);
        
        
        
        
        DrawText("New Game", newGameLoc.x, newGameLoc.y, 20, LIGHTGRAY);
        
        DrawRectangleLinesEx(newGameRect, 3, ngRectColor);
        
        DrawCircleLines(mousePos.x, mousePos.y, 5, LIGHTGRAY);
        
        
        
        
        if (doMagic) {
            EndTextureMode();
            doneMagic = true;
        }
        
        if (doneMagic) {
            //DrawTexture(screenCapture.texture, 400.0f, 400.0f, WHITE);
            struct Rectangle toDraw = {.x = 0.0f, .y = 0.0f, .width = screenWidth/2, .height = -screenHeight/2};
            struct Vector2 toDrawLoc = {.x = 400.0f, .y = 100.0f};
            DrawTextureRec(screenCapture.texture, toDraw, toDrawLoc, WHITE);
        }
     
        
        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}