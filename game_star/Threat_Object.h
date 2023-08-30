#pragma once
#ifndef THREATOBJECT_H_
#define THREATOBJECT_H_

#include"Common_function.h"
#include "Base_Object.h"
#include "Amo_Object.h"
#include<vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33



class THREATOBJECT :public BASE_OBJECT
{
private:
	int x_Val_;
	int y_val_;
	std::vector<AMOOBJECT*> p_amo_list_;

public:
	THREATOBJECT();
	~THREATOBJECT();

	void HandlMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event(events));
	void SET_x_val(const int& val)
	{
		x_Val_ = val;
	}
	int GET_x_Val()
	{
		return  x_Val_;
	}

	void SET_y_val(const int& val)
	{
		y_val_ = val;
	}
	int GET_y_val()
	{
		return y_val_;
	}

	void SetAmoList(std::vector<AMOOBJECT*> amo_list)
	{
		p_amo_list_ = amo_list;
	}

	std::vector<AMOOBJECT*> GetAmoList() const
	{
		return p_amo_list_;
	}

	void initamo(AMOOBJECT* p_amo);
	void make_amo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void make_amo_2(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void make_amo_3(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void reset(const int& xboder);
	void resetAmo(AMOOBJECT* p_amo);

};

#endif // !THREATOBJECT_H_
