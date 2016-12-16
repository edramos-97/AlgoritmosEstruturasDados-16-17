#ifndef CLASS_H
#define CLASS_H

#include "person.h"
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Class;

class ClassQueue {
public:
	Class* getMostVacantClass() const;
	void createClass(uint year, uint slots);
	void removeMostVacantClass();
	void removeClass(uint id);
	void addStudent(Student *stud);
private:
	priority_queue<Class *> classes;
	set<uint> ids;

	uint getNewId() const;
};

class Class {
public:
	Class(uint id, uint year, uint slots);
	void enrollStudent(Student *stud);
	uint getOpenSlots() const;
	uint getId() const;

private:
	uint id;
	uint year;
	const uint slots;
	vector<Student *> studs;
};

bool operator < (Class &c1, Class &c2);

#endif