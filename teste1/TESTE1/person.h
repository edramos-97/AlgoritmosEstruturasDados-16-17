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
			throw short_argument(name, "Nome que tentou atribuir a esta pessoa é demasiado pequeno");
		if (code.length() != 11)
			throw short_argument(code, "Codigo de aluno ou tutor invalido");
	};
	virtual string get_name() const = 0;
	virtual string get_code() const = 0;

};

class Tutor : public Person {
private:
	
public:
	vector<Student *> students;
	Tutor(string code, string name) : Person(code, name) {
	};
	string get_name() const { return name; }
	string get_code() const { return code; }
	void add_student(Student* x);
	bool operator< (const Tutor &t) const;
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
	Student(string code, string name, string email, string status) : Person(code, name), email(email), status(status){
		approved_credits = 0;
		credits = 0;
	};
	string get_name() const { return name; }
	string get_code() const { return code; }
	string get_email() const { return email; }
	string get_status() const { return status; }
	string get_tutor() const { return tutor; }
	const vector<string> get_enrol_courses() const;
	double get_appcredits() const { return approved_credits; }
	double get_credits() const { return credits; }
	void add_approved_credits(double x) { approved_credits += x; };
	void add_credits(double x) { credits += x; };
	void assign_tutor(Tutor * x) {tutor = x->get_code(); };
	friend ostream& operator<<(ostream& os, const Student & s);
};