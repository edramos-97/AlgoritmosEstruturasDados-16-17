#pragma once

#include "Date.h"
#include <iostream>
#include <string>
#include <vector>
#include "exceptions.h"

class Meeting
{
	Date date;
	string studentCod;
	vector <string> appointmentBook;
	string description;
public:
	Meeting(Date date, string studentCod, vector <string> appointmentBook, string description);
	// a implementar
};

