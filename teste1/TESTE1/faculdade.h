/**
* @file person.h
* @author AEDA T4GE
* @title Class Department
* @brief Classe used to store all the information
*/
#pragma once

#include "course.h"
#include "person.h"
#include "utils.h"
#include <fstream>
#include <algorithm>

#define NEW_TUTOR true
#define NEW_STUDENT true

class Department {
	string name;
	vector<Tutor*> tutors;
	vector<Student*> students;
	vector<vector<vector<Course*>>> courses; //courses[semester][year][courseInfo]
	vector<Course*> external_courses;
	int next_assign_tutor;
	int next_assign_student;
public:
	/**
	*@brief Constructor of class department
	*@param name name of the department
	*/
	Department(string name);
	/**
	*@brief returns the name of the department
	*/
	string get_name() const;
	/**
	*@brief returns the number on the code of the next tutor
	*/
	int getNext_assigned_tutor(bool newTutor = false);
	/**
	*@brief returns the number on the code of the next tutor
	*/
	int getNext_assigned_student(bool newStudent = false);
	/**
	*@brief returns a student given a student code
	*@param studCode code of the student to look
	*@return returns a pointer to the student you were looking
	*/
	Student* getStudent(const string &studCode) const;
	/**
	*@brief returns a course given a name
	*@param courseName name of the course 
	*@return returns a pointer to the course you were looking
	*/
	Course* getCourse(const string &courseName) const;
	/**
	*@brief adds a tutor to the department
	*@param tutor pointer to the tutor to add
	*/
	void new_tutor(Tutor *tutor);
	/**
	*@brief adds a student without tutor to the department
	*@param stud pointer to the student to add
	*/
	void new_student(Student *stud);
	/**
	*@brief adds a course to the department
	*@param course pointer to the course to add
	*/
	void new_course(Course *course);
	/**
	*@brief adds a student to the department
	*@param stud pointer to the student to add
	*/
	void add_student(Student *stud);
	/**
	*@brief adds an optional course to the department
	*@param course pointer to the course to add
	*/
	void add_external(Course *course);
	/**
	*@brief approves a student if enrolled in a specfied course
	*@param course pointer to the course to appove the student
	*@param stud pointer to the student to approve
	*/
	void approve_student(Student *stud, Course *course);
	/**
	*@brief enrolls a student to a specfied course
	*@param course pointer to the course to enroll the student
	*@param stud pointer to the student to enroll
	*@return returns true if that student was enrolled with success else false
	*/
	bool apply_for_course(Student *stud, Course *course);
	/**
	*@brief enrolls a student to a specfied optional course
	*@param course pointer to the optional course to enroll the student
	*@param stud pointer to the student to enroll
	*@return returns true if that student was enrolled with success else false
	*/
	bool apply_for_course(Student *stud, OptionalCourse *course);
	/**
	*@brief veryfies if a student got approved to a specified course
	*@param year wich year the course is taken
	*@param semester wich semester the course was taken
	*@param course pointer to the course
	*@param stud pointer to the student 
	*@param date pointer to the date
	*@return returns true if that student was approved else false
	*/
	bool verify_courses_completition(uint year, uint semestre, Student *stud, Course *course, Date *date);
	/**
	*@brief look for optional courses with the same scientific area specified on a param
	*@param scientific_area scientific are to look for
	*@return returns a vector with the name of the optional courses found
	*/
	vector<string> search_sci_area(string scientific_area);
	/**
	*@brief reads a course from the textfile
	*@param f reference to the file
	*@param linenum line number 
	*/
	void processCourse(ifstream &f, uint &linenum);
	/**
	*@brief reads everything from the textfile
	*@param filename name of the file
	*/
	void load_dept(string filename);
	/**
	*@brief saves everything on a textfile with the same name as department
	*/
	void save_dept();
	/**
	@brief Operator << for Department
	@param os ostream&
	@param d Department object to use the operator
	*/
	friend ostream& operator<<(ostream &os, const Department &d);
	/**
	@brief returns all courses of the department
	*/
	const vector<vector<vector<Course*>>> get_courses() const;
};