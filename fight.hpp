
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *      Fight Functions Declarations    *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  Contains fight and won instances rendering functions declarations

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FIGHT_HPP
#define FIGHT_HPP

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

//****** Headers lib. files, must be declared first
//****** Contains Global Variables enumerators INST_TYPE, INST_RESULTS, PLAYER_STATE, ORIGINAL_WINDOW_SIZE, ORIGINAL_BTN_SIZE, BTN_TYPE
//****** and the structs Ether and Button
#include "hether.hpp"

#include "Instance.hpp"
#include "Menu.hpp"
#include "Exit_game.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------- Fight instances functions -------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------------------------

    Rolls the dices utilized by fight()

 --------------------------------------------------------------------------------------------*/
vector<int> attack(bool attacks);


/*--------------------------------------------------------------------------------------------

    Computes the dice ouputes, played and monster health outcomes

 --------------------------------------------------------------------------------------------*/
vector<int> fight(Ether &player, Monster &monster, bool player_attacks, bool monster_attacks);

/*--------------------------------------------------------------------------------------------

   Renders Fight instance

 --------------------------------------------------------------------------------------------*/
unsigned render_fight_instance(Instance &instance, Ether &player, Menu &menu, Exit_game &x_game, Texture2D &disp_bar);

/*--------------------------------------------------------------------

   Renders won instance

--------------------------------------------------------------------*/
void render_won_instance(Instance &instance, Ether &player, unsigned state_type, unsigned state_gained, Menu &menu, Exit_game &x_game, Texture2D &disp_bar);

#endif