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
	obstacle.positionX = screenWidth - obstacle.size / 2;
	obstacle.positionY = screenHeight / 2 - obstacle.size / 2;
	obstacle.speedX = 150;
}

void startGame(Player& player, Obstacle& obstacle, int screenWidth, int screenHeight)
{
	//margen de pantalla
	float margin = screenWidth * 0.05f;

	//inicio jugador
	player.positionX = margin;
	player.rectangleSize = 50;
	player.positionY = (screenHeight / 2) - (player.rectangleSize / 2);
	player.points = 0;
	player.speedY = 300;

	//obsaculo
	obstacle.size = 50;
	startObstacle(obstacle, screenWidth, screenHeight);
}

void playerMovement(Player& player, const int screenHeight);

void obstacleMovement(Obstacle& obstacle, Player& player, const int screenWidth);

bool colisionCheck(Obstacle obstacle, Player player);

int main()
{
	const int screenWidth = 1080;
	const int screenHeight = 720;
	bool isRunning = true;
	InitWindow(screenWidth, screenHeight, "Flappy Chan UwU");

	Player player;
	Obstacle obstacle;

	startGame(player, obstacle, screenWidth, screenHeight);
	while (!WindowShouldClose() && isRunning)
	{

		//actualizacion
		playerMovement(player, screenHeight);
		obstacleMovement(obstacle, player, screenWidth);

		//coliciones
		if (colisionCheck(obstacle, player))
		{
			cout << "acontece una colicion" << endl;
			isRunning = false;
		}


		//dibujado
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangle(player.positionX, player.positionY, player.rectangleSize, player.rectangleSize, WHITE);
		DrawRectangle(obstacle.positionX, obstacle.positionY, obstacle.size, obstacle.size, WHITE);
		DrawText("V0.1", 0, 0, 20, WHITE);
		EndDrawing();
	}

}

void obstacleMovement(Obstacle& obstacle, Player& player, const int screenWidth)
{
	obstacle.positionX -= obstacle.speedX * GetFrameTime();
	if (obstacle.positionX < 0 - obstacle.size)
	{
		obstacle.positionX = screenWidth;
	}
}

void playerMovement(Player& player, const int screenHeight)
{
	if (player.positionY > 0 && IsKeyDown(KEY_W))
	{
		player.positionY -= player.speedY * GetFrameTime();
	}
	//abajo
	if (player.positionY < screenHeight - player.rectangleSize && IsKeyDown(KEY_S))
	{
		player.positionY += player.speedY * GetFrameTime();
	}
}

bool colisionCheck(Obstacle obstacle, Player player)
{
	//si la pelota "toca" el la tabla
	bool colisionX = ((obstacle.positionX + obstacle.size > player.positionX) && obstacle.positionX < player.positionX + player.rectangleSize);
	//si la pelota se encuentra dentro de el espacio que ocupa la tabla en y
	bool colisionY = ((obstacle.positionY + obstacle.size > player.positionY) && obstacle.positionY < player.positionY + player.rectangleSize);

	return colisionX && colisionY;
}