#pragma once
/**
* @file Meeting.h
* @author AEDA T4GE
* @title Class Meeting
* @brief Declaration of Meeting that handles all Meetings in the project.
*/
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
	/**
	*@brief Creates a Meeting on the current or future day, used if the tutor wants create meetings
	*@param id id of the meeting
	*@param date date of the meeting
	*@param studentcod code of the student that requested the meeting
	*@param appointmentBook topics of the meeting
	*/
	Meeting(unsigned id, Date date, string studentCod, string appointmentBook);
	/**
	*@brief Creates a Meeting on any day, used to read from files
	*@param id id of the meeting
	*@param date date of the meeting
	*@param studentcod code of the student that requested the meeting
	*@param appointmentBook topics of the meeting
	*@param description of the meeting
	*/
	Meeting(unsigned id, Date date, string studentCod, string appointmentBook,string description);
	/**
	*@brief Returns the date of the meeting
	*/
	Date getDate() const;
	/**
	*@brief Returns the id of the meeting
	*/
	unsigned getId() const;
	/**
	*@brief Returns the description of the meeting
	*/
	string getDescription() const;
	/**
	*@brief Returns the topics of the meeting
	*/
	string getTopics() const;
	/**
	*@brief Returns the code of the student that requested the meeting
	*/
	string getStudentCod() const;
	/**
	*@brief Sets a the description of a meeting that already ocurred to string passed as param
	*/
	void setDescription(string discription);
	/**
	*@brief operator << with the information of a meeting
	*@param out Stream of the file to print to.
	*@param meeting Meeting to use the operator.
	*/
	friend ostream& operator<<(ostream &out, const Meeting *meeting);
};

