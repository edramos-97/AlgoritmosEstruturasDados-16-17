#pragma once

#include "course.h"
#include "person.h"


class Department {
	string name;
	
	vector<Student*> students;
	vector<Tutor*> tutors;
	vector<Course*> courses;
public:
	Department(string name): name(name)
	{
		if (name.size() < 3)
			throw short_argument(name,"name");
	};
	uint last_assinged_tutor = 0;
	void new_tutor(Tutor x);
	void new_student(Student x);
	void new_course(Course x);



};