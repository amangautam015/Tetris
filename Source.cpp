#include "Header.h"


#define NUMBER_OF_SHAPES 3
#define VK_E 0X45
int AvailableShapes[NUMBER_OF_SHAPES] = { 2,0,1 };
void DisplayFrame(PlayArena& Game);
void MakeGame(PlayArena& Game,Item& It);
void PlayGame(PlayArena& Game);
void AddDump(PlayArena& Game,Item& It,int posX[4], int posY[4]);
void CheckCancel(PlayArena& game);
int main() {

	ScreenC ScreenParam; //Initiliazing Screen
	PlayArena Game;
	PlayGame(Game);
	

	return EXIT_SUCCESS;
}

void DisplayFrame(PlayArena& Game)
{
	//Final Display
	for (int j = 0; j < Game.PLayArea_RightLimit;j++) {
		Game.play_arena[Game.rowsOfConsole - 2][j] = '=';
	}
	for (int i = 0;i < Game.rowsOfConsole;i++) {
		{
			cout << Game.play_arena[i];
		}
	
	}
	
}

void MakeGame(PlayArena& Game,Item& It)
{
	//Build Game
	for (int i = 0;i < Game.rowsOfConsole;i++) {
		Game.play_arena.push_back("");
		for (int j = 0;j < Game.colsOfConsole;j++) {
			if (Game.PLayArea_RightLimit == j) {
				Game.play_arena[i][j] = '|';
				continue;
			}
			if (Game.dump[i][j] == ' ') {
				Game.play_arena[i][j] = ' ';
			}
			else {
				Game.play_arena[i][j] = Game.dump[i][j];
			}
		}
	}


	int ty = It.orientation_type;
	//int X[4];
	//int Y[4];
	//int cX = 0, cY = 0;
	//int c = 0;
	//for (int k = 0; k < It.orientation[ty].length(); k++) {
	//	if ((It.orientation[ty])[k] == '\n') {
	//		cX = 0;
	//		cY++;
	//		continue;
	//	}
	//	else if ((It.orientation[ty])[k] == '2') {
	//		X[c] = It.m_X + cX;
	//		Y[c] = It.m_Y + cY;
	//		cX++;
	//		c++;
	//		continue;
	//	}
	//	else {
	//		cX++;
	//		continue;
	//	}
	//}
	for (int k = 0; k < 4;k++) {
		Game.play_arena[It.m_Y+It.Y[k]][It.m_X+It.X[k]] = '2';
	}
	bool addDump = false;
	for (int k = 0; k < 4;k++) {
		if (Game.dump[It.m_Y + It.Y[k] + 1][It.m_X + It.X[k]] == '0' || It.m_Y + It.orientationHeight[ty] >= Game.rowsOfConsole - 2)
		{
			addDump = true;
			break;
		}

	}
	if (addDump) {
		AddDump(Game, It, It.X, It.Y);
		It.isDown = true;
	}
	/*

	if (It.current_Shape == It.LSHAPE) {
		int height_from_base[4]; //Negative
		//SHIFT THIS TO CLASS CONSTRUCTOR
		switch (It.orientation_type)
		{
			case 0:
				height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
				height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X];
				height_from_base[2] = It.m_Y + 2 - Game.stackHeight[It.m_X];
				height_from_base[3] = It.m_Y + 2 - Game.stackHeight[It.m_X+1];
				Game.play_arena[It.m_Y][It.m_X] = '2';
				Game.play_arena[It.m_Y+1][It.m_X] = '2';
				Game.play_arena[It.m_Y+2][It.m_X] = '2';
				Game.play_arena[It.m_Y+2][It.m_X+1] = '2';
				for (int k = 0;k < 4;k++) {
					if (height_from_base[k] == -1 || It.m_Y+2 == Game.rowsOfConsole - 2) {
						int arrX[4] = { It.m_X,It.m_X,It.m_X,It.m_X + 1 };
						int arrY[4] = { It.m_Y,It.m_Y + 1,It.m_Y + 2,It.m_Y + 2 };
						AddDump(Game,It,arrX ,arrY);
						It.isDown = true;
						break;
					}
				}
				break;
			case 1:
				height_from_base[0] = It.m_Y + 1 - Game.stackHeight[It.m_X];
				height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X+1];
				height_from_base[2] = It.m_Y + Game.stackHeight[It.m_X+2];
				height_from_base[3] = It.m_Y + 1 - Game.stackHeight[It.m_X+2];
				Game.play_arena[It.m_Y + 1][It.m_X] = '2';
				Game.play_arena[It.m_Y + 1][It.m_X + 1] = '2';
				Game.play_arena[It.m_Y][It.m_X+2] = '2';
				Game.play_arena[It.m_Y + 1][It.m_X + 2] = '2';
				for (int k = 0;k < 4;k++) {
					if (height_from_base[k] == -1 || It.m_Y + 1 == Game.rowsOfConsole - 2) {
						int arrX[4] = { It.m_X,It.m_X + 1,It.m_X+2,It.m_X + 2 };
						int arrY[4] = { It.m_Y + 1,It.m_Y + 1,It.m_Y,It.m_Y + 1 };
						AddDump(Game, It, arrX, arrY);
						It.isDown = true;
						break;
					}
				}
				break;
			case 2:
				height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
				height_from_base[1] = It.m_Y - Game.stackHeight[It.m_X + 1];
				height_from_base[2] = It.m_Y + 1 - Game.stackHeight[It.m_X + 1];
				height_from_base[3] = It.m_Y + 2 - Game.stackHeight[It.m_X + 1];
				Game.play_arena[It.m_Y][It.m_X] = '2';
				Game.play_arena[It.m_Y][It.m_X + 1] = '2';
				Game.play_arena[It.m_Y + 1][It.m_X + 1] = '2';
				Game.play_arena[It.m_Y + 2][It.m_X + 1] = '2';
				for (int k = 0;k < 4;k++) {
					if (height_from_base[k] == -1 || It.m_Y + 2 == Game.rowsOfConsole - 2) {
						int arrX[4] = { It.m_X,It.m_X + 1,It.m_X + 1,It.m_X + 1 };
						int arrY[4] = { It.m_Y,It.m_Y,It.m_Y + 1,It.m_Y + 2 };
						AddDump(Game, It, arrX, arrY);
						It.isDown = true;
						break;
					}
				}
				break;
			case 3:
				height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
				height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X];
				height_from_base[2] = It.m_Y - Game.stackHeight[It.m_X + 1];
				height_from_base[3] = It.m_Y - Game.stackHeight[It.m_X + 2];
				Game.play_arena[It.m_Y][It.m_X] = '2';
				Game.play_arena[It.m_Y + 1][It.m_X] = '2';
				Game.play_arena[It.m_Y][It.m_X + 1] = '2';
				Game.play_arena[It.m_Y][It.m_X + 2] = '2';
				for (int k = 0;k < 4;k++) {
					if (height_from_base[k] == -1 || It.m_Y + 1 == Game.rowsOfConsole - 2) {
						int arrX[4] = { It.m_X,It.m_X,It.m_X + 1,It.m_X + 2 };
						int arrY[4] = { It.m_Y,It.m_Y + 1,It.m_Y,It.m_Y };
						AddDump(Game, It, arrX, arrY);
						It.isDown = true;
						break;
					}
				}
				break;
			default:
				break;
		}

	}

	if (It.current_Shape == It.SQUARE) {
		int height_from_base[4];
		//SHIFT THIS TO CLASS CONSTRUCTOR
		switch (It.orientation_type)
		{
		case 0:
			height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
			height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X];
			height_from_base[2] = It.m_Y - Game.stackHeight[It.m_X + 1];
			height_from_base[3] = It.m_Y + 1 - Game.stackHeight[It.m_X + 1];
			Game.play_arena[It.m_Y][It.m_X] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X] = '2';
			Game.play_arena[It.m_Y][It.m_X + 1] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X+1] = '2';
			for (int k = 0;k < 4;k++) {
				if (height_from_base[k] == -1 || It.m_Y + 1 == Game.rowsOfConsole - 2) {
					int arrX[4] = { It.m_X,It.m_X,It.m_X+1,It.m_X + 1 };
					int arrY[4] = { It.m_Y,It.m_Y + 1,It.m_Y,It.m_Y + 1 };
					AddDump(Game, It, arrX, arrY);
					It.isDown = true;
					break;
				}
			}
			break;
		case 1:
			height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
			height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X];
			height_from_base[2] = It.m_Y - Game.stackHeight[It.m_X + 1];
			height_from_base[3] = It.m_Y + 1 - Game.stackHeight[It.m_X + 1];
			Game.play_arena[It.m_Y][It.m_X] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X] = '2';
			Game.play_arena[It.m_Y][It.m_X + 1] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X+1] = '2';
			for (int k = 0;k < 4;k++) {
				if (height_from_base[k] == -1 || It.m_Y + 1 == Game.rowsOfConsole - 2) {
					int arrX[4] = { It.m_X,It.m_X,It.m_X + 1,It.m_X + 1 };
					int arrY[4] = { It.m_Y,It.m_Y + 1,It.m_Y,It.m_Y + 1 };
					AddDump(Game, It, arrX, arrY);
					It.isDown = true;
					break;
				}
			}
			break;
		case 2:
			height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
			height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X];
			height_from_base[2] = It.m_Y - Game.stackHeight[It.m_X + 1];
			height_from_base[3] = It.m_Y + 1 - Game.stackHeight[It.m_X + 1];
			Game.play_arena[It.m_Y][It.m_X] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X] = '2';
			Game.play_arena[It.m_Y][It.m_X + 1] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X+1] = '2';
			for (int k = 0;k < 4;k++) {
				if (height_from_base[k] == -1 || It.m_Y + 1 == Game.rowsOfConsole - 2) {
					int arrX[4] = { It.m_X,It.m_X,It.m_X + 1,It.m_X + 1 };
					int arrY[4] = { It.m_Y,It.m_Y + 1,It.m_Y,It.m_Y + 1 };
					AddDump(Game, It, arrX, arrY);
					It.isDown = true;
					break;
				}
			}
			break;
		case 3:
			height_from_base[0] = It.m_Y - Game.stackHeight[It.m_X];
			height_from_base[1] = It.m_Y + 1 - Game.stackHeight[It.m_X];
			height_from_base[2] = It.m_Y - Game.stackHeight[It.m_X + 1];
			height_from_base[3] = It.m_Y + 1 - Game.stackHeight[It.m_X + 1];
			Game.play_arena[It.m_Y][It.m_X] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X] = '2';
			Game.play_arena[It.m_Y][It.m_X + 1] = '2';
			Game.play_arena[It.m_Y + 1][It.m_X+1] = '2';
			for (int k = 0;k < 4;k++) {
				if (height_from_base[k] == -1 || It.m_Y + 1 == Game.rowsOfConsole - 2) {
					int arrX[4] = { It.m_X,It.m_X,It.m_X + 1,It.m_X + 1 };
					int arrY[4] = { It.m_Y,It.m_Y + 1,It.m_Y,It.m_Y + 1 };
					AddDump(Game, It, arrX, arrY);
					It.isDown = true;
					break;
				}
			}
			break;
		default:
			break;
		}
	}
		
	*/
}

void PlayGame(PlayArena& Game)
{

	srand(time(NULL));
	int main_speed;
	int movement_speed;
	int item_velocity;
	int counterPsec = 0;
	int Shape = AvailableShapes[rand() % NUMBER_OF_SHAPES];  //Gets a Random Shape
	Item It(Shape);
	while (1) {
		bool respondToKey = true;
		MakeGame(Game,It);
		DisplayFrame(Game);
		if (counterPsec % 1 == 0) {
			It.m_Y += 1;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			for (int k = 0; k < 4;k++) {
				if(Game.dump[It.m_Y + It.Y[k]][It.m_X+ It.X[k] - 1] != ' ' || It.m_X == 1){
					respondToKey = false;
					break;
				}
			}
			if (respondToKey) {
				It.m_X--;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			for (int k = 0; k < 4;k++) {
				if (Game.dump[It.m_Y + It.Y[k]][It.m_X + It.X[k] + 1] != ' ' || It.m_X == Game.PLayArea_RightLimit -  1) {
					respondToKey = false;
					break;
				}
			}
			if (respondToKey) {
				It.m_X++;
			}
		
		}
		if (GetAsyncKeyState(VK_E)) { 
			if (Game.dump[It.m_Y + It.orientationHeight[(It.orientation_type + 1) % 4]][It.m_X] != ' ' || Game.dump[It.m_Y][It.m_X + It.orientationBreadth[(It.orientation_type + 1) % 4] - 1] != ' ' || It.m_X + It.orientationBreadth[(It.orientation_type + 1)%4] >= Game.PLayArea_RightLimit || It.m_Y + It.orientationHeight[(It.orientation_type + 1) % 4] > Game.rowsOfConsole - 2) {
				respondToKey = false;
			}
			if (respondToKey) {
				It.orientation_type = (It.orientation_type + 1) % 4;
				It.getMap();
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}

		counterPsec += 1;
		Sleep(100);
		Game.ClearScreen();
	}
}

void AddDump(PlayArena& Game, Item& It, int posX[4], int posY[4])
{
	for (int i = 0; i < 4; i++) {
		Game.dump[It.m_Y+posY[i]][It.m_X+posX[i]] = '0';
	}
	//for (int j = 0;j < Game.PLayArea_RightLimit;j++) {
	//	Game.stackHeight[j] = Game.rowsOfConsole - 2;
	//}
	////Update Height Info
	//for (int i = 0; i < Game.rowsOfConsole;i++) {
	//	for (int j = 0;j < Game.PLayArea_RightLimit;j++) {
	//		if (Game.dump[i][j] == '0' && Game.stackHeight[j] == Game.rowsOfConsole - 2) {
	//			Game.stackHeight[j] = i;
	//		}
	//	}
	//}
	//for (int i = 0; i < Game.PLayArea_RightLimit;i++)
	//{
	//	if (Game.stackHeight[i] <= 3) {
	//		cout << "YOU LOST\N";
	//		exit(0);
	//	}
	//}
	CheckCancel(Game);
	for (int k = 0; k < Game.PLayArea_RightLimit; k++) {
		if (Game.dump[2][k] == '0') {
			cout << "-------YOU----LOST-------\n\n\n YOUR SCORE : "<<Game.score<<endl<<endl;
			system("PAUSE");
			exit(0);
		}
	}
	srand(time(NULL));
	int Shape = AvailableShapes[rand() % NUMBER_OF_SHAPES];
	It.redef(Shape);
}

void CheckCancel(PlayArena & Game)
{
	int f = 0;
	for (int i = 0;i < Game.rowsOfConsole;i++) {
		 f = 0;
		for (int j = 1; j < Game.PLayArea_RightLimit;j++) {
			if (Game.dump[i][j] == ' ') {
				f = 1;
				break;
			}
		}
		if (f == 0) {
			Game.dump.erase(Game.dump.begin() + i);
			Game.dump.insert(Game.dump.begin(), Game.insert_Blank_Row);
			Game.score += 1;
		}
	}
}
