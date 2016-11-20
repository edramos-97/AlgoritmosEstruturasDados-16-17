#include "faculdade.h"

int Department::getNext_assigned_tutor(bool newTutor) {
	if (newTutor)
		++next_assign_tutor;
	return next_assign_tutor;
};

int Department::getNext_assigned_student(bool newStudent) {
	if (newStudent)
		++next_assign_student;
	return next_assign_student;
}

/**
* @brief Adds a new Student to the Department.
* @param x Previously created Student to add.
*
* Adds a Previously created Student pointer to the Department vector of students and assigns a Tutor to given student.
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
* @param x Previously created Tutor to add.
*
* Adds a Previously created Tutor pointer to the Department vector of Tutors.
*/
void Department::new_tutor(Tutor* x)
{
	tutors.push_back(x);
}

/**
* @brief Adds a Course to the Department.
* @param c Previously created Course to add.
*
* Adds a Previously created Course pointer to the Department vector of Course.
*/
void Department::new_course(Course* c)
{
	uint year, semester;

	year = c->get_year();
	semester = c->get_semestre();

	courses.at(semester - 1).at(year - 1).push_back(c);
}

/**
* @brief Adds an existent course to the Department.
* @param course Previously read course to add.
*
* An existing Course read from a text file is added to the Department vector of courses.
*/
void Department::add_course(Course *course) {
	new_course(course);
	for (Student *student : course->get_approv_students())
	{
		if (check_duplicates<Student *>(students, student)) {
			student->approve_course(course);
			continue;
		}
		add_student(student);
	}

	for (Student *student : course->get_enrol_students())
	{
		if (check_duplicates<Student *>(students, student)) {
			student->enroll_course(course);
			continue;
		}
		add_student(student);
	}
}
/**
* @brief Adds an existent student to the Department.
* @param x Previously read student to add.
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

void Department::processCourse(ifstream &f, uint &linenum) {
	bool isOptional = false;
	Course *course = nullptr;
	OptionalCourse *optCourse = nullptr;
	Date *date = nullptr;
	string name, line, dateStr, scientificArea;
	uint year, semester, openSlots;
	double credits;

	read_line(f, line, linenum);

	if (line != "main_course_start" && line != "opt_course_start")
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum));

	if (line == "opt_course_start")
		isOptional = true;

	read_line(f, line, linenum);

	name = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	year = stoul(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	semester = stoul(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));

	if (!isOptional) {
		course = new Course(year, semester, credits, name);
	}
	else {
		line.erase(0, line.find(';') + 1);
		openSlots = stoul(line.substr(0, line.find(';')));
		line.erase(0, line.find(';') + 1);
		scientificArea = line.substr(0, line.find(';'));
		optCourse = new OptionalCourse(year, semester, credits, openSlots, name, scientificArea);
	}

	read_line(f, line, linenum);

	for (; line != "approved_students";) {
		string studCode;
		Student *originalStud = nullptr;
		readStudentInCourse(line, studCode, &date);
		for (Student *stud : students) {
			if (stud->get_code() == studCode) {
				originalStud = stud;
				break;
			}
		}

		if (!isOptional) {
			originalStud->enroll_course(course);
			course->add_student(originalStud, date);
		}
		else {
			originalStud->enroll_course(optCourse);
			optCourse->add_student(originalStud, date);
		}

		read_line(f, line, linenum);
	}

	read_line(f, line, linenum);
	for (; line != "end_course";) {
		string studCode;
		Student *originalStud = nullptr;
		readStudentInCourse(line, studCode, &date);
		for (Student *stud : students) {
			if (stud->get_code() == studCode) {
				originalStud = stud;
				break;
			}
		}

		if (!isOptional) {
			originalStud->approve_course(course);
			course->add_approved_student(originalStud, date);
		}
		else {
			originalStud->approve_course(optCourse);
			optCourse->add_approved_student(originalStud, date);
		}

		read_line(f, line, linenum);
	}

	if (!isOptional) {
		courses.at(semester - 1).at(year - 1).push_back(course);
	}
	else {
		courses.at(semester - 1).at(year - 1).push_back(optCourse);
	}

}

/**
* @brief Reads a file containing Department info.
* @param x Filename of a .txt file, no extension given (e.g. "Mieic" instead of "Mieic.txt").
*
* Reads from a text file tutors into the Department's tutors vector, courses into the Department's corresponding courses[semestre][year] vector and students into the Department's students vector.
*/
void Department::load_dept(string x)
{
	string filename = x + ".txt", line;
	uint linenum = 0;
	ifstream f;
	f.open(filename);
	if (!f.is_open()) {
		throw exception_or_error("O ficheiro " + x + " nao foi encontrado verifique se o mesmo existe ou esta em local adequado");
	}
	read_line(f, line, linenum);
	this->next_assign_tutor = stoi(line);

	read_line(f, line, linenum);
	this->next_assign_student = stoi(line);

	read_line(f, line, linenum);
	if (line != "#tutors_start") {
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #tutors_start");
	}
	while (f.peek() != '#') {
		new_tutor(read_tutor(f, linenum));
	}
	read_line(f, line, linenum);

	if (line != "#tutors_end")
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #tutors_end");

	read_line(f, line, linenum);
	if (line != "#students_start")
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #students_start");
	while (f.peek() != '#') {
		Student* temp = read_student(f, linenum);
		add_student(temp);
	}
	read_line(f, line, linenum);
	if (line != "#students_end")
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #students_end");

	read_line(f, line, linenum);
	if (line != "#courses_start")
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #courses_start");

	while (f.peek() != '#') {
		processCourse(f, linenum);
	}
	read_line(f, line, linenum);
	if (line != "#courses_end")
		throw exception_or_error("O ficheiro está corrompido, problema encontrado na linha " + to_string(linenum) + ", esperava-se #courses_end");;

	f.close();
}

/**
* @brief Saves to a text file the Department's info.
* @param filename Filename of a .txt file, extension given (e.g. "Mieic.txt" instead of "Mieic").
*
* Saves to a text file the Department's tutors, courses and students.
*/
void Department::save_dept()
{
	ofstream f(name + ".txt");
	f << this->next_assign_tutor << "\n";
	f << this->next_assign_student << "\n";
	f << "#tutors_start" << endl;
	for (auto x : tutors)
		save_tutor(f, x);
	f << "#tutors_end" << endl;
	f << "#students_start" << endl;
	for (auto x : students) {
		save_student(f, x);
		f << endl;
	}
	f << "#students_end" << endl;
	f << "#courses_start" << endl;
	for (size_t year = 0; year < courses.at(0).size(); ++year) {
		for (Course *course : courses.at(0).at(year))
			save_course(f, course);
		for (Course *course : courses.at(1).at(year))
			save_course(f, course);
	}


	f << "#courses_end" << endl;
	f.close();
}

void Department::approve_student(Student *stud, Course *course) {
	Date *date = new Date();
	stud->approve_course(course);
	course->approve_student(stud, date);

}

/**
* @brief Verifies if it is possible for the student to apply for the given course and enrolls him.
* @param s The student that is applying for a Course.
* @param c The course to which a student is applying.
*
* Verifies if the student has completed or is enrolled in all previous years courses and if he is, he is going to be enrolled in the course specified.
*/
bool Department::apply_for_course(Student *stud, Course *course)
{
	Date *date = new Date();
	int result = 0;
	bool success;
	switch (course->get_semestre()) {
	case 1:
		switch (course->get_year()) {
		case 1:
			course->add_student(stud, date);
			stud->enroll_course(course);
			success = true;
			break;
		case 2:
			success = verify_courses_completition(2, 1, stud, course, date);
			break;
		case 3:
			success = verify_courses_completition(3, 1, stud, course, date);
			break;
		case 4:
			success = verify_courses_completition(4, 1, stud, course, date);
			break;
		case 5:
			success = verify_courses_completition(5, 1, stud, course, date);
		default:
			success = false;
			break;
		}
		break;
	case 2:
		switch (course->get_year()) {
		case 1:
			course->add_student(stud, date);
			stud->enroll_course(course);
			success = true;
			break;
		case 2:
			success = verify_courses_completition(2, 2, stud, course, date);
			break;
		case 3:
			success = verify_courses_completition(3, 2, stud, course, date);
			break;
		case 4:
			success = verify_courses_completition(4, 2, stud, course, date);
			break;
		case 5:
			success = verify_courses_completition(5, 2, stud, course, date);
			break;
		default:
			success = false;
			break;
		}
		break;
	default:
		success = false;
		break;
	}
	if (!success) {
		delete date;
	}
	return success;
}

ostream & operator<<(ostream & os, const Department & d)
{
	os << d.name << endl
		<< "Number of Students: " << d.students.size() << endl
		<< "Number of Tutors: " << d.tutors.size() << endl
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
* @param semester The semester of the course specified.
* @param s The student that is applying for a Course.
* @param c The course to which a student is applying.
*
* Verifies if the student has completed or is enrolled in all previous years courses.
*/
bool Department::verify_courses_completition(uint year, uint semester, Student *stud, Course *course, Date *date) {
	int result;
	for (uint i = 0; i < (year - 1); i++) {
		result = search_for_student(courses.at(semester - 1).at(i), stud);
		if (result != -1) {
			cout << "Para se puder increver a esse curso o estudante tem primeiro que completar "
				<< courses.at(semester - 1).at(i).at(result)->get_name() << '.';
			return false;
		}
		else
		{
			course->add_student(stud, date);
			stud->enroll_course(course);
			return true;
		}
	}
	return false;
}

Student* Department::getStudent(const string &studCode) const {
	for (size_t studInd = 0; studInd < students.size(); ++studInd) {
		if (studCode == students.at(studInd)->get_code()) {
			return students.at(studInd);
		}
	}

	throw exception_or_error("O estudante com o codigo (" + studCode + ") nao foi encontrado");
}

Course* Department::getCourse(const string &courseName) const {
	for (size_t sem = 0; sem < courses.size(); ++sem) {
		for (size_t year = 0; year < courses.at(sem).size(); ++year) {
			for (size_t courseInd = 0; courseInd < courses.at(sem).at(year).size(); ++courseInd) {
				if (courseName == courses.at(sem).at(year).at(courseInd)->get_name()) {
					return courses.at(sem).at(year).at(courseInd);
				}
			}
		}
	}

	throw exception_or_error("O curso com o nome (" + courseName + " não foi encontrado");
}

const vector<vector<vector<Course*>>> Department::get_courses() const {
	return courses;
}