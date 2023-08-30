#include "Items.h"

ITEMOBJECT::ITEMOBJECT()
{
	x_Val_It = 0;
	y_val_It = 0;

	rect_.x = SCREEN_WIDTH;// nằm mép bên phải
	rect_.y = SCREEN_HEIGHT * 0.5; // nằm giữa màn hình 
	rect_.w = WIDTH_ITEMS;  // độ rộng tấm ảnh
	rect_.h = HEIGHT_ITEMS; // độ rộng tấm ảnh
}
ITEMOBJECT::~ITEMOBJECT()
{

}

void ITEMOBJECT::HandlMove_IT(const int& x_border, const int& y_border)
{
	rect_.x -= x_Val_It; // cứ dịch chuyển lùi dần về 0 
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH; // đưa về đầu bên phải màn hình
		rect_.y = SDLcommonfunction::MakeRandValue();
	}
}

void ITEMOBJECT::HandleInputAction_IT(SDL_Event events)
{

}

void ITEMOBJECT::reset_IT(const int& xboder = 0) // reset lai items khi bi main an trung
{
	rect_.x = xboder;
	rect_.y = SDLcommonfunction::MakeRandValue();
}




