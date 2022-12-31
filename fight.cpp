

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *      Fight Functions Definitions     *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  Contains fight and won instances rendering functions definitions

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "fight.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------- Fight instances functions -------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------

    Rolls the dices utilized by fight()

 -----------------------------------------------------------------------*/
vector<int> attack(bool attacks)
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------
    vector<int> roll;

    //----------------------------------------------------------------------------------

    // Function operations
    //----------------------------------------------------------------------------------
    if (attacks) { // attacks is true then roll 2 20 dices
        roll.push_back(rand() % (20 - 1) + 1);
        roll.push_back(rand() % (20 - 1) + 1);
    }
    else { // attacks is false then roll 2 10 dices, defence
        roll.push_back(rand() % (10 - 1) + 1);
        roll.push_back(rand() % (10 - 1) + 1);
    }

    return roll;
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------

  Computes the dice ouputes, played and monster health outcomes

 -----------------------------------------------------------------------*/
vector<int> fight(Ether &player, Monster &monster, bool player_attacks, bool monster_attacks)
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------
    unsigned attack_results = 0;
    vector<int> monster_rolls,
        player_rolls,
        fight_results;
    //----------------------------------------------------------------------------------

    // Function operations
    //----------------------------------------------------------------------------------
    // the monster attacks
    if (monster_attacks) {

        monster_rolls = attack(monster_attacks); // monster attack rolls
        player_rolls = attack(player_attacks); // player defence rolls

        if ((monster_rolls[0] + monster_rolls[1]) > (player_rolls[0] + player_rolls[1])) { // checks result of the monster attack rolls

            attack_results = MONSTER_HITS;
            player.health = player.health - monster.get_strength() - round(player.armor / 150);

            if (player.health <= 0) { // checks if the play died

                attack_results = PLAYER_DEAD;
                player.health = 0;
            }
        }
        else { // monster attack miss

            attack_results = MONSTER_MISS;

        }
    }
    else if (player_attacks) { // Player attacks

        player_rolls = attack(player_attacks); // player attack rolls
        monster_rolls = attack(monster_attacks); // player defence rolls

        if ((player_rolls[0] + monster_rolls[1]) > (monster_rolls[0] + monster_rolls[1])) { // checks result of the player attack rolls

            attack_results = PLAYER_HITS;
            monster.set_health(monster.get_health() - player.strength - round(monster.get_armor() / 150));

            if (monster.get_health() <= 0) { // checks if the play died

                attack_results = MONSTER_DEAD;
                monster.set_health(0);
            }
        }
        else { // monster attack miss
            attack_results = PLAYER_MISS;
        }
    }

    // Stores results
    fight_results.push_back(attack_results);
    fight_results.push_back(player_rolls[0]);
    fight_results.push_back(player_rolls[1]);
    fight_results.push_back(monster_rolls[0]);
    fight_results.push_back(monster_rolls[1]);

    return fight_results;

} // fight()

//////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------

   Renders Fight instance

--------------------------------------------------------------------*/
unsigned render_fight_instance(Instance &instance, Ether &player, Menu &menu, Exit_game &x_game, Texture2D &disp_bar)
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------

    // Monster
    Monster monster = instance.get_monster();

    //--- Player and monster health
    int m_health = monster.get_health(),
        temp_m_health = m_health,
        p_health = player.health, // Store the player's health before the monster fight
        temp_p_health = player.health;

    //--- Player text
    string player_state = "Ether   Health: " + to_string(player.health)
           + "   Armor: " + to_string(player.armor)
           + "   Strength: " + to_string(player.strength);
    //--- Monster text
    // space to add between the monster name and the monster states
    string m_name_spaces = (monster.get_name().size() > 5) ? " " : "   ";
    // Monster state
    string monster_state = monster.get_name() + m_name_spaces + "Health: "
           + to_string(monster.get_health())
           + "   Armor: " + to_string(monster.get_armor())
           + "   Strength: " + to_string(monster.get_strength());
    //--- fight
    string fight_rolls_text = monster.get_name() + " attacks first.\nThe attacker rolls two twenty sided dice.\nThe defender rolls two ten sided dice.";
    // Turn to attack
    bool monster_attacks = true,
         player_attacks = false,
         exit_loop = false; // exits do loop
    // Results
    vector<int> fight_results;
    unsigned who_is_dead;

    //-- -Window
    float window_width = (float)O_WIN_WD,
          window_height = (float)O_WIN_HT;
    //--- Mouse position, window scale
    Vector2 mouse_point = { 0.0f, 0.0f },
            window_scale = { 1.0f, 1.0f },
            old_window_scale = window_scale;
    // Text scale
    float text_scale = 1.0f;
    //--- Backgrounsd image, display bar, and buttons resizing
    Rectangle img_resized_rec,
              btn_resized_rec,
              disp_bar1_resized_rec,
              disp_bar2_resized_rec;
    //--- Button
    Texture2D button;

    //--- Display bar original size
    Rectangle disp_bar_source_rec{
        0.0f, 0.0f,
        1941.0f, 461.0f
    };

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

        // window scale, if not resized then ratio is 1:1
        window_scale = { (float)GetScreenWidth() / window_width, (float)GetScreenHeight() / window_height };
        // Text scale, Window rezied 
        if (IsWindowResized()) text_scale = ((2.0f * ((float)GetScreenWidth() / window_width) + ((float)GetScreenHeight() / window_height)) / 3.0f);
        // re-initializes old_window_scale
        old_window_scale = window_scale;
        
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
        // Bar1 resized
        disp_bar1_resized_rec = {
            830 * window_scale.x,
            610 * window_scale.y,
            (disp_bar_source_rec.width / 4.5f) * window_scale.x,
            (disp_bar_source_rec.height / 5.0f) * window_scale.y
        };
        // Bar2 resized
        disp_bar2_resized_rec = {
            100 * window_scale.x,
            575 * window_scale.y,
            (disp_bar_source_rec.width / 4.4f) * window_scale.x,
            (disp_bar_source_rec.height / 3.6f) * window_scale.y
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
                // Roll the dice return Miss or hit or dead (monster or player)
                fight_results = fight(player, monster, player_attacks, monster_attacks);

                // Turn to attack loops
                if (monster_attacks)
                { // if Monster turn to attack
                    if (fight_results[0] == MONSTER_MISS)
                    { // if Monster miss
                        fight_rolls_text = monster.get_name() + " atacked Ether and missed.\n";
                    }
                    else if ((fight_results[0] == MONSTER_HITS))
                    { // if Monster hit player
                        fight_rolls_text = monster.get_name()
                                           + " attacked Ether and hit Ether for "
                                           + to_string(temp_p_health - player.health)
                                           + " points.\n";
                    }
                    else
                    { // Player is dead
                        // Reset the player health to the value set before the fight
                        player.health = p_health;
                        who_is_dead = PLAYER_DEAD;
                        exit_loop = true; // exits do loop
                    }
                }
                else if (player_attacks)
                { // if it is the player turn to attack
                    if (fight_results[0] == PLAYER_MISS)
                    { // if player hit
                        fight_rolls_text = "Ether attacked the " + monster.get_name() + " and missed.\n";
                    }
                    else if ((fight_results[0] == PLAYER_HITS))
                    { // if player miss
                        fight_rolls_text = "Ether attacked the "
                                            + monster.get_name()
                                            + " and hit it for "
                                            + to_string(temp_m_health - monster.get_health())
                                            + " points.\n";
                    }
                    else
                    { // Monster is dead
                        // Reset the player health to the value set before the fight
                        player.health = p_health;
                        who_is_dead = MONSTER_DEAD;
                        exit_loop = true; // exits do loop
                    }
                } // end if loops turn to attack 

                // Store the fight result to be dislayed
                fight_rolls_text += "You rolled " + to_string(fight_results[1])
                                    + " and " + to_string(fight_results[2])
                                    + "  for a total of: " + to_string(fight_results[1] + fight_results[2])
                                    + "\nThe " + monster.get_name() + " rolled " + to_string(fight_results[3])
                                    + " and " + to_string(fight_results[4])
                                    + "  for a total of: " + to_string(fight_results[3] + fight_results[4]);
                // Renders text player's state
                player_state = "Ether      Health: "
                               + to_string(player.health)
                               + "    Armor: " + to_string(player.armor)
                               + "    Strength: " + to_string(player.strength);
                // Renders text monster's state
                monster_state = monster.get_name() + m_name_spaces + "Health: "
                                + to_string(monster.get_health())
                                + "    Armor: " + to_string(monster.get_armor())
                                + "    Strength: " + to_string(monster.get_strength());

                // Set state variable for next play
                temp_m_health = monster.get_health();
                temp_p_health = player.health;
                monster_attacks = !monster_attacks;
                player_attacks = !player_attacks;

            } // if IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
        } // if CheckCollisionPointRec(mouse_point, btn_resized_rec)
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
            // Displays bar1 for player and monster states
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                disp_bar,
                disp_bar_source_rec,
                disp_bar1_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );
            // Player state text
            DrawTextEx(
                instance.get_font(),
                player_state.c_str(),
                { 850 * window_scale.x, 655.0f * window_scale.y },
                18 * text_scale,
                1 * text_scale,
                WHITE
            );
            // Monster state text
            DrawTextEx(
                instance.get_font(),
                monster_state.c_str(),
                { 850 * window_scale.x, 635.0f * window_scale.y },
                18 * text_scale,
                1 * text_scale,
                WHITE
            );
            // Display bar2 for fight text
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                disp_bar,
                disp_bar_source_rec,
                disp_bar2_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );
            // Fight roll results text
            DrawTextEx(
                instance.get_font(),
                fight_rolls_text.c_str(),
                { 120.0f * window_scale.x, 602.0f * window_scale.y },
                18 * text_scale,
                1 * text_scale,
                WHITE
            );

        EndDrawing();

        //----------------------------------------------------------------------------------

        //----- Loops instance ambience sound 
        if (!IsSoundPlaying(instance.get_ambience())) PlaySound(instance.get_ambience());

    } while (!exit_loop); // do loop

    // Stop sound
    if (instance.get_is_voice()) // is voice, true or false
    { 
        if (IsSoundPlaying(instance.get_voice())) StopSound(instance.get_voice()); 
    }
    if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

    return (who_is_dead == PLAYER_DEAD) ? PLAYER_DEAD :
           (who_is_dead == MONSTER_DEAD) ? MONSTER_DEAD :
            throw "EVENT ERROR: render_fight_instance()";

} // render_fight_instance()


//////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------

   Renders won instance

--------------------------------------------------------------------*/
void render_won_instance(Instance &instance, Ether &player, unsigned state_type, unsigned state_gained, Menu &menu, Exit_game &x_game, Texture2D &disp_bar)
{
    //----------------------------------------------------------------------------------

    // Variables
    //----------------------------------------------------------------------------------

    // Player State to add to
    string state;
    // Picks the player state to add to
    switch (state_type)
    {
    case ARMOR:
        player.armor = player.armor + state_gained;
        state = "armor";
        break;
    case STRENGTH:
        player.strength = player.strength + state_gained;
        state = "strength";
        break;
    case HEALTH:
        player.health = player.health + state_gained;
        state = "health";
        break;
    default:
        break;
    }

    //--- Player text
    string player_state = "Ether   Health: " + to_string(player.health)
                          + "   Armor: " + to_string(player.armor)
                          + "   Strength: " + to_string(player.strength);
    //--- Player gained text
    string player_gained = "Ether gained " + to_string(state_gained) + " " + state;

    //--- Window
    float window_width = (float)O_WIN_WD,
          window_height = (float)O_WIN_HT;
    //--- Mouse position, window scale
    Vector2 mouse_point = { 0.0f, 0.0f },
            window_scale = { 1.0f, 1.0f },
            old_window_scale = window_scale;
    // Text scale
    float text_scale = 1.0f;
    //--- Backgrounsd image and buttons resizing
    Rectangle img_resized_rec,
              btn_resized_rec,
              disp_bar_resized_rec;
    //--- Button
    Texture2D button;
    bool btn1_pressed = false;

     //--- Display bar original size
    Rectangle disp_bar_source_rec{
        0.0f, 0.0f,
        1941.0f, 461.0f
    };

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

        // window scale, if not resized then ratio is 1:1
        window_scale = { (float)GetScreenWidth() / window_width, (float)GetScreenHeight() / window_height };
        // Text scale, Window rezied 
        if (IsWindowResized()) text_scale = ((2.0f * ((float)GetScreenWidth() / window_width) + ((float)GetScreenHeight() / window_height)) / 3.0f);
        // re-initializes old_window_scale
        old_window_scale = window_scale;
       
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
        // Bar resized
        disp_bar_resized_rec = {
            830 * window_scale.x,
            610 * window_scale.y,
            (disp_bar_source_rec.width / 4.5f) * window_scale.x,
            (disp_bar_source_rec.height / 5.0f) * window_scale.y
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
            // Displays bar for player states and player gained
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                disp_bar,
                disp_bar_source_rec,
                disp_bar_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );
            // Button
            DrawTexturePro( // Draw a part of a texture (images) defined by a rectangle with 'pro' parameters
                button,
                instance.btn_source(),
                btn_resized_rec,
                { 0, 0 }, 0.0f, WHITE
            );
            // Player state text
            DrawTextEx(
                instance.get_font(),
                player_state.c_str(),
                { 850 * window_scale.x, 655.0f * window_scale.y },
                18 * text_scale,
                1 * text_scale,
                WHITE
            );
            // Player gain 
            DrawTextEx(
                instance.get_font(),
                player_gained.c_str(),
                { 850 * window_scale.x, 635.0f * window_scale.y },
                18 * text_scale,
                1 * text_scale,
                WHITE
            );

        EndDrawing();

        //----------------------------------------------------------------------------------

        // Exits do loop
        if (btn1_pressed) break;

    } while (true); // do loop

    // Stop sound
    if (instance.get_is_voice()) // is voice, true or false
    {
        if (IsSoundPlaying(instance.get_voice())) StopSound(instance.get_voice());
    }
    if (IsSoundPlaying(instance.get_ambience())) StopSound(instance.get_ambience());

} // render_won_instance()

