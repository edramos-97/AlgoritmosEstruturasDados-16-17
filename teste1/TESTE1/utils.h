#pragma once
#include <windows.h>
#include "course.h"
#include "person.h"
#include "iostream"
#include <fstream>

#define TAB	"\t"		
#define BIG_TAB	"\t\t\t\t\t\t\t"
void clrscr();

Student* read_student(ifstream &f, uint &linenum);
Student* read_student(string &line);
Tutor* read_tutor(ifstream &f, uint &linenum);
Course* read_course(ifstream &f, uint &linenum);
void read_line(ifstream &f, string &line, uint &linenum);
template<typename T>bool check_duplicates(vector<T> v,T arg) 
{
	for (auto x : v)
	{
		if (x->get_name() == arg->get_name() || x->get_code() == arg->get_code())
			return true;
	}
	return false;
};
void save_student(ofstream &f,Student* x);
void save_tutor(ofstream &f,Tutor * x);
void save_course(ofstream &f,Course * x);
int search_for_student(vector<Course*> v, Student * t);
