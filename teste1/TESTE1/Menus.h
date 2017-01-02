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

void callMeetingManagement(Department &dept);

void MeetingManagement(Tutor* tutor, Department &dept);
void call_listbeetween2dates(Tutor *tutor);
void call_createnewmeeting(Tutor *tutor, Department &dept);
void call_removemeeting(Tutor *tutor);
void call_changemeetingdescription(Tutor *tutor);


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

/**
*@brief Displays the tutor management menu on the console and inputs the option of the menu
*
*@param dept Department being used.
*/
void tutorManagement(Department &dept);

/**
*@brief Displays the student management menu on the console and inputs the option of the menu
*
*@param dept Department being used.
*/
void studentManagement(Department &dept);

/**
*@brief Displays the class management menu on the console and inputs the option of the menu
*
*@param dept Department being used.
*/
void classManagement(Department &dept);

/**
*@brief Function of the menu that calls the function of the departement class for a tutor name change
*
*@param dept Department being used.
*/
void tutorNameChange(Department &dept);


/**
*@brief Reads and displays the tutor information on the console
*
*@param dept Department being used.
*/
void tutorInfo(const Department &dept);

/**
*@brief Displays the student change menu on the console and inputs the option of the menu
*
*@param dept Department being used.
*/
void studentChange(Department &dept);

/**
*@brief Function of the menu that calls the function of the departement to list specific students
*
*@param dept Department being used.
*/
void m_listStudents(const Department &dept);

/**
*@brief Displays the students that have an ongoing degree alphabetically or ordered by their code
*
*@param dept Department being used.
*/
void m_listCurrentStuds(const Department &dept);

/**
*@brief Displays the students that have interrupted the degree course alphabetically or ordered by their code
*
*@param dept Department being used.
*/
void m_listIntStuds(const Department &dept);

/**
*@brief Displays the students that have finished the degree alphabetically or ordered by their code
*
*@param dept Department being used.
*/
void m_listFinishedStuds(const Department &dept);

/**
*@brief Displays all students of the dergee alphabetically or ordered by their code
*
*@param dept Department being used.
*/
void m_listAllStuds(const Department &dept);

/**
*@brief Function of the menu that calls the function of the departement class to display the 3 classes with the most open slots
*
*@param dept Department being used.
*/
void m_top_slots(Department &dept);