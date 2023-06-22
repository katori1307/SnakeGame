#include "SnakeSegment.h"

int main()
{
	SetConsoleTitle(L"Snake game");
	Game g;
	g.launch();
	/*while (1)
	{
		g.handleSettings();
	}*/
	/*while (1)
	{
		if (_kbhit())
		{
			char input = toupper(_getch());
			cout << input << " ";
		}
		else
			cout << "Nothing" << " ";
		Sleep(500);
	}*/


	return 0;
}