#pragma once


#include <vector>
#include <string>
#include "exceptions.h"

using namespace std;

typedef unsigned int uint;



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



class Student : public Person {
private:
	string email, status;
	uint approved_credits, credits;
	Tutor * assigned_tutor;
public:
	Student(string code, string name, string email, string status) : Person(code, name), email(email), status(status) {
	
	};
	string get_name() const { return name; }
	string get_code() const { return code; }
	void add_approved_credits(uint x) { approved_credits += x; };
	void add_credits(uint x) { credits += x; };
	void assign_tutor(Tutor * x) { assigned_tutor = x; };
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