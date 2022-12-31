
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *    Instances Functions Definitions   *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  Contains one and two buttons rendering instances functions definitions

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "instances.hpp"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------- one and two buttons instances functions -------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

   Renders one button instances (Monster, Place)

 --------------------------------------------------------------------------------------------*/
void render_btn1_instance(Instance &instance, Menu &menu, Exit_game &x_game)
{
    //--------------------------------------------------------------------------------------

    // variables
    //--------------------------------------------------------------------------------------
    // Window
    float window_width = (float)O_WIN_WD,
          window_height = (float)O_WIN_HT;
    // Mouse position, window scale
    Vector2 mouse_point = { 0.0f, 0.0f },
            window_scale = { 1.0f, 1.0f };
    // Backgrounsd image and buttons resizing
    Rectangle img_resized_rec,
              btn_resized_rec;
    // Button
    Texture2D button;
    bool btn1_pressed = false;

    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    //---- Narrators' voices
    if (instance.get_is_voice()) PlaySound(instance.get_voice()); // is voice, true or false
    //---- Ambience volume
    PlaySound(instance.get_ambience());

    // Event loop
    do  
    {
        //----------------------------------------------------------------------------------

        // Update
        //----------------------------------------------------------------------------------
        
        // Window state, closed, escape button pressed
        if (WindowShouldClose())
        {
            x_game.exit_game_now();
        }
        else if (IsKeyPressed(KEY_ESCAPE))
        {
            // Stop sound
            if (instance.get_is_voice()) // is voice, true or false
            {
                if (IsSoundPlaying(instance.get_voice())) StopSound(instance.get_voice());
            }
            if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

            menu.render_menu();
        }

        // window scale, window not resized scale is 1:1
        window_scale = { (float)GetScreenWidth() / window_width, (float)GetScreenHeight() / window_height };
        // Mousse
        mouse_point = GetMousePosition();
        // Backgound image resized
        img_resized_rec = {
            0.0f, 0.0f,
            (float)GetScreenWidth(),
            (float)GetScreenHeight()
        };
        // Button resized
        btn_resized_rec = {
            (window_width / 2.0f) * window_scale.x,
            (window_height - window_height / 9.0f) * window_scale.y,
            (instance.btn_source().width / 11.0f) * window_scale.x,
            (instance.btn_source().height / 11.0f) * window_scale.y
        };
        // Check button state
        if (CheckCollisionPointRec(mouse_point, btn_resized_rec))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                button = instance.button().pressed;
            }
            else
            {
                button = instance.button().hover;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                btn1_pressed = true;
            }
        }
        else
        {
            button = instance.button().idle;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Background image rezises with window 
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                instance.image(),
                instance.img_source(),
                img_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

            // Button
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                button,
                instance.btn_source(),
                btn_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

        EndDrawing();

        //----------------------------------------------------------------------------------

        //----- Loops instance ambience sound 
        if (!IsSoundPlaying(instance.get_ambience())) PlaySound(instance.get_ambience());
        

        // Exits do loop
        if (btn1_pressed) break;

    } while (true); // do loop

    // Stop sound
    if (instance.get_is_voice()) // is voice, true or false
    {
        if (IsSoundPlaying(instance.get_voice())) StopSound(instance.get_voice());
    }
    if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

} // render_btn1_instance()

//////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

   Renders two buttons instances (Quest, Direction, Exit menu)

 --------------------------------------------------------------------------------------------*/
unsigned render_btn2_instance(Instance &instance, Menu &menu, Exit_game &x_game)
{
    //--------------------------------------------------------------------------------------

    // variables
    //--------------------------------------------------------------------------------------
    // Window
    float window_width = (float)O_WIN_WD,
          window_height = (float)O_WIN_HT;
    // Mouse position, window scale
    Vector2 mouse_point = { 0.0f, 0.0f },
            window_scale = { 1.0f, 1.0f };
    // Backgrounsd image and buttons resizing
    Rectangle img_resized_rec,
              btn1_resized_rec,
              btn2_resized_rec;
    // Buttons
    Texture2D btn1, btn2;
    bool btn1_pressed = false,
         btn2_pressed = false;

    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    //---- Narrators' voices
    if (instance.get_is_voice()) PlaySound(instance.get_voice()); // is voice, true or false
    PlaySound(instance.get_ambience());

    // Window loop
    do
    {
        //----------------------------------------------------------------------------------

        // Update
        //----------------------------------------------------------------------------------

       // Window state, closed, escape button pressed
        if (WindowShouldClose())
        {
            x_game.exit_game_now();
        }
        else if (IsKeyPressed(KEY_ESCAPE))
        {
            // Stop sound
            if (instance.get_is_voice()) // is voice, true or false
            {
                if (IsSoundPlaying(instance.get_voice())) StopSound(instance.get_voice());
            }
            if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

            menu.render_menu();
        }

        // window scale, window not resized scale is 1:1
        window_scale = { (float)GetScreenWidth() / window_width, (float)GetScreenHeight() / window_height };
        // Mousse
        mouse_point = GetMousePosition();
        // Backgound image resized
        img_resized_rec = {
            0.0f, 0.0f,
            (float)GetScreenWidth(),
            (float)GetScreenHeight()
        };
        // Buttons resized
        btn1_resized_rec = {
            (window_width / 25.0f) * window_scale.x,
            (window_height - window_height / 7.0f) * window_scale.y,
            (instance.btn_source().width / 11.0f) * window_scale.x,
            (instance.btn_source().height / 11.0f) * window_scale.y
        };
        btn2_resized_rec = {
            (window_width / 4.5f) * window_scale.x,
            (window_height - window_height / 7.0f) * window_scale.y,
            (instance.btn_source().width / 11.0f) * window_scale.x,
            (instance.btn_source().height / 11.0f) * window_scale.y
                };
        // Check button-1 state
        if (CheckCollisionPointRec(mouse_point, btn1_resized_rec))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                btn1 = instance.button2()[0].pressed;
            }
            else
            {
                btn1 = instance.button2()[0].hover;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                btn1_pressed = true;
            }
        }
        else
        {
            btn1 = instance.button2()[0].idle;
        }

        // Check button-2 state
        if (CheckCollisionPointRec(mouse_point, btn2_resized_rec))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                btn2 = instance.button2()[1].pressed;
            }
            else
            {
                btn2 = instance.button2()[1].hover;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                btn2_pressed = true;
            }
        }
        else
        {
            btn2 = instance.button2()[1].idle;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Background image rezises with window 
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                instance.image(),
                instance.img_source(),
                img_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

            // Button
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                btn1,
                instance.btn_source(), // Both Buttons, btn1 and btn2, have the same original size
                btn1_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

            // Button
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                btn2,
                instance.btn_source(), // Both Buttons, btn1 and btn2, have the same original size
                btn2_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

        EndDrawing();

        //----------------------------------------------------------------------------------

        //----- Loops instance ambience sound if any
        if (!IsSoundPlaying(instance.get_ambience())) PlaySound(instance.get_ambience());
        
        // Exits do loop
        if (btn1_pressed || btn2_pressed) break;

    } while (true); // do loop

    // Stop sound
    if (instance.get_is_voice()) // is voice, true or false
    {
        if (IsSoundPlaying(instance.get_voice())) StopSound(instance.get_voice());
    }
    if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

    return (btn1_pressed) ? BTN1_PRESSED :
           (btn2_pressed) ? BTN2_PRESSED :
           throw "EVENT ERROR: render_btn2_instance()";

}// render_btn2_instance()




