/**
* @file utils.h
* @author AEDA T4GE
* @title Utilitie Functions
* @brief Utilitie functions and definitions to help in the development of this project
*/

#pragma once
#include <windows.h>
#include "course.h"
#include "person.h"
#include "Class.h"
#include <iostream>
#include <fstream>

#define TAB	"\t"		
#define BIG_TAB	"\t\t\t\t\t\t\t"
/**
@brief Clears console screen, for a clean look, expecially used in menus
*/
void clrscr();
/**
*@brief reads the information of a student from the text file, used in Faculdade::load_dept
*@param f ifstream that contains reference to the file
*@param linenum number of the line being treated
*@return returns a pointer to the student created 
*/
Student* read_student(ifstream &f, uint &linenum);

//TODO - Docs.
void readStudentInCourse(string &line, string &studCode, Date **date);
/**
*@brief reads  the information of a student from the textfile under some course, used in read_course
*@param line string to conver to object type student
*@return returns a pointer to the student created
*/
Student* read_student(string &line);
/**
*@brief reads the information of a tutor from the text file, used in Faculdade::load_dept
*@param f ifstream that contains reference to the file
*@param linenum number of the line being treated
*@return returns a pointer to the tutor created
*/
Tutor* read_tutor(ifstream &f, uint &linenum);

Meeting* read_meeting(ifstream &f, uint &linenum);
/**
*@brief reads a line from the text file and puts it on a string, used in Faculdade::load_dept
*@param f ifstream that contains reference to the file
*@param line string wich will have the content from the line
*@param linenum number of the line being treated
*/
void read_line(ifstream &f, string &line, uint &linenum);
/**
*@brief checks if a vector already contains an equal argument to the what he want;
*@param v vector to check
*@param arg argument to check if already exists in the vector
*@return returns a true if it already exist else false
*/
template<typename T>bool check_duplicates(vector<T> v,T arg);
/**
*@brief saves the information of an object of type class in the textfile, used in Faculdade::save_dept
*@param f ofstream that contains reference to the file
*@param x student to save
*@return returns a true if it already exist else false
*/
void save_class(ofstream &f, Class * x);

void save_meeting(ofstream &f, Meeting * x);
/**
*@brief saves the information of an object of type student in the textfile, used in Faculdade::save_dept
*@param f ofstream that contains reference to the file
*@param x student to save
*/
void save_student(ofstream &f,Student* x);
/**
*@brief saves the information of an object of type tutor in the textfile, used in Faculdade::save_dept
*@param f ofstream that contains reference to the file
*@param x tutor to save
*/
void save_tutor(ofstream &f,Tutor * x);
/**
*@brief saves the information of an object of type tutor in the textfile, used in Faculdade::save_dept
*@param f ofstream that contains reference to the file
*@param x tutor to save
*/
void save_course(ofstream &f,Course * x);
/**
*@brief saves the information of an object type external course in the textfile, used in Faculdade::save_dept
*@param f ofstream that contains reference to the file
*@param x external course to save
*/
void save_external(ofstream & f, Course * x);
/**
*@brief 
*@param v Vector of courses
*@param t student to find
*@return  
*/
int search_for_student(vector<Course*> v, Student * t);
/**
*@brief reads a line from the text file open in faculdade::load_dept and creates an external course
*@param f ifstream that contains reference to the file
*@param linenum number of the line being treated
*@return returns a pointer to an external course
*/
Course * read_external(ifstream &f, uint &linenum);
