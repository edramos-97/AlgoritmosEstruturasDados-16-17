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
	*@reason  reason that caused a throw
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
	NoSlots(uint year) { this->year = year; }
	uint getYear() const { return year;	}
};

class NoClasses {
public:
	NoClasses(uint year) { this->year = year; }
	uint getYear() const { return year; }
private:
	uint year;
};