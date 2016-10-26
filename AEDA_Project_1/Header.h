#pragma once

#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

class Course {
protected:
	const uint year, semester, credits;
	string name;
public:
	Course(uint year, uint semester, uint credits) : year(year), semester(semester), credits(credits) {
	// do exceptions
	};
};

/**
  * test
  * @param: stuff what
*/
class OptionalCourse : public Course {
private:
	uint openSlots;
	string scientificArea;
public:
	OptionalCourse(uint year, uint semester, uint credits, uint openSlots) : Course(year, semester, credits), openSlots(openSlots) {
		// if (semester < 1 || semester > 2)
		//		throw ;
	};
	uint getYear() const { return year; }
};

class Person {
protected:
	string code, name;
public:
	Person(string code, string name) : code(code), name(name) {
		// do exceptions
	};
	virtual string getName() const = 0;

};

class Student : public Person {
private:
	string email, status;
public:
	Student(string code, string name, string email, string status) : Person(code, name), email(email), status(status) {
		// do exceptions
	};
	string getName() const { return name; }
};

class Tutor : public Person {
private:
	vector<Student *> students;
public:
	Tutor(string code, string name) : Person(code, name) {
		// do exceptions
	};
	string getName() const { return name; }
};