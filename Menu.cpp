
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *        Menu class Definitions        *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  The Menu class creates game menu object (Play, Information, Exit the game)

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Menu.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------- Class Menu ------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------

// Constructors
//----------------------------------------------------------------------------------

Menu::Menu() {
	// Empty
}

Menu::Menu(Texture2D &img, vector<Button> &menu_bars, Exit_game &x_game, Instance &info, Instance &roll_info, Instance credits, Sound &ambience) 
{

	this->img = img;
	this->menu_bars = menu_bars;
    this->ambience = ambience;
    Instance inst(MENU, img, menu_bars[0], menu_bars[1], menu_bars[2], this->ambience);
    this->instance = inst;
    this->info = info;
    this->roll_info = roll_info;
    this->credits = credits;
    this->x_game = x_game;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors 
//----------------------------------------------------------------------------------

vector<Button> Menu::bars() {
	return menu_bars;
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------

   Renders Menu instance

--------------------------------------------------------------------*/
void Menu::render_menu()
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
              bar1_resized_rec,
              bar2_resized_rec,
              bar3_resized_rec;

    // Buttons
    Texture2D bar1, bar2, bar3;
    bool bar1_pressed = false,
         bar2_pressed = false,
         bar3_pressed = false;
    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    //---- Ambience volume
    SetSoundVolume(instance.get_ambience(), 0.05);
    PlaySound(instance.get_ambience());

    // Window loop
    do
    {
        //----------------------------------------------------------------------------------

        // Update
        //----------------------------------------------------------------------------------

       // Window state
        if (WindowShouldClose())
        {
            x_game.exit_game_now(); // exit game
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
        // Bars resized
        bar1_resized_rec = {
            (window_width / 9.0f) * window_scale.x,
            (window_height - window_height / 1.4f ) * window_scale.y,
            (instance.btn_source().width) * window_scale.x,
            (instance.btn_source().height) * window_scale.y
        };
        bar2_resized_rec = {
            (window_width / 9.0f) * window_scale.x,
            (window_height - window_height / 1.9f) * window_scale.y,
            (instance.btn_source().width) * window_scale.x,
            (instance.btn_source().height) * window_scale.y
        };
        bar3_resized_rec = {
            (window_width / 9.0f) * window_scale.x,
            (window_height - window_height / 2.9f) * window_scale.y,
            (instance.btn_source().width) * window_scale.x,
            (instance.btn_source().height) * window_scale.y
        };

        // Check bar-1 state, play
        if (CheckCollisionPointRec(mouse_point, bar1_resized_rec))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                bar1 = instance.button3()[0].pressed;
            }
            else
            {
                bar1 = instance.button3()[0].hover;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                bar1_pressed = true;
            }
        }
        else
        {
            bar1 = instance.button3()[0].idle;
        }

        // Check bar-2 state, info
        if (CheckCollisionPointRec(mouse_point, bar2_resized_rec))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                bar2 = instance.button3()[1].pressed;
            }
            else
            {
                bar2 = instance.button3()[1].hover;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                bar2_pressed = true;
            }
        }
        else
        {
            bar2 = instance.button3()[1].idle;
        }

        // Check bar-3 state, exit game
        if (CheckCollisionPointRec(mouse_point, bar3_resized_rec))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                bar3 = instance.button3()[2].pressed;
            }
            else
            {
                bar3 = instance.button3()[2].hover;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                bar3_pressed = true;
            }
        }
        else
        {
            bar3 = instance.button3()[2].idle;
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

            // Bar-1
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                bar1,
                instance.btn_source(), // all 3 bars ahave the same original size
                bar1_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

            // Bar-2
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                bar2,
                instance.btn_source(), // all 3 bars ahave the same original size
                bar2_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );
            // Bar-3
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                bar3,
                instance.btn_source(), // all 3 bars ahave the same original size
                bar3_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );

        EndDrawing();

        //----------------------------------------------------------------------------------
       
        // Checks button pressed
        if (bar1_pressed) { break; } // Exits game
        else if (bar3_pressed) { x_game.exit_game_now(); } // Exits game
        else if (bar2_pressed) // info intance
        { 
            render_sub_instance(info, x_game);
            render_sub_instance(roll_info, x_game);
            render_sub_instance(credits, x_game);
            bar2_pressed = false; 
        } 

        //----- Loops instance ambience sound 
        if (!IsSoundPlaying(instance.get_ambience())) PlaySound(instance.get_ambience());
            
    } while (true); // do loop

    if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

}// render_menu()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

   Renders sub instance menu, info, roll_info, and credits

 --------------------------------------------------------------------------------------------*/
void Menu::render_sub_instance(Instance &instance, Exit_game &x_game)
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
            break; // exist do loop
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

        // Exits do loop
        if (btn1_pressed) break;

        //----- Loops instance ambience sound 
        if (!IsSoundPlaying(instance.get_ambience())) PlaySound(instance.get_ambience());

    } while (true); // do loop

} // render_sub_instance()

