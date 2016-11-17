#pragma once

#include "course.h"
#include "person.h"
#include "utils.h"
#include <fstream>
#include <algorithm>

class Department {
	string name;
	
	vector<Tutor*> tutors;
	vector<Student*> students;
	vector<vector<vector<Course*>>> courses; //courses[semestre][year]
	/*vector<Course*> courses_12;
	vector<Course*> courses_21;
	vector<Course*> courses_22;
	vector<Course*> courses_31;
	vector<Course*> courses_32;
	vector<Course*> courses_41;
	vector<Course*> courses_42;
	vector<Course*> courses_51;
	vector<Course*> courses_52;*/
public:
		
	Department(string name): name(name)
	{
		if (name.size() < 3)
			throw short_argument(name,"Nome para a faculdade demasiado pequeno : \"");
		vector<vector<Course*>>v1(5, vector<Course*>());
		courses.push_back(v1);
		courses.push_back(v1);
	};
	
	string get_name() const { return name; };
	void new_tutor(Tutor* x);
	void new_student(Student* x);
	void new_course(Course* x);
	void add_course(Course * x);
	void add_student(Student* x);
	string apply_for_course(Student * s, Course * c);
	string verify_courses_completition(uint year, uint semestre, Student * s,Course* c);
	void load_dept(string filename);
	void save_dept(string filename);
	friend ostream& operator<<(ostream& os, const Department & d);
	const vector<vector<vector<Course*>>> get_courses() const;
};