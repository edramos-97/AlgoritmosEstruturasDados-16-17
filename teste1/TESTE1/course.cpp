#include "course.h"
#include <algorithm>
#include <iomanip>
#include "utils.h"

using namespace std;

void Course::add_student(Student *student, Date *date)
{
	enrolled_students.push_back(student);
	date_enrolled.push_back(date);
}

void Course::add_approved_student(Student *student, Date *date)
{
	approved_students.push_back(student);
	date_approved.push_back(date);
}

/*
void Course::add_date(Date *date)
{
	date_enrolled.push_back(date);
}
*/

void Course::approve_student(Student student, Date *date)
{
	auto it = find(enrolled_students.begin(), enrolled_students.end(), &student);
	if (it == enrolled_students.end())
		throw not_in_container(student.get_code());
	else
	{
		enrolled_students.erase(it);
		approved_students.push_back(&student);
	}
}

void Course::print_enrolled() const
{
	for (uint i = 0; i < enrolled_students.size(); i++)
	{
		cout << *(enrolled_students.at(i)) << "Date of enrolment: " << *(date_enrolled.at(i))
			<< "\n ||||||||||||||||||||||||||||\n\n";
	}
}

void Course::print_approved() const
{
	for (Student *stud : approved_students)
	{
		cout << *stud << "\n ||||||||||||||||||||||||||||\n\n";
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

vector<Student *> Course::get_enrol_students() const {
	return enrolled_students;
}

vector<Student *> Course::get_approv_students() const {
	return approved_students;
}

vector<Date *> Course::get_date_enrolled() const {
	return date_enrolled;
}

ostream & operator<<(ostream & os, const Course & c)
{
	os << right << setw(6) << c.name << "::" << left << setw(4) << c.credits << endl;
	os << "\nEnrolled students:\n" << endl;
	c.print_enrolled();
	os << "\nApproved students:\n" << endl;
	c.print_approved();
	return os;
}

ostream & operator<<(ostream & os, const OptionalCourse & c)
{
	os << right << setw(10) << c.name << "::" << left << setw(4) << c.credits << "Available slots: " << c.openSlots;
	os << "\nEnrolled students:\n" << endl;
	c.print_enrolled();
	os << "\nApproved students:\n" << endl;
	c.print_approved();
	return os;
}
