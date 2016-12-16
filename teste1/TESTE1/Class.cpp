#include "Class.h"

Class* ClassQueue::top() const {
	return classes.top();
}

void ClassQueue::createClass(uint year, uint slots) {
	uint id = getNewId();
	Class *c = new Class(id, year, slots);
	ids.insert(id);
}

void ClassQueue::pop() {
	Class *c = classes.top();
	ids.erase(c->getId());
	classes.pop();
}

Class::Class(uint id, uint year, uint slots) : slots(slots) {
	this->id = id;
	this->year = year;
}

bool Class::enrollStudent(Student *stud) {
	if (slots - studs.size() > 0) {
		studs.push_back(stud);
		return true;
	}
	else
		return false;
}

uint Class::getOpenSlots() const {
	return slots - studs.size();
}

uint Class::getId() const {
	return id;
}

bool operator < (Class &c1, Class &c2) {
	return (c1.getOpenSlots() < c2.getOpenSlots());
}


uint ClassQueue::getNewId() const {
	for (uint id = 0; id < UINT_MAX; ++id) {
		if (ids.find(id) == ids.end()) {
			return id;
		}
	}

	//TODO: Exception.
}