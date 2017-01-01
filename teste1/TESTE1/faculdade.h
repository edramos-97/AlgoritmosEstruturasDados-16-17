/**
* @file faculdade.h
* @author AEDA T4GE
* @title Class Department
* @brief Class used to store all the information
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

struct stoppedStudsHash {
	size_t operator () (const Student *s) const {
		try {
			return stoul(s->get_code().substr(2, string::npos));
		}
		catch (invalid_argument) {
			throw exception_or_error("Invalid Student code: " + s->get_code());
		}
	}
	bool operator () (const Student *s1, const Student *s2) const {
		return (*s1 == *s2);
	}
};

class classComp {
public:
	bool operator () (const Class *c1, const Class *c2) const {
		return (*c1 < *c2);
	}
};

class Department {
private:
	string name;
	vector<Tutor*> tutors;
	vector<Student*> students;
	vector<vector<vector<Course*>>> courses; //courses[semester][year][courseInfo]
	vector<Course*> external_courses;
	int next_assign_tutor;
	int next_assign_student;

	vector<priority_queue<Class*, vector<Class*>, classComp>> classes = vector<priority_queue<Class*, vector<Class*>, classComp>>(5);
	unordered_set<Student*, stoppedStudsHash, stoppedStudsHash> stoppedStuds; // For students who interrupted or finished the degree.
public:
	/**
	*@brief Constructor of class Department.
	*@param name Name of the Department.
	*/
	Department(string name);

	/**
	*@brief Gets Department's name.
	*@return Name of the Department.
	*/
	string get_name() const;

	/**
	*@brief Gets the code, as a number, which will be given to a new Tutor.
	*@return Number of a new Tutor's code.
	*/
	int getNext_assigned_tutor(bool newTutor = false);

	/**
	*@brief Gets the code, as a number, which will be given to a new Student.
	*@return Number of a new Student's code.
	*/
	int getNext_assigned_student(bool newStudent = false);

	/**
	*@brief Gets the Student of a given Student code.
	*@param studCode Code of the wanted Student.
	*@return Pointer to the wanted Student.
	*/
	Student* getStudent(const string &studCode) const;

	/**
	*@brief Gets the Tutor of a given Tutor code.
	*@param tutorCode Code of the wanted Tutor.
	*@return Pointer to the wanted Tutor.
	*/
	Tutor* getTutor(const string &tutorCode) const;

	/**
	*@brief Gets the Course of a given course name.
	*@param courseName Name of the wanted Course.
	*@return Pointer to the wanted Course.
	*/
	Course* getCourse(const string &courseName) const;

	/**
	*@brief Adds a Tutor to the Department.
	*@param tutor Pointer to the Tutor to add.
	*/
	void new_tutor(Tutor *tutor);

	/**
	*@brief Adds a Student without an assigned Tutor to the Department.
	*@param stud Pointer to the Student to add.
	*/
	void new_student(Student *stud);

	/**
	*@brief Assigns a Tutor to a Student.
	*@param stud Pointer to the Student to receive a Tutor.
	*/
	void assignTutor(Student *stud);

	/**
	*@brief Adds a Course to the Department.
	*@param course Pointer to the Course to add.
	*/
	void new_course(Course *course);

	/**
	*@brief Adds a Student to the Department while making sure a Tutor is given.
	*@param stud Pointer to the Student to add.
	*/
	void add_student(Student *stud);

	/**
	*@brief Adds an external Course to the Department.
	*@param course Pointer to the Course to add.
	*/
	void add_external(Course *course);

	/**
	*@brief Approves a Student enrolled in a certain Course.
	*@param course Pointer to the Course to approve the Student to.
	*@param stud Pointer to the student to approve.
	*/
	void approve_student(Student *stud, Course *course);

	/**
	*@brief Enrolls a Student in a certain Course.
	*@param course Pointer to the Course to enroll the Student to.
	*@param stud Pointer to the Student to enroll.
	*@return True if student was successfully enrolled, else false.
	*/
	bool apply_for_course(Student *stud, Course *course);

	/**
	*@brief Enrolls a Student in a certain OptionalCourse.
	*@param course Pointer to the OptionalCourse to enroll the Student to.
	*@param stud Pointer to the Student to enroll.
	*@return True if student was successfully enrolled, else false.
	*/
	bool apply_for_course(Student *stud, OptionalCourse *course);

	/**
	*@brief Verifies if a Student can be approved to certain Course, approving him if so.
	*@param year Year of the Course.
	*@param semester Semester of the Course.
	*@param course Pointer to the Course.
	*@param stud Pointer to the Student wanting approval.
	*@param date Pointer to the Date of the Student's wanted approval.
	*@return True if Student was approved, false otherwise.
	*/
	bool verify_courses_completition(uint year, uint semestre, Student *stud, Course *course, Date *date);

	/**
	*@brief Gets external courses of a certain scientific area.
	*@param scientific_area Wanted scientific area.
	*@return Vector with the name of the external courses.
	*/

	bool searchstudent(string studentCod) const;
	vector<string> search_sci_area(string scientific_area);

	/**
	*@brief Reads a Course from a text file.
	*@param f File to read.
	*@param linenum File's line currently being read.
	*/
	void processCourse(ifstream &f, uint &linenum);

	/**
	*@brief Reads a Class from a text file.
	*@param f File to read.
	*@param linenum File's line currently being read.
	*/
	void processClass(ifstream &f, uint &linenum);

	/**
	*@brief Loads Department from a text file.
	*@param filename Name of the file.
	*/
	void load_dept(string filename);

	/**
	*@brief Saves Department's information to a text file named with the Department's name.
	*/
	void save_dept();

	/**
	*@brief Prints information about a Department to an output stream.
	*@param os Output stream to print to.
	*@param dept Department to print information of.
	*/
	friend ostream& operator << (ostream &os, const Department &dept);

	/**
	*Vector is organized per semester and year. It should be accessed as: courses.at(semester - 1).at(year - 1).at(courseInd)
	*@brief Gets Department's Courses.
	*@return 3D vector with pointers to Courses.
	*/
	const vector<vector<vector<Course*>>> get_courses() const;

	/**
	*New ID is the lowest starting from 1 which isn't in use by another Class.
	*Function does not alter Department. It is not const because it changes the classes vector but finishes by restoring it to its initial state.
	*@brief Gets the ID for a new Class.
	*@param year Year of the new Class.
	*@return ID of a new Class.
	*/
	uint getNewClassId(uint year);

	/**
	*@brief Creates a new Class in the Department.
	*@param year Year of the Class.
	*@param slots Slots available.
	*@param id ID of the Class.
	*/
	void createClass(uint year, uint slots, uint id);

	/**
	*@brief Enrolls a Student in a Class.
	*@param stud Pointer to the Student to enroll.
	*@param year Year of the Class.
	*/
	void enrollInClass(Student *stud, uint year);

	/**
	*@brief Deletes a certain Class from the Department.
	*@param year Year of the Class.
	*@param id ID of the Class.
	*/
	int deleteClass(uint year, uint id);

	/**
	*Function does not alter Department. It is not const because it changes the classes vector but finishes by restoring it to its initial state.
	*@brief Gets a Class in the Department.
	*@param year Year of the Class.
	*@param id ID of the Class.
	*@return Pointer to the wanted Class.
	*/
	Class* findClass(uint year, uint id);

	/**
	*@brief Function that outputs to the console the 3 classe with the most slts available in a given year.
	*@param year Year of the Class.
	*/
	void top_slots(uint year);

	/**
	*@brief Prints the current Students to stdout in an user-defined order.
	*@param comp Comparison function used to sort the printed Students.
	*/
	void listCurrentStuds(bool comp(Student *s1, Student *s2)) const;

	/**
	*@brief Prints the Students who interrupted their degrees to stdout in an user-defined order.
	*@param comp Comparison function used to sort the printed Students.
	*/
	void listIntStuds(bool comp(Student *s1, Student *s2)) const;

	/**
	*@brief Prints the Students who finished their degrees to stdout in an user-defined order.
	*@param comp Comparison function used to sort the printed Students.
	*/
	void listFinishedStuds(bool comp(Student *s1, Student *s2)) const;
};