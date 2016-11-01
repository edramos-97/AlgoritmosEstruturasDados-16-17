#include "course.h"
#include <algorithm>
#include <iomanip>
#include "utils.h"

using namespace std;

void Course::add_student(Student* x)
{
	enrolled_students.push_back(x);
}

void Course::add_approved_student(Student* x)
{
	approved_students.push_back(x);
}

void Course::approve_student(Student x)
{
	auto it = find(enrolled_students.begin(), enrolled_students.end(), &x);
	if (it == enrolled_students.end())
		throw not_in_container(x.get_code());
	else
	{
		enrolled_students.erase(it);
		approved_students.push_back(&x);
	}
}

void Course::print_enrolled() const
{
	for (auto x: enrolled_students)
	{
		cout << *x << "\n ||||||||||||||||||||||||||||\n\n";
	}
}

void Course::print_approved() const
{
	for (auto x : approved_students)
	{
		cout << *x << "\n ||||||||||||||||||||||||||||\n\n";
	}
}

void OptionalCourse::add_student(Student x)
{
	enrolled_students.push_back(&x);
	--openSlots;
}

void OptionalCourse::approve_student(Student x)
{
	auto it = find(enrolled_students.begin(), enrolled_students.end(), &x);
	if (it == enrolled_students.end())
		throw not_in_container(x.get_code());
	else
	{
		enrolled_students.erase(it);
		approved_students.push_back(&x);
	}
	++openSlots;
}

ostream & operator<<(ostream & os, const Course & c)
{
	os <<right << setw(6) << c.name << "::" << left <<setw (4) << c.credits<< endl;
	os << "\nEnrolled students:\n" << endl;
	c.print_enrolled();
	os << "\nApproved students:\n" << endl;
	c.print_approved();
	return os;
}

ostream & operator<<(ostream & os, const OptionalCourse & c)
{
	os << right << setw(10) << c.name << "::" << left << setw(4) << c.credits << "Available slots: "<< c.openSlots;
	os << "\nEnrolled students:\n" << endl;
	c.print_enrolled();
	os << "\nApproved students:\n" << endl;
	c.print_approved();
	return os;
}
