#pragma once

#include <string>
#include <vector>
#include "exceptions.h"
#include "person.h"


using namespace std;

typedef unsigned int uint;

class Course {
protected:
	const uint year, semester, credits;
	string name;
	vector<Student*> attending_students;
	vector<Student*> approved_students;
public:
	Course(uint year, uint semester, uint credits) : year(year), semester(semester), credits(credits) {
		if (year < 1 || year > 5)
			throw value_out_of_range<uint,string>(year, "year");
		if (semester < 1 || semester > 2)
			throw value_out_of_range<uint,string>(semester, "semestre");
		if (credits < 1 || credits > 30)
			throw value_out_of_range<uint,string>(credits, "credits");
	};
	virtual void add_student(Student x);
	virtual void approve_student(Student x);
	virtual const uint get_year() { return year; };
	virtual const uint get_semestre() { return semester; };
	virtual const uint get_credits() { return credits; };
};



class OptionalCourse : public Course {
private:
	uint openSlots;
	string scientificArea;
public:
	OptionalCourse(uint year, uint semester, uint credits, uint openSlots) : Course(year, semester, credits), openSlots(openSlots) {
	};
	uint getYear() const { return year; }
	string get_scientificArea() const { return scientificArea; };
	void add_student(Student x);
	void approve_student(Student x);
};
