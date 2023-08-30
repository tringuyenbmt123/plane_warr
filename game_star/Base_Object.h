#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_function.h"
class BASE_OBJECT
{
public:
	BASE_OBJECT();
	~BASE_OBJECT();
	void show(SDL_Surface* des);
	bool loadImg(const char* file_name);

	void SETrect(int x, int y)
	{
		rect_.x = x, rect_.y = y;
	}
	SDL_Rect GETrect()
	{
		return rect_;
	}

	SDL_Surface* GETobject()
	{
		return p_object_;
	}
protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;

};


#endif // !BASE_OBJECT_H_
