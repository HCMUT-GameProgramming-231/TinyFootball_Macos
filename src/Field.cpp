#include "../header/Field.h"


Field::Field(int width, int height, SDL_Renderer * renderer)
{
	this->width = width;
	this->height = height;

	//field
	Rectangle field_rect = Rectangle(Vector(width / 2, height / 2), width, height);
	this->field =  new Sprite<Rectangle>("./image/BG/BG3.png", renderer, field_rect);

	SDL_Surface * grass_surf = IMG_Load("./image/BG/grass_3.png");
	this->grass  = SDL_CreateTextureFromSurface(renderer, grass_surf);

	//init for edge
	SDL_FRect rect = this->field->shape.get_rect();
	float x = rect.x;
	float y = rect.y;
	float w = rect.w;
	float h = rect.h;

	//upper wind
	SDL_FRect wind_rect = {x + 20, y + 110, w - 50, 100};
	this->upper_wind = Wind(Vector(0, 1), 0, 40, wind_rect);
	//std::cout<<this->upper_wind.direction.x<< " "<<this->upper_wind.direction.y<<std::endl;

	//lower wind 
	wind_rect = {x + 20, y + h - 210, w - 50, 100};
	this->lower_wind = Wind(Vector(0, -1), 0, 40, wind_rect);

	//upper edge
	this->upper_edge = Rectangle(Vector(x + w / 2, y + 100), w - 50, 20);

	//lower edge
	this->lower_edge = Rectangle(Vector(x + w / 2, y + h - 100), w - 50, 20);

	//left edge 1
	this->left_edge_1 = Rectangle(Vector(x + 60, y - 70), 20, h - 50);

	//left edge 2
	this->left_edge_2 = Rectangle(Vector(x + 60, y + h + 70), 20, h - 50);

	//right edge 1
	this->right_edge_1 = Rectangle(Vector(x + w - 60, y - 70), 20, h - 50);

	//right edge 2
	this->right_edge_2 = Rectangle(Vector(x + w - 60, y + h + 70), 20, h - 50);

}

void Field::Display(SDL_Renderer * renderer)
{
	SDL_RenderCopyF(renderer, this->grass, NULL, NULL);
	SDL_RenderCopyF(renderer, this->field->texture, NULL, NULL);

	// SDL_FRect frect = this->upper_wind.range;
	// SDL_RenderFillRectF(renderer, &frect);

	//frect = this->lower_wind.range;
	 //SDL_RenderFillRectF(renderer, &frect);

	/*
	//upper
	SDL_FRect frect = this->upper_edge.get_rect();
	SDL_RenderFillRectF(renderer, &frect);

	//lower
	frect = this->lower_edge.get_rect();
	SDL_RenderFillRectF(renderer, &frect);

	//left 1
	frect = this->left_edge_1.get_rect();
	SDL_RenderFillRectF(renderer, &frect);

	//left 2
	frect = this->left_edge_2.get_rect();
	SDL_RenderFillRectF(renderer, &frect);

	//right 1
	frect = this->right_edge_1.get_rect();
	SDL_RenderFillRectF(renderer, &frect);

	//right 2
	frect = this->right_edge_2.get_rect();
	SDL_RenderFillRectF(renderer, &frect);
	*/
}

Field::~Field()
{
	delete this->field;
	SDL_DestroyTexture(this->upper_lower_edge_texture);
}