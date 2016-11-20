#pragma once

#include "course.h"
#include "person.h"
#include "utils.h"
#include <fstream>
#include <algorithm>

#define NEW_TUTOR true
#define NEW_STUDENT true

class Department {
	string name;
	
	vector<Tutor*> tutors;
	vector<Student*> students;
	vector<vector<vector<Course*>>> courses; //courses[semester][year][courseInfo]
	vector<Course*> external_courses;
	int next_assign_tutor;
	int next_assign_student;
public:
		
	Department(string name): name(name)
	{
		if (name.size() < 3)
			throw exception_or_error("Nome para a faculdade demasiado pequeno (" + name + ")");
		vector<vector<Course*>>v1(5, vector<Course*>());
		courses.push_back(v1);
		courses.push_back(v1);
		next_assign_tutor = 1;
		next_assign_student = 1;
	};
	
	string get_name() const { return name; };
	int getNext_assigned_tutor(bool newTutor = false);
	int getNext_assigned_student(bool newStudent = false);
	Student* getStudent(const string &studCode) const;
	Course* getCourse(const string &courseName) const;
	void new_tutor(Tutor *tutor);
	void new_student(Student *stud);
	void new_course(Course *course);
	void add_student(Student *stud);
	void add_external(Course *course);
	void approve_student(Student *stud, Course *course);
	bool apply_for_course(Student *stud, Course *course);
	bool apply_for_course(Student *stud, OptionalCourse *course);
	bool verify_courses_completition(uint year, uint semestre, Student *stud, Course *course, Date *date);
	vector<string> search_sci_area(string scientific_area);
	void Department::processCourse(ifstream &f, uint &linenum);
	void load_dept(string filename);
	void save_dept();
	friend ostream& operator<<(ostream &os, const Department &d);
	const vector<vector<vector<Course*>>> get_courses() const;
};