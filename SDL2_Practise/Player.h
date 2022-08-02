#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player
{
public:
	Player();
	~Player();

	void ChangeX(int _x);
	void ChangeY(float _y);

	SDL_Rect* GetRect();
	int GetSpeed();
	float GetY();

	void Jump();
	void HandleGravity();
	bool IsOnGround();
private:
	SDL_Rect playerRect;
	int speed;
	float gravity;
	float y;
};