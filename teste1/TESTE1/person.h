/**
* @file person.h
* @author AEDA T4GE
* @title Class Person and Subclasses Stundent and Tutor
* @brief Classes used to store information of a Student or a Tutor
*/
#pragma once


#include <vector>
#include <string>
#include <set>
#include "exceptions.h"
#include "course.h"
#include "Date.h"
#include "Meeting.h"

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
	uint nextid;
	set<Meeting *> meetings;
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

	void create_newMeeting(string studentCod,string topics, string dateStr);

	void add_meeting(Meeting *meeting);

	void remove_meeting(uint IdMeeting);

	void ChangeMeetingDescription(unsigned IdMeeting,string description);

	void ListAllMeettings() const;

	void ListPastMeetings() const;

	void ListFutureMeetings() const;

	void ListMeetingsBeetween2Dates(Date date1, Date date2) const;

	vector<uint> PastMeetings_NoDescription() const;

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
	*@brief Constructor of Student.
	*@param code Student's code.
	*@param name Student's name.
	*@param email Student's e-mail.
	*@param status Student's status ("Trabalhador Estudante", "Ordinário").
	*@param tutor Student's Tutor's code.
	*/
	Student(string code, string name, string email, string status, string tutor);

	/**
	*@brief Constructor of Student.
	*@param code Student's code.
	*@param name Student's name.
	*@param email Student's e-mail.
	*@param status Student's status ("Trabalhador Estudante", "Ordinário").
	*@param interrupted True if student has interrupted the degree, false otherwise.
	*@param finished True if student has terminated the degree, false otherwise.
	*/
	Student(string code, string name, string email, string status, bool interrupted, bool finished);

	/**
	*@brief Gets a Student's name.
	*@return Name of the Student.
	*/
	string get_name() const;

	/**
	*@brief Gets a Student's code.
	*@return Code of the Student.
	*/
	string get_code() const;

	/**
	*@brief Gets a Student's e-mail.
	*@return E-mail of the Student.
	*/
	string get_email() const;

	/**
	*@brief Gets a Student's status.
	*@return Status of the Student.
	*/
	string get_status() const;

	/**
	*@brief Gets a Student's Tutor's code.
	*@return Student's Tutor's code.
	*/
	string get_tutor() const;
	
	/**
	*@brief Gets interrupted attribute.
	*@return True if Student interrupted degree, false otherwise.
	*/
	bool hasInterrupted() const;

	/**
	*@brief Gets finished attribute.
	*@return True if Student finished degree, false otherwise.
	*/
	bool hasFinished() const;

	/**
	*@brief Gets the Courses the Student is enrolled in.
	*@return Vector with pointers to Courses the Student is enrolled in.
	*/
	vector<Course *> get_enrol_courses() const;

	/**
	*@brief Gets the Courses the Student is approved in.
	*@return Vector with pointers to Courses the Student is approved in.
	*/
	vector<Course *> get_approv_courses() const;

	/**
	*Gets the Dates of when the Student enrolled each Course with the same index in the enrolled_courses vector.
	*@brief Gets the enrolled Dates.
	*@return Vector with pointers to enrolled Dates.
	*/
	vector<Date *> get_enrol_dates() const;

	/**
	*Gets the Dates of when the Student approved each Course with the same index in the approved_courses vector.
	*@brief Gets the approved Dates.
	*@return Vector with pointers to approved Dates.
	*/
	vector<Date *> get_approv_dates() const;

	/**
	*@brief Gets the Student's approved credits.
	*@return Number of approved credits.
	*/
	double get_appcredits() const;

	/**
	*@brief Gets the Student's enrolled credits.
	*@return Number of enrolled credits.
	*/
	double get_credits() const;

	/**
	*@brief Changes state of Student from interrupted to current.
	*/
	void resumeDegree();

	/**
	*@brief Changes the Student's name.
	*@param newName Student's new name.
	*/
	void setName(string newName);

	/**
	*@brief Changes the Student's e-mail.
	*@param newEmail Student's new e-mail.
	*/
	void setEmail(string newEmail);

	/**
	*@brief Changes the Student's status.
	*@param newStatus Student's new status.
	*/
	void setStatus(string newStatus);

	/**
	*@brief Moves given credits from enrolled to approved.
	*@param cred Number of credits.
	*/
	void add_approved_credits(double cred);

	/**
	*@brief Add given credits to the Student's enrolled credits.
	*@param cred Number of credits.
	*/
	void add_credits(double cred);

	/**
	*@brief Assigns a given tutor to the Student.
	*@param tut Pointer to the Tutor to assign.
	*/
	void assign_tutor(Tutor *tut);
	
	/**
	*Adds the Course and Date in the Student's enrolled vectors.
	*@brief Enrolls the Student in a Course.
	*@param course Course to enroll in.
	*@param date Date of the Student's enrollment in the Course.
	*/
	void enroll_course(Course *course, Date *date);

	/**
	*Adds the Course and Date in the Student's approved vectors.
	*@brief Approves the Student in a Course.
	*@param course Course to approve in.
	*@param date Date of the Student's approval.
	*/
	void approve_course(Course *course, Date *date);

	/**
	*Prints the Student's code, name, e-mail, status, tutor, and enrolled and approved credits.
	@brief Prints to an output stream information about a Student.
	@param os Output stream.
	@param s Student to get information from.
	@return Output stream os.
	*/
	friend ostream& operator << (ostream &os, const Student &s);
};