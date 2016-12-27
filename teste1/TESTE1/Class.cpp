#include "Class.h"

//ClassQueue::ClassQueue(uint year) {
//	this->year = year;
//}
//
//Class* ClassQueue::getMostVacantClass() const {
//	return classes.top();
//}
//
//void ClassQueue::createClass(uint year, uint slots) {
//	uint id = getNewId();
//	Class *c = new Class(id, year, slots);
//	ids.insert(id);
//}
//
//void ClassQueue::removeMostVacantClass() {
//	Class *c = classes.top();
//	ids.erase(c->getId());
//	classes.pop();
//}
//
//void ClassQueue::removeClass(uint id) {
//	stack<Class *> tempClasses;
//	while (!classes.empty()) {
//		if (id == classes.top()->getId()) {
//			Class *removedClass = classes.top();
//			delete removedClass;
//			classes.pop();
//			ids.erase(id);
//			while (!tempClasses.empty()) {
//				classes.push(tempClasses.top());
//				tempClasses.pop();
//			}
//			return;
//		}
//		tempClasses.push(classes.top());
//		classes.pop();
//	}
//	
//	while (!tempClasses.empty()) {
//		classes.push(tempClasses.top());
//		tempClasses.pop();
//	}
//
//	//TODO
//	//throw ClassNotFound(id);
//}
//
//void ClassQueue::addStudent(Student *stud) {
//	if (classes.empty()) {
//		throw NoClasses(year);
//	}
//	classes.top()->enrollStudent(stud);
//}


Class::Class(uint id, uint year, uint slots) : slots(slots),year(year),id(id) {
}

int Class::enrollStudent(Student *stud) {
	if (getOpenSlots() <= 0) {
		return 1;
	}
	studs.push_back(stud);
	return 0;
}

void Class::setStudents(const vector<Student *> &studs) {
	this->studs = studs;
}

vector<Student*> Class::getStuds() const
{
	return studs;
}

uint Class::getOpenSlots() const {
	return slots - (uint) studs.size();
}

bool Class::operator<(Class & c)
{
	return this->getOpenSlots() > c.getOpenSlots();
}

uint Class::getId() const {
	return id;
}

uint Class::getYear() const {
	return year;
}

//bool operator < (Class &c1, Class &c2) {
//	return (c1.getOpenSlots() < c2.getOpenSlots());
//}


// Private methods.

//uint ClassQueue::getNewId() const {
//	for (uint id = 0; id < UINT_MAX; ++id) {
//		if (ids.find(id) == ids.end()) {
//			return id;
//		}
//	}
//
//	//TODO: Exception.
//}