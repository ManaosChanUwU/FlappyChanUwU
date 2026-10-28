#include <iostream>
#include "raylib.h"

using namespace std;

struct Player {
	float positionX;
	float positionY;
	int points;
	float rectangleSize;
	float speedY;
	float flappForce;
	float gravity;
};

struct Obstacle {
	float positionX;
	float positionY;
	float speedX;
	float size;
};


void startObstacle(Obstacle& obstacle, int screenWidth, int screenHeight)
{
	obstacle.positionX = screenWidth / 2 - obstacle.size / 2;
	obstacle.positionY = screenHeight / 2 - obstacle.size / 2;	
	obstacle.speedX = -100 * GetFrameTime();
}

void startGame(Player& player, Obstacle& obstacle, int screenWidth, int screenHeight)
{
	//tamaño de tablas y margen horizontal
	float margin = screenWidth * 0.05f;

	//inicio jugador 1
	player.positionX = margin;
	player.rectangleSize = 50;
	player.positionY = (screenHeight / 2) - (player.rectangleSize / 2);
	player.points = 0;


	//pelota
	obstacle.size = 50;
	startObstacle(obstacle, screenWidth, screenHeight);
}

int main()
{
	const int screenWidth = 1080;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "Flappy Chan UwU");

	Player player;
	Obstacle obstacle;

	while (!WindowShouldClose())
	{
		startGame(player, obstacle, screenWidth, screenHeight);
		startObstacle(obstacle, screenWidth, screenHeight);
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangle(player.positionX, player.positionY, player.rectangleSize, player.rectangleSize, WHITE);
		DrawRectangle(obstacle.positionX, obstacle.positionY, obstacle.size, player.rectangleSize, WHITE);

		EndDrawing();
	}

}
