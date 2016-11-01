#pragma once


#include <vector>
#include <string>
#include "exceptions.h"

using namespace std;

typedef unsigned int uint;

class Person;
class Tutor;
class Student;

class Person {
protected:
	string code, name;
public:
	Person(string code, string name) : code(code), name(name) {
		if (name.size() < 3)
			throw short_argument(name, "name");
		if (code.size() != 9)
			throw short_argument(code, "code");
	};
	virtual string get_name() const = 0;
	virtual string get_code() const = 0;

};

class Tutor : public Person {
private:
	vector<Student *> students;
public:
	Tutor(string code, string name) : Person(code, name) {
	};
	string get_name() const { return name; }
	string get_code() const { return code; }
	void add_student(Student x);
};

class Student : public Person {
private:
	string email, status, tutor;
	double approved_credits, credits;
	vector<string> enrolled_courses;

public:
	Student(string code, string name, string email, string status,string tutor) : Person(code, name), email(email), status(status),tutor(tutor) {
		approved_credits = 0;
		credits = 0;
	};
	string get_name() const { return name; }
	string get_code() const { return code; }
	string get_email() const { return email; }
	void add_approved_credits(double x) { approved_credits += x; };
	void add_credits(double x) { credits += x; };
	void assign_tutor(Tutor * x) {tutor = x->get_code(); };
	friend ostream& operator<<(ostream& os, const Student & s);
};



