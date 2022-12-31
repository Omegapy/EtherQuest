
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *      Instance Class Declarations     *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  The Instance class creates game instances objects 

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

//****** Headers lib. files, must be declared first
//****** Contains Global Variables enumerators INST_TYPE, INST_RESULTS, PLAYER_STATE, and ORIGINAL_WINDOW_SIZE
//****** and the structs Ether and Button
#include "hether.hpp"
#include "Monster.hpp"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------- Instance Class --------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Instance 
{
	//----------------------------------------------------------------------------------

	// Variables
	//----------------------------------------------------------------------------------

	unsigned inst_type;
	//--- Background image
	Texture2D img;
	// Background images original sizes
	// All the images have the same size
	Rectangle img_source_rec = {
		      0.0f, 0.0f,
		     (float)O_WIN_WD, (float)O_WIN_HT
	};
	//--- Buttons
	Button btn1, btn2, btn3;
	bool is_two_btn = false, 
		 is_three_btn = false;
	//--- Font
	Font font;
	bool is_font = false;
	//--- Monster
	Monster monster;
	bool is_monster = false;
	//--- Sounds
	// Narrators' voices
	Sound voice;
	bool is_voice = false;
	// background ambience
	Sound ambience;

public:

	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------

	// Constructors
	//----------------------------------------------------------------------------------

	Instance();

	/*--------------------------------------------------------------------

		constructor-1 one button, ambience
		Instances: Menu

	 --------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Sound &ambience);

	/*--------------------------------------------------------------------

		constructor-2 one button, voice, ambience
		Instances: Place and Monster

	 --------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Sound &voice, Sound &ambience);


	/*---------------------------------------------------------------------

		constructor-3 one button, monster, font, ambience
		Instance: Fight

     --------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Monster &monster, Font &font, Sound &ambience);

	/*-------------------------------------------------------------------

		constructor-4 one button, font, voice, ambience
		Instance: Won

	-------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Font &font, Sound voice, Sound &ambience);


	/*--------------------------------------------------------------------

		constructor-5 two buttons, ambience.
		Instances: Quest, and Direction	

	 --------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Button btn2, Sound &ambience);

	/*--------------------------------------------------------------------

		constructor-6 two buttons, voice, ambience
		Instances: Quest and Direction

	 --------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Button btn2, Sound voice, Sound &ambience);

	/*--------------------------------------------------------------------

		constructor-6 three buttons.
		Instance: Menu

	--------------------------------------------------------------------*/
	Instance(unsigned inst_type, Texture2D &img, Button &btn1, Button &btn2, Button &btn3, Sound &ambience);

	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------

	// Accessors 
	//----------------------------------------------------------------------------------

	unsigned type();

	//-------------------------------------------------

	Texture2D image();

	Rectangle img_source();

	/*--------------------------------------------------------------------

		Returns btn1 source rectangle

	 --------------------------------------------------------------------*/

	Button button();

	/*--------------------------------------------------------------------

		Return btn1 and btn2

	 --------------------------------------------------------------------*/
	vector <Button> button2();

	/*--------------------------------------------------------------------

		Return btn1, btn2, and btn2

	 --------------------------------------------------------------------*/
	vector<Button> button3();

	/*--------------------------------------------------------------------

		Return btn1

	 --------------------------------------------------------------------*/
	Rectangle btn_source();

	/*--------------------------------------------------------------------

		Returns btn1 and btn2 source rectangles

	 --------------------------------------------------------------------*/  
	vector<Rectangle> btn_source2();

	/*--------------------------------------------------------------------

	Returns btn1, btn2, and btn3 source rectangles

	 --------------------------------------------------------------------*/
	vector<Rectangle> btn_source3();

	/*--------------------------------------------------------------------

		Returns font

	 --------------------------------------------------------------------*/
	Font get_font();

	/*--------------------------------------------------------------------

		Returns monster

	 --------------------------------------------------------------------*/
	Monster get_monster();

	/*--------------------------------------------------------------------

		Returns Narrators' voices

	 --------------------------------------------------------------------*/
	Sound get_voice();

	/*--------------------------------------------------------------------

		Returns backgrond ambience

	 --------------------------------------------------------------------*/
	Sound get_ambience();

	/*--------------------------------------------------------------------

		Returns is voice, true or false

	 --------------------------------------------------------------------*/
	bool get_is_voice();

};	// Classe Instance

#endif