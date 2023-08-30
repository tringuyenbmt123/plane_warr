#include "Text_Object.h"

TEXT_OBJECT::TEXT_OBJECT()
{
	rect_.x = 0;
	rect_.y = 0;
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255; // maac dinh la mau trang 
}

TEXT_OBJECT::~TEXT_OBJECT()
{

}

void TEXT_OBJECT::set_color(const int& type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };  // mau do
		text_color = color;
	}

	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255,255,255 };
		text_color = color;
	}
	else
	{
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void TEXT_OBJECT::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, str_val.c_str(), text_color); // tao ra doi tuong sufare
	show(des);
}