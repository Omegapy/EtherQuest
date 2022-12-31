
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Ether's Quest                 *        Instance class Definitions    *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  The Instance class creates game instances objects 

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Instance.hpp"
#include "Exit_game.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------- Instance Class --------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------

// Constructors
//----------------------------------------------------------------------------------

Instance::Instance()
{
	// Empty
}

/*-----------------------------------------------------------------------

	constructor-1 one button, ambience
	Instances: Menu

 -----------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}


/*--------------------------------------------------------------------

	constructor-2 one button, voice, ambience
	Instances: Place and Monster

 --------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Sound &voice, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->voice = voice;
	is_voice = true;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}

/*-------------------------------------------------------------------

	constructor-3 one button, monster, font, ambience
	Instance: Fight

 -------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Monster &monster, Font &font, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->font = font;
	is_font = true;
	this->monster = monster;
	is_monster = true;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}

/*-------------------------------------------------------------------

	constructor-4 one button, font, voice, ambience
	Instance: Won

 -------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Font &font, Sound voice, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->font = font;
	is_font = true;
	this->monster = monster;
	this->voice = voice;
	is_voice = true;
	is_monster = true;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}
/*--------------------------------------------------------------------

	constructor-5 two buttons, ambience
	Instances: Menu

 --------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Button btn2, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->btn2 = btn2;
	is_two_btn = true;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}

/*--------------------------------------------------------------------

	constructor-6 two buttons, voice, ambience
	Instances: Quest and Direction

 --------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Button btn2, Sound voice, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->btn2 = btn2;
	is_two_btn = true;
	this->voice = voice;
	is_voice = true;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}

/*--------------------------------------------------------------------

	constructor-7 three buttons.
	Instance: Menu

 --------------------------------------------------------------------*/
Instance::Instance(unsigned inst_type, Texture2D &img, Button &btn1, Button &btn2, Button &btn3, Sound &ambience)
{
	this->inst_type = inst_type;
	this->img = img;
	this->btn1 = btn1;
	this->btn2 = btn2;
	this->btn3 = btn3;
	is_three_btn = true;
	this->ambience = ambience;
	//---- Ambience volume
	SetSoundVolume(ambience, 0.3);
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors 
//----------------------------------------------------------------------------------

unsigned Instance::type()
{
	return inst_type;
}

//-------------------------------------------------

Texture2D Instance::image()
{
	return img;
}

Rectangle Instance::img_source()
{
	return img_source_rec;
}

//-------------------------------------------------

Button Instance::button()
{
	return btn1;
}

/*--------------------------------------------------------------------

	Return btn1 and btn2

 --------------------------------------------------------------------*/
vector<Button> Instance::button2()
{
	vector<Button> buttons;
	 
	if (!is_two_btn) 
	{
		throw "This instance has less than or more than 2 buttons";
	}
	else
	{
		buttons.push_back(btn1);
		buttons.push_back(btn2);
	}
	
	return buttons;
}

/*--------------------------------------------------------------------

	Return btn1, btn2, and btn2

 --------------------------------------------------------------------*/
vector<Button> Instance::button3()
{
	vector<Button> buttons;

	if (!is_three_btn)
	{
		throw "This instance has less than 3 buttons";
	}
	else
	{
		buttons.push_back(btn1);
		buttons.push_back(btn2);
		buttons.push_back(btn3);
	}

	return buttons;
};

/*--------------------------------------------------------------------

	Returns btn1 source rectangle

 --------------------------------------------------------------------*/
Rectangle Instance::btn_source() 
{
	return btn1.org_size;
}

/*--------------------------------------------------------------------

	Returns btn1 and btn2 source rectangles 

 --------------------------------------------------------------------*/
vector<Rectangle> Instance::btn_source2()
{
	vector<Rectangle> buttons_rec;

	if (is_two_btn)
	{
		buttons_rec = { btn1.org_size, btn2.org_size };
	}
	else
	{
		throw "This instance has only one button";
	}

	return buttons_rec;
}

/*--------------------------------------------------------------------

	Returns btn1, btn2, and btn3 source rectangles

 --------------------------------------------------------------------*/
vector<Rectangle> Instance::btn_source3()
{
	vector<Rectangle> buttons_rec;

	if (is_three_btn)
	{
		buttons_rec = { btn1.org_size, btn2.org_size, btn3.org_size };
	}
	else
	{
		throw "This instance has less then 3 buttons";
	}

	return buttons_rec;
}

/*--------------------------------------------------------------------

	Returns font

 --------------------------------------------------------------------*/
Font Instance::get_font()
{

	if (!is_font) throw "This instance has no font";

	return font;
}

/*--------------------------------------------------------------------

	Returns monster

 --------------------------------------------------------------------*/
Monster Instance::get_monster()
{
	if (!is_monster) throw "This instance has no monster";

	return monster;
}

/*--------------------------------------------------------------------

	Returns Narrators' voices

 --------------------------------------------------------------------*/
Sound Instance::get_voice() 
{
	
	if (!is_voice) throw "This instance has no narrators' voices";

	return voice;
}

/*--------------------------------------------------------------------

	Returns backgrond ambience

 --------------------------------------------------------------------*/
Sound Instance::get_ambience()
{
	return ambience;
}

/*--------------------------------------------------------------------

	Returns is voice, true or false

 --------------------------------------------------------------------*/
bool Instance::get_is_voice()
{
	return is_voice;
}

