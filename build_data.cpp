
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************-----------------------------------
  |                                *                                      *                                  |
  |  Ether's Quest                 *   Build data Functions Definitions   *                                  |
  |                                *                                      *                                  |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  Contains Build data functions definitions. Loads background, bars and buttons images

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "build_data.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------- 2D Textures ----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

   Loads backgrounds images into a vector.
   Returns a vector of images.

 --------------------------------------------------------------------------------------------*/
vector<Texture2D> load_images()
{
    //--------------------------------------------------------------------------------------

     // variables
     //-------------------------------------------------------------------------------------
    vector<Texture2D> images;
    string name;
    Image slide;
    Texture2D img;

    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    // Loads background images from secondary memory
    for (int i = 0; i < 41; i++)
    {

        name = "resources/img/Slide" + to_string(i) + ".png";

        slide = LoadImage(name.c_str());    // Load image in CPU memory (RAM)
        img = LoadTextureFromImage(slide);  // Image converted to texture, uploaded to GPU memory (VRAM)
        UnloadImage(slide); // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

        images.push_back(img);
    }

    return images;

}// Load_images()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

  Loads button texture state in the button struct.
  Utilized by Load_buttons() and Load_bars().

 --------------------------------------------------------------------------------------------*/
Texture2D load_btn_state(Image &image, Color &color)
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------
    Color *pixels;
    Image btn_img = ImageCopy(image);
    Texture2D btn = LoadTextureFromImage(btn_img); // Image converted to texture, uploaded to GPU memory (VRAM)

    //----------------------------------------------------------------------------------

    // Function operations
    //----------------------------------------------------------------------------------
    // Shades button image
    ImageColorTint(&btn_img, color);
    pixels = LoadImageColors(btn_img);    // Load pixel data from image (RGBA 32bit)
    // Udate button texture
    UpdateTexture(btn, pixels);

    //--- De-Initialization
    UnloadImageColors(pixels);
    UnloadImage(btn_img);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    return btn;

} // Load_btn_state()


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

  Stores button images into a button textures struct.
  Returns a vector of button textures structs.

 --------------------------------------------------------------------------------------------*/
vector<Button> load_buttons()
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------
    Button button;
    string name;
    Image btn_img;
    vector<Button> buttons;

    //----------------------------------------------------------------------------------

    // Function operations
    //----------------------------------------------------------------------------------
    // Loads buttons images from secondary memory
    /*
        btn-0: Continues
        btn-1: Fight
        btn-2: Right
        btn-3: Left
        btn-4: Roll
        btn-5: Accept
        btn-6: Reject
    */
    for (int i = 0; i < 7; i++)
    {
        name = "resources/buttons/button-" + to_string(i) + ".png";
        btn_img = LoadImage(name.c_str());  // Load image in CPU memory (RAM)

        // Button idle
        button.idle = load_btn_state(btn_img, LIGHTGRAY);
        // Button hover
        button.hover = load_btn_state(btn_img, GRAY);
        // Button pressed
        button.pressed = load_btn_state(btn_img, DARKGRAY);

        buttons.push_back(button);
        //--- De-Initialization
        UnloadImage(btn_img);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    }

    return buttons;

}// Load_buttons()


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

  Stores bar images into a button textures struct.
  Returns a vector of button textures struct.

 --------------------------------------------------------------------------------------------*/
vector <Button> load_bars()
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------
    Button bar;
    string name;
    Image bar_img;
    vector<Button> bars;

    //----------------------------------------------------------------------------------

    // Function operations
    //----------------------------------------------------------------------------------
    // Loads buttons images from secondary memory
    /*
        bar-0: Play
        bar-1: Info
        bar-2: Exit game

    */
    for (int i = 0; i < 3; i++)
    {
        name = "resources/menu_bars/bar-" + to_string(i) + ".png";
        bar_img = LoadImage(name.c_str());  // Load image in CPU memory (RAM)

        // Bar idle
        bar.idle = load_btn_state(bar_img, LIGHTGRAY);
        // Bar hover
        bar.hover = load_btn_state(bar_img, GRAY);
        // Bar pressed
        bar.pressed = load_btn_state(bar_img, DARKGRAY);
        // Bar original size
        bar.org_size = {
            0.0f, 0.0f,
            338.0f,60.0f
        };

        bars.push_back(bar);
        //--- De-Initialization
        UnloadImage(bar_img);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    }

    return bars;

}// Load_bars()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

  Loads the display state bar image.
  Returns a texture display bar.

 --------------------------------------------------------------------------------------------*/
Texture2D load_disp_bar() 
{
    Image bar_img = LoadImage("resources/menu_bars/disp_bar.png");  // Load image in CPU memory (RAM)
    Texture2D disp_bar = LoadTextureFromImage(bar_img); // Image converted to texture, uploaded to GPU memory (VRAM)

    return disp_bar;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------- Sounds ------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

  Loads the narrators' voices.
  Returns a Sound vector of voices.

 --------------------------------------------------------------------------------------------*/
vector<Sound> load_voices()
{
    //--------------------------------------------------------------------------------------

    // variables
    //-------------------------------------------------------------------------------------
    vector<Sound> voices;
    string name;
    Sound voice;

    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    // Loads boopers wav file from secondary memory, fill up for vector voices
    for (int i = 1; i < 6; i++)
    {

        name = "resources/voices/boopers (" + to_string(i) + ").wav";
        voice = LoadSound(name.c_str());    // Load image in CPU memory (RAM)

        voices.push_back(voice);
    }

    // Loads sound wav file from secondary memory
    for (int i = 1; i < 37; i++)
    {

        name = "resources/voices/voice (" + to_string(i) + ").wav";
        voice = LoadSound(name.c_str());    // Load image in CPU memory (RAM)

        voices.push_back(voice);
    }

    return voices;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

  Loads the ambience background sounds.
  Returns a Sound vector of ambiences.

 --------------------------------------------------------------------------------------------*/
vector<Sound> load_ambiences()
{
    //--------------------------------------------------------------------------------------

    // variables
    //-------------------------------------------------------------------------------------
    vector<Sound> ambiences;
    string name;
    Sound ambience;

    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    // Loads sound wav file from secondary memory
    for (int i = 1; i < 28; i++)
    {

        name = "resources/ambiences/ambience (" + to_string(i) + ").wav";
        ambience = LoadSound(name.c_str());    // Load image in CPU memory (RAM)
        ambiences.push_back(ambience);
    }

    return ambiences;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------Render screen -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

    Render the load screen

 --------------------------------------------------------------------------------------------*/
void render_load_screen()
{
    //--------------------------------------------------------------------------------------

    // variables
    //--------------------------------------------------------------------------------------
    // Window
    float window_width = (float)O_WIN_WD,
          window_height = (float)O_WIN_HT;
    // Backgrounsd image and buttons resizing
    Rectangle img_resized_rec,
              img_source_rec = {
                    0.0f, 0.0f,
                    (float)O_WIN_WD, (float)O_WIN_HT
              };
    // Image
    Image slide = LoadImage("resources/img/Slide0.png");    // Load image in CPU memory (RAM)
    Texture2D img = LoadTextureFromImage(slide);

    //--------------------------------------------------------------------------------------

    // Function operations
    //--------------------------------------------------------------------------------------
    
    // Window state, closed, escape button pressed
    if (WindowShouldClose())
    {
        //--------------------------------------------------------------------------------------

        // De-Initialization
        //--------------------------------------------------------------------------------------

        CloseAudioDevice();
        CloseWindow(); // Close window and OpenGL context
        exit(0); // exit game
    }
  
    // Backgound image resized
    img_resized_rec = {
        0.0f, 0.0f,
        (float)GetScreenWidth(),
        (float)GetScreenHeight()
    };
        

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Background image rezises with window 
        DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
            img,
            img_source_rec,
            img_resized_rec,
            { 0, 0 }, 0.0f, WHITE
        );

    EndDrawing();

    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadImage(slide);
    UnloadTexture(img);

} // render_bload-screen()