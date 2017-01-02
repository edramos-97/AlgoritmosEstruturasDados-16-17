#include "Date.h"

//cria uma date do dia atual
Date::Date(){
	time_t t = time(0);   // get time now
	struct tm  now;
	localtime_s(&now,&t);

	year = (now.tm_year + 1900);
	month = (now.tm_mon + 1);
	day = now.tm_mday;
}

int maxmonthday(int month){
	switch (month){
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return 29;
	default:
		return 31;
	}
}

Date::Date(string dateStr){
	string tmp;
	size_t pos;
	pos = dateStr.find('/');
	
	if (pos == -1)
		throw exception_or_error("Data nao tem o formato DD/MM/YY");
		
	tmp = dateStr.substr(0, pos);
	day = stoi(tmp);
	dateStr.erase(0, pos + 1);
	pos = dateStr.find('/');
	
	if (pos == -1)
		throw exception_or_error("Data nao tem o formato DD/MM/YY");
	
	tmp = dateStr.substr(0, pos);
	month = stoi(tmp);
	dateStr.erase(0, pos + 1);
	year = stoi(dateStr);
	
	Date currentyear;

	if (month > 12 || day > maxmonthday(month)||year<1970||year>currentyear.getYear())
		throw exception_or_error("Data nao tem o formato DD/MM/YY");
}

int Date::getDay() const{
	return day;
}

int Date::getMonth() const{
	return month;
}

int Date::getYear() const{
	return year;
}

void Date::save(ofstream & out) const{
	out << day << '/' << month << '/' << year;
	return;
}

ostream& operator<<(ostream& out, const Date & date){
	out << date.day << '/' << date.month << '/' << date.year;
	return out;
}

bool operator<(const Date &date1, const Date &date2){
	if (date1.getYear() < date2.getYear())
		return true;
	else if (date1.getYear() > date2.getYear())
		return false;

	if (date1.getMonth() < date2.getMonth())
		return true;
	else if (date1.getMonth() > date2.getMonth())
		return false;

	return date1.getDay() < date2.getDay();
}

bool Date::operator==(const Date &date) const {
	return (day == date.getDay() && month == date.getMonth() && year == date.getYear());
}
