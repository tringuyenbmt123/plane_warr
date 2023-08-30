#pragma once
#pragma once
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "Base_Object.h"
#include <SDL_ttf.h>
#include<string>
class TEXT_OBJECT :public BASE_OBJECT
{
private:

	std::string str_val; // noi dung text hien thi 
	SDL_Color text_color;

public:

	enum TextColor  // set mac dinh 
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	TEXT_OBJECT();
	~TEXT_OBJECT();

	void set_text(const std::string& text)
	{
		str_val = text;
	}
	void set_color(const int& type);
	void CreateGameText(TTF_Font* font, SDL_Surface* des);

};

#endif // !TEXT_OBJECT_H_
