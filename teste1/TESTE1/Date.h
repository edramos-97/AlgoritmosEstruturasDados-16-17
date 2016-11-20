/**
* @file Date.h
* @author AEDA T4GE
* @title Date
* @brief Definition of Class that handles all dates in this project
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
	@brief By default contructor wich creates an object date with the actual date of the day
	*/
	Date();

	/**
	@brief Contructor wich creates an object date from a string in the format Day/Month/Year
	@param dateStr String that contains a date
	*/
	Date(string dateStr); 

	/**
	@brief Returns the day of an object type Date
	@return day
	*/
	int getDay() const;

	/**
	@brief Returns the month of an object type Date
	@return month
	*/
	int getMonth() const;

	/**
	@brief Returns the year of an object type Date
	@return year
	*/
	int getYear() const;

	/**
	@brief Saves an object type Date in a file in the format DD/MM/YY
	@param out reference to the file
	*/
	void save(ofstream & out) const;

	/**
	@brief Operator << for Date
	@param out ostream&
	@param data Date object to use the operator
	*/
	friend ostream& operator<<(ostream& out, const Date & data);

	/**
	@brief Operator < for class Date
	@param date1 object type Date
	@param date2 object type Date
	@return return true if date1 < date2
	*/
	friend bool operator<(const Date &date1, const Date &date2);
};

