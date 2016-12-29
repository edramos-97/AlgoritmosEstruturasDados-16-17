/**
* @file exceptions.h
* @author AEDA T4GE
* @title Generic exception class
* @brief Exception class used throughout the project.
*/
#pragma once

#include <string>
typedef unsigned int uint;
using namespace std;

class exception_or_error {
	string reason;
public:
	/**
	*@brief Creates an exception with a given reason.
	*@param reason Reason for exception throw.
	*/
	exception_or_error(string reason) : reason(reason) {};

	/**
	*@brief Gets exception throw's reason.
	*@return Reason for exception throw.
	*/
	string get_reason() { return reason; };
};


// Unused exceptions.
//class NoSlots {
//	uint year;
//public:
//	/**
//	*@brief constructor of the exception class
//	*@param year year of the class with no slots available
//	*/
//	NoSlots(uint year) { this->year = year; }
//	/**
//	*@brief returns the year data-member
//	*@return year data-member
//	*/
//	uint getYear() const { return year;	}
//};
//
//class NoClasses {
//	uint year;
//public:
//	/**
//	*@brief constructor of the exception class
//	*@param year year that has no available class
//	*/
//	NoClasses(uint year) { this->year = year; }
//	/**
//	*@brief returns the year data-member
//	*@return year data-member
//	*/
//	uint getYear() const { return year; }
//};