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
//	double apcredits, credits;

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

//	apcredits = stod(line.substr(0, line.find(';')));
//	line.erase(0, line.find(';') + 1);

//	credits = stod(line.substr(0, line.find(';')));

	Student* stud = new Student(code, name, email, status, tutor);
//	s->add_approved_credits(apcredits);
//	s->add_credits(credits);

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
//	double approv_credits, credits;
	
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

/*	approv_credits = stod(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1); */



	Student *stud = new Student(code, name, email, status, tutor);
/*	stud->add_approved_credits(approv_credits);
	stud->add_credits(credits); */

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
/*
Course* read_course(ifstream &f, uint &linenum) {
	string name, line, dateStr;
	uint year, semestre;
	double credits;
	Date *date;

	read_line(f, line, linenum);

	if (line != "course_start")
		throw corrupted_file(linenum, "expected course_start");

	read_line(f, line, linenum);

	name = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	year = stoul(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	semestre = stoul(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));

	Course* course = new Course(year, semestre, credits, name);
	read_line(f, line, linenum);
	
	for (; line != "approved_students";) {
		Student *copyStud = read_student(line);
		Student *originalStud;

		dateStr = line.substr(0, line.find(';'));
		date = new Date(dateStr);
		copyStud->enroll_course(course);
		course->add_student(copyStud, date);
		read_line(f, line, linenum);
	}

	read_line(f, line, linenum);
	for (;line!="end_course";){
		Student *stud = read_student(line);
		dateStr = line.substr(0, line.find(';'));
		date = new Date(dateStr);
		stud->approve_course(course);
		course->add_approved_student(stud, date);
		read_line(f, line, linenum);
	}

	return course;
}*/

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
		<< x->get_tutor();/* << ';'
		<< x->get_appcredits() << ';'
		<< x->get_credits();*/
}

void save_tutor(ofstream & f,Tutor* x)
{
	f << x->get_name() << ';' << x->get_code()<< endl;
}

void save_course(ofstream & f, Course* course)
{
	f << "course_start" << endl;
	f << course->get_name() << ';'
		<< course->get_year() << ';'
		<< course->get_semestre() << ';'
		<< course->get_credits() << endl;
	for (uint studInd = 0; studInd < course->get_enrol_students().size(); studInd++)
	{
		save_student(f, course->get_enrol_students().at(studInd));
		f << ';' << *(course->get_date_enrolled().at(studInd)) << endl;
	}
	f << "approved_students" << endl;
	for (auto student : course->get_approv_students()) {
		save_student(f, student);
		f << endl;
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