/**
* @file course.h
* @author AEDA T4GE
* @title Classes Course and OptionalCourse
* @brief Classes used to store information of both mandatory and optional courses.
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
	*@brief Constructor of Course.
	*@param year Year of the Course from 1 to 5.
	*@param semester Semester of the Course from 1 to 2.
	*@param credits Number of credits the Course is worth.
	*@param name Name of the Course.
	*/
	Course(uint year, uint semester, double credits, string name);

	/**
	*Adds Student to the Course's vector of enrolled students.
	*@brief Enrolls a Student in the Course.
	*@param stud Pointer to Student to enroll.
	*@param date Pointer to Date of the student's enrollment.
	*/
	virtual void add_student(Student *stud, Date *date);

	/**
	*Adds a Student to the Course's vector of approved students.
	*@brief Approves a Student in the Course.
	*@param stud Pointer to Student to approve.
	*@param date Pointer to Date of the Student's approvement.
	*/
	virtual void add_approved_student(Student *stud, Date *date);

	/**
	*Moves the Student from the vector of enrolled Students to the vector of approved Students.
	*@brief Approves a Student in the Course.
	*@param stud Pointer to Student to approve.
	*@param date Pointer to Date of the Student's approvement.
	*/
	virtual void approve_student(Student *stud, Date *date);

	/**
	*@brief Gets the Course's year.
	*@return Year of the Course.
	*/
	virtual const uint get_year();

	/**
	*@brief Gets the Course's semester.
	*@return Semester of the Course.
	*/
	virtual const uint get_semestre();

	/**
	*@brief Gets the Course's credits.
	*@return Credits that the Course is worth.
	*/
	virtual const double get_credits();

	/**
	*@brief Gets the Course's name.
	*@return Name of the Course.
	*/
	virtual const string get_name();

	/**
	*@brief Gets the Course's enrolled students.
	*@return Vector of pointers to Students enrolled in the Course.
	*/
	virtual vector<Student *> get_enrol_students() const;

	/**
	*@brief Gets the Course's approved Students.
	*@return Vector of pointers to Students approved in the Course.
	*/
	virtual vector<Student *> get_approv_students() const;

	/**
	*@brief Gets the Course's Student enrollment Dates.
	*@return Vector of pointers to Dates corresponding by index to Students enrolled in the Course.
	*/
	virtual vector<Date *> get_date_enrolled() const;

	/**
	*@brief Gets the Course's Student approvement Dates.
	*@return Vector of pointers to Dates corresponding by index to Students approved in the Course.
	*/
	virtual vector<Date *> get_date_approved() const;

	/**
	*For each Student, it prints its info according to the Student's << operator and its date of enrollment.
	*@brief Prints enrolled students.
	*/
	virtual void print_enrolled() const;

	/**
	*For each Student, it prints its info according to the Student's << operator and its date of approvement.
	*@brief Prints approved students.
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
	*Prints a Course's name, credits, enrolled students and respective enrollment dates, and approved students and respective approvement dates.
	*@brief Prints to a given output stream information of a Course.
	*@param os Output stream.
	*@param course Course to print.
	*/
	friend ostream& operator<<(ostream &os, const Course &course);
};



class OptionalCourse : public Course {
private:
	const uint maxSlots;
	uint openSlots;
	string scientificArea;
public:
	/**
	*@brief Constructor of OptionalCourse.
	*@param year Year of the OptionalCourse from 1 to 5.
	*@param semester Semester of the OptionalCourse from 1 to 2.
	*@param credits Number of credits the OptionalCourse is worth.
	*@param name Name of the OptionalCourse.
	*@param maxSlots Maximum number of the OptionalCourse's open slots.
	*@param scientificArea Scientific area of the OptionalCourse.
	*/
	OptionalCourse(uint year, uint semester, double credits, uint maxSlots, string name, string scientificArea);

	/**
	*@brief Gets the OptionalCourse's scientific area.
	*@return Scientific area.
	*/
	string get_scientificArea() const;

	/**
	*@brief Gets the OptionalCourse's maximum number of slots.
	*@return Maximum number of slots.
	*/
	uint get_maxSlots() const;

	/**
	*@brief Gets the OptionalCourse's open slots.
	*@return Open slots.
	*/
	uint get_openSlots() const;

	/**
	*Adds Student to the OptionalCourse's vector of enrolled students.
	*@brief Enrolls a Student in the OptionalCourse.
	*@param stud Pointer to Student to enroll.
	*@param date Pointer to Date of the student's enrollment.
	*/
	void add_student(Student *student, Date *date);

	/**
	*Moves the Student from the vector of enrolled Students to the vector of approved Students.
	*@brief Approves a Student in the OptionalCourse.
	*@param stud Pointer to Student to approve.
	*@param date Pointer to Date of the Student's approvement.
	*/
	void approve_student(Student *student, Date *date);

	/**
	*Prints a OptionalCourse's name, credits, open slots, enrolled students and respective enrollment dates,
	*and approved students and respective approvement dates.
	*@brief Prints to a given output stream information of a OptionalCourse.
	*@param os Output stream.
	*@param course OptionalCourse to print.
	*/
	friend ostream& operator<<(ostream &os, const OptionalCourse &course);
};
