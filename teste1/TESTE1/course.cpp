#include "course.h"
#include <algorithm>
#include <iomanip>

using namespace std;

void Course::add_student(Student x)
{
	attending_students.push_back(&x);
	
}

void Course::approve_student(Student x)
{
	auto it = find(attending_students.begin(), attending_students.end(), &x);
	if (it == attending_students.end())
		throw not_in_container(x.get_code());
	else
	{
		attending_students.erase(it);
		approved_students.push_back(&x);
	}
}

void OptionalCourse::add_student(Student x)
{
	attending_students.push_back(&x);
	--openSlots;
}

void OptionalCourse::approve_student(Student x)
{
	auto it = find(attending_students.begin(), attending_students.end(), &x);
	if (it == attending_students.end())
		throw not_in_container(x.get_code());
	else
	{
		attending_students.erase(it);
		approved_students.push_back(&x);
	}
	++openSlots;
}

ostream & operator<<(ostream & os, const Course & c)
{
	os <<right << setw(10) << c.name << "::" << left <<setw (4) << c.credits;
	return os;
}

ostream & operator<<(ostream & os, const OptionalCourse & c)
{
	os << right << setw(10) << c.name << "::" << left << setw(4) << c.credits << "Available slots: "<< c.openSlots;
	return os;
}
