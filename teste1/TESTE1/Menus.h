/**
* @file Menus.h
* @author AEDA T4GE
* @title Menus and some functions
* @brief Menus functions and some "call fucntins"
*/
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

#include "utils.h"
#include "exceptions.h"
#include "faculdade.h"
#include "course.h"
#include <cstdlib>
#undef max

using namespace std;
/**
*@brief Creates a completely new department with a tutor
*@param name name of the department
*/
Department newDepartment(string name);
/**
*@brief Menu used to know if the user wants to creat a completely new department or read an old one from a file
*/
bool Menu_department();
/**
*@brief Main Menu with all the options implemented
*@param dept Department being used
*/
void mainMenu(Department &dept);
/**
*@brief function used to prepare a call to the Department::newtutor 
*@param d Department being used
*/
void call_newtutor(Department &d);
/**
*@brief function used to prepare a call to the Department::addstudent
*@param d Department being used
*/
void call_newstudent(Department &d);
/**
*@brief function used to call needed functions to show a certain student info
*@param dept Department being used
*/
void studentInfo(const Department &dept);
/**
*@brief function used to call needed functions to show a certain course info
*@param dept Department being used
*/
void courseInfo(const Department &dept);
/**
*@brief function used to call needed functions to enroll a student
*@param dept Department being used
*/
void enrollStudent(Department &dept);
/**
*@brief function used to call needed functions to approve a student
*@param dept Department being used
*/
void approveStudent(Department &dept);