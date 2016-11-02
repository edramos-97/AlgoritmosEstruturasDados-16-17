#include "exceptions.h"
#include "faculdade.h"
#include "utils.h"
#include <iostream>

using namespace std;

void mainMenu() {

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

	D.load_dept("Mieic");

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