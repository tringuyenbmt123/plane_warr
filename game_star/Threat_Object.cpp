#include "Threat_Object.h"

THREATOBJECT::THREATOBJECT()
{
	x_Val_ = 0;
	y_val_ = 0;

	rect_.x = SCREEN_WIDTH;// nằm mép bên phải
	rect_.y = SCREEN_HEIGHT * 0.5; // nằm giữa màn hình 
	rect_.w = WIDTH_THREAT;  // độ rộng tấm ảnh
	rect_.h = HEIGHT_THREAT; // độ rộng tấm ảnh

}
THREATOBJECT::~THREATOBJECT()
{
	if (p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			AMOOBJECT* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void THREATOBJECT::initamo(AMOOBJECT* p_amo)
{
	if (p_amo != NULL)
	{
		bool ret = p_amo->loadImg(g_name_amo_threats);
		if (ret == true) // viec doc thanh cong ->
		{
			p_amo->SET_is_move(true);// cho phep di chuyen
			p_amo->SetwwidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE); // gan kich thuoc dan ban ra 
			p_amo->SET_type(AMOOBJECT::SPHERE);
			p_amo->SETrect(rect_.x, rect_.y + rect_.h * 0.5); // set vitri xuat hien dan ban ra
			p_amo->SET_x_val(SPEED_AMO_THREATS);
			p_amo_list_.push_back(p_amo); //Push amo object vào list amo
		}
	}
}

void THREATOBJECT::make_amo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AMOOBJECT* p_amo = p_amo_list_.at(i); // truy cap phan tu tai vi tri i
		if (p_amo != NULL)
		{
			if (p_amo->GET_is_move())// true
			{
				p_amo->show(des);
				p_amo->HandleMoveRighttoLeft_1();//neu ma bang 0 thi ham nay  is_move = false  thi ham p_amo->GET_is_move() =false luoon 
			}
			else// false - > set dan quay ve ban dau
			{
				p_amo->SET_is_move(true);
				p_amo->SETrect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}
}

void THREATOBJECT::make_amo_2(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AMOOBJECT* p_amo = p_amo_list_.at(i); // truy cap phan tu tai vi tri i
		if (p_amo != NULL)
		{
			if (p_amo->GET_is_move())// true
			{
				p_amo->show(des);
				p_amo->HandleMoveRighttoLeft_2();//neu ma bang 0 thi ham nay  is_move = false  thi ham p_amo->GET_is_move() =false luoon 
			}
			else// false - > set dan quay ve ban dau
			{
				p_amo->SET_is_move(true);
				p_amo->SETrect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}
}

void THREATOBJECT::make_amo_3(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AMOOBJECT* p_amo = p_amo_list_.at(i); // truy cap phan tu tai vi tri i
		if (p_amo != NULL)
		{
			if (p_amo->GET_is_move())// true
			{
				p_amo->show(des);
				p_amo->HandleMoveRighttoLeft_3();//neu ma bang 0 thi ham nay  is_move = false  thi ham p_amo->GET_is_move() =false luoon 
			}
			else// false - > set dan quay ve ban dau
			{
				p_amo->SET_is_move(true);
				p_amo->SETrect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}
}

void THREATOBJECT::HandlMove(const int& x_border, const int& y_border)
{
	rect_.x -= x_Val_; // cứ dịch chuyển lùi dần về 0 
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH; // đưa về đầu bên phải màn hình
		rect_.y = SDLcommonfunction::MakeRandValue();
	}
}

void THREATOBJECT::HandleInputAction(SDL_Event events)
{

}


void THREATOBJECT::reset(const int& xboder) // reset lai threat khi bi dan ban

{
	rect_.x = xboder;
	rect_.y = SDLcommonfunction::MakeRandValue();

	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AMOOBJECT* p_amo = p_amo_list_.at(i);
		if (p_amo != NULL)
		{
			resetAmo(p_amo);
		}
	}
}

void THREATOBJECT::resetAmo(AMOOBJECT* p_amo)
{
	p_amo->SETrect(rect_.x, rect_.y + rect_.h * 0.5); // set vitri xuat hien dan ban ra

}