#pragma once
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Base_Object.h"
#include"Common_function.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class EXPLOSION_OBJECT :public BASE_OBJECT
{
private:
	int frame_;  // tạo khung 
	SDL_Rect clip_[4];

public:
	EXPLOSION_OBJECT();
	~EXPLOSION_OBJECT();
	void set_clip();
	void set_frame(const int& fr)
	{
		frame_ = fr;
	}

	void ShowEx(SDL_Surface* des);
};
#endif // !EXPLOSION_H_
