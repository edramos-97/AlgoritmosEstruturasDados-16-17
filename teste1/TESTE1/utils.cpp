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

Student* read_student(ifstream &f,uint &linenum)
{
	string code, name, email, status, tutor, line;

	read_line(f,line,linenum);



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

	Student* stud = new Student(code, name, email, status, tutor);

	return stud;
}

void readStudentInCourse(string &line, string &studCode, Date **date) {
	studCode = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	string dateStr = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);
	*date = new Date(dateStr);
}

Student* read_student(string &line)
{
	string code, name, email, status, tutor;
	
	code = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	name = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	email = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	status = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	tutor = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	Student *stud = new Student(code, name, email, status, tutor);

	return stud;
}

Tutor* read_tutor(ifstream &f,uint &linenum) {
	string code, name, line;

	read_line(f, line, linenum);
	name = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	code = line.substr(0, line.find(';'));

	Tutor* t= new Tutor(code, name);
	return t;
}

void read_line(ifstream & f, string & line, uint &linenum)
{
	getline(f, line);
	++linenum;
}

void save_student(ofstream & f, Student* x)
{
	f << x->get_code() << ';'
		<< x->get_name() << ';'
		<< x->get_email() << ';'
		<< x->get_status() << ';'
		<< x->get_tutor();
}

void save_tutor(ofstream & f,Tutor* x)
{
	f << x->get_name() << ';' << x->get_code()<< endl;
}

void save_course(ofstream & f, Course* course)
{
	bool isOptional = (!(dynamic_cast<OptionalCourse *>(course) == NULL));

	if (!isOptional) {
		f << "main_course_start" << endl;
	}
	else {
		f << "opt_course_start" << endl;
	}
	f << course->get_name() << ';'
		<< course->get_year() << ';'
		<< course->get_semestre() << ';'
		<< course->get_credits();
	if (isOptional) {
		f << ';' << course->get_openSlots() << ';'
			<< course->get_scientificArea();
	}
	f << endl;
	for (uint studInd = 0; studInd < course->get_enrol_students().size(); studInd++) {
		f << course->get_enrol_students().at(studInd)->get_code() <<
			';' << *(course->get_date_enrolled().at(studInd)) << endl;
	}
	f << "approved_students" << endl;
	for (uint studInd = 0; studInd < course->get_approv_students().size(); studInd++) {
		f << course->get_approv_students().at(studInd)->get_code() <<
			';' << *(course->get_date_approved().at(studInd)) << endl;
	}
	f << "end_course" << endl;
}

int search_for_student(vector<Course*> v, Student* t) {
	int counter = 0;
	for (auto course : v) {
		if (check_duplicates<Student*>(course->get_approv_students(), t))
		{
			++counter;
			continue;
		}
		else if (check_duplicates<Student*>(course->get_enrol_students(), t))
		{
			++counter;
			continue;
		}
		else
		{
			++counter;
			return counter;
		}
	}
	return -1;
}

template<typename T>
bool check_duplicates(vector<T> v, T arg)
{
	for (auto x : v) {
		if (x->get_name() == arg->get_name() || x->get_code() == arg->get_code())
			return true;
	}
	return false;
}