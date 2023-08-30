#include "Common_function.h"
#include "Main_Object.h"
#include "Threat_Object.h"
#include"ExplosionObject.h"
#include "PlayPower.h"
#include "Text_Object.h"
#include"Items.h"
#include<iostream>
#undef main



TTF_Font* g_font_Text = NULL;   // font text
TTF_Font* g_font_Menu = NULL;   // font text


//  hàm Init để khởi tạo các thuộc tính ban đầu.
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == GA_FAILED)
	{
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (g_screen == NULL)
	{
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == GA_FAILED)  // =-1 la sai .
	{
		return false;
	}

	// read file audio
	g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_amo_main); // am thanh cua dan laze
	g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_amo_main2); // am thanhb cua dan tron
	g_sound_exp[0] = Mix_LoadWAV(g_name_audio_exp_threats);
	g_sound_exp[1] = Mix_LoadWAV(g_name_audio_exp_main);
	g_music = Mix_LoadMUS(g_name_audio_nhac_nen);
	g_game_over[0] = Mix_LoadWAV(g_name_audio_game_over);
	g_sound_coil[0] = Mix_LoadWAV(g_name_audio_coil);
	if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL || g_music == NULL || g_game_over == NULL)
	{
		return false;
	}

	// font text
	if (TTF_Init() == GA_FAILED)
	{
		return false;
	}

	g_font_Text = TTF_OpenFont("COMICATE.TTF", 25); // kich thuoc la 20
	g_font_Menu = TTF_OpenFont("ArialCEBold.ttf", 30); // kich thuoc la 30
	if (g_font_Text == NULL || g_font_Menu == NULL)
	{
		return false;
	}
	return true;
}



int main(int arc, char* argv[])
{
	if (quan_ly_start_and_pause == true)
	{
		int bkgn_x = 0;
		bool is_run_screen = true;
		bool is_quit = false;

		if (Init() == false)
			return 0;


		g_bkground = SDLcommonfunction::LoadImage(g_name_bk_ground); // cách 2 : thiết kế 1 ảnh dài luôn 
		if (g_bkground == NULL)
		{
			return 0;
		}




		TEXT_OBJECT time_game;
		time_game.set_color(TEXT_OBJECT::RED_TEXT);

		// text 
		TEXT_OBJECT mark_game;
		mark_game.set_color(TEXT_OBJECT::RED_TEXT);


		//------------------------  MAKE - main object
		MAINOBJECT plane_object;
		plane_object.SETrect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
		bool ret = plane_object.loadImg(g_name_main_obj);
		if (!ret)
		{
			return 0;

		}




		// init explosion object   : main đụng threat thì boom
		EXPLOSION_OBJECT exp_main;
		ret = exp_main.loadImg(g_name_exp_main);
		exp_main.set_clip();
		if (ret == false)
		{
			return 0;
		}

		// init explosion object :dan cua main dung vao threat
		EXPLOSION_OBJECT exp_threat;
		ret = exp_threat.loadImg(g_name_exp_threats);
		exp_threat.set_clip();
		if (ret == false)
		{
			return 0;
		}


		// item
		ITEMOBJECT* items = new ITEMOBJECT[NUM_ITEMS];
		for (int m = 0; m < NUM_ITEMS; m++)
		{
			ITEMOBJECT* p_item = (items + m);
			if (p_item != NULL)
			{
				ret = p_item->loadImg("xu.png");
				if (!ret)
				{
					delete[] items;
					SDLcommonfunction::CleanUp();
					SDL_Quit();
					return 0;
				}

			//	int random_y_item = SDLcommonfunction::MakeRandValue_for_items();
			//	p_item->SETrect(SCREEN_WIDTH + m * VAL_OFFSET_START_POST_ITEMS, random_y_item + 100); // xét vị trí xuất hiện của item ko cung thời điểm
			//	p_item->SET_x_val_IT(SPEED_ITEMS); // set toc do cua item
			}
		}

		//-------------------------- threat object
		THREATOBJECT* p_threats = new THREATOBJECT[NUM_THREAT];
		for (int i = 0; i < NUM_THREAT; i++)
		{
			THREATOBJECT* p_threat = (p_threats + i);
			if (p_threat != NULL)
			{
				ret = p_threat->loadImg(g_name_threats);
				if (!ret)
				{
					delete[] p_threats;
					SDLcommonfunction::CleanUp();
					SDL_Quit();
					return 0;
				}



				int random_y = SDLcommonfunction::MakeRandValue();
				p_threat->SETrect(SCREEN_WIDTH + i * VAL_OFFSET_START_POST_THREATS, random_y); // xét vị trí xuất hiện của threat ko cung thời điểm
				p_threat->SET_x_val(SPEED_THREAT); // set toc do cua threat

				AMOOBJECT* p_amo = new AMOOBJECT();
				p_threat->initamo(p_amo); // nap dan cho threat
			}

		}
		Mix_PlayMusic(g_music, GA_FAILED); // nhac nen 

		//MENU
		unsigned int mark_value = 0; // quan li diem so 
		unsigned int number_coil = 0;



		int ret_menu = SDLcommonfunction::showMenu(g_screen, g_font_Menu);
		if (ret_menu == 2)
		{
			is_quit = true;
		}

		while (!is_quit)
		{




			while (SDL_PollEvent(&g_even))
			{
				if (g_even.type == SDL_QUIT)
				{
					is_quit = true;
					break;
				}

				plane_object.HandleInputAction(g_even);



			}

			SDLcommonfunction::ApplySurface(g_bkground, g_screen, bkgn_x, 0);



			// implement object đe
			plane_object.HandleMove();
			plane_object.show(g_screen);
			plane_object.MakeAmo(g_screen, g_sound_bullet);

			// ITEMS    check va chạm giữa item và plane
			for (int n = 0; n < NUM_ITEMS; n++)
			{
				ITEMOBJECT* p_item = (items + n);
				if (p_item != NULL)
				{
					p_item->HandlMove_IT(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_item->show(g_screen);
				}
				bool va_cham = SDLcommonfunction::checkCollision(p_item->GETrect(), plane_object.GETrect());
				if (va_cham == true)
				{
					Mix_PlayChannel(-1, g_sound_coil[0], 0);

					p_item->reset_IT(SCREEN_WIDTH);	 // xóa item khi va chạm với main 	
					if (SDL_Flip(g_screen) == -1)
					{
						delete[] items;
						SDLcommonfunction::CleanUp();
						SDL_Quit();
						return 0;
					}
				}
			}


			// implement threats object , huong di chuyen cua amo
			for (int ii = 0; ii < NUM_THREAT; ii++)
			{
				THREATOBJECT* p_threat = (p_threats + ii);
				if (p_threat != NULL) // con trỏ thì nên phải kiếm tra khác NULL đề phongf chết chương trình 
				{
					if (ii == 0)
					{
						p_threat->HandlMove(SCREEN_WIDTH, SCREEN_HEIGHT);
						p_threat->show(g_screen);
						p_threat->make_amo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);


					}
					if (ii == 1)
					{
						p_threat->HandlMove(SCREEN_WIDTH, SCREEN_HEIGHT);
						p_threat->show(g_screen);
						p_threat->make_amo_2(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					if (ii == 2)
					{
						p_threat->HandlMove(SCREEN_WIDTH, SCREEN_HEIGHT);
						p_threat->show(g_screen);
						p_threat->make_amo_3(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
					}





					// check collision main and threats
					bool is_col = SDLcommonfunction::checkCollision(plane_object.GETrect(), p_threat->GETrect());
					if (is_col == true)

					{

						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (plane_object.GETrect().x + plane_object.GETrect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (plane_object.GETrect().y + plane_object.GETrect().h * 0.5) - EXP_HEIGHT * 0.5;

							exp_main.set_frame(ex);
							exp_main.SETrect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							// update screen
							if (SDL_Flip(g_screen) == -1)
							{
								delete[] p_threats;
								SDLcommonfunction::CleanUp();
								SDL_Quit();
								return 0;
							}

						}
						Mix_PlayChannel(-1, g_sound_exp[0], 0);
						Mix_PlayChannel(-1, g_game_over[0], 0);
						Mix_HaltMusic();
						if (MessageBox(NULL, L"GAME OVER !", L"INFO", MB_OK) == IDOK)
						{

							delete[] p_threats;
							SDLcommonfunction::CleanUp();
							SDL_Quit();
							return 1;


						}


					}

					// check va cham giua đạn  cua nhan vat chinh va threat

					std::vector<AMOOBJECT*>amo_list = plane_object.GetAmoList();
					ITEMOBJECT* p_item = (items);
					for (int im = 0; im < amo_list.size(); im++)
					{
						AMOOBJECT* p_amo = amo_list.at(im);
					
						if (p_amo != NULL)
						{
							bool ret_col = SDLcommonfunction::checkCollision(p_amo->GETrect(), p_threat->GETrect());
						
							if (ret_col)
							{
								mark_value++; // cong diem cho nhan vat.

								// TEST - boom - main ban dan trung threat
								for (int ex = 0; ex < 4; ex++)
								{
									int x_pos = (p_threat->GETrect().x + p_threat->GETrect().w * 0.5) - EXP_WIDTH * 0.5;
									int y_pos = (p_threat->GETrect().y + p_threat->GETrect().h * 0.5) - EXP_HEIGHT * 0.5;

									exp_threat.set_frame(ex);
									exp_threat.SETrect(x_pos, y_pos);
									exp_threat.ShowEx(g_screen);


									


									// update screen
									if (SDL_Flip(g_screen) == -1)
									{
										delete[] p_threats;
										SDLcommonfunction::CleanUp();
										SDL_Quit();
										return 0;
									}
								}
								
								
									

								//khi 2 thằng va chạm nhau thì threat được reset về vị trí ban đầu, đạn cũng được reset lại
								p_threat->reset(SCREEN_WIDTH + ii * VAL_OFFSET_START_POST_THREATS);
								// dan cua plane ban trung threat
								plane_object.remove_amo(im); // đạn của plane được xóa bỏ 
								Mix_PlayChannel(-1, g_sound_exp[1], 0);



								int x_pos = (p_threat->GETrect().x + p_threat->GETrect().w * 0.5) - EXP_WIDTH * 0.5;
								int y_pos = (p_threat->GETrect().y + p_threat->GETrect().h * 0.5) - EXP_HEIGHT * 0.5;
								std::cout << "\n" << x_pos << "    " << y_pos; 

								
								
							

							}
							
						}
					}

					std::vector<AMOOBJECT*>amo_list2 = p_threat->GetAmoList();
					for (int im = 0; im < amo_list2.size(); im++)
					{
						AMOOBJECT* p_amo2 = amo_list2.at(im);
						if (p_amo2 != NULL)
						{
							bool ret_col = SDLcommonfunction::checkCollision(p_amo2->GETrect(), plane_object.GETrect());
							if (ret_col)
							{
								// boom
								for (int ex = 0; ex < 4; ex++)
								{
									int x_pos = (plane_object.GETrect().x + plane_object.GETrect().w * 0.5) - EXP_WIDTH * 0.5;
									int y_pos = (plane_object.GETrect().y + plane_object.GETrect().h * 0.5) - EXP_HEIGHT * 0.5;

									exp_threat.set_frame(ex);
									exp_threat.SETrect(x_pos, y_pos);
									exp_threat.ShowEx(g_screen);
									SDL_Delay(100);

									// update screen
									if (SDL_Flip(g_screen) == -1)
									{
										delete[] p_threats;
										SDLcommonfunction::CleanUp();
										SDL_Quit();
										return 0;
									}
								}
								//&boom36

								Mix_PlayChannel(-1, g_sound_exp[0], 0);
								Mix_PlayChannel(-1, g_game_over[0], 0);
								Mix_HaltMusic();
								if (MessageBox(NULL, L"GAME OVER !", L"INFO", MB_OK) == IDOK)
								{
									delete[] p_threats;
									SDLcommonfunction::CleanUp();
									SDL_Quit();
									return 1;
								}


							}
						}
					}
				}
			}


			// show time screen
			std::string str_time("Time :");
			UINT32  time_val = SDL_GetTicks() / 1000;
			std::string str_val = std::to_string(time_val);
			str_time += str_val;
			time_game.set_text(str_time);
			time_game.SETrect(SCREEN_WIDTH - 200, 10);
			time_game.CreateGameText(g_font_Text, g_screen);

			// show mark value to screen
			std::string val_string_mark = std::to_string(mark_value); // chuyen tu int sang string
			std::string str_mark("CORE : ");
			str_mark += val_string_mark;

			mark_game.set_text(str_mark);
			mark_game.CreateGameText(g_font_Text, g_screen);

			// update screen
			if (SDL_Flip(g_screen) == -1)

			{
				delete[] p_threats;
				SDLcommonfunction::CleanUp();
				SDL_Quit();
				return 0;
			}

		}

		delete[]p_threats;
		// update screen
		SDLcommonfunction::CleanUp();
		SDL_Quit();
	}
	//------------------------------------------------------------------------------------------------------------- pause============
	

	
	return 1;
}
