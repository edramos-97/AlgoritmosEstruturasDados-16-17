#include "Meeting.h"

Meeting::Meeting(unsigned id, Date date, string studentCod, string appointmentBook)
{
	this->id = id;
	this->date = date;
	this->studentCod = studentCod;
	this->topicsMeeting = appointmentBook;
	description = "No description";
}

Meeting::Meeting(unsigned id, Date date, string studentCod, string appointmentBook, string description)
{
	this->id = id;
	this->date = date;
	this->studentCod = studentCod;
	this->topicsMeeting = appointmentBook;
	this->description = description;
}

Date Meeting::getDate() const
{
	return date;
}

unsigned Meeting::getId() const
{
	return id;
}

string Meeting::getDescription() const
{
	return string();
}


void Meeting::setDescription(string discription)
{
	this->description = description;
	return;
}

bool Meeting::operator<(const Meeting * meeting) const
{
	if (date == meeting->getDate())
		return id < meeting->getId;
	return date < meeting->getDate();
}

ostream & operator<<(ostream & out, const Meeting * meeting)
{
	out << "Meeting Id: " << meeting->id << endl;
	out << "Date: " << meeting->date << endl;
	out << "Student Code that requested the meeting: " << meeting->studentCod << endl;
	out << "Topics of the meeting: " << meeting->topicsMeeting << endl;
	if (meeting->description != "No description")
		out << "Description: " << meeting->description;
	return out;
}
