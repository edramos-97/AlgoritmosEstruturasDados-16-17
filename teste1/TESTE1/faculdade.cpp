#include "faculdade.h"

void Department::new_student(Student x)
{
	students.push_back(&x);
}


void Department::new_tutor(Tutor x)
{
	tutors.push_back(&x);
}


void Department::new_course(Course x)
{
	courses.push_back(&x);
}
