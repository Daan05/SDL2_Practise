#include "SDL2_Application.h"

Application::Application(const char* _title)
{
	// Assigns a value to the variables
	// Most will be assigned later, so NULL for now
	window = NULL;
	renderer = NULL;

	screen_surface = NULL;
	ground_surface = NULL;
	startscreen = NULL;

	pixelFormat = NULL;

	startscreenRect = { 270, 150, 540, 300 };
	groundRect = { 0, 540, 60, 60 };

	player = NULL;

	title = _title;
	quit = false;

	gamestate = STARTSCREEN;
}
Application::~Application()
{
	std::cout << "Game ended" << "\n";
}

bool Application::Init()
{
	bool success = true;

	// Init SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL2 could not initialize! SDL_Error: " << SDL_GetError() << "\n";
		success = false;
	}
	// If Init was succes
	else
	{
		//Create window
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
			success = false;
		}
		else
		{
			// What you see
			screen_surface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

bool Application::Loadmedia()
{
	bool success = true;

	//Loads and optimizes all images	#2
	ground_surface = IMG_Load("Ground_surface.png");
	if (ground_surface == NULL)
	{
		std::cout << "Unable to load the image! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else
	{
		pixelFormat = ground_surface->format;
	}
	ground_surface = SDL_ConvertSurface(ground_surface, pixelFormat, 0);

	startscreen = IMG_Load("Startscreen.png");
	if (startscreen == NULL)
	{
		std::cout << "Unable to load the image! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	startscreen = SDL_ConvertSurface(startscreen, pixelFormat, 0);

	return success;
}

void Application::Close()
{
	std::cout << "game closing" << "\n";

	// Clear surfaces
	SDL_FreeSurface(screen_surface);
	screen_surface = NULL;
	SDL_FreeSurface(ground_surface);
	ground_surface = NULL;

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Delete player
	delete player;

	// Quit SDL2
	SDL_Quit();
}

void Application::Startscreen()
{
	// Make screen lightgray	
	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(pixelFormat, 220, 220, 220));

	// Print startscreen
	SDL_BlitScaled(startscreen, NULL, screen_surface, &startscreenRect);

	// Update screen
	UpdateScreen();
}

void Application::GoToMainGame()
{
	// Go to main game and create a player instance
	gamestate = MAIN_GAME;
	player = new Player();

	// Deallocates the startscreen from memory
	SDL_FreeSurface(startscreen);
	startscreen = NULL;

	std::cout << "Now in main game" << "\n";
}

void Application::MainGame()
{
	// handle player gravity
	player->HandleGravity();

	// Draw everything to the screen
	Draw();

	// Update the screen
	UpdateScreen();
}

void Application::Draw()
{
	// CLean screen gray
	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(pixelFormat, 160, 160, 160));

	// Draw the ground
	while (groundRect.x < SCREENWIDTH)
	{
		SDL_BlitScaled(ground_surface, NULL, screen_surface, &groundRect);
		// Go from left to right
		groundRect.x += 60;
	}
	// Go back to left side of screen
	groundRect.x = 0;

	// Draw player	#just a blue square
	SDL_FillRect(screen_surface, player->GetRect(), SDL_MapRGB(pixelFormat, 160, 0, 0));
}
	
void Application::UpdateScreen()
{
	// Update the screen	#makes you see the changes
	SDL_UpdateWindowSurface(window);
}