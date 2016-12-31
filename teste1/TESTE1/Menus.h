/**
* @file Menus.h
* @author AEDA T4GE
* @title Menus
* @brief Menu functions.
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
*@brief Creates a new Department with one Tutor.
*@param name Name of the Department.
*@return New Department.
*/
Department newDepartment(string name);

/**
*@brief Menu to ask user to create a new Department or read one from a text file.
*@return True to exit program, false to repeat.
*/
bool Menu_department();

/**
*@brief Main Menu.
*@param dept Department being used.
*/
void mainMenu(Department &dept);


/**
*@brief Asks user for info to create a new Tutor in the Department.
*@param dept Department being used.
*/
void call_newtutor(Department &dept);

/**
*@brief Asks user for info to create a new Student in the Department.
*@param dept Department being used.
*/
void call_newstudent(Department &dept);

/**
*@brief Asks user for a Student's code whose info is then printed.
*@param dept Department being used.
*/
void studentInfo(const Department &dept);

/**
*@brief Asks user for a Course's code whose info is then printed.
*@param dept Department being used
*/
void courseInfo(const Department &dept);

/**
*@brief Asks user for info to enroll a Student in a Course.
*@param dept Department being used.
*/
void enrollStudent(Department &dept);

/**
*@brief Asks user for info to approve a Student in a Course.
*@param dept Department being used.
*/
void approveStudent(Department &dept);

void tutorManagement(Department &dept);
void studentManagement(Department &dept);
void classManagement(Department &dept);
void tutorNameChange(Department &dept);
void tutorInfo(const Department &dept);
void studentChange(Department &dept);
void m_listStudents(const Department &dept);
void m_listCurrentStuds(const Department &dept);
void m_listIntStuds(const Department &dept);
void m_listFinishedStuds(const Department &dept);
void m_listAllStuds(const Department &dept);
void m_top_slots(Department &dept);