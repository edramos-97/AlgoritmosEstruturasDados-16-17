#ifndef CLASS_H
#define CLASS_H

#include "person.h"
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

class Class;

/*class ClassQueue {
public:
	ClassQueue(uint year);
	Class* getMostVacantClass() const;
	void createClass(uint year, uint slots);
	void removeMostVacantClass();
	void removeClass(uint id);
	void addStudent(Student *stud);
private:
	priority_queue<Class *> classes;
	set<uint> ids;
	uint year;

	uint getNewId() const;
};*/

class Class {
private:
	uint id;
	uint year;
	const uint slots;
	vector<Student *> studs;
	bool operator < (Class &c);
public:
	/**
	*@brief Constructor of class Class
	*@param year year of the Class
	*@param slots number of slots per course
	*/
	Class(uint id ,uint year, uint slots);
	/**
	*@brief adds a students to the class with the most open slots
	*@param stud pointer to the student
	*/
	int enrollStudent(Student *stud);
	/**
	*@brief gets the value of open slots of a class
	*@return returns the value of open slots of a class
	*/
	vector<Student *> getStuds() const;
	uint getOpenSlots() const;
	uint getId() const;
	uint getYear() const;
};



#endif