#include "Base_Object.h"

BASE_OBJECT::BASE_OBJECT()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}

BASE_OBJECT::~BASE_OBJECT()
{
	if (p_object_ != NULL)
	{
		SDL_FreeSurface(p_object_);
	}
}

bool BASE_OBJECT::loadImg(const char* file_name)
{
	p_object_ = SDLcommonfunction::LoadImage(file_name);
	if (p_object_ == NULL)
	{
		return false;
	}
	return true;
}

void BASE_OBJECT::show(SDL_Surface* des)
{
	if (p_object_ != NULL)
	{
		rect_ = SDLcommonfunction::ApplySurface(p_object_, des, rect_.x, rect_.y);

	}
}


//24:03