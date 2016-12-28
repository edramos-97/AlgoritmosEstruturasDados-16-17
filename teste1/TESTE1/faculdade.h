/**
* @file faculdade.h
* @author AEDA T4GE
* @title Class Department
* @brief Classe used to store all the information
*/
#pragma once

#include "Class.h"
#include "course.h"
#include "person.h"
#include "utils.h"
#include <queue>
#include <set>
#include <unordered_set>
#include <fstream>
#include <algorithm>

#define NEW_TUTOR true
#define NEW_STUDENT true

class Department {
private:
	string name;
	vector<Tutor*> tutors;
	vector<Student*> students;
	vector<vector<vector<Course*>>> courses; //courses[semester][year][courseInfo]
	vector<Course*> external_courses;
	int next_assign_tutor;
	int next_assign_student;

	vector<priority_queue<Class *>> classes = vector<priority_queue<Class *>>(5);
	unordered_set<Student *> stoppedStuds; // For students who interrupted or finished the degree.
public:
	/**
	*@brief Constructor of class department
	*@param name Name of the department
	*/
	Department(string name);

	/**
	*@brief Returns the name of the department
	*/
	string get_name() const;

	/**
	*@brief Returns the number on the code of the next tutor
	*/
	int getNext_assigned_tutor(bool newTutor = false);

	/**
	*@brief returns the number on the code of the next tutor
	*/
	int getNext_assigned_student(bool newStudent = false);

	/**
	*@brief Returns a student given a student code
	*@param studCode Code of the wanted student
	*@return Returns a pointer to the wanted student
	*/
	Student* getStudent(const string &studCode) const;

	/**
	*@brief Returns a tutor given a tor code
	*@param tutorCode Code of the wanted tutor
	*@return Returns a pointer to the wanted tutor
	*/
	Tutor* getTutor(const string &tutorCode) const;

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
	*@brief Adds a student without tutor to the department
	*@param stud Pointer to the student to add
	*/
	void new_student(Student *stud);

	/**
	*@brief Assigns a tutor to a student
	*@param stud Pointer to the student that will be assigned a tutor
	*/
	void assignTutor(Student *stud);

	/**
	*@brief Adds a course to the department
	*@param course Pointer to the course to add
	*/
	void new_course(Course *course);

	/**
	*@brief adds a student to the department
	*@param stud pointer to the student to add
	*/
	void add_student(Student *stud);

	/**
	*@brief Adds an optional course to the department
	*@param course Pointer to the course to add
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
	*@brief reads a class from the textfile
	*@param f reference to the file
	*@param linenum line number in the file
	*/
	void processClass(ifstream &f, uint &linenum);

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

	// This should be const.
	uint getNewClassId(uint year);

	/**
	*@brief creates a new class and add it to the respective queue in the classes vector
	*@param year year of the class
	*@param slots max number of slots available
	*@param id id number of the class
	*/
	void createClass(uint year, uint slots, uint id);

	/**
	*@brief enrolls a student to a class
	*@param stud pointer to the student to enroll in the class
	*@param year year of the class to which the student will enroll
	*/
	void enrollInClass(Student *stud, uint year);

	/**
	*@brief removes a class from the respective queue
	*@param year year of the class
	*@param id id number of the class
	*/
	int deleteClass(uint year, uint id);

	/**
	*@brief finds a class in the classes vector
	*@param year year of the class
	*@param id id number of the class
	*/
	Class* findClass(uint year, uint id);

	/**
	*@brief sorts the student vector and outputs it in a user friendly way to the console
	*@param comp comparison funciton to use in order to sort the vector
	*/
	void Department::listCurrentStuds(bool comp(Student *s1, Student *s2)) const;

	/**
	*@brief sorts the student that interrupted the degree and outputs them in a user friendly way to the console
	*@param comp comparison function to use in order to sort the vector
	*/
	void listIntStuds(bool comp(Student *s1, Student *s2)) const;

	/**
	*@brief sorts the students that finished the degree and outputs them in a user friendly way to the console
	*@param comp comparison function to use in order to sort the vector
	*/
	void listFinishedStuds(bool comp(Student *s1, Student *s2)) const;
};