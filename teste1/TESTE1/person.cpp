#include "person.h"

void Tutor::add_student(Student x)
{
	students.push_back(&x);
}

ostream & operator<<(ostream & os, const Student & s)
{
	os << s.code << s.name << s.email <<s.status << s.tutor << s.approved_credits<< s.credits;
	return os;
}
