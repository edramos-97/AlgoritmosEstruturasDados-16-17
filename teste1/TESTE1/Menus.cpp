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
			Department D = newDepartment();
			clrscr();
			mainMenu(D);
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
			clrscr();
			mainMenu(D);
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
	default: 
		cerr << "O input nao e valido. Tente novamente " << endl << endl;
		system("PAUSE");
		clrscr();
	}
	return false;
}

//TODO
void menu_enroll(Department & dept) {

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