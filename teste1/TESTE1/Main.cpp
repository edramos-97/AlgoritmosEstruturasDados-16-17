#include "exceptions.h"
#include "faculdade.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

#undef max  //To use numeric_limits<streamsize>::max()

void courseEnrollmentInfo(const Department &dept) {
	string courseName;
	cout << "Course name: ";
	getline(cin, courseName);
	//TODO - cout << course;
}

void mainMenu(Department &dept, string filename) {
	int option;

	while (true) {
		clrscr();
		cout << "Main Menu\n\n";

		cout << setw(6) << right << "1) " << "Apply for degree\n";
		cout << setw(6) << right << "2) " << "List enrollments by student\n";
		cout << setw(6) << right << "3) " << "List enrollments by course\n";
		cout << setw(6) << right << "4) " << "Other options\n";
		cout << "\n0) Save and exit\n\n";

		cout << "Option: ";
		cin >> option;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (option) {
		case 0:
			dept.save_dept(filename);
		case 1:
			//	applyForDegree();
			return;
		case 2:
			//	studentEnrollmentInfo(dept);
			break;
		case 3:
			courseEnrollmentInfo(dept);
			break;
		case 4:
			break;
		default:
			continue;
		}
	}
}


int main() {

	Department D("Mieic");
	/*Tutor* t= new Tutor("199703569", "Raul Vidal");
	Course* c= new Course(2, 1, 6, "AEDA");
	Student* s1= new Student("201505779", "Eduardo Ramos", "up201505779@fe.up.pt", "ordinario", "199703569");
	Student* s2= new Student("201505789", "Paulo Ribeiro", "up201505789@fe.up.pt", "atleta");
	
	c->add_student(s1);

	D.new_tutor(t);
	D.add_course(c);
	D.new_student(s2);
	for (auto x : D.tutors.at(0)->students)
		cout << *x;
	
	D.save_dept("Mieic.txt");*/

	D.load_dept("test");

	D.save_dept("test.txt");



	
	

	/*vector<Student*> v1;

	v1.push_back(read_student(line));

	cout<< v1[0]->get_code()<<endl;
	cout << v1[0]->get_email() << endl;
	cout << v1[0]->get_name() << endl;
	cout << "read student successfull";*/

	/*vector<Course*> v1;

	v1.push_back(read_course(d,linenum));
	cout << linenum<<endl;
	cout << *v1[0];*/



	std::cout << "Course created"<< endl;
	return 0;
}