#include "../header/MainMenu.h"
#include "../header/Game.h"
#include "../header/Status.h"
#include <iostream>
//Load image into windows : 1. Create Surface of that img -> 2. Create texture from that surface -> 3. Copy to renderer


int main(int argv, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3);	
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

	int width = 1900;
	int height = 900;

	Mix_Music * BG_Music = Mix_LoadMUS("./Music/BG_Music.mp3");
	SDL_Window * window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	status s = menu;

	Mix_PlayMusic(BG_Music, -1);
	if(BG_Music == NULL) std::cout<<1;
	
	MainMenu * main_menu = new MainMenu(width, height, window, renderer);
	Game * game = new Game(width, height, window, renderer, pvp);

    while (s != end)
    {
		switch (s)
		{
		case menu:
			s = main_menu->Display();
			break;
		case pvp:
			game->game_mode = pvp;
			s = game->Display();
			break;
		case pvc:
			game->game_mode = pvc;
			s = game->Display();
			break;
		default:
			break;
		}
    }

	//SDL_Log();
	delete main_menu;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

/*
//my animation linear interpol function
double GetPos(double started, double begin, double end, double duration)
{
    return 10;

}

int main(int argc, char* argv[])
{
    //init SDL system
    SDL_Init(SDL_INIT_EVERYTHING);

    //create windows
    SDL_Window * wnd = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, SDL_RENDERER_PRESENTVSYNC);

    //create renderer in my case this is D3D9 renderer, but this behavior is the same with D3D11 and OPENGL

    SDL_Renderer* renderer = SDL_CreateRenderer(wnd, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);

    //load image and create texture
    SDL_Surface* surf = IMG_Load("./image/Ball/ball.png");

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    //get rid of surface we dont need surface anymore
    SDL_FreeSurface(surf);

    SDL_Event event;
    int action = 0;
    bool done = false;

    //animation time start and duration
    double time_start = (double) SDL_GetTicks();
    double duration = 15000;

	double myX = 0;
    //loop render
    while (!done)
    {
        action = 0;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_KEYDOWN:
                action = event.key.keysym.sym;
                break;
            }
        }

        switch (action)
        {
        case SDLK_q:
            done = 1;
        default:
            break;
        }

        //clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //calculate new position
        myX += GetPos(time_start, 10, 1000, duration);

        SDL_Rect r;

        //assaign position
        r.x = (int) round(myX);
        r.y = 10;
        r.w = 50;
        r.h = 50;

        //render to rendertarget
        SDL_RenderCopy(renderer, tex, 0, &r);

        //present
        SDL_RenderPresent(renderer);


    }

    //cleanup
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(wnd);


    SDL_Quit();

    return 0;
}*/

