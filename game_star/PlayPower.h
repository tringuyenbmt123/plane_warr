#pragma once
#ifndef PLAYER_POWERE_H_
#define PLAYER_POWERE_H_
#include "Base_Object.h"
#include <vector>
class PLAYER_POWER :public BASE_OBJECT
{
public:
	PLAYER_POWER();
	~PLAYER_POWER();
	void SetNumber(const int& num)
	{
		number_ = num;
	}

	void AddPos(const int& x_pos);
	void Render(SDL_Surface* des);
	void Init();
	void Decrease(); // giảm 1 mạng khi va chạm 
	void Increase(); // tawng khi an vat phjam 


private:
	int number_; // so mang nhan vat
	std::vector <int > pos_list_;
};
#endif // !PLAYER_POWERE_H_
