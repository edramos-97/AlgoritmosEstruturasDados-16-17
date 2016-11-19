#include "course.h"
#include <algorithm>
#include <iomanip>
#include "utils.h"

using namespace std;

/*********************************
*CLASS COURSE
*********************************/
Course::Course(uint year, uint semester, double credits, string name) : year(year), semester(semester), credits(credits), name(name) {
	if (year < 1 || year > 5)
		throw value_out_of_range<uint, string>(year, "year");
	if (semester < 1 || semester > 2)
		throw value_out_of_range<uint, string>(semester, "semestre");
	if (credits < 1 || credits > 30)
		throw value_out_of_range<double, string>(credits, "credits");
	if (name.size() < 3)
		throw short_argument(name, "name");
}

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


//TODO - Date.
void Course::approve_student(Student *student, Date *date)
{
	auto it = find(enrolled_students.begin(), enrolled_students.end(), student);
	if (it == enrolled_students.end())
		throw not_in_container(student->get_code());
	else
	{
		enrolled_students.erase(it);
		approved_students.push_back(student);
	}
}

const uint Course::get_year() { return year; }

const uint Course::get_semestre() { return semester; }

const double Course::get_credits() { return credits; }

const string Course::get_name() { return name; }

vector<Student *> Course::get_enrol_students() const {
	return enrolled_students;
}

vector<Student *> Course::get_approv_students() const {
	return approved_students;
}

vector<Date *> Course::get_date_enrolled() const {
	return date_enrolled;
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

ostream & operator<<(ostream & os, const Course & c)
{
	os << right << setw(6) << c.name << "::" << left << setw(4) << c.credits << endl;
	os << "\nEnrolled students:\n" << endl;
	c.print_enrolled();
	os << "\nApproved students:\n" << endl;
	c.print_approved();
	return os;
}




/*********************************
*CLASS Optional Course
*********************************/
OptionalCourse::OptionalCourse(uint year, uint semester, double credits, uint openSlots, string name,
	string scientificArea) : Course(year, semester, credits, name), openSlots(openSlots), scientificArea(scientificArea) {
}

string OptionalCourse::get_scientificArea() const { return scientificArea; }

uint OptionalCourse::get_openSlots() const { return openSlots; }

void OptionalCourse::add_student(Student *x)
{
	enrolled_students.push_back(x);
	--openSlots;
}

void OptionalCourse::approve_student(Student *student)
{
	auto it = find(enrolled_students.begin(), enrolled_students.end(), student);
	if (it == enrolled_students.end())
		throw not_in_container(student->get_code());
	else
	{
		enrolled_students.erase(it);
		approved_students.push_back(student);
	}
	++openSlots;
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
