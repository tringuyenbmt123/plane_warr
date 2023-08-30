#pragma once
#ifndef ITEM_OBJECT_H
#define ITEM_OBJECT_H
#include"Common_function.h"
#include "Base_Object.h"
#include "Amo_Object.h"
#include<vector>
#include "Threat_Object.h"


#define WIDTH_ITEMS 64
#define HEIGHT_ITEMS 64

class ITEMOBJECT :public BASE_OBJECT
{
public:
	ITEMOBJECT();
	~ITEMOBJECT();

	void HandlMove_IT(const int& x_border, const int& y_border);
	void HandleInputAction_IT(SDL_Event(events));
	void reset_IT(const int& xboder);
	void SET_x_val_IT(const int& val)
	{
		x_Val_It = val;
	}
	int GET_x_Val_IT()
	{
		return  x_Val_It;
	}

	void SET_y_val_IT(const int& val)
	{
		y_val_It = val;
	}
	int GET_y_val_IT()
	{
		return y_val_It;
	}





private:
	int x_Val_It;
	int y_val_It;
};

#endif // !ITEM_OBJECT_H
