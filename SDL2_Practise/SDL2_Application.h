#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Player.h"

// Gamestates
enum Gamestate
{
	STARTSCREEN,
	MAIN_GAME
};

class Application
{
public:
	Application(const char* _title);
	~Application();

	bool quit;

	bool Init();
	bool Loadmedia();
	void Close();

	void Startscreen();
	void GoToMainGame();
	void MainGame();

	void Draw();

	void UpdateScreen();

	Gamestate gamestate;

	Player* player;

private:
	const int SCREENWIDTH = 1080;
	const int SCREENHEIGHT = 600;

	const char* title;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Surface* screen_surface;
	SDL_Surface* ground_surface;
	SDL_Surface* startscreen;

	SDL_Rect startscreenRect;
	SDL_Rect groundRect;

	SDL_PixelFormat* pixelFormat;
};