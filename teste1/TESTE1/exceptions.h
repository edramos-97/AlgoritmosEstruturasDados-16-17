#pragma once

#include <string>
typedef unsigned int uint;
using namespace std;

class exception_or_error {
	string reason;
public:
	exception_or_error(string reason) : reason(reason) {};
	string get_reason() { return reason; };
};


//
//class short_argument {
//	string arg,info;
//public:
//	short_argument(string arg,string info) : arg(arg),info(info) {};
//	string get_arg() { return arg; };
//	string get_info() { return info; };
//};

//class not_in_container {
//	string info;
//public:
//	not_in_container(string info) : info(info) {};
//	string get_info() { return info; };
//};
//
//class file_not_open {
//	string name;
//public:
//	file_not_open(string name) : name(name) {};
//	string get_info() { return name; };
//};
//
//class corrupted_file {
//	uint line;
//	string info;
//public:
//	corrupted_file(uint line,string info) : line(line),info(info){};
//	uint get_linenum() { return line; };
//	string get_info() { return info; };
//};
//
//class date_not_valid {};
//class input_not_valid {};
//
//class StudentNotFound {
//	string studentCode;
//public:
//	StudentNotFound() {}
//	StudentNotFound(string studCode) {
//		studentCode = studCode;
//	}
//	string getStudCode() const {
//		return studentCode;
//	}
//};
//
//class CourseNotFound {
//	string courseName;
//public:
//	CourseNotFound() {}
//	CourseNotFound(string cName) {
//		courseName = cName;
//	}
//	string getCourseName() const {
//		return courseName;
//	}
//};

