#ifndef  COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#define GA_FAILED -1
#define GA_SUCCESS 0;

#include<SDL.h>
#include<Windows.h>
#include<string>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>


//items
const int NUM_ITEMS = 10; // so vat pham
const int SPEED_ITEMS = 2;
const int VAL_OFFSET_START_POST_ITEMS = 500;

//Khai báo biến const để định dạng các thông sốcố định.  : SCREEN
const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 1;



//Main
const int POS_X_START_MAIN_OBJ = 100;
const int POS_Y_START_MAIN_OBJ = 100;
const int SPEED_MAIN_OBJECT = 5;
const int SPEED_AMO_MAIN = 5;
const int NUMBER_HEART = 3; // so mang cua main

//Threats
const int SPEED_THREAT = 4;// set toc do cua threat
const int NUM_THREAT = 3;
const int SPEED_AMO_THREATS = 5;
const int VAL_OFFSET_START_POST_THREATS = 400; // xét vị trí xuất hiện của threat ko cung thời điểm
const int UNDER_LIMIT_THREAT = 200; // gioi han cua may bay

// biến global : toàn cục
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even;
static SDL_Surface* g_img_menu = NULL;

static Mix_Chunk* g_sound_bullet[2]; // tieng dan ban
static Mix_Chunk* g_sound_exp[2]; // vu no 
static Mix_Music* g_music = NULL; // nhac nen
static Mix_Chunk* g_game_over[1]; // game over
static Mix_Chunk* g_sound_coil[1]; // vu no 


static char g_name_bk_ground[] = { "bkground.jpg" };

static char g_name_items[] = { "coil.jpg" };// items
static char g_name_main_obj[] = { "ROCKET.png" };
static char g_name_exp_main[] = { "exp_main.png" };
static char g_name_amo_main_laser[] = { "laser.png" };
static char g_name_amo_main_fire[] = { "sphere.png" };
static char g_name_audio_amo_main[] = { "Lazer.wav" };
static char g_name_audio_amo_main2[] = { "sphere.wav" };
static char g_name_audio_exp_main[] = { "boom.wav" };
static char g_name_audio_game_over[] = { "gameover.wav" };
static char g_name_exp_threats[] = { "exp.png" };
static char g_name_threats[] = { "plane.png" };
static char g_name_amo_threats[] = { "sphere2.png" };
static char g_name_audio_exp_threats[] = { "boom1.wav" };
static char g_name_audio_nhac_nen[] = { "nhacnen.wav" };
static char g_name_audio_coil[] = { "coil.wav" };
namespace SDLcommonfunction
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool checkCollision(const SDL_Rect& object_1, const SDL_Rect& object_2);
	int MakeRandValue(const int& div_val = 400);
	int MakeRandValue_for_items(const int& div_val = 100);
	int showMenu(SDL_Surface* des, TTF_Font* font);
	bool checkFocusWitchRect(const int& x, const int& y, const SDL_Rect& rect);
}


#endif