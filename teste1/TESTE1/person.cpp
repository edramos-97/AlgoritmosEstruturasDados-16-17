#include "person.h"

void Tutor::add_student(Student x)
{
	students.push_back(&x);
}

ostream & operator<<(ostream & os, const Student & s)
{
	os << s.code << "||" << s.name << "||" << s.email << endl <<
		"Status: " << s.status << endl <<
		"Tutor: " << s.tutor << endl <<
		"Completed credits: " << s.approved_credits << endl <<
		"Credits currently enrolled for: " << s.credits << endl;
	return os;
}
