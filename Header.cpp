#include "Header.h"


ScreenC::ScreenC()
{
	GetConsoleScreenBufferInfo(this->hStdOut, &(this->csbi));
	this->colsOfConsole = csbi.srWindow.Right+1;
	this->rowsOfConsole = csbi.srWindow.Bottom;
	this->PLayArea_RightLimit = this->colsOfConsole / 4;
	isScreenBuilt = true;

}

void ScreenC::ClearScreen()
{
	DWORD countt;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 }; //FOR NOW SET TO (0,0)

	
	if(this->hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if(!GetConsoleScreenBufferInfo(this->hStdOut, &csbi)) return;
	cellCount = (this->csbi).dwSize.X *(this->csbi).dwSize.Y;

	/* Fill the entire buffer with spaces */
	if(!FillConsoleOutputCharacter(
		this->hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&countt
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	/*if (!FillConsoleOutputAttribute(
		this->hStdOut,
		(this->csbi).wAttributes,
		cellCount,
		homeCoords,
		&countt
	)) return;*/

	/* Move the cursor home */
	SetConsoleCursorPosition(this->hStdOut, homeCoords);
}

void Item::redef(int Shape)
{
	orientation_type = 0;
	m_X = PLayArea_RightLimit / 2;
	m_Y = 0;
	isDown = false;
	current_Shape = Shape;
	
	if (Shape == SQUARE) {
		orientation[0] = "22\n22";
		orientation[1] = "22\n22";
		orientation[2] = "22\n22";
		orientation[3] = "22\n22";
		for (int i = 0;i < 4;i++) {
			orientationHeight[i] = 2;
			orientationBreadth[i] = 2;
		}
	}

	if (Shape == LSHAPE) {
		orientation[0] = "2\n2\n22";
		orientation[1] = "  2\n222";
		orientation[2] = "22\n 2\n 2";
		orientation[3] = "222\n2  ";
		for (int i = 0;i < 4;i++) {
			orientationHeight[i] = count(orientation[i].begin(), orientation[i].end(), '\n') + 1;
			orientationBreadth[i] = 4 - count(orientation[i].begin(), orientation[i].end(), '\n');
		}
	}
	this->getMap();
}

void Item::getMap()
{
	int cX = 0, cY = 0;
	int c = 0;
	int ty = orientation_type;
	for (int k = 0; k < orientation[ty].length(); k++) {
		if ((orientation[ty])[k] == '\n') {
			cX = 0;
			cY++;
			continue;
		}
		else if ((orientation[ty])[k] == '2') {
			X[c] = cX;
			Y[c] = cY;
			cX++;
			c++;
			continue;
		}
		else {
			cX++;
			continue;
		}
	}
}

Item::Item()
{
}

Item::Item(int Shape)
{
	orientation_type = 0;
	m_X = PLayArea_RightLimit/2;
	m_Y = 0;
	isDown = false;
	current_Shape = Shape;
	if (Shape == SQUARE) {
		orientation[0] = "22\n22";
		orientation[1] = "22\n22";
		orientation[2] = "22\n22";
		orientation[3] = "22\n22";
		for (int i = 0;i < 4;i++) {
			orientationHeight[i] =2;
			orientationBreadth[i] = 2;
		}
	}

	if (Shape == ISHAPE) {
		orientation[0] = "2222";
		orientation[1] = "2\n2\n2\n2";
		orientation[2] = "2222";
		orientation[3] = "2\n2\n2\n2";
		for (int i = 0;i < 4;i++) {
			orientationHeight[i] = count(orientation[i].begin(), orientation[i].end(), '\n') + 1;
			orientationBreadth[i] = 4 - count(orientation[i].begin(), orientation[i].end(), '\n');
		}
	}

	if (Shape == LSHAPE) {
		orientation[0] = "2\n2\n22";
		orientation[1] = "  2\n222";
		orientation[2] = "22\n 2\n 2";
		orientation[3] = "222\n2  ";
		for (int i = 0;i < 4;i++) {
			orientationHeight[i] = count(orientation[i].begin(), orientation[i].end(), '\n') + 1;
			orientationBreadth[i] = 4 - count(orientation[i].begin(), orientation[i].end(), '\n');
		}
	}
	this->getMap();
}


PlayArena::PlayArena()
{

	//Build Game
	for (int i = 0;i < rowsOfConsole;i++) {
		play_arena.push_back("");
		for (int j = 0;j < colsOfConsole;j++) {
			if (PLayArea_RightLimit == j) {
				play_arena[i] += "|";
				continue;
			}
			play_arena[i] += " ";
		}
	}

	for (int i = 0;i < rowsOfConsole;i++) {
		dump.push_back("");
		for (int j = 0;j < colsOfConsole;j++) {
			if (PLayArea_RightLimit == j) {
				dump[i] += "|";
				continue;
			}
			dump[i] += " ";
		}
	}
	score = 0;
	maxStackHeight = 0;
	insert_Blank_Row = play_arena[0];
	for (int j = 0; j < PLayArea_RightLimit;j++) {
		play_arena[rowsOfConsole - 1][j] = '=';
	}
	for (int j = 0;j < colsOfConsole;j++) {
		stackHeight.push_back(rowsOfConsole - 2);
	}
	GameInfoPosX = rowsOfConsole / 2;
	GameInfoPosY = (3*PLayArea_RightLimit)/4;
}



