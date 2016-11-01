#pragma once

#include "course.h"
#include "person.h"
#include "utils.h"
#include <fstream>

class Department {
	string name;
	
	vector<Student*> students;
	vector<Tutor*> tutors;
	vector<Course*> courses_11;
	vector<Course*> courses_12;
	vector<Course*> courses_21;
	vector<Course*> courses_22;
	vector<Course*> courses_31;
	vector<Course*> courses_32;
	vector<Course*> courses_41;
	vector<Course*> courses_42;
	vector<Course*> courses_51;
	vector<Course*> courses_52;
public:
	Department(string name): name(name)
	{
		if (name.size() < 3)
			throw short_argument(name,"name");
		last_assinged_tutor = 0;
	};
	uint last_assinged_tutor;
	void new_tutor(Tutor* x);
	void new_student(Student* x);
	void new_course(Course* x);
	void add_student(Student* x);
	void load_dept(string x);
	friend ostream& operator<<(ostream& os, const Department & d);


};