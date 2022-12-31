

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *      Exit_game class Definitions     *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

   The Exit_game class creates an exit game object
   De-Initialization
        background images, buttons, and bars textures
        Closes window and OpenGL context
        Exits game

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Exit_game.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------- Class Exit_game ----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Constructors
//----------------------------------------------------------------------------------
Exit_game::Exit_game()
{
    // Empty
}

/*--------------------------------------------------------------------

    Constructor-1
    Creates an instance EXIT_MENU intance object
    asks user if she/he wants to exit game

 --------------------------------------------------------------------*/
Exit_game::Exit_game(vector<Texture2D> &images, vector<Button> &buttons, vector<Button> &bars, Texture2D disp_bar, vector<Sound> voices, vector<Sound> ambiences)
{
    this->images = images;
    this->buttons = buttons;
    this->bars = bars;
    this->disp_bar = disp_bar;
    this->voices = voices;
    this->ambiences = ambiences;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators
//----------------------------------------------------------------------------------


/*--------------------------------------------------------------------

    De-Initialization
    background images, buttons, and bars textures
    Closes window and OpenGL context
    Exits game

 --------------------------------------------------------------------*/
void Exit_game::exit_game_now()
{
    // De-Initialization background images textures
    for (int i = 0; i < 40; i++)
    {
        UnloadTexture(images[i]);
    }
    // De-Initialization buttons images textures
    for (int i = 0; i < 7; i++)
    {
        UnloadTexture(buttons[i].idle);
        UnloadTexture(buttons[i].hover);
        UnloadTexture(buttons[i].pressed);
    }
    // De-Initialization bars images textures
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(bars[i].idle);
        UnloadTexture(bars[i].hover);
        UnloadTexture(bars[i].pressed);
    }
    // De-Initialization state display bar images textures
    UnloadTexture(disp_bar);
    // De-Initialization narrators' voices
    for (int i = 0; i < 36; i++)
    {
        UnloadSound(voices[i]);
    }
    // De-Initialization background ambiences
    for (int i = 0; i < 27; i++)
    {
        UnloadSound(ambiences[i]);
    }

    //CloseAudioDevice(); // Close audio context
    CloseWindow();  // Close window and OpenGL context
    exit(0);    // Exits game
}