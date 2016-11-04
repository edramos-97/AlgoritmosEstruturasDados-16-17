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
	int totaldays;
public:
	Date();
	Date(string dateStr); // data na forma DD/MM/AAA
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	int getTotaldays() const;
	void setDay(int dia);
	void setMonth(int mes);
	void setYear(int ano);
	void save(ofstream & out) const;
	friend ostream& operator<<(ostream& out, const Date & data);
	friend bool operator<(const Date &date1, const Date &date2);
};

