#pragma once

#include <string>
#include <vector>
#include "exceptions.h"
#include "person.h"
#include "date.h"


using namespace std;

typedef unsigned int uint;

class Student;

class Course {
protected:
	const uint year, semester;
	const double credits;
	string name;
	vector<Student *> enrolled_students;
	vector<Student *> approved_students;
	vector<Date *> date_enrolled;
public:
	Course(uint year, uint semester, double credits, string name) : year(year), semester(semester), credits(credits), name(name) {
		if (year < 1 || year > 5)
			throw value_out_of_range<uint, string>(year, "year");
		if (semester < 1 || semester > 2)
			throw value_out_of_range<uint, string>(semester, "semestre");
		if (credits < 1 || credits > 30)
			throw value_out_of_range<double, string>(credits, "credits");
		if (name.size() < 3)
			throw short_argument(name, "name");
	};
	void add_student(Student* x);
	void add_approved_student(Student* x);
	void add_date(Date* d);
	virtual void approve_student(Student x);
	virtual const uint get_year() { return year; };
	virtual const uint get_semestre() { return semester; };
	virtual const double get_credits() { return credits; };
	virtual const string get_name() { return name; };
	vector<Student *> get_enrol_students() const;
	vector<Student *> get_approv_students() const;
	vector<Date *> Course::get_date_enrolled() const;
	void print_enrolled() const;
	void print_approved() const;
	friend ostream& operator<<(ostream& os, const Course & c);
};



class OptionalCourse : public Course {
private:
	uint openSlots;
	string scientificArea;
public:
	OptionalCourse(uint year, uint semester, double credits, uint openSlots, string name) : Course(year, semester, credits, name), openSlots(openSlots) {
	};
	string get_scientificArea() const { return scientificArea; };
	uint get_openSlots() const { return openSlots; };
	void add_student(Student x);
	void approve_student(Student x);
	friend ostream& operator<<(ostream& os, const OptionalCourse & c);
};
