/**
* @file exceptions.h
* @author AEDA T4GE
* @title exception class used on this project
* @brief exception class used on this project
*/
#pragma once

#include <string>
typedef unsigned int uint;
using namespace std;

class exception_or_error {
	string reason;
public:
	/**
	*@brief constructor of the exception class
	*@param reason  reason that caused a throw
	*/
	exception_or_error(string reason) : reason(reason) {};
	/**
	*@brief returns reason that caused a throw
	*@return  returns reason that caused a throw
	*/
	string get_reason() { return reason; };
};

class NoSlots {
	uint year;
public:
	/**
	*@brief constructor of the exception class
	*@param year year of the class with no slots available
	*/
	NoSlots(uint year) { this->year = year; }
	/**
	*@brief returns the year data-member
	*@return year data-member
	*/
	uint getYear() const { return year;	}
};

class NoClasses {
	uint year;
public:
	/**
	*@brief constructor of the exception class
	*@param year year that has no available class
	*/
	NoClasses(uint year) { this->year = year; }
	/**
	*@brief returns the year data-member
	*@return year data-member
	*/
	uint getYear() const { return year; }
};