/**
* @file course.h
* @author AEDA T4GE
* @title Classes Course and OptionalCourse
* @brief Classes used to store information of both mandatory and optional courses
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
	*@brief Constructor of class course
	*@param year Year of the course ranging from 1 to 5
	*@param semester Semester of the course ranging from 1 to 2
	*@param credits How many credits the course is worth
	*@param name Name of the course
	*/
	Course(uint year, uint semester, double credits, string name);

	/**
	*@brief Enrolls student in the course
	*@param stud Student to enroll
	*@param date Date of the student's enrollment
	*Adds student to the course's vector of enrolled students
	*/
	virtual void add_student(Student *stud, Date *date);

	/**
	*@brief Approves student in the course
	*@param stud Student to approve
	*@param date Date of the student's approvement
	*Adds student to the course's vector of approved students
	*/
	virtual void add_approved_student(Student *stud, Date *date);

	/**
	*@brief Approves a student in the course
	*@param stud Student to approve
	*@param date Date of the student's approvement
	*Removes the student from the vector of enrolled students and adds the student to the vector of approved students
	*/
	virtual void approve_student(Student *stud, Date *date);

	/**
	*@brief Returns the course's year
	*/
	virtual const uint get_year();

	/**
	*@brief Returns the course's semester
	*/
	virtual const uint get_semestre();

	/**
	*@brief Returns the course's credits
	*/
	virtual const double get_credits();

	/**
	*@brief Returns the course's name
	*/
	virtual const string get_name();

	/**
	*@brief Returns a copy of the course's vector of enrolled students
	*/
	virtual vector<Student *> get_enrol_students() const;

	/**
	*@brief Returns a copy of the course's vector of approved students
	*/
	virtual vector<Student *> get_approv_students() const;

	/**
	*@brief Returns a copy of the course's vector of dates of enrolled students
	*/
	virtual vector<Date *> get_date_enrolled() const;

	/**
	*@brief Returns a copy of the course's vector of dates of approved students
	*/
	virtual vector<Date *> get_date_approved() const;

	/**
	*@brief Prints enrolled students
	*/
	virtual void print_enrolled() const;

	/**
	*@brief Prints approved students
	*/
	virtual void print_approved() const;

	/**
	*@brief Declared to be used on OptionalCourse. Do not invoke.
	*/
	virtual uint get_maxSlots() const { cerr << "Invoked Course::get_maxSlots()\n"; return 0; };

	/**
	*@brief Declared to be used on OptionalCourse. Do not invoke.
	*/
	virtual string get_scientificArea() const { cerr << "Invoked Course::get_scientificArea()\n"; return "NULL"; };

	/**
	*@brief Declared to be used on OptionalCourse. Do not invoke.
	*/
	virtual uint get_openSlots() const { cerr << "Invoked Course::get_openSlots()\n"; return 0; };

	/**
	@brief Operator << for Course
	@param os Output stream
	@param course Course
	*/
	friend ostream& operator<<(ostream& os, const Course & course);
};



class OptionalCourse : public Course {
private:
	const uint maxSlots;
	uint openSlots;
	string scientificArea;
public:
	/**
	*@brief Constructor of sub-class OptionalCourse
	*@param year Year of the course ranging from 1 to 5
	*@param semester Semester of the course ranging from 1 to 2
	*@param credits How many credits the course is worth
	*@param name Name of the course
	*@param maxSlots Maximum number of the course's open slots
	*@param scientificArea Scientific area of the course
	*/
	OptionalCourse(uint year, uint semester, double credits, uint maxSlots, string name, string scientificArea);

	/**
	*@brief Returns the scientific area of the course
	*/
	string get_scientificArea() const;

	/**
	*@brief Returns the maximum number of the course's open slots
	*/
	uint get_maxSlots() const;

	/**
	*@brief Returns the current number of the course's open slots
	*/
	uint get_openSlots() const;

	/**
	*@brief Enrolls student in the course
	*@param stud Student to enroll
	*@param date Date of the student's enrollment
	*Adds student to the course's vector of enrolled students
	*/
	void add_student(Student *student, Date *date);

	/**
	*@brief Approves enrolled student in the course
	*@param stud Student to approve
	*@param date Date of the student's approvement
	*Removes the student from the vector of enrolled students, adds the student to the vector of approved students and adds an open slot to the course
	*/
	void approve_student(Student *student, Date *date);

	/**
	@brief Operator << for OptionalCourse
	@param os Output Stream
	@param course Course
	*/
	friend ostream& operator<<(ostream& os, const OptionalCourse & course);
};
