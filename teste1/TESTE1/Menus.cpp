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
void menu_enroll(Department & dept) {
	clrscr();

	bool isNew = false; //TODO - Needed?
	string courseName;
	Student *stud = nullptr;
	Course *course = nullptr;
	unsigned short option;
	cout << "1 - Novo estudante" << endl;
	cout << "2 - Estudante existente" << endl;
	cout << "0 - Voltar" << endl;
	cout << "Opcao: ";
	cin >> option;

	switch (option) {
		case 1:
			stud = create_student();
			isNew = true;
			break;
		case 2:
			//TODO - Find student.
			break;
		case 0:
			return;
		default:
			//TODO - Loop.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clrscr();
	}

	// Choose course.
	//TODO - How to choose semester? Date-dependent?
	uint semester = 0;
	bool invalidCourse = true, foundCourse = false;

	while (invalidCourse) {
		cout << "Nome da UC: ";
		cin >> courseName;

		{
			size_t year = 0, courseInd = 0;
			for (; year < dept.get_courses().at(semester).size(); ++year) {
				for (size_t courseInd = 0; courseInd < dept.get_courses().at(semester).at(year).size(); ++courseInd) {
					if (courseName == dept.get_courses().at(semester).at(year).at(courseInd)->get_name()) {
						course = dept.get_courses().at(semester).at(year).at(courseInd);
						foundCourse = true;
						break;
					}
				}
				if (foundCourse)
					break;
			}

			if ("OK" == dept.apply_for_course(stud, dept.get_courses().at(semester).at(year).at(courseInd))) {
				invalidCourse = false;
			}
		}
	}
	if (course == nullptr) {
		cerr << "menu_enroll(): Unintended behavior: course = nullptr after initialization cycle" << endl;
		exit(1); //Replace by exception.
	}
	
	// TODO - Enroll student.

}

void mainMenu(Department & dept)
{
	unsigned short option;
	bool exit_program=false;
	 //without .txt
	while (!exit_program)
	{


		cout << BIG_TAB << "Menu Principal!" << endl << endl;
		cout << TAB << "1 - Inscricao" << endl;
		cout << TAB << "2 - " << endl;
		cout << TAB << "3 - " << endl;
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
			menu_enroll(dept);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 0:
			//grava tudo num ficheiro 
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

	cout << "A faculdade necessita de pelo menos um tutor, por favor insira o seu nome: ";
	cin >> name;
	cod = "tu000000001";//a alterar
	Tutor *T= new Tutor(cod, name);
	D.new_tutor(T);
	return D;
}