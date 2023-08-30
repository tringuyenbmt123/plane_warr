#include "PlayPower.h"

PLAYER_POWER::PLAYER_POWER()
{

}
PLAYER_POWER::~PLAYER_POWER()
{

}

void PLAYER_POWER::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos);
}

void PLAYER_POWER::Render(SDL_Surface* des)
{
	if (number_ == pos_list_.size())
	{
		for (int i = 0; i < pos_list_.size(); i++)
		{
			rect_.x = pos_list_.at(i); // show cac hinh trai tim tai vi tri khac nhau !
			show(des);
		}
	}
}

void PLAYER_POWER::Init()
{
	loadImg("heart.png");
	number_ = NUMBER_HEART;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	AddPos(0);
	AddPos(30);
	AddPos(60);
}

void PLAYER_POWER::Decrease()
{
	number_--;
	pos_list_.pop_back(); // xoa di phan tu cuoi trong list
}

void PLAYER_POWER::Increase()
{
	//number_++;
	//// Thêm vị trí mới vào danh sách
	//if (number_ < NUMBER_HEART) // Đảm bảo không vượt quá giới hạn số lượng trái tim
	//{
	//	// Thêm vị trí mới ở vị trí cuối danh sách hoặc có thể thêm vào vị trí cố định khác
	//	AddPos(pos_list_.back() + 30); // Ví dụ: tăng thêm 30 đơn vị x để tạo khoảng cách giữa các trái tim
	//	
	//}

	if (number_ < 4) // Kiểm tra số lượng trái tim đã đạt tối đa chưa
	{
		number_++;
		// Thêm vị trí mới vào danh sách
		if (number_ < NUMBER_HEART + 1) // Đảm bảo không vượt quá giới hạn số lượng trái tim
		{
			// Thêm vị trí mới ở vị trí cuối danh sách hoặc có thể thêm vào vị trí cố định khác
			AddPos(pos_list_.back() + 30); // Ví dụ: tăng thêm 30 đơn vị x để tạo khoảng cách giữa các trái tim
		}
	}
}


