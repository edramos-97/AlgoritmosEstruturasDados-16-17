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
* @param x Previously created Course to add.
*
* Adds a Previously created Course pointer to the Department vector of Course.
*/
void Department::new_course(Course* x)
{
	uint year, semestre;

	year = x->get_year();
	semestre = x->get_semestre();

	courses.at(semestre-1).at(year-1).push_back(x);
}

/**
* @brief Adds an existent course to the Department.
* @param x Previously read course to add.
*
* An existing Course read from a text file is added to the Department vector of courses.
*/
void Department::add_course(Course * course) {
	new_course(course);
	for (auto student : course->get_approv_students())
	{
		add_student(student);
	}

	for (auto student : course->get_enrol_students())
	{
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

/**
* @brief Reads a file containing Department info.
* @param x Filename of a .txt file, no extension given (e.g. "Mieic" instead of "Mieic.txt").
*
* Reads from a text file tutors into the Department's tutors vector, courses into the Department's corresponding courses[semestre][year] vector and students into the Department's students vector.
*/
void Department::load_dept(string x)
{
	string filename = x + ".txt", line;
	uint linenum=0;
	ifstream f;
	f.open(filename);
	if (!f.is_open()) {
		throw file_not_open(x);
	}
	read_line(f, line, linenum);
	this->next_assign_tutor = stoi(line);

	read_line(f, line, linenum);
	this->next_assign_student = stoi(line);
	
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
void Department::save_dept()
{
	ofstream f(name+".txt");
	f << this->next_assign_tutor << "\n";
	f << this->next_assign_student << "\n";
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
* @param semester The semester of the course specified.
* @param s The student that is applying for a Course.
* @param c The course to which a student is applying.
*
* Verifies if the student has completed or is enrolled in all previous years courses.
*/
bool Department::verify_courses_completition(uint year, uint semester, Student *stud, Course *course, Date *date) {
	int result;
	for (uint i = 0; i < (year-1); i++) {
		result = search_for_student(courses[semester][i], stud);
		if (result != -1) {
			cout << "Para se puder increver a esse curso o estudante tem primeiro que completar "
				<< courses.at(semester).at(i).at(result)->get_name() << '.';
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
	
	throw StudentNotFound(studCode);
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

	throw CourseNotFound(courseName);
}

const vector<vector<vector<Course*>>> Department::get_courses() const {
	return courses;
}