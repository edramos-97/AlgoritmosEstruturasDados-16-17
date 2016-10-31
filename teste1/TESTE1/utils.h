#pragma once
#include <windows.h>
#include "course.h"
#include "person.h"
#include "iostream"
#include <fstream>

void clrscr();

Student read_student(ifstream f);
