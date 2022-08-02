#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL2_Application.h"

int main(int argc, char* args[])
{
	// Application
	Application app("SDL2 Game");

	// Initialize SDL2 + window
	if (!app.Init())
	{
		std::cout << "Failed to initialize!" << "\n";
		SDL_Delay(2000);
		return 0;
	}

	// Load media
	if (!app.Loadmedia()) std::cout << "Failed to load media!" << "\n";

	// Events
	SDL_Event e;

	// Game loop
	while (!app.quit)
	{
		// Loop through events
		while (SDL_PollEvent(&e) != 0)
		{
			// Quit
			if (e.type == SDL_QUIT)
			{
				app.quit = true;
			}

			// Something pressed events
			if (e.type = SDL_KEYDOWN)
			{
				// Mouse click events
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (app.gamestate == STARTSCREEN)
					{
						app.GoToMainGame();
					}
				}

				// Check in main game
				if (app.gamestate == STARTSCREEN)
					break;

				// Player movement
				// Back
				if (e.key.keysym.sym == SDLK_LEFT)
					app.player->ChangeX(-app.player->GetSpeed());
				// Forward
				if (e.key.keysym.sym == SDLK_RIGHT)
					app.player->ChangeX(app.player->GetSpeed());
				// jump
				if (e.key.keysym.sym == SDLK_SPACE)
					app.player->Jump();
			}
		}

		// Game functions
		switch (app.gamestate)
		{
		case STARTSCREEN:
			app.Startscreen();
			break;

		case MAIN_GAME:
			app.MainGame();
			break;
		}
	}

	// CLean up and close application
	app.Close();
	return 0;
}