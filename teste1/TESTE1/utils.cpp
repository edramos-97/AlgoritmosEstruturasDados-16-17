#include "utils.h"

void clrscr(void)
{
	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

Student read_student(ifstream f)
{
	string code, name, email, status, tutor, line;
	double apcredits, credits;

	getline(f, line);



	code = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	name = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	email = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	status = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	tutor = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	apcredits = stod(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));

	Student s(code, name, email, status, tutor);
	s.add_approved_credits(apcredits);
	s.add_credits(credits);

	return s;
}

