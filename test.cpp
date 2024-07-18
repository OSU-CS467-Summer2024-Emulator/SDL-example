#include <iostream>
#include <SDL2/SDL.h>
using namespace std;



int speed = 10;
int white[4] = {255, 255, 255, 255};
int blue[4] = {0, 0, 255, 255};
int red[4] = {255, 0, 0, 255};
int green[4] = {0, 255, 0, 255};

int color[4] = {255, 255, 255, 255};
char cur_color = 'w';

void color_cycle(int arr[])
    {
        for (int ii = 0; ii < 4; ii++) 
        {
            color[ii] = arr[ii];
        }
    }

int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Rect r = {10, 10, 20, 20};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_RenderSetScale(renderer, 4, 4);
    SDL_RenderSetLogicalSize(renderer, 640, 480); // Logical size to match the original window size

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            
            // ACTIONS ON KEY PRESS
            else if (e.type == SDL_KEYDOWN) 
            {
                switch(e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        // cout << "RIGHT DOWN" << endl;
                        r.x += speed;
                        break;
                    
                    case SDLK_LEFT:
                        // cout << "LEFT DOWN" << endl;
                        r.x -= speed;
                        break;
                    
                    case SDLK_UP:
                        // cout << "UP DOWN" << endl;
                        if (r.y - 10 > -1)
                        {
                            r.y -= speed;
                        }
                        break;
                    
                    case SDLK_DOWN:
                        // cout << "DOWN DOWN" << endl;
                        r.y += speed;
                        break;

                    case SDLK_p:
                        speed += 10;
                        cout << "Speed increased 10. Speed = " << speed << endl;
                        break;

                    case SDLK_o:
                       
                        if (speed - 10 > 0)
                        {
                            speed -= 10;
                            cout << "Speed decreased 10. Speed = " << speed << endl;
                        }
                        break;

                    case SDLK_1:
                        speed = 10;
                        cout << "Speed set to 10. Speed = " << speed << endl;
                        break;
                }
            }
            
            // ACTIONS ON KEY RELEASE
            else if (e.type == SDL_KEYUP) 
            {
                switch(e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        // cout << "RIGHT UP" << endl;
                        break;
                }
            }

            // MOUSE ACTIONS
            else if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&r.x, &r.y);
            }

            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                cout << r.x << ' ' << r.y << endl;
                if (cur_color == 'w')
                {
                    cur_color = 'r';
                    color_cycle(red);
                }
                else if (cur_color == 'r')
                {
                    cur_color = 'g';
                    color_cycle(green);
                }
                else if (cur_color == 'g')
                {
                    cur_color = 'b';
                    color_cycle(blue);
                }
                else if (cur_color == 'b')
                {
                    cur_color = 'w';
                    color_cycle(white);
                }
               
            }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
        SDL_RenderFillRect(renderer, &r);

        SDL_RenderPresent(renderer);
        }
        SDL_Delay(16); // Delay to avoid high CPU usage
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}