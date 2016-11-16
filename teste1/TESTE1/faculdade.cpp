#include "faculdade.h"

/**
* @brief Adds a new Student to the Department.
* @param x Preaviously created Student to add.
*
* Adds a preaviously created Student pointer to the Department vector of students and assigns a Tutor to given student.
*/
void Department::new_student(Student* x)
{
	sort(tutors.begin(), tutors.end());
	x->assign_tutor(tutors[0]);
	students.push_back(x);
	tutors[0]->add_student(x);
}
/**
* @brief Adds a Tutor to the Department.
* @param x Preaviously created Tutor to add.
*
* Adds a preaviously created Tutor pointer to the Department vector of Tutors.
*/
void Department::new_tutor(Tutor* x)
{
	tutors.push_back(x);
}
/**
* @brief Adds a Course to the Department.
* @param x Preaviously created Course to add.
*
* Adds a preaviously created Course pointer to the Department vector of Course.
*/
void Department::new_course(Course* x)
{
	uint year, semestre;

	year = x->get_year();
	semestre = x->get_semestre();

	courses[semestre-1][year-1].push_back(x);
}
/**
* @brief Adds an existant course to the Department.
* @param x Preaviously read course to add.
*
* An existing Course read from a text file is added to the Department vector of courses.
*/
void Department::add_course(Course * x) {
	new_course(x);
	for (auto elem : x->approved_students)
	{
		add_student(elem);
	}

	for (auto elem : x->enrolled_students)
	{
		add_student(elem);
	}
}
/**
* @brief Adds an existant student to the Department.
* @param x Preaviously read student to add.
*
* An existing Student read from a text file is added to the Department vector of students.
*/
void Department::add_student(Student * x)
{
	if (x->get_tutor().empty()) {
		new_student(x);
		return;
	}

	for (auto t : tutors) {
		if (t->get_code() == x->get_tutor()) {
			students.push_back(x);
			t->add_student(x);
			return;
		}
	}
	return;
}
/**
* @brief Reads a file containing Department info.
* @param x Filename of a .txt file, no extension given (e.g. "Mieic" instead of "Mieic.txt").
*
* Reads from a text file tutors into the Department's tutors vector, courses into the Department's corresponding courses[semestre][year] vector and students into the Department's students vector.
*/
/*Verify comment*/void Department::load_dept(string x)
{
	string filename = x + ".txt", line;
	uint linenum=0;
	ifstream f;
	f.open(filename);
	if (!f.is_open()) {
		throw file_not_open(x);
	}
	read_line(f, line, linenum);
	if (line != "#tutors_start") {
		throw corrupted_file(linenum, "expected #tutors_start");
	}
	while (f.peek() != '#') {
		new_tutor(read_tutor(f, linenum));
	}
	read_line(f, line, linenum);

	if (line != "#tutors_end")
		throw corrupted_file(linenum,"expected #tutors_end");
	
	read_line(f,line, linenum);
	if (line != "#courses_start")
		throw corrupted_file(linenum,"expected #courses_start");
	
	while (f.peek() != '#') {
		Course* temp = read_course(f, linenum);
		add_course(temp);
	}
	read_line(f, line, linenum);
	if (line != "#courses_end")
		throw corrupted_file(linenum, "expected #courses_end");
	read_line(f, line, linenum);
	if (line != "#students_start")
		throw corrupted_file(linenum,"expected #students_start");
	while (f.peek() != '#') {
		Student* temp = read_student(f, linenum);
		if (students.size() != 0) {
			if (check_duplicates<Student*>(students, temp))
				continue;
			//throw corrupted_file(linenum,"duplicate students are not allowed");
		}
			
		add_student(temp);
	}
	read_line(f, line, linenum);
	if (line != "#students_end")
		throw corrupted_file(linenum,"expected #students_end");
	f.close();
}
/**
* @brief Saves to a text file the Department's info.
* @param filename Filename of a .txt file, extension given (e.g. "Mieic.txt" instead of "Mieic").
*
* Saves to a text file the Department's tutors, courses and students.
*/
void Department::save_dept(string filename)
{
	ofstream f(/*this->get_name()+".txt"*/filename);
	f << "#tutors_start" << endl;
	for (auto x : tutors)
		save_tutor(f, x);
	f << "#tutors_end" << endl;
	f << "#courses_start" << endl;
	/*for (auto x : courses_11)
		save_course(f, x);
	for (auto x : courses_12)
		save_course(f, x);
	for (auto x : courses_21)
		save_course(f, x);
	for (auto x : courses_22)
		save_course(f, x);
	for (auto x : courses_31)
		save_course(f, x);
	for (auto x : courses_32)
		save_course(f, x);
	for (auto x : courses_41)
		save_course(f, x);
	for (auto x : courses_42)
		save_course(f, x);
	for (auto x : courses_51)
		save_course(f, x);
	for (auto x : courses_52)
		save_course(f, x);*/
	for (auto x : courses)
		for (auto y : x)
			for (auto c : y)
				save_course(f, c);
	f << "#courses_end" << endl;
	f << "#students_start" << endl;
	for (auto x : students) {
		save_student(f, x);
		f << endl;
	}
	f << "#students_end" << endl;
	f.close();
}
/**
* @brief Verifies if it is possible for the student to apply for the given course and enrolls him.
* @param s The student that is applying for a Course.
* @param c The course to which a student is applying.
*
* Verifies if the student has completed or is enrolled in all previous years courses and if he is, he is going to be  enrolled in the course specified.
*/
string Department::apply_for_course(Student * s, Course * c)
{
	int result = 0;
	switch (c->get_semestre()) {
	case 1:
		switch (c->get_year()) {
		case 1:
			c->add_student(s);
		case 2:
			verify_courses_completition(2, 1, s, c);
		case 3:
			verify_courses_completition(3, 1, s, c);
		case 4:
			verify_courses_completition(4, 1, s, c);
		case 5:
			verify_courses_completition(5, 1, s, c);
		default: return "FAIL";
		}
	case 2:
		switch (c->get_year()) {
		case 1:
			c->add_student(s);
		case 2:
			verify_courses_completition(2, 2, s, c);
		case 3:
			verify_courses_completition(3, 2, s, c);
		case 4:
			verify_courses_completition(4, 2, s, c);
		case 5:
			verify_courses_completition(5, 2, s, c);
		default: return "FAIL";
		}
	default:
		return "FAIL";
	}
}

ostream & operator<<(ostream & os, const Department & d)
{
		os << d.name << endl
		<< "Number of Students: " << d.students.size()<< endl
		<< "Number of Tutors: " << d.tutors.size()<<endl
		<< "Number of courses: " <<
		(d.courses[0][0].size() +
			d.courses[0][1].size() +
			d.courses[0][2].size() +
			d.courses[0][3].size() +
			d.courses[0][4].size() +
			d.courses[1][0].size() +
			d.courses[1][1].size() +
			d.courses[1][2].size() +
			d.courses[1][3].size() +
			d.courses[1][4].size())
		<< endl;

		return os;
}
/**
* @brief Verifies if it is possible for the student to apply for the given course.
* @param year The year of the Course specified.
* @param semestre The semestre of the course specified.
* @param s The student that is applying for a Course.
* @param c The course to which a student is applying.
*
* Verifies if the student has completed or is enrolled in all previous years courses.
*/
string Department::verify_courses_completition(uint year, uint semestre,Student* s,Course * c) {
	int result;
	for (uint i = 0; i < (year-1); i++) {
		result = search_for_student(courses[semestre][i], s);
		if (result != -1) {
			cout << "Para se puder increver a esse curso o estudante tem primeiro que completar "
				<< courses[semestre][i][result]->get_name() << '.';
			return "FAIL";
		}
		else
		{
			c->add_student(s);
			return "OK";
		}
	}
	return "FAIL";
}