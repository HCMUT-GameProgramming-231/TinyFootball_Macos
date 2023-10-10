#include "../header/MainMenu.h"

//prototype implementation

MainMenu::MainMenu(int width, int height, SDL_Window * window, SDL_Renderer * renderer)
{
	this->window = window;
	this->renderer = renderer;

	//background
	Rectangle bg_rect = Rectangle(Vector(width / 2, height / 2), width - 100, height - 200);
	this->bg_sprite =  new Sprite<Rectangle>("./image/BG/BG3.png", this->renderer, bg_rect);

	//button
	Rectangle PvP = Rectangle(Vector(width / 2, height / 2 - 70), 250, 50);
	this->buttons[0] = new Sprite<Rectangle>("./image/Button/PvP_button.png", this->renderer, PvP, "pvp");

	Rectangle PvC = Rectangle(Vector(width / 2, height / 2), 250, 50);
	this->buttons[1] =  new Sprite<Rectangle>("./image/Button/PvC_button.png", this->renderer, PvC, "pvc");

	Rectangle Exit = Rectangle(Vector(width / 2, height / 2 + 70), 250, 50);
	this->buttons[2] = new Sprite<Rectangle>("./image/Button/exit_button.png", this->renderer, Exit, "exit");



	//cursor
	SDL_Rect cursor_rect = {0, 0, 50, 50};

	//default cursor
	SDL_Surface * surface = IMG_Load("./image/Cursor/default.png");
	SDL_Surface * scaled = SDL_CreateRGBSurface(0, 50, 50, 32, 0xff, 0xff00, 0xff0000, 0xff000000); //transparent surface
	SDL_BlitScaled(surface, NULL, scaled, &cursor_rect);
	this->default_cursor = SDL_CreateColorCursor(scaled, 10, 5);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(scaled);

	//hovering cursor
	surface = IMG_Load("./image/Cursor/hovering.png");
	scaled = SDL_CreateRGBSurface(0, 50, 50, 32, 0xff, 0xff00, 0xff0000, 0xff000000); 
	SDL_BlitScaled(surface, NULL, scaled, &cursor_rect);
	this->hovering_cursor = SDL_CreateColorCursor(scaled, 15, 5);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(scaled);

	this->window_width = width;
	this->window_height = height;
}


MainMenu::~MainMenu()
{
	delete this->bg_sprite;
	for(int i = 0; i < 3; i++) delete this->buttons[i];
}

status MainMenu::Display()
{
	status s = menu;
	SDL_Event event;
	CollisionDectector detector = CollisionDectector();
	bool hovering= false;
	std::string current_button = "";

	//background init
	SDL_Surface * grass_surf = IMG_Load("./image/BG/grass_3.png");
	SDL_Texture * grass_texture = SDL_CreateTextureFromSurface(this->renderer, grass_surf);
	SDL_FRect bg_rect = this->bg_sprite->shape.get_rect();
	SDL_FreeSurface(grass_surf);

	//init for cursor
	int cur_pos_x, cur_pos_y;
	Rectangle cursor_rect;


	//Hide default cursor

	while (s == menu)
	{
		hovering = false;
		current_button = "";
		//render background
		//last args is position and size of img to draw , NULL = full windows
		//std:: cout << rect.x << " "<< rect.y << " "<< rect.h << " "<< rect.w<<std::endl;
		SDL_RenderCopyF(this->renderer, grass_texture, NULL, NULL);
        SDL_RenderCopyF(this->renderer, this->bg_sprite->texture, NULL, NULL);
		
		//render button
		for(int i = 0; i < 3; i++)
		{
			SDL_FRect button_rect = this->buttons[i]->shape.get_rect();
			SDL_RenderCopyF(this->renderer, this->buttons[i]->texture, NULL, &button_rect);
			if(detector.RectAndRect(this->buttons[i]->shape, cursor_rect)) hovering = true;
			else hovering = false;
		}
		
		//cursor
		//Create cursor rectangle
		
		SDL_GetMouseState(&cur_pos_x, &cur_pos_y);
		cursor_rect = Rectangle(Vector(cur_pos_x, cur_pos_y), 10, 10);

		//check_hover
		for(int i = 0; i < 3; i++)
		{
			if(detector.RectAndRect(this->buttons[i]->shape, cursor_rect)) 
			{
				hovering = true;
				current_button = this->buttons[i]->name;
				break;
			}
		}

		if(hovering) SDL_SetCursor(this->hovering_cursor);
		else SDL_SetCursor(this->default_cursor);

		/*
		//vùng màu đen xanh quanh cursor là vùng ckicj có hiệu lực
		SDL_Rect reg = cursor_rect.get_rect();
		SDL_Surface * surf = SDL_CreateRGBSurface(0, reg.w, reg.h, 32, 0, 0, 0, 0);
		SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0, 0, 255));
		SDL_Texture * reg_t = SDL_CreateTextureFromSurface(this->renderer, surf);
		SDL_RenderCopy(this->renderer, reg_t, NULL, &reg);
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(reg_t);*/

	

		while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
				case SDL_QUIT:
					s = end;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (hovering)
					{
						if (current_button == "exit") s = end;
						else if (current_button == "pvp") s = pvp;
						else if (current_button == "pvc") s = pvc;
					}
					break;
            }
        }



		SDL_RenderPresent(renderer);
	}
	
	Mix_PauseMusic();

	SDL_DestroyTexture(grass_texture);
	return s;
}