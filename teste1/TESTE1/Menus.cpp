#include "Menus.h"

/*
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
			//dept.save_dept(filename);
		case 1:
			//	applyForDegree();
			return;
		case 2:
			//	studentEnrollmentInfo(dept);
			break;
		case 3:
			//courseEnrollmentInfo(dept);
			break;
		case 4:
			break;
		default:
			continue;
		}
	}
}*/


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
			Department D = newDepartment();
			//chama menu
			return true;
		}
		catch (input_not_valid) {
			cerr << "Essa faculdade ja existe. Tente novamente" << endl;
			system("PAUSE");
			clrscr();
		}
		catch (short_argument x) {
			cerr << x.get_arg() << ". Tente novamente!" << endl;
			system("PAUSE");
			clrscr();
		}
		break;
	}

	case 2:
	{
		try
		{
			cout << "Insira o nome do ficheiro que contem as informacoes da faculdade: ";
			cin >> filename;
			Department D(filename);
			D.load_dept(filename);
			//chama menu
			return true;
		}
		catch (file_not_open x)
		{
			cerr << "Nao existe nenhum ficheiro com o nome: " << x.get_info() << ". Tente novamente!" << endl;
			system("PAUSE");
			clrscr();
		}
		catch (short_argument x) {
			cerr << x.get_info() << ". Tente novamente!" << endl;
			system("PAUSE");
			clrscr();
		}
		break;
	}

	case 0:
		return true;
	}
	return false;
}

Department newDepartment() {
	ifstream f;
	
	string name, cod;
	cout << "Insira o nome da nova faculdade: ";
	cin >> name;
	
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