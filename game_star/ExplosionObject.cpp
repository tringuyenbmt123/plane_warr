#include"ExplosionObject.h"

EXPLOSION_OBJECT::EXPLOSION_OBJECT()
{

}
EXPLOSION_OBJECT::~EXPLOSION_OBJECT()
{

}

void EXPLOSION_OBJECT::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH;
	clip_[0].h = EXP_HEIGHT;

	clip_[1].x = EXP_WIDTH;
	clip_[1].y = 0;
	clip_[1].w = EXP_WIDTH;
	clip_[1].h = EXP_HEIGHT;

	clip_[2].x = EXP_WIDTH * 2;
	clip_[2].y = 0;
	clip_[2].w = EXP_WIDTH;
	clip_[2].h = EXP_HEIGHT;

	clip_[3].x = EXP_WIDTH * 3;
	clip_[3].y = 0;
	clip_[3].w = EXP_WIDTH;
	clip_[3].h = EXP_HEIGHT;
}

void EXPLOSION_OBJECT::ShowEx(SDL_Surface* des)
{
	if (frame_ >= 4)
	{
		frame_ = 0;
	}

	SDLcommonfunction::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}