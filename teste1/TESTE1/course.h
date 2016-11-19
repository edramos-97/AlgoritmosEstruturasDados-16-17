/**
* @file person.h
* @author AEDA T3GE
* @title Class Course
* @brief Classes used to store information of Course or optional course
*/
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
	vector<Date *> date_approved;
public:
	/**
	*@brief Constructor of virtual class course
	*@param year wich year corresponds the course from 1 to 5
	*@param semester wich semester corresponds the course 1/2
	*@param credits how much credits it gives to the students
	*@param name name of the course
	*/
	Course(uint year, uint semester, double credits, string name);
	/**
	*@brief adds student to the course
	*@param x Student to add
	*/
	virtual void add_student(Student *stud, Date *date);
	/**
	*@brief adds student to the course approved vector
	*@param x Student to add
	*/
	virtual void add_approved_student(Student *stud, Date *date);

	/**
	*@brief virtual function, approves a stundent on the course, removes from vector enrolled students and puts the student on approved students
	*@param x students to approve
	*/
	virtual void approve_student(Student *stud, Date *date);
	/**
	*@brief virtual function, gets curricular year that a student is suppoded to take the course
	*/
	virtual const uint get_year();
	/**
	*@brief virtual function, gets semester that a student is suppoded to take the course
	*/
	virtual const uint get_semestre();
	/**
	*@brief virtual function, gets how much credits is worth the course
	*/
	virtual const double get_credits();
	/**
	*@brief virtual function, gets name of the course
	*/
	virtual const string get_name();
	/**
	*@brief virtual function, gets vector with the enrolled students
	*/
	virtual vector<Student *> get_enrol_students() const;
	/**
	*@brief virtual function, gets vector with the approved students
	*/
	virtual vector<Student *> get_approv_students() const;
	/**
	*@brief virtual function, gets vector with the dates of assignment of the students to the course
	*/
	virtual vector<Date *> get_date_enrolled() const;
	/**
	*@brief virtual function, prints enrolled students
	*/
	virtual void print_enrolled() const;
	/**
	*@brief virtual function, prints approved students
	*/
	virtual void print_approved() const;
	/**
	@brief Operator << for Course
	@param os ostream&
	@param c Course object to use the operator
	*/
	friend ostream& operator<<(ostream& os, const Course & c);
};



class OptionalCourse : public Course {
private:
	uint openSlots;
	string scientificArea;
public:
	/**
	*@brief Constructor of sub-class Optional Course
	*@param year wich year corresponds the course from 1 to 5
	*@param semester wich semester corresponds the course 1/2
	*@param credits how much credits it gives to the students
	*@param name name of the course
	*/
	OptionalCourse(uint year, uint semester, double credits, uint openSlots, string name, string scientificArea);
	/**
	*@brief gets scientficArea of the OptionalCourse
	*/
	string get_scientificArea() const;
	/**
	*@brief gets how much open slots the course has
	*/
	uint get_openSlots() const;
	/**
	*@brief adds student to the course
	*@param x Student to add
	*/
	void add_student(Student *student, Date *date);
	/**
	*@brief virtual function, approves a stundent on the course, removes from vector enrolled students and puts the student on approved students
	*@param x students to approve
	*/
	void approve_student(Student *student, Date *date);
	/**
	@brief Operator << for optionalCourse
	@param os ostream&
	@param c Course object to use the operator
	*/
	friend ostream& operator<<(ostream& os, const OptionalCourse & c);
};
