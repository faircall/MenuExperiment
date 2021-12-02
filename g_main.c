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


// todo: always look at position plus heading
// always move position + heading


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
    
    RenderTexture2D screenCapture = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D screenCapture2 = LoadRenderTexture(screenWidth, screenHeight);
    //screenCapture.texture.height = -screenCapture.texture.height;
    
    bool doneMagic = false;
    
   
    
    Camera camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 6.75f}; // this is probably a little screen size dependent
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    //SetCameraMoveControls('w', 's', 'a', 'd', 'z', 'x');
    //SetCameraMode(camera, CAMERA_FIRST_PERSON);
    rlDisableBackfaceCulling();
   
        
    
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
        if (!doneMagic) {
            
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
                BeginTextureMode(screenCapture2);
                
               
                Rectangle toDraw = {.x = 0.0f, .y = 0.0f, .width = screenWidth, .height = screenHeight};
                Vector2 toDrawLoc = {.x = 0.0f, .y = 0.0f};
                DrawTextureRec(screenCapture.texture, toDraw, toDrawLoc, WHITE);
                EndTextureMode();
                doneMagic = true;
            }
            
        } else {
            /* Now we are in 3D */
            Vector3 playerMove = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
            static float headingAngle = 90.0f;
            
            // I think we use a strafe vec and a heading vec?
            if (IsKeyDown(KEY_W)) {
                playerMove.z = -1.0f;
            }
            if (IsKeyDown(KEY_S)) {
                playerMove.z = 1.0f;
            }
            if (IsKeyDown(KEY_A)) {
                playerMove.x = -1.0f;
            }
            if (IsKeyDown(KEY_D)) {
                playerMove.x = 1.0f;
            }
            
            if (IsKeyDown(KEY_Q)) {
                headingAngle -= 5.0f*dt;
            }
            
            if (IsKeyDown(KEY_E)) {
                headingAngle += 5.0f*dt;
            }
            Rectangle toDraw = {.x = 0.0f, .y = 0.0f, .width = 1.0f * screenWidth, .height = 1.0f * screenHeight};
            Vector3 toDrawLoc = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
           
            Vector2 toDrawSize = {.x = 10.0f, .y = 10.0f};
            
            //DrawTextureRec(screenCapture.texture, toDraw, toDrawLoc, WHITE);
            
            BeginMode3D(camera);
            camera.position.z += (10.0f*playerMove.z*dt);
            camera.position.x += (10.0f*playerMove.x*dt);
            
            camera.target = (Vector3){camera.position.x + , 0.0f, camera.position.z - 3.0f };
            UpdateCamera(&camera);
            
            ClearBackground(WHITE);
            
            //DrawBillboard(camera, screenCapture.texture, toDraw, toDrawLoc, toDrawSize, WHITE);
            //DrawBillboard(camera, screenCapture.texture, toDrawLoc, 10, WHITE);
            DrawBillboardRec(camera, screenCapture2.texture, toDraw, toDrawLoc, toDrawSize, WHITE);
            //DrawCube((Vector3){2.0f, 0.0f, 0.0f}, 10.0f, 10.0f, 10.0f, RED);
            
            EndMode3D();
            
     
        
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