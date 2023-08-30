#include "Common_function.h"
#include "Text_Object.h"


bool SDLcommonfunction::checkFocusWitchRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}


int SDLcommonfunction::showMenu(SDL_Surface* des, TTF_Font* font)
{
    g_img_menu = LoadImage("menu_game.png");
    if (g_img_menu == NULL)
    {
        return 1;
    }

    const int kMenuItemNum = 3;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x =250;
    pos_arr[0].y = 370;

    pos_arr[1].x = 520;
    pos_arr[1].y = 370;

    pos_arr[2].x = 820;
    pos_arr[2].y = 370;

    TEXT_OBJECT text_menu[kMenuItemNum];

    text_menu[0].set_text("PLAY");
    text_menu[0].set_color(TEXT_OBJECT::WHITE_TEXT);
    text_menu[0].SETrect(pos_arr[0].x, pos_arr[0].y);


    text_menu[1].set_text("RESUME");
    text_menu[1].set_color(TEXT_OBJECT::WHITE_TEXT);
    text_menu[1].SETrect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].set_text("EXIT");
    text_menu[2].set_color(TEXT_OBJECT::WHITE_TEXT);
    text_menu[2].SETrect(pos_arr[2].x, pos_arr[2].y);

    bool selected[kMenuItemNum] = { 0,0 };
    int x_m = 0;
    int y_m = 0;
    SDL_Event m_event;

    SDL_Color boxColors[kMenuItemNum] = {
    {248,211,24},   // Màu đỏ cho hộp chứa "Play Game"
    {19,178,243},   // Màu xanh lá cho hộp chứa "Resume"
    {228,23,24}    // Màu xanh dương cho hộp chứa "Exit"
    };


    while (true)
    {
        SDLcommonfunction::ApplySurface(g_img_menu, des, 0, 0);
      

        for (int i = 0; i < kMenuItemNum; i++)
        {
            //SDL_Rect boxRect = { pos_arr[i].x - 10, pos_arr[i].y - 10, text_menu[i].GETrect().w + 20, text_menu[i].GETrect().h + 20 };

            //SDL_Color boxColor = boxColors[i];
            //Uint32 sdlBoxColor = SDL_MapRGB(des->format, boxColor.r, boxColor.g, boxColor.b);
            //SDL_FillRect(des, &boxRect, sdlBoxColor);

            //// Vẽ văn bản lên hộp chứa
            //text_menu[i].CreateGameText(font, des);

            SDL_Rect boxRect = { pos_arr[i].x - 10, pos_arr[i].y - 10, text_menu[i].GETrect().w + 20, text_menu[i].GETrect().h + 20 };
            SDL_Color boxColor = boxColors[i];
          Uint32 sdlBoxColor = SDL_MapRGB(des->format, boxColor.r, boxColor.g, boxColor.b);
          SDL_FillRect(des, &boxRect, sdlBoxColor);

          

            // Vẽ góc bo tròn
            SDL_Rect topLeft = { boxRect.x, boxRect.y, 10, 10 };
            SDL_Rect topRight = { boxRect.x + boxRect.w - 10, boxRect.y, 10, 10 };
            SDL_Rect bottomLeft = { boxRect.x, boxRect.y + boxRect.h - 10, 10, 10 };
            SDL_Rect bottomRight = { boxRect.x + boxRect.w - 10, boxRect.y + boxRect.h - 10, 10, 10 };

            Uint32 cornerColor = SDL_MapRGB(des->format, 52, 23, 77); // Màu góc bo tròn
            SDL_FillRect(des, &topLeft, cornerColor);
            SDL_FillRect(des, &topRight, cornerColor);
            SDL_FillRect(des, &bottomLeft, cornerColor);
            SDL_FillRect(des, &bottomRight, cornerColor);

            // Vẽ văn bản lên hộp chứa
            text_menu[i].CreateGameText(font, des);
        }

       
      

        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                x_m = m_event.motion.x;
                y_m = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (checkFocusWitchRect(x_m, y_m, text_menu[i].GETrect()))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].set_color(TEXT_OBJECT::BLACK_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].set_color(TEXT_OBJECT::WHITE_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                x_m = m_event.button.x;
                y_m = m_event.button.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (checkFocusWitchRect(x_m, y_m, text_menu[i].GETrect()))
                    {
                       
                        return i;
                       
                    }
                }
            }

          


            break;
          
            default:
                break;
            }

        }

      
        SDL_Flip(des);

    }
    return 1;
}


//hàm LoadImage để thực hiện việc load các image 
SDL_Surface* SDLcommonfunction::LoadImage(std::string file_path)
{
    SDL_Surface* load_image = NULL;
    SDL_Surface* optimize_image = NULL;
    load_image = IMG_Load(file_path.c_str());
    if (load_image != NULL)
    {
        optimize_image = SDL_DisplayFormat(load_image);
        SDL_FreeSurface(load_image);
        if (optimize_image != NULL)
        {
            UINT32 color_key = SDL_MapRGB(optimize_image->format, 0,0, 0);// 0xFF
            SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
        }
    }
    return optimize_image;
}
// hàm ApplySurface thực hiện load Image vào màn hình screen.
SDL_Rect SDLcommonfunction::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);

    return offset;
}


void SDLcommonfunction::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, clip, des, &offset);
}

bool SDLcommonfunction::checkCollision(const SDL_Rect& object_1, const SDL_Rect& object_2)
{
    int left_a = object_1.x;
    int right_a = object_1.x + object_1.w;
    int top_a = object_1.y;
    int bottom_a = object_1.y + object_1.h;

    int left_b = object_2.x;
    int right_b = object_2.x + object_2.w;
    int top_b = object_2.y;
    int bottom_b = object_2.y + object_2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

int SDLcommonfunction::MakeRandValue(const int& div_val /*400*/)
{
    int rand_y = rand() % div_val;  // sinh so tu 0 ->  div_val
    if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT) // phạm vi từ 200 trở về 0 , khỏi đụng đất 
    {
        rand_y = SCREEN_HEIGHT * 0.3;
    }
    return rand_y;
}

int SDLcommonfunction::MakeRandValue_for_items(const int& div_val /*400*/)
{
    int rand_y = rand() % div_val;  // sinh so tu 0 ->  div_val
    if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT) // phạm vi từ 200 trở về 0 , khỏi đụng đất 
    {
        rand_y = SCREEN_HEIGHT * 0.8;
    }
    return rand_y;
}




// hàm giải phóng các đối tượng biến global
void SDLcommonfunction::CleanUp()
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_bkground);
}