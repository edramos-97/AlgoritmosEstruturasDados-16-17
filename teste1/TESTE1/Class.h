#ifndef CLASS_H
#define CLASS_H

#include "person.h"
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <utility>
#include <memory>

using namespace std;

class Class {
private:
	uint id;
	uint year;
	vector<pair<Course*, uint>> openSlots;
	vector<Student *> studs;
public:
	/**
	*@brief Constructor of Class.
	*@param id ID of the Class.
	*@param year Year of the Class from 1 to 5.
	*@param courses Vector with pointers to the Courses to associate with the Class.
	*@param slots Number of slots per course.
	*/
	Class(uint id, uint year, vector<Course*> courses, uint slots);

	/**
	*@brief Constructor of class Class.
	*@param id ID of the Class.
	*@param year Year of the Class from 1 to 5.
	*@param courseSlots Vector of pairs (Course*, uint) describing open slots per course.
	*/
	Class(uint id, uint year, vector<pair<Course*, uint>> courseSlots);
	
	/**
	*@brief Adds a students to the Class.
	*@param stud Pointer to the student to enroll.
	*/
	void enrollStudent(Student *stud);

	/**
	*@brief Sets new students belonging to the Class (any previous students are forgotten).
	*@param studs Vector with pointers to Students.
	*/
	void setStudents(const vector<Student *> &studs);

	/**
	*@brief Gets the students belong to the Class.
	*@return Vector with pointers to Students.
	*/
	vector<Student *> getStuds() const;

	/**
	*@brief Gets the open slots per course.
	*@return Vector of pairs (Course*, uint) describing open slots per course.
	*/
	vector<pair<Course*, uint>> getCourseSlots() const;

	/**
	*The amount of open slots is the lowest of the amounts per course.
	*@brief Gets the amount of open slots in a Class.
	*@return Number of open slots in a Class.
	*/
	uint getOpenSlots() const;

	/**
	*@brief Gets the ID of the Class.
	*@return Class ID.
	*/
	uint getId() const;
	
	/**
	*@brief Gets the year of the Class.
	*@return Year of the Class.
	*/
	uint getYear() const;

	/**
	*c1 is "smaller" than c2 if the amount of its open slots is higher than the amount of c2's open slots.
	*@brief Compares Classes in a way that they're correctly ordered in a priority queue.
	*@param c1 Class.
	*@param c2 Class.
	*@return True if c1 is "smaller" than c2, false otherwise.
	*/
	friend bool operator < (const Class &c1, const Class &c2);

	/*template <class template_Class = Class *>
	bool classComp(const template_Class c1, const template_Class c2) {
		return (*c1 < *c2);
	}*/
};

//bool class_cmp(Class &a,Class &b)
//{
//	return (a.getOpenSlots() < b.getOpenSlots());
//}
#endif