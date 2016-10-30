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
	virtual string getName() const = 0;

};



class Student : public Person {
private:
	string email, status;
public:
	Student(string code, string name, string email, string status) : Person(code, name), email(email), status(status) {
	
	};
	string getName() const { return name; }
};



class Tutor : public Person {
private:
	vector<Student *> students;
public:
	Tutor(string code, string name) : Person(code, name) {

	};
	string getName() const { return name; }
};