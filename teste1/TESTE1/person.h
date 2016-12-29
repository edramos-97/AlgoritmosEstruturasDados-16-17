/**
* @file person.h
* @author AEDA T4GE
* @title Class Person and Subclasses Stundent and Tutor
* @brief Classes used to store information of a Student or a Tutor
*/
#pragma once


#include <vector>
#include <string>
#include "exceptions.h"
#include "course.h"
#include "Date.h"

using namespace std;

typedef unsigned int uint;

class Person;
class Tutor;
class Student;
class Course;
class Date;

class Person {
protected:
	string code, name;
public:
	/**
	*@brief Constructor of pure virtual class Person.
	*@param Code of the Person.
	*@param Name of the Person.
	*/
	Person(string code, string name);

	/**
	*@brief Gets the Person's name.
	*@return Name of the Person.
	*/
	virtual string get_name() const = 0;

	/**
	*@brief Gets the Person's code.
	*@return Code of the Person.
	*/
	virtual string get_code() const = 0;

	/**
	*@brief Sets the Person's name.
	*@param newName New name of the Person.
	*/
	virtual void setName(string newName) = 0;
};

class Tutor : public Person {
private:

public:
	//se der tempo mudar isto para privado
	vector<Student *> students;

	/**
	*@brief Constructor of Tutor.
	*@param code Code of the Tutor.
	*@param name Name of the Tutor.
	*/
	Tutor(string code, string name);

	/**
	*@brief Gets the Tutor's name.
	*@return Name of the Tutor.
	*/
	string get_name() const;

	/**
	*@brief Gets the Tutor's code.
	*@return Code of the Tutor.
	*/
	string get_code() const;

	/**
	*@brief Sets the Tutor's name.
	*@param newName New name of the Tutor.
	*/
	void setName(string newName);

	/**
	*@brief Adds a Student to the Tutor's Students vector.
	*@param stud Pointer to the Student to add.
	*/
	void add_student(Student *stud);

	/**
	*@brief Compares the amount of Students in the Tutors' Students vectors.
	*@param tutor Tutor to compare with.
	*@return True if the amount of students in *this is lower than the one in tutor.
	*/
	bool operator < (const Tutor &tutor) const;

	/**
	*Format: "code || name".
	*@brief Prints to an output stream the Tutor's code and name.
	*@param os Output stream.
	*@param tutor Tutor to print.
	*@return The printed stream, os.
	*/
	friend ostream& operator << (ostream &os, const Tutor &tutor);
};

class Student : public Person {
private:
	bool interrupted, finished;
	string email, status, tutor;
	double approved_credits, credits;
	vector<Course *> enrolled_courses;
	vector<Course *> approved_courses;
	vector<Date *> enrolled_dates;
	vector<Date *> approved_dates;
public:
	/**
	*@brief Constructor of the class Student
	*@param code Student's code generated automatically or read from a text file
	*@param name Student's name
	*@param email Student's e-mail
	*@param status Student's status ("Trabalhador Estudante", "Ordinário")
	*@param tutor Student's Tutor's code
	*/
	Student(string code, string name, string email, string status, string tutor);

	/**
	*@brief Constructor of the class Student
	*@param code Student's code generated automatically or read from a text file
	*@param name Student's name
	*@param email Student's e-mail
	*@param status Student's status ("Trabalhador Estudante", "Ordinário")
	*@param interrupted True if student has interrupted the degree, false otherwise
	*@param finished True if student has terminated the degree, false otherwise
	*/
	Student(string code, string name, string email, string status, bool interrupted, bool finished);

	/**
	*@brief Get a Student's name
	*@return Student's name as a string
	*/
	string get_name() const;

	/**
	*@brief Get a Student's code
	*@return Student's code as a string
	*/
	string get_code() const;

	/**
	*@brief Get a student's e-mail
	*@return Student's e-mail as a string
	*/
	string get_email() const;

	/**
	*@brief Get a student's status
	*@return Student's status as a string
	*/
	string get_status() const;

	/**
	*@brief Get a student's tutor's code
	*@return Student's tutor's code as a string
	*/
	string get_tutor() const;
	
	/**
	*@brief access the data-member "interrupted"
	*@return value of the data-member "interrupted"
	*/
	bool hasInterrupted() const;

	/**
	*@brief access the data-member "finished"
	*@return value of the data-member "finished"
	*/
	bool hasFinished() const;

	/**
	*@brief Function that returns a vector with the courses the student is enrolled
	*@return vector<Course *> with student enrolled courses
	*/
	vector<Course *> get_enrol_courses() const;

	/**
	*@brief Function that returns a vector with the courses the student has been approved at
	*@return vector<Course *> with student approved courses
	*/
	vector<Course *> get_approv_courses() const;

	/**
	*@brief Function that returns a vector with the dates at which the student enrolled at a course (organized respectively with the vector of enrolled courses)
	*@return vector<Date *> with the date at which the student enrolled at a course
	*/
	vector<Date *> get_enrol_dates() const;

	/**
	*@brief Function that returns a vector with the dates at which the student was approved at a course (organized respectively with the vector of enrolled courses)
	*@return vector<Date *> with the date at which the student was approved at a course
	*/
	vector<Date *> get_approv_dates() const;

	/**
	*@brief returns the number of approved credits
	*@return number of credits
	*/
	double get_appcredits() const;

	/**
	*@brief returns the number of credits assigned
	*@return number of credits assigned for
	*/
	double get_credits() const;

	/**
	*@brief sets the status of the student to active
	*/
	void resumeDegree();

	/**
	*@brief Changes the Student's name
	*@param newName Student's new name
	*/
	void setName(string newName);

	/**
	*@brief Changes the Student's e-mail
	*@param newEmail Student's new e-mail
	*/
	void setEmail(string newEmail);

	/**
	*@brief Changes the Student's status
	*@param newStatus Student's new status
	*/
	void setStatus(string newStatus);

	/**
	*@brief If a course is complered add credits of the respective course to approved credits of the student
	*@param x number of credits to add
	*/
	void add_approved_credits(double x);

	/**
	*@brief If a course is enrolled add credits of the respective course to credits of the student
	*@param x number of credits to add
	*/
	void add_credits(double x);

	/**
	*@brief Assigns a tutor to the student
	*@param tut Pointer to the Tutor to assign
	*/
	void assign_tutor(Tutor *tut);
	
	/**
	*@brief Enrols a student in a course
	*@param course Course to enrol in
	*@param date Date of the student's enrolment in the course
	*/
	void enroll_course(Course *course, Date *date);

	/**
	*@brief Approves a student at a course
	*@param course Course the student got approved at
	*@param date Date of the student's approval
	*/
	void approve_course(Course *course, Date *date);

	/**
	@brief Prints to an output stream information about a student
	@param os ostream&
	@param s Student to get information from
	*/
	friend ostream& operator<<(ostream &os, const Student &s);
};