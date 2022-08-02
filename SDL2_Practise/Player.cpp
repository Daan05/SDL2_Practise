#include "Player.h"

Player::Player()
{
	// Assigns a value to the variables
	y = 440;
	playerRect = { 100, (int) y, 50, 100 };
	speed = 10;
	gravity = 0;
	std::cout << "Player created" << "\n";
}

Player::~Player()
{
	std::cout << "Player destroyed" << "\n";
}

SDL_Rect* Player::GetRect()
{
	// Returns a rect pointer of the player
	playerRect = { playerRect.x, (int) y, playerRect.w, playerRect.h };
	return &playerRect;
}

int Player::GetSpeed()
{
	// Returns speed;
	return speed;
}

float Player::GetY()
{
	// Returns y
	return y;
}

void Player::ChangeX(int _x)
{
	// Change the player x
	playerRect.x += _x;
}

void Player::ChangeY(float _y)
{
	// Change the player y	#applies gravity
	y -= _y;
}

void Player::Jump()
{
	// Only jump if player on ground
	if (IsOnGround()) gravity = -8;
}

void Player::HandleGravity()
{
	// Apply gravity to player
	ChangeY(-gravity);

	// Jump physics
	if (gravity < 8.0f)
		gravity += 0.2f;

	// If on ground dont go further down
	if (IsOnGround())
		gravity = 0.0f;
}

bool Player::IsOnGround()
{
	// When y > 440, the player is on the ground
	if (y > 440) return true;
	return false;
}