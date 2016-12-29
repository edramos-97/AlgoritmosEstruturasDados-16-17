/**
* @file Date.h
* @author AEDA T4GE
* @title Class Date
* @brief Declaration of Date that handles all dates in the project.
*/

#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "exceptions.h"
using namespace std;


class Date {
private:
	int day;
	int month;
	int year;
public:
	/**
	*@brief Creates a Date with the current date.
	*/
	Date();

	/**
	*@brief Creates a Date with the date information in a string.
	*@param dateStr String containing a date in the format DD/MM/YYYY.
	*/
	Date(string dateStr); 

	/**
	*@brief Gets the Date's day.
	*@return Day.
	*/
	int getDay() const;

	/**
	*@brief Gets the Date's month.
	*@return Month.
	*/
	int getMonth() const;

	/**
	*@brief Gets the Date's year.
	*@return Year.
	*/
	int getYear() const;

	/**
	*@brief Prints the Date to a file in the format DD/MM/YYYY.
	*@param out Stream of the file to print to.
	*/
	void save(ofstream &out) const;

	/**
	*@brief Prints a Date to an output stream in the format DD/MM/YYYY.
	*@param out Stream to print to.
	*@param date Date to print.
	*@return The printed stream, out.
	*/
	friend ostream& operator<<(ostream &out, const Date &date);

	/**
	*Compares Dates by their amount of days since 00/00/0000.
	*@brief Compares Dates.
	*@param date1 Date.
	*@param date2 Date.
	*@return True if date1 is older than date2, false otherwise.
	*/
	friend bool operator<(const Date &date1, const Date &date2);
};

