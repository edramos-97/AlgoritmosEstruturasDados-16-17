#include "exceptions.h"
#include "faculdade.h"
#include "utils.h"
#include <iostream>

using namespace std;

void mainMenu() {

}

int main() {

	/*Course c(2, 1, 6, "AEDA");
	Student s1("201505779", "Eduardo Ramos", "up201505779@fe.up.pt", "ordinario", "199703569");
	Student s2("201505789", "Eduardo Ramos", "up201505789@fe.up.pt", "atleta", "199703542");
	cout << s1.get_email();
	cout << s2.get_code()<<endl;
	Student * ptrS = &s1;
	
	cout << ptrS<<endl;
	c.add_student(&s1);
	cout << c.enrolled_students.size() << endl;
	cout << c.enrolled_students[0]->get_name();*/
		



	
	uint linenum = 0;
	string line;
	ifstream d("Text.txt");
	if(!d.is_open())
		cout << "file not open ";
	
	read_line(d, line,linenum);

	/*vector<Student*> v1;

	v1.push_back(read_student(line));

	cout<< v1[0]->get_code()<<endl;
	cout << v1[0]->get_email() << endl;
	cout << v1[0]->get_name() << endl;
	cout << "read student successfull";*/

	vector<Course*> v1;

	v1.push_back(read_course(d,linenum));
	cout << linenum<<endl;
	cout << *v1[0];



	std::cout << "Course created"<< endl;
	return 0;
}