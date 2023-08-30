#pragma once
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_function.h"
#include "Base_Object.h"
#include<vector>
#include "Amo_Object.h"
#include <chrono>
#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

#define quan_ly_start_and_pause true

class MAINOBJECT :public BASE_OBJECT
{
private:
	int x_val;
	int y_val;
	std::vector<AMOOBJECT*> p_amo_list_;
	std::chrono::steady_clock::time_point lastShotTime_;
	const std::chrono::milliseconds shootInterval_ = std::chrono::milliseconds(200); // Khoảng thời gian giữa mỗi lần bắn (500 ms ở đây)

public:


	MAINOBJECT();
	~MAINOBJECT();

	void HandleInputAction(SDL_Event events);
	void HandleMove();
	void SetAmoList(std::vector<AMOOBJECT*> amo_list)
	{
		p_amo_list_ = amo_list;
	}

	std::vector<AMOOBJECT*> GetAmoList() const
	{
		return p_amo_list_;
	}

	void MakeAmo(SDL_Surface* des,  Mix_Chunk* bullet_sound[2]);
	void remove_amo(const int& index);
	void AutoShoot();
};
#endif // !MAIN_OBJECT_H_ 
