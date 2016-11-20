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
		throw exception_or_error("Ano curricular invalido(" + to_string(year) + ")");
	if (semester < 1 || semester > 2)
		throw exception_or_error("Semestre invalido(" + to_string(semester) + ")");
	if (credits < 1 || credits > 30)
		throw exception_or_error("Numero de creditos invalido (" + to_string(credits) + ")");
	if (name.size() < 2)
		throw exception_or_error("Nome para a UC invalido (" + name + ")");
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


//TODO - Date. //done i think needs testing
void Course::approve_student(Student *student, Date *date)
{
	size_t i;
	for (i = 0; i < enrolled_students.size();i++) {
		if (enrolled_students.at(i)->get_code() == student->get_code()) {
			enrolled_students.erase(enrolled_students.begin()+i);
			date_enrolled.erase(date_enrolled.begin() + i);
			approved_students.push_back(student);
			date_approved.push_back(date);
			return;
		}
	}
	throw exception_or_error("O estudante com o codigo (" + student->get_code() + ") nao foi encontrado");
	return;
	/*auto it = find(enrolled_students.begin(), enrolled_students.end(), student);
	if (it == enrolled_students.end())
		throw StudentNotFound(student->get_code());
	else
	{
		enrolled_students.erase(it);
		approved_students.push_back(student);
	}*/
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

vector<Date *> Course::get_date_approved() const {
	return date_approved;
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

void OptionalCourse::add_student(Student *student, Date *date)
{
	enrolled_students.push_back(student);
	date_enrolled.push_back(date);
	--openSlots;
}

void OptionalCourse::approve_student(Student *student, Date *date)
{
	size_t i;
	for (i = 0; i < enrolled_students.size();i++) {
		if (enrolled_students.at(i)->get_code() == student->get_code()) {
			enrolled_students.erase(enrolled_students.begin() + i);
			date_enrolled.erase(date_enrolled.begin() + i);
			approved_students.push_back(student);
			date_approved.push_back(date);
			++openSlots;
			return;
		}
	}
	throw exception_or_error("O estudante com o codigo (" + student->get_code() + ") nao foi encontrado");
	return;
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
