#include "Menus.h"

bool Menu_department() {
	unsigned short option;
	string filename; //without .txt

	cout << BIG_TAB << "Bem vindo!" << endl << endl;
	cout << TAB << "1 - Criar uma nova faculdade" << endl;
	cout << TAB << "2 - Importar uma faculdade ja existente" << endl;
	cout << TAB << "0 - Sair" << endl << endl;
	
	cout << "Escolha uma opcao: ";
	cin >> option;

	if (!cin.good())
		throw input_not_valid();

	switch (option) {
	case 1:
	{
		try {
			cout << "Para voltar atras insira \"exit\"\nInsira o nome da nova faculdade: ";//escrevi aqui o que fazer, nao se preocupem com o que esta escrito isso está bem que já verifiquei
			cin >> filename;
			if (filename == "exit") {//    É melhor por isto em cada um acho eu. Penso que retorna true mas verifiquem
				clrscr();
				return false;
			}
			Department D = newDepartment(filename);
			clrscr();
			mainMenu(D);
			return true;
		}
		catch (input_not_valid) {
			cerr << "Essa faculdade ja existe. Tente novamente\n";
			system("PAUSE");
			clrscr();
		}
		catch (short_argument x) {
			cerr << x.get_info() <<  x.get_arg()<< "\"" << ". Tente novamente!\n";
			system("PAUSE");
			clrscr();
		}
		break;
	}

	case 2:
	{
		try
		{
			cout << "Para voltar atras insira \"exit\"\nInsira o nome do ficheiro que contem as informacoes da faculdade: ";//escrevi aqui o que fazer, nao se preocupem com o que esta escrito isso está bem que já verifiquei
			cin >> filename;
			if (filename == "exit") {//    É melhor por isto em cada um acho eu. Penso que retorna true mas verifiquem
				clrscr();
				return false;
			}
			Department D(filename);
			D.load_dept(filename);
			clrscr();
			mainMenu(D);
			return true;
		}
		catch (file_not_open x)
		{
			cerr << "Nao existe nenhum ficheiro com o nome: \"" << x.get_info() << "\". Tente novamente!\n";
			system("PAUSE");
			clrscr();
		}
		catch (short_argument x) {
			cerr << x.get_info() << ". Tente novamente!\n";
			system("PAUSE");
			clrscr();
		}
		break;
	}

	case 0:
		return true;
	default: 
		cerr << "O input nao e valido. Tente novamente " << endl << endl;
		system("PAUSE");
		clrscr();
	}
	return false;
}

//TODO
//void menu_enroll(Department & dept) {
//	clrscr();
//
//	bool isNew = false; //TODO - Needed?
//	string courseName;
//	Student *stud = nullptr;
//	Course *course = nullptr;
//	unsigned short option;
//	cout << "1 - Novo estudante" << endl;
//	cout << "2 - Estudante existente" << endl;
//	cout << "0 - Voltar" << endl;
//	cout << "Opcao: ";
//	cin >> option;
//
//	switch (option) {
//		case 1:
//			stud = create_student();
//			isNew = true;
//			break;
//		case 2:
//			//TODO - Find student.
//			break;
//		case 0:
//			return;
//		default:
//			//TODO - Loop.
//			cin.clear();
//			cin.ignore(numeric_limits<streamsize>::max(), '\n');
//			clrscr();
//	}
//
//	// Choose course.
//	//TODO - How to choose semester? Date-dependent?
//	uint semester = 0;
//	bool invalidCourse = true, foundCourse = false;
//
//	while (invalidCourse) {
//		cout << "Nome da UC: ";
//		cin >> courseName;
//
//		{
//			size_t year = 0, courseInd = 0;
//			for (; year < dept.get_courses().at(semester).size(); ++year) {
//				for (size_t courseInd = 0; courseInd < dept.get_courses().at(semester).at(year).size(); ++courseInd) {
//					if (courseName == dept.get_courses().at(semester).at(year).at(courseInd)->get_name()) {
//						course = dept.get_courses().at(semester).at(year).at(courseInd);
//						foundCourse = true;
//						break;
//					}
//				}
//				if (foundCourse)
//					break;
//			}
//
//			if (dept.apply_for_course(stud, dept.get_courses().at(semester).at(year).at(courseInd))) {
//				invalidCourse = false;
//			}
//		}
//	}
//	if (course == nullptr) {
//		cerr << "menu_enroll(): Unintended behavior: course = nullptr after initialization cycle" << endl;
//		exit(1); //Replace by exception.
//	}
//	
//	// TODO - Enroll student.
//
//}

void mainMenu(Department & dept)
{
	unsigned short option;
	bool exit_program=false;
	 //without .txt
	while (!exit_program)
	{


		cout << BIG_TAB << "Menu Principal" << endl << endl;
		cout << TAB << "1 - Novo Tutor" << endl;
		cout << TAB << "2 - Novo Estudante" << endl;
		cout << TAB << "3 - Informacao de Estudante" << endl;
		cout << TAB << "4 - " << endl;
		cout << TAB << "5 - " << endl;
		cout << TAB << "6 - " << endl;
		cout << TAB << "7 - " << endl;
		cout << TAB << "0 - Sair" << endl << endl; //grava num ficheiro e sai definitvamente do programa

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente " << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		//chamam uma funcao que apenas vai corrigir o erro e chamar a função que se quer!!!
		switch (option) {
		case 1:
			call_newtutor(dept);
			break;
		case 2:
			call_newstudent(dept);
			break;
		case 3:
			studentInfo(dept);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			/*menu_enroll(dept);*/
			break;
		case 0:
			dept.save_dept();
			exit_program=true;
			break;
		default: 
			cerr << "O input nao e valido. Tente novamente " << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
	return;
}


Department newDepartment(string name) {
	ifstream f;
	
	string cod;
	
	f.open(name + ".txt");
	if (f.is_open())
		throw input_not_valid();
	
	Department D(name);

	cout << "O departamento necessita de pelo menos um tutor, por favor insira o seu nome: ";
	getline(cin, name);
	cod=to_string(D.getNext_assigned_tutor(NEW_TUTOR));
	while (cod.length() < 9) {
		cod = '0' + cod;
	}
	cod = "tu" + cod;
	Tutor *T= new Tutor(cod, name);
	D.new_tutor(T);
	return D;
}

void call_newtutor(Department &D) {
	string name, cod;
	cout <<  "Por favor insira o seu nome: ";
	cin.ignore();
	getline(cin, name);
	cod = to_string(D.getNext_assigned_tutor(NEW_TUTOR));
	while (cod.length() < 9) {
		cod = '0' + cod;
	}
	cod = "tu" + cod;
	try {
		Tutor *T = new Tutor(cod, name);
		D.new_tutor(T);
	}
	catch (...) {}
	return;
}

void call_newstudent(Department &d)
{
	string name, cod, status_str;
	uint status;
	cout << "Insira o nome do novo estudante: ";
	cin.ignore();
	getline(cin,name);
	cout << "Insira o seu estatuto:\n"
		<< "1 - Trabalhador Estudante\n"
		<< "2 - Estudante\n"
		<< "3 - Atleta Estudante\n";
	cin >> status;
	
	if (!cin.good()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "O input nao e valido. Tente novamente " << endl << endl;
		system("PAUSE");
		clrscr();
		return;
	}
	switch (status)
	{
	case 1: 
		status_str = "Trabalhador Estudante";
		break;
	case 2:
		status_str = "Estudante";
		break;
	case 3:
		status_str = "Atleta Estudante";
		break;
	default:
		cerr << "O input nao e valido. Tente novamente " << endl << endl;
		system("PAUSE");
		clrscr();
		return;
	}	

	cod = to_string(d.getNext_assigned_student(NEW_STUDENT));
	while (cod.length() < 9) {
		cod = '0' + cod;
	}
	cod = "st" + cod;
	try {
		Student *st = new Student(cod, name, cod + "@fe.up.pt", status_str);
		d.add_student(st);
	}
	catch (...) {
	}

}

void studentInfo(const Department &dept) {	
	string studCode;
	const Student *stud;
	
	while (true) {
		try {
			clrscr();
			cout << "Codigo do estudante (\"exit\" para sair): ";
			cin >> studCode;
			if (studCode == "exit") {
				return;
			}
			stud = dept.getStudent(studCode);
			break;
		}
		catch (StudentNotFound(studCode)) {
			continue;
		}
	}

	cout << *stud << "\n";
	cout << "Enrolled in:\n";
	for (Course *course : stud->get_enrol_courses()) {
		cout << " - " << course->get_name() << "\n";
	}
	cout << "Approved in:\n";
	for (Course *course : stud->get_approv_courses()) {
		cout << " - " << course->get_name() << "\n";
	}

	system("pause");
}