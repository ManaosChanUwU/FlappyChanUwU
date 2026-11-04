#include <iostream>
#include <cstdlib>
#include <ctime>
#include "raylib.h"

//separar los archivos y arreglar el desastre de las funciones
//hacer bien el menu y los creditos
//poner tags
//ver como se ponen tags
//preparar release sin consola
//buscar fondos para aprovechar el paralax


using namespace std;

struct Player
{
	float positionX;
	float positionY;
	int points;
	float rectangleSize;
	float speedY;
	float flappForce;
	float gravity;
};

struct Obstacle
{
	float positionX;
	float positionY;
	float speedX;
	float sizeY;
	float sizeX;
};


void startObstacle(Obstacle& obstacle, Obstacle& obstacle2, int screenWidth, int screenHeight)
{
	//obstáculo superior
	obstacle.sizeX = 50;
	obstacle.sizeY = rand() % (screenHeight / 2) + (screenHeight / 8);
	obstacle.positionX = screenWidth;
	obstacle.positionY = 0;
	obstacle.speedX = 150;

	//obstáculo inferior
	obstacle2.sizeX = 50;
	obstacle2.positionX = obstacle.positionX;
	obstacle2.positionY = obstacle.sizeY + 300;//para ej juego final dejar en 150 o 200, y hacer una variable a parte
	obstacle2.sizeY = screenHeight - obstacle2.positionY;
	obstacle2.speedX = obstacle.speedX;
}


void startGame(Player& player, int screenWidth, int screenHeight)
{
	float margin = screenWidth * 0.05f;

	player.positionX = margin;
	player.rectangleSize = 50;
	player.positionY = (screenHeight / 2) - (player.rectangleSize / 2);

	player.points = 0;
	player.speedY = 0;
	player.gravity = 300;
	player.flappForce = -200;
}

void playerMovement(Player& player, const int screenHeight);

void obstacleMovement(Obstacle& obstacle, Obstacle& obstacle2, const int screenWidth, const int screenHeight);

bool colisionCheck(Obstacle obstacle, Obstacle obstacle2, Player player);


enum GameScreen { MENU, PLAY, CREDITS, TUTORIAL, EXIT, VICTORY, LOSE };

void loseConditions(const Obstacle& obstacle, const Obstacle& obstacle2, Player& player, bool& isRunning, const int screenHeight);

int main()
{
	srand(time(0));

	const int screenWidth = 1080;
	const int screenHeight = 720;

	bool isRunning = true;

	InitWindow(screenWidth, screenHeight, "Flappy Chan UwU");

	Player player;
	Obstacle obstacle;
	Obstacle obstacle2;
	GameScreen actualScreen = MENU;

	int selector;

	startGame(player, screenWidth, screenHeight);
	startObstacle(obstacle, obstacle2, screenWidth, screenHeight);

	while (!WindowShouldClose() && isRunning)
	{


		if (actualScreen == MENU)
		{
			if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1))
			{
				startGame(player, screenWidth, screenHeight);
				actualScreen = PLAY;
			}
			if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
			{
				actualScreen = CREDITS;
			}
		}
		else if (actualScreen == CREDITS)
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				actualScreen = MENU;
			}
		}
		//actualizacion
		else if (actualScreen == PLAY)
		{
			playerMovement(player, screenHeight);
			obstacleMovement(obstacle, obstacle2, screenWidth, screenHeight);
			loseConditions(obstacle, obstacle2, player, isRunning, screenHeight);
		}





		//dibujado

		BeginDrawing();

		ClearBackground(BLACK);


		if (actualScreen == MENU)
		{
			DrawText("PONG", screenWidth / 2, screenHeight * 0.2, 100, WHITE);
			DrawText("1. JUGAR", screenWidth / 2, screenHeight * 0.5, 40, GREEN);
			DrawText("2. CREDITOS", screenWidth / 2, screenHeight * 0.6, 40, YELLOW);
		}
		else if (actualScreen == PLAY)
		{
			//jugador
			DrawRectangle(player.positionX, player.positionY, player.rectangleSize, player.rectangleSize, WHITE);

			//obstáculo superior
			DrawRectangle(obstacle.positionX, obstacle.positionY, obstacle.sizeX, obstacle.sizeY, WHITE);

			//obstáculo inferior
			DrawRectangle(obstacle2.positionX, obstacle2.positionY, obstacle2.sizeX, obstacle2.sizeY, WHITE);
		}

		//version
		DrawText("V0.1", 0, 0, 20, WHITE);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}

//practicar ingles:c
//hacer pantallas de derrota y luego volver al menu
void loseConditions(const Obstacle& obstacle, const Obstacle& obstacle2, Player& player, bool& isRunning, const int screenHeight)
{
	//colisiones
	if (colisionCheck(obstacle, obstacle2, player))
	{
		cout << "Acontecio una colision" << endl;
		isRunning = false;
	}
	//piso
	if (player.positionY > screenHeight)
	{
		cout << "Perdiste: tocaste el suelo" << endl;
		isRunning = false;
	}
}


void obstacleMovement(Obstacle& obstacle, Obstacle& obstacle2, const int screenWidth, const int screenHeight)
{
	// Calculamos cuánto se desplazan durante este frame
	float movement = obstacle.speedX * GetFrameTime();

	obstacle.positionX -= movement;
	obstacle2.positionX = obstacle.positionX;
	if (obstacle.positionX + obstacle.sizeX < 0)
	{
		obstacle.positionX = screenWidth;
		obstacle.sizeY = rand() % (screenHeight / 2) + (screenHeight / 8);
		obstacle2.positionY = obstacle.sizeY + 300;//para ej juego final dejar en 150 o 200
		obstacle2.sizeY = screenHeight - obstacle2.positionY;
		cout << obstacle.sizeY;
	}
}


void playerMovement(Player& player, const int screenHeight)
{
	if (IsKeyPressed(KEY_W))
	{
		player.speedY = player.flappForce;
	}
	player.speedY += player.gravity * GetFrameTime();
	player.positionY += player.speedY * GetFrameTime();
	//techo
	if (player.positionY < 0)
	{
		player.positionY = 0;
		player.speedY = 0;
	}
}

//colisones
bool colisionCheck(Obstacle obstacle, Obstacle obstacle2, Player player)
{
	//Colisión horizontal con el obstáculo superior
	bool colisionX1 = obstacle.positionX + obstacle.sizeX > player.positionX && obstacle.positionX < player.positionX + player.rectangleSize;

	//Colisión vertical con el obstáculo superior
	bool colisionY1 = obstacle.positionY + obstacle.sizeY > player.positionY && obstacle.positionY < player.positionY + player.rectangleSize;

	//Colisión horizontal con el obstáculo inferior
	bool colisionX2 = obstacle2.positionX + obstacle2.sizeX > player.positionX && obstacle2.positionX < player.positionX + player.rectangleSize;

	//Colisión vertical con el obstáculo inferior
	bool colisionY2 = obstacle2.positionY + obstacle2.sizeY > player.positionY && obstacle2.positionY < player.positionY + player.rectangleSize;

	//Si choca con cualquiera de los dos, devuelve true
	return (colisionX1 && colisionY1) || (colisionX2 && colisionY2);
}
