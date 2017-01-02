#pragma once

#include "Date.h"
#include <iostream>
#include <string>
#include <vector>
#include "exceptions.h"

class Meeting
{
	unsigned id;
	Date date;
	string studentCod;
	string topicsMeeting;
	string description;
public:
	Meeting(unsigned id, Date date, string studentCod, string appointmentBook);
	Meeting(unsigned id, Date date, string studentCod, string appointmentBook,string description);
	Date getDate() const;
	unsigned getId() const;
	string getDescription() const;
	string getTopics() const;
	string getStudentCod() const;
	void setDescription(string discription);
	friend ostream& operator<<(ostream &out, const Meeting *meeting);
};

