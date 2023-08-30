#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "Base_Object.h"


#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10
class AMOOBJECT :public BASE_OBJECT
{
public:
	enum AmoType
	{
		NONE = 0,
		LASER = 1,
		SPHERE = 2
	};
	AMOOBJECT();
	~AMOOBJECT();
	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveRighttoLeft_1();
	void HandleMoveRighttoLeft_2(); // kiểu đạn di chuyển 
	void HandleMoveRighttoLeft_3(); // kiểu đạn di chuyển 


	void HandleInputAction(SDL_Event events);

	int GET_type() const
	{
		return amo_type_;
	}
	void SET_type(const int& type)
	{
		amo_type_ = type;
	}

	bool GET_is_move()
	{
		return is_move_;
	}
	void SET_is_move(bool is_move)
	{
		is_move_ = is_move;
	}


	void SetwwidthHeight(const int& widht, const int& height)
	{
		rect_.w = widht;
		rect_.h = height;
	}

	void SET_x_val(const int& val)
	{
		x_val = val;
	}
	void SET_y_val(const int& val)
	{
		y_val = val;
	}

	int GET_x_val() const
	{
		return x_val;
	}
	int GET_y_val() const
	{
		return y_val;
	}

private:
	int x_val;
	int y_val;
	bool is_move_;
	int amo_type_;
};
#endif // !AMO_OBJECT_H_
