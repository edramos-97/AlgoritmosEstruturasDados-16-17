#pragma once

#include <string>
typedef unsigned int uint;
using namespace std;

template <class A, class B> 
class value_out_of_range {
	A value;
	B info;
public:
	value_out_of_range(A value, B info) : value(value),info(info) {};
	A get_value() { return value; };
	B get_info() { return info; };
};



class short_argument {
	string arg,info;
public:
	short_argument(string arg,string info) : arg(arg),info(info) {};
	string get_arg() { return arg; };
	string get_info() { return info; };
};

class not_in_container {
	string info;
public:
	not_in_container(string info) : info(info) {};
	string get_info() { return info; };
};

class file_not_open {
	string name;
public:
	file_not_open(string name) : name(name) {};
	string get_info() { return name; };
};


class corrupted_file {
	uint line;
	string info;
public:
	corrupted_file(uint line,string info) : line(line),info(info){};
	uint get_linenum() { return line; };
	string get_info() { return info; };
};