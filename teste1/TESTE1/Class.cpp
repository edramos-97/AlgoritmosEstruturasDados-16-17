#include "Class.h"

Class::Class(uint id, uint year, vector<Course*> courses, uint slots) : year(year), id(id) {
	for (size_t ind = 0; ind < courses.size(); ++ind) {
		pair<Course*, uint> slot(courses.at(ind), slots);
		openSlots.push_back(slot);
	}
}

Class::Class(uint id, uint year, vector<pair<Course*, uint>> courseSlots) {
	this->id = id;
	this->year = year;
	openSlots = courseSlots;
}

void Class::enrollStudent(Student *stud) {
	if (getOpenSlots() <= 0) {
		throw exception_or_error("Nao ha vagas nas turmas deste ano.");
	}
	for (size_t ind = 0; ind < openSlots.size(); ++ind) {
		openSlots.at(ind).second--;
	}
	studs.push_back(stud);
}

void Class::setStudents(const vector<Student *> &studs) {
	this->studs = studs;
}

vector<Student*> Class::getStuds() const {
	return studs;
}

vector<pair<Course*, uint>> Class::getCourseSlots() const {
	return openSlots;
}

uint Class::getOpenSlots() const {
	uint lowestSlots = UINT_MAX;
	for (size_t ind = 0; ind < openSlots.size(); ++ind) {
		if (openSlots.at(ind).second < lowestSlots) {
			lowestSlots = openSlots.at(ind).second;
		}
	}
	return lowestSlots;
}

//bool Class::operator<(Class & c)
//{
//	return this->getOpenSlots() > c.getOpenSlots();
//}

uint Class::getId() const {
	return id;
}

uint Class::getYear() const {
	return year;
}

bool operator < (const Class &c1, const Class &c2) {
	return (c1.openSlots[0].second < c2.openSlots[0].second);
}