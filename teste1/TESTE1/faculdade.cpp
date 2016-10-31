#include "faculdade.h"

void Department::new_student(Student x)
{
	x.assign_tutor(tutors[last_assinged_tutor]);
	students.push_back(&x);
	++last_assinged_tutor;
	if (last_assinged_tutor >= tutors.size())
		last_assinged_tutor = 0;	
}


void Department::new_tutor(Tutor x)
{
	tutors.push_back(&x);
}


void Department::new_course(Course x)
{
	uint year, semestre;

	year = x.get_year();
	semestre = x.get_semestre();

	switch(year) {
	case 1:
		semestre == 1 ? courses_11.push_back(&x) : courses_12.push_back(&x);
	case 2:
		semestre == 1 ? courses_21.push_back(&x) : courses_22.push_back(&x);
	case 3:
		semestre == 1 ? courses_31.push_back(&x) : courses_32.push_back(&x);
	case 4:
		semestre == 1 ? courses_41.push_back(&x) : courses_42.push_back(&x);
	case 5:
		semestre == 1 ? courses_51.push_back(&x) : courses_52.push_back(&x);
	}
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
