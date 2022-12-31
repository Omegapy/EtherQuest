
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *   Instances Functions Declarations   *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  Contains one and two buttons rendering instances functions declaration

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INSTANCES_HPP
#define INSTANCES_HPP

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
//---------------------------------- one and two butoons instances functions -------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------

   Renders one button instances (Monster, Place)

 --------------------------------------------------------------------*/
void render_btn1_instance(Instance &instance, Menu &menu, Exit_game &x_game);

/*--------------------------------------------------------------------

   Renders two buttons instances (Quest, Direction)

 --------------------------------------------------------------------*/
unsigned render_btn2_instance(Instance &instance, Menu &menu, Exit_game &x_game);

#endif


