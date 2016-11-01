#include "faculdade.h"


void Department::new_student(Student* x)
{
	x->assign_tutor(tutors[last_assinged_tutor]);
	students.push_back(x);
	++last_assinged_tutor;
	if (last_assinged_tutor >= tutors.size())
		last_assinged_tutor = 0;	
}

void Department::new_tutor(Tutor* x)
{
	tutors.push_back(x);
}

void Department::new_course(Course* x)
{
	uint year, semestre;

	year = x->get_year();
	semestre = x->get_semestre();

	switch(year) {
	case 1:
		semestre == 1 ? courses_11.push_back(x) : courses_12.push_back(x);
	case 2:
		semestre == 1 ? courses_21.push_back(x) : courses_22.push_back(x);
	case 3:
		semestre == 1 ? courses_31.push_back(x) : courses_32.push_back(x);
	case 4:
		semestre == 1 ? courses_41.push_back(x) : courses_42.push_back(x);
	case 5:
		semestre == 1 ? courses_51.push_back(x) : courses_52.push_back(x);
	}
}

void Department::add_student(Student * x)
{
	students.push_back(x);
}

void Department::load_dept(string x)
{
	string filename = x + ".txt", line;
	uint linenum=0;
	ifstream f(filename);
	if (!f.is_open())
		throw file_not_open(x);
	read_line(f, line, linenum);
	if (line != "#tutors_start")
		throw corrupted_file(linenum,"expected #tutors_start");
	while (f.peek() != '#') {
		tutors.push_back(read_tutor(f, linenum));
	}
	read_line(f, line, linenum);
	if (line != "#tutors_end")
		throw corrupted_file(linenum,"expected #tutors_end");
	read_line(f,line, linenum);
	if (line != "#courses_start")
		throw corrupted_file(linenum,"expected #courses_start");
	while (f.peek() != '#') {
		Course* temp = read_course(f, linenum);
		new_course(temp);
		for (auto x:temp->approved_students)
		{
			students.push_back(x);
		}
		for (auto x : temp->enrolled_students)
		{
			students.push_back(x);
		}
	}
	read_line(f, line, linenum);
	if (line != "#courses_end")
		throw corrupted_file(linenum, "expected #courses_end");
	if (line != "#students_start")
		throw corrupted_file(linenum,"expected #students_start");
	while (f.peek() != '#') {
		Student* temp = read_student(f, linenum);
		if (check_duplicates<Student*>(students, temp))
			throw corrupted_file(linenum,"duplicate students are not allowed");
		students.push_back(temp);
	}
	read_line(f, line, linenum);
	if (line != "#students_end")
		throw corrupted_file(linenum,"expected #students_end");
	

}

ostream & operator<<(ostream & os, const Department & d)
{
		os << d.name << endl
		<< "Number of Students: " << d.students.size()<< endl
		<< "Number of Tutors: " << d.tutors.size()<<endl
		<< "Number of courses: " <<
		(d.courses_11.size() +
			d.courses_12.size() +
			d.courses_21.size() +
			d.courses_22.size() +
			d.courses_31.size() +
			d.courses_32.size() +
			d.courses_41.size() +
			d.courses_42.size() +
			d.courses_51.size() +
			d.courses_52.size())
		<< endl;

		return os;
}
