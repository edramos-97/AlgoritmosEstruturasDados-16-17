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
	int date1totaldays = date1.day + 32 * date1.month + 367 * date1.year;
	int date2totaldays = date2.day + 32 * date2.month + 367 * date2.year;
	
	return date1totaldays < date2totaldays;
}

bool Date::operator==(const Date &date) const {
	int this_Datetotaldays = day + 32 * month + 367 * year;
	int datetotaldays = date.getDay() + 32 * date.getMonth() + 367 * date.getYear();

	return this_Datetotaldays == datetotaldays;
}
