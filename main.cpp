

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------*****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		        Ether's Quest            *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************----------------------------------*/
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Alejandro (Alex) Ricciardi
created date: 12 / 30 / 2022


                                            Ether's Quest

Ether’s Quest is a small story-based ‘D&D game.’
The game lore is based on the Innistrad universe, and it is where Ether journeys to save his younger sister Clarabella.

The game project started as a c++ console assignment for mu computer science 1 class (COS1030),
which became a small game app using SFML library, and into a personal project using the Raylib library.

Requirement
Raylib library: https://www.raylib.com
c++ 11 or later
This project runs on MS Windows 10

****** Please see the README.txt file for more information about this project **********

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------*****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		          Headers                *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****** Headers lib. files, must be declared first
//****** Contains Global Variables enumerators INST_TYPE, INST_RESULTS, PLAYER_STATE, ORIGINAL_WINDOW_SIZE, ORIGINAL_BTN_SIZE, BTN_TYPE
//****** and the structs Ether and Button
#include "hether.hpp"

#include "build_data.hpp"
#include "Instance.hpp"
#include "instances.hpp"
#include "Monster.hpp"
#include "fight.hpp"
#include "Menu.hpp"
#include "Exit_game.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *	            Classes                  *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    Menu.hpp / Menu.cpp  
    The Menu class creates game menu object (Play, Information, Exit the game).

    Instance.hpp / Instance.cpp 
    The Instance class creates game instances objects.

    Monster.hpp / Monster.cpp 
    The Monster class creates objects with the states: string name, int health, int armor, and int strength.

    Exit_game.hpp / Exit_game.cpp 
    The Exit_game class creates an exit game object
    De-Initialization
        background images, buttons, and bars textures
        Closes window and OpenGL context
        Exits game.
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *	        Function Declaration         *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    build_data.hpp / build.cpp
    Contains Build data functions declations/definitions. Loads background, bars and buttons images.

    instances.hpp / instances.cpp
    Contains one and two buttons rendering instances functions declarations/definitions

    fight.hpp / fight.cpp
    Contains fight and won rendering instances functions declarations/definitions
*/

/*--------------------------------------------------------------------

   Switch to render instances Place, Quest, Monster, Direction

--------------------------------------------------------------------*/
unsigned render_instances(Instance instance, Menu menu, Exit_game x_game);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		           Main                  *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

int main(void)
{ 

    //--------------------------------------------------------------------------------------

    // variables
    //--------------------------------------------------------------------------------------

    //--- Game window
    const unsigned window_width = O_WIN_WD;
    const unsigned window_height = O_WIN_HT;

    // Intances Quest, direction and fight results
    unsigned result = 0;
   
    //--------------------------------------------------------------------------------------

    // Initialization Window, OpenGL context, Texture Loads need to be call after this point 
    //--------------------------------------------------------------------------------------
    // 
    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(O_WIN_WD, O_WIN_HT, "Ether's Quest");


    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    SetWindowMinSize((O_WIN_WD - O_WIN_WD / 3) + 15, (O_WIN_HT - O_WIN_HT / 3) + 15);  // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
    SetExitKey(KEY_NULL);  // Disable KEY_ESCAPE to close window, X-button still works

    //--------------------------------------------------------------------------------------

    // Initialize audio device and context
    //--------------------------------------------------------------------------------------
    InitAudioDevice();

    render_load_screen();

    //--------------------------------------------------------------------------------------

    // 2D textures
    //--------------------------------------------------------------------------------------
    //---- Background textures image
    vector<Texture2D> images = load_images();
    //---- Buttons textures
    vector<Button> buttons = load_buttons();
    //---- Menu bars textures
    vector<Button> bars = load_bars();
    //---- State Bar
    Texture2D disp_bar = load_disp_bar();

    //--------------------------------------------------------------------------------------

    // Sounds
    //--------------------------------------------------------------------------------------
    //---- Narrators' voices
    vector<Sound> voices = load_voices();
    //---- Background ambiences sounds
    vector<Sound> ambiences = load_ambiences();

    //--------------------------------------------------------------------------------------

    // Font
    //-------------------------------------------------------------------------------------- 
    // TTF font : Font data and atlas are generated directly from TTF
    // NOTE: font base size of 32 pixels tall and up-to 250 characters
    Font font = LoadFontEx("resources/font/segoeui.ttf", 32, 0, 250);

    //--------------------------------------------------------------------------------------

    // De-Initialization instance object
    //--------------------------------------------------------------------------------------
    //---- Exit game instance
    Exit_game x_game(images, buttons, bars, disp_bar, voices, ambiences);

    //--------------------------------------------------------------------------------------

    // Monsters
    //--------------------------------------------------------------------------------------
    Monster no_monster;
    Monster geist("Geist", 100, 100, 10);
    Monster ophra("Ophra", 150, 150, 20);
    Monster four_heads("Four Heads", 150, 150, 20);
    Monster horde("Horde", 150, 150, 23);
    Monster boar("Boar", 165, 165, 35);
    Monster moose("Moose", 175, 175, 35);
    Monster brian("Brian", 175, 175, 35);
    Monster creature("Creature", 175, 175, 38);
    Monster frog("Frog", 195, 200, 45);
    Monster dalia("Dalia", 200, 195, 45);
    Monster nightmare("Nightmare", 200, 195, 55);
    Monster zombies("Zombies", 200, 195, 53);
    Monster salt("Salt", 350, 350, 65);
    Monster iretrat("Iretrat", 400, 200, 100);
    //--------------------------------------------------------------------------------------

    // Player
    //--------------------------------------------------------------------------------------
    Ether player;

    
                                    ////////////////////////////////////////////////// 
                                    /*-----------------------------------------------
                                     |                                              |
                                     |                Game Instances                |
                                     |                                              |
                                     -----------------------------------------------*/
                                     //////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //----------------------------------------------- Game Menu -----------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance info(PLACE, images[2], buttons[CONTINUE_BTN], ambiences[0]);
    Instance roll_info(PLACE, images[3], buttons[CONTINUE_BTN], ambiences[0]);
    Instance credits(PLACE, images[4], buttons[CONTINUE_BTN], ambiences[0]);
    //--------------------------------------------------------------------------------------
    // Menu instance object
    //---------------------------------------------------------------------------------------
    Menu menu(images[1], bars, x_game, info, roll_info, credits, ambiences[0]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //----------------------------------------------- Game Intro ----------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance intro1(PLACE, images[5], buttons[CONTINUE_BTN], voices[5], ambiences[0]);
    Instance intro2(PLACE, images[6], buttons[CONTINUE_BTN], voices[6], ambiences[0]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------Ether dead or won -------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---- Ether died
    Instance dead(PLACE, images[7], buttons[CONTINUE_BTN], voices[7], ambiences[1]);
    //---- Ether won
    Instance won_inst(WON, images[8], buttons[CONTINUE_BTN], font, voices[8], ambiences[2]);
    //---------------------------------------------------------------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------------------------------------------------------------------------
    //                                              Naphalia
    //---------------------------------------------------------------------------------------------------------------
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------------------------------ Naphalia First Road Monster, Geist ----------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance naphalia(PLACE, images[9], buttons[CONTINUE_BTN], voices[9], ambiences[3]);
    Instance geist_monster(MONSTER, images[10], buttons[FIGHT_BTN], voices[10], ambiences[4]);
    Instance fight_geist(FIGHT, images[10], buttons[ROLL_BTN], geist, font, ambiences[4]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //-------------------------------------------------- Fork -------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance fork(DIRECTION, images[11], buttons[LEFT_BTN], buttons[RIGHT_BTN], voices[11], ambiences[5]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //-------------------------------- Village of Napha Omagra's quest  ---------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance omagra(QUEST, images[12], buttons[ACCEPT_BTN], buttons[REJECT_BTN], voices[12], ambiences[6]);
    Instance ophra_monster(MONSTER, images[13], buttons[FIGHT_BTN], voices[13], ambiences[7]);
    Instance fight_ophra(FIGHT, images[13], buttons[ROLL_BTN], ophra, font, ambiences[7]);
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //----------------------------------- Kalla Oupost Kayla's quest -------------------------------------------------
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance kayla(QUEST, images[14], buttons[ACCEPT_BTN], buttons[REJECT_BTN], voices[14], ambiences[8]);
    Instance fourheads_monster(MONSTER, images[15], buttons[FIGHT_BTN], voices[15], ambiences[9]);
    Instance fight_fourheads(FIGHT, images[15], buttons[ROLL_BTN], four_heads, font, ambiences[9]);
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //---------------------------------------- Leaving Naphalia ------------------------------------------------------
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance leaving_naphalia(PLACE, images[17], buttons[CONTINUE_BTN], voices[17], ambiences[10]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //--------------------------------- Monster on the road Horde of undeads ----------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance horde_monster(MONSTER, images[16], buttons[FIGHT_BTN], voices[16], ambiences[11]);
    Instance fight_horde(FIGHT, images[16], buttons[ROLL_BTN], horde, font, ambiences[11]);
    //----------------------------------------------------------------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------------------------------------------------------------------------
    //                                    Leaving Naphalia Entering Kessig 
    //---------------------------------------------------------------------------------------------------------------
    Instance kessig(PLACE, images[18], buttons[CONTINUE_BTN], voices[18], ambiences[5]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //-------------------------------------- Monster on the road boar  ----------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance boar_monster(MONSTER, images[19], buttons[FIGHT_BTN], voices[19], ambiences[12]);
    Instance fight_boar(FIGHT, images[19], buttons[ROLL_BTN], boar, font, ambiences[12]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------------------------------ Redwood village Connor's quest -------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance connor(QUEST, images[20], buttons[ACCEPT_BTN], buttons[REJECT_BTN], voices[20], ambiences[6]);
    Instance moose_monster(MONSTER, images[21], buttons[FIGHT_BTN], voices[21], ambiences[13]);
    Instance fight_moose(FIGHT, images[21], buttons[ROLL_BTN], moose, font, ambiences[13]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //--------------------------------------- Logus plains Matteo's quest -------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance matteo(QUEST, images[22], buttons[ACCEPT_BTN], buttons[REJECT_BTN], voices[22], ambiences[14]);
    Instance brian_monster(MONSTER, images[23], buttons[FIGHT_BTN], voices[23], ambiences[15]);
    Instance fight_brian(FIGHT, images[23], buttons[ROLL_BTN], brian, font, ambiences[15]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //--------------------------------------- Monster on the road, creature -----------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance creature_monster(MONSTER, images[24], buttons[FIGHT_BTN], voices[24], ambiences[16]);
    Instance fight_creature(FIGHT, images[24], buttons[ROLL_BTN], creature, font, ambiences[16]);
    //----------------------------------------------------------------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------------------------------------------------------------------------
    //                                    Leaving Kessig Entering Stensia
    //---------------------------------------------------------------------------------------------------------------
    Instance leaving_kessig(PLACE, images[25], buttons[CONTINUE_BTN], voices[25], ambiences[17]);
    Instance stensia(PLACE, images[26], buttons[CONTINUE_BTN], voices[26], ambiences[17]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //--------------------------------- Monster on the road Amphibian, Frog -----------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance frog_monster(MONSTER, images[27], buttons[FIGHT_BTN], voices[27], ambiences[18]);
    Instance fight_frog(FIGHT, images[27], buttons[ROLL_BTN], frog, font, ambiences[18]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //-------------------------------------- Graful castle, Eryn's quest -------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance eryn(QUEST, images[28], buttons[ACCEPT_BTN], buttons[REJECT_BTN], voices[28], ambiences[19]);
    Instance dalia_monster(MONSTER, images[29], buttons[FIGHT_BTN], voices[29], ambiences[20]);
    Instance fight_dalia(FIGHT, images[29], buttons[ROLL_BTN], dalia, font, ambiences[20]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------------------------------------ Morna Isaac's quest ------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance isaac(QUEST, images[30], buttons[ACCEPT_BTN], buttons[REJECT_BTN], voices[30], ambiences[21]);
    Instance nightmare_monster(MONSTER, images[31], buttons[FIGHT_BTN], voices[31], ambiences[22]);
    Instance fight_nightmare(FIGHT, images[31], buttons[ROLL_BTN], nightmare, font, ambiences[22]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //------------------------------------- Monster on the road, Zombies --------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance zombies_monster(MONSTER, images[32], buttons[FIGHT_BTN], voices[32], ambiences[23]);
    Instance fight_zombies(FIGHT, images[32], buttons[ROLL_BTN], zombies, font, ambiences[23]);
    //----------------------------------------------------------------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------------------------------------------------------------------------
    //                                          Entering High Temple
    //---------------------------------------------------------------------------------------------------------------
    Instance leaving_stensia(PLACE, images[33], buttons[CONTINUE_BTN], voices[33], ambiences[24]);
    Instance temple(PLACE, images[34], buttons[CONTINUE_BTN], voices[34], ambiences[24]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //--------------------------------------------- Lord Salt -------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance salt_monster(MONSTER, images[35], buttons[FIGHT_BTN], voices[35], ambiences[25]);
    Instance fight_salt(FIGHT, images[35], buttons[ROLL_BTN], salt, font, ambiences[25]);
    Instance dead_salt(PLACE, images[36], buttons[CONTINUE_BTN], voices[36], ambiences[25]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------- Iretrat --------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance iretrat_monster(MONSTER, images[37], buttons[FIGHT_BTN], voices[37], ambiences[26]);
    Instance fight_iretrat(FIGHT, images[37], buttons[ROLL_BTN], salt, font, ambiences[26]);
    Instance dead_iretrat(PLACE, images[38], buttons[CONTINUE_BTN], voices[38], ambiences[26]);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //-------------------------------------------- Clarabella -------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Instance clarabella1(PLACE, images[39], buttons[CONTINUE_BTN], voices[39], ambiences[0]);
    Instance clarabella2(PLACE, images[40], buttons[CONTINUE_BTN], voices[40], ambiences[0]);


                                       //////////////////////////////////////////////////
                                       /*-----------------------------------------------
                                        |                                              |
                                        |           Game Instance Rendering            |
                                        |                                              |
                                        -----------------------------------------------*/
                                       //////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  AA:   //----------------------------------------------- Game Menu -----------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        menu.render_menu();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //----------------------------------------------- Game Intro ----------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SetSoundVolume(intro1.get_ambience(), 0.05); // Ambience volume
        render_instances(intro1, menu, x_game);
        render_instances(intro2, menu, x_game);
        //---------------------------------------------------------------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //---------------------------------------------------------------------------------------------------------------
        //                                              Naphalia
        //---------------------------------------------------------------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   A:   //------------------------------------ Naphalia First Road Monster, Geist ----------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        render_instances(naphalia, menu, x_game);
        SetSoundVolume(geist_monster.get_ambience(), 0.1); // Ambience volume
        render_instances(geist_monster, menu, x_game);
        if (render_fight_instance(fight_geist, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto A; // Naphalia First Road Monster, Geist
        }
        SetSoundVolume(won_inst.get_ambience(), 0.05); // Ambience volume
        render_won_instance(won_inst, player, ARMOR, 50, menu, x_game, disp_bar);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    B:  //------------------------------------------- First Road Fork  --------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(fork, menu, x_game) == RIGHT) goto C;
        // else continue
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //-------------------------------- Village of Napha Omagra's quest  ---------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(omagra, menu, x_game) == REJECT) goto D;
        // else fight ophra
        SetSoundVolume(ophra_monster.get_ambience(), 0.05); // Ambience volume
        render_instances(ophra_monster, menu, x_game);
        if (render_fight_instance(fight_ophra, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto B; // First Road Fork
        }
        render_won_instance(won_inst, player, STRENGTH, 25, menu, x_game, disp_bar);
        render_instances(leaving_naphalia, menu, x_game); // leaving naphalia
        goto E; // Go to Leaving Naphalia Entering Kessig
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    C:  //----------------------------------- Kalla Oupost Kayla's quest ------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(kayla, menu, x_game) == REJECT) goto D;
        // else fight ophra
        render_instances(fourheads_monster, menu, x_game);
        if (render_fight_instance(fight_fourheads, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto B; // First Road Fork
        }
        render_won_instance(won_inst, player, STRENGTH, 25, menu, x_game, disp_bar);
        render_instances(leaving_naphalia, menu, x_game); // leaving naphalia
        goto E; // Go to Leaving Naphalia Entering Kessig
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    D:  //--------------------------------- Monster on the road Horde of undeads ----------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        render_instances(leaving_naphalia, menu, x_game);
        SetSoundVolume(horde_monster.get_ambience(), 0.1); // Ambience volume
        render_instances(horde_monster, menu, x_game);
        if (render_fight_instance(fight_horde, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto B; // First Road Fork
        }
        render_won_instance(won_inst, player, STRENGTH, 25, menu, x_game, disp_bar);
        //----------------------------------------------------------------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //---------------------------------------------------------------------------------------------------------------
    E:  //                                    Leaving Naphalia Entering Kessig 
        //--------------------------------------------------------------------------------------------------------------- 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //-------------------------------------- Monster on the road boar  ----------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        render_instances(boar_monster, menu, x_game);
        if (render_fight_instance(fight_boar, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto E; // Monster on the road boar 
        }
        render_won_instance(won_inst, player, ARMOR, 50, menu, x_game, disp_bar);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    F:  //------------------------------------------ Second Road Fork  --------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(fork, menu, x_game) == RIGHT) goto G;
        // else continue
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //------------------------------------ Redwood village Connor's quest -------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(connor, menu, x_game) == REJECT) goto H;
        // else fight moose
        SetSoundVolume(moose_monster.get_ambience(), 0.05); // Ambience volume
        render_instances(moose_monster, menu, x_game);
        if (render_fight_instance(fight_moose, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto F; // Second Road Fork
        }
        render_won_instance(won_inst, player, HEALTH, 50, menu, x_game, disp_bar);
        goto I; // go to Leaving Kessig entering Stensia
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    G:  //--------------------------------------- Logus plains Matteo's quest -------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(matteo, menu, x_game) == REJECT) goto H;
        // else fight ophra
        render_instances(brian_monster, menu, x_game);
        if (render_fight_instance(fight_brian, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto F; // Second Road Fork
        }
        render_won_instance(won_inst, player, HEALTH, 50, menu, x_game, disp_bar);
        goto I; // go to Leaving Kessig entering Stensia
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    H:  //--------------------------------------- Monster on the road, creature  ----------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        render_instances(creature_monster, menu, x_game);
        if (render_fight_instance(fight_creature, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto F; // Second Road Fork
        }
        render_won_instance(won_inst, player, HEALTH, 50, menu, x_game, disp_bar);
        //----------------------------------------------------------------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //---------------------------------------------------------------------------------------------------------------
     I: //                                    Leaving Kessig Entering Stensia
        //---------------------------------------------------------------------------------------------------------------
        SetSoundVolume(leaving_kessig.get_ambience(), 0.05); // Ambience volume
        render_instances(leaving_kessig, menu, x_game);
        render_instances(stensia, menu, x_game);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //--------------------------------- Monster on the road Amphibian, Frog -----------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SetSoundVolume(frog_monster.get_ambience(), 0.05); // Ambience volume
        render_instances(frog_monster, menu, x_game);
        if (render_fight_instance(fight_frog, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto I; 
        }
        render_won_instance(won_inst, player, ARMOR, 50, menu, x_game, disp_bar);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    J:  //------------------------------------------ Third Road Fork  --------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(fork, menu, x_game) == RIGHT) goto K;
        // else continue
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //-------------------------------------- Graful castle, Eryn's quest --------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SetSoundVolume(eryn.get_ambience(), 0.05); // Ambience volume
        if (render_instances(eryn, menu, x_game) == REJECT) goto L;
        // else fight ophra
        SetSoundVolume(dalia_monster.get_ambience(), 0.05); // Ambience volume
        render_instances(dalia_monster, menu, x_game);
        if (render_fight_instance(fight_dalia, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto J; // Third Road Fork
        }
        render_won_instance(won_inst, player, STRENGTH, 55, menu, x_game, disp_bar);
        goto M; // Go to Entering the High Temple
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    K:  //------------------------------------------ Morna Isaac's quest ------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (render_instances(isaac, menu, x_game) == REJECT) goto L;
        // else fight ophra
        render_instances(nightmare_monster, menu, x_game);
        if (render_fight_instance(fight_nightmare, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto J; // Third Road Fork
        }
        render_won_instance(won_inst, player, STRENGTH, 55, menu, x_game, disp_bar);
        goto M; // Go to Entering the High Temple
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   L:   //--------------------------------------- Monster on the road, Zombies ------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SetSoundVolume(zombies_monster.get_ambience(), 0.05); // Ambience volume
        render_instances(zombies_monster, menu, x_game);
        if (render_fight_instance(fight_zombies, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto J; // Third Road Fork
        }
        render_won_instance(won_inst, player, STRENGTH, 55, menu, x_game, disp_bar);
        //----------------------------------------------------------------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //---------------------------------------------------------------------------------------------------------------
    M:  //                                          Entering High Temple
        //---------------------------------------------------------------------------------------------------------------
        render_instances(leaving_stensia, menu, x_game);
        render_instances(temple, menu, x_game);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //--------------------------------------------- Lord Salt -------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SetSoundVolume(salt_monster.get_ambience(), 0.02); // Ambience volume
        render_instances(salt_monster, menu, x_game);
        if (render_fight_instance(fight_salt, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto M; // Third Road Fork
        }
        render_won_instance(won_inst, player, HEALTH, 100, menu, x_game, disp_bar);
        render_instances(dead_salt, menu, x_game);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //---------------------------------------------- Iretrat --------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SetSoundVolume(iretrat_monster.get_ambience(), 0.1); // Ambience volume
        render_instances(iretrat_monster, menu, x_game);
        if (render_fight_instance(fight_iretrat, player, menu, x_game, disp_bar) == PLAYER_DEAD)
        {
            render_instances(dead, menu, x_game);
            goto M; // Third Road Fork
        }
        render_won_instance(won_inst, player, HEALTH, 100, menu, x_game, disp_bar);
        render_instances(dead_iretrat, menu, x_game);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //-------------------------------------------- Clarabella -------------------------------------------------------
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        render_instances(clarabella1, menu, x_game);
        render_instances(clarabella2, menu, x_game);
        goto AA; // go to menu

    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseAudioDevice();
    CloseWindow();          // Close window and OpenGL context

    //--------------------------------------------------------------------------------------


    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		         Functions               *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************----------------------------------*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*--------------------------------------------------------------------

   Switch to render instances Place, Quest, Monster, Direction

--------------------------------------------------------------------*/
unsigned render_instances(Instance instance, Menu menu, Exit_game x_game)
{
    unsigned result = CONTINUE;

    switch (instance.type())
    {
    case PLACE:
        render_btn1_instance(instance, menu, x_game);
        break;
    case MONSTER:
        render_btn1_instance(instance, menu, x_game);
        break;
    case QUEST:
        (render_btn2_instance(instance, menu, x_game) == BTN1_PRESSED) ?
            result = ACCEPT : result = REJECT;
        break;
    case DIRECTION:
        (render_btn2_instance(instance, menu, x_game) == BTN1_PRESSED) ?
            result = LEFT : result = RIGHT;
    default:
        break;
    }
    
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




