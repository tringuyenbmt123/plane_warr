#include "Amo_Object.h"
AMOOBJECT::AMOOBJECT()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val = 0;
	y_val = 0;
	is_move_ = false;
	amo_type_ = NONE;
}

AMOOBJECT::~AMOOBJECT()
{

}

void AMOOBJECT::HandleMove(const int& x_border, const int& y_border)
{
	if (is_move_ == true)
	{
		rect_.x += x_val;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
	}

}

void AMOOBJECT::HandleMoveRighttoLeft_1() // ban xuong
{
	rect_.x -= x_val;
	rect_.y += 3;
	if (rect_.x < 0 || rect_.y >500)
	{
		is_move_ = false;
	}
}

void AMOOBJECT::HandleMoveRighttoLeft_2() // ban thang
{


	rect_.x -= x_val;

	if (rect_.x < 0)
	{
		is_move_ = false;
	}


}

void AMOOBJECT::HandleMoveRighttoLeft_3() // ban len
{
	rect_.x -= x_val;
	rect_.y -= 3;
	if (rect_.x < 0 || rect_.y < 0)
	{
		is_move_ = false;
	}
}




void AMOOBJECT::HandleInputAction(SDL_Event events)
{
	;
}