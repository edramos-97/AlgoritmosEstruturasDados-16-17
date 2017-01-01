#include "Menus.h"
#include "faculdade.h"

bool Menu_department() {
	unsigned short option;
	string filename; //without .txt

	cout << BIG_TAB << "Bem vindo!" << endl << endl;
	cout << TAB << "1 - Criar um novo curso" << endl;
	cout << TAB << "2 - Importar um curso ja existente" << endl;
	cout << TAB << "0 - Sair" << endl << endl;
	
	cout << "Escolha uma opcao: ";
	cin >> option;

	if (!cin.good()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception_or_error("O input nao e valido");
	}
	switch (option) {
	case 1:
	{
		try {
			cout << "\nPara voltar atras insira \"exit\"\n"
				<< "Insira o nome do novo curso: ";
			cin >> filename;
			if (filename == "exit") {
				clrscr();
				return false;
			}
			Department D = newDepartment(filename);
			clrscr();
			mainMenu(D);
			return true;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
		break;
	}

	case 2:
	{
		try
		{
			cout << "Para voltar atras insira \"exit\"\n"
				<< "Insira o nome do ficheiro que contem as informacoes do curso: "; //escrevi aqui o que fazer, nao se preocupem com o que esta escrito isso está bem que já verifiquei
			cin >> filename;
			if (filename == "exit") {
				clrscr();
				return false;
			}
			Department D(filename);
			D.load_dept(filename);
			clrscr();
			mainMenu(D);
			return true;
		}
		catch (exception_or_error x)
		{
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
		break;
	}

	case 0:
		return true;
	default: 
		cerr << "O input nao e valido. Tente novamente." << endl << endl;
		system("PAUSE");
		clrscr();
	}
	return false;
}

void mainMenu(Department &dept)
{
	unsigned short option;
	bool exit_program = false;
	 //without .txt
	while (!exit_program)
	{
		cout << BIG_TAB << "Menu Principal" << endl << endl;
		cout << TAB << "1 - Gestao de Tutores" << endl;
		cout << TAB << "2 - Gestao de Estudantes" << endl;
		cout << TAB << "3 - Informacao de UC" << endl;
		cout << TAB << "4 - Gestao de Turmas" << endl;
		cout << TAB << "5 - " << endl;
		cout << TAB << "0 - Sair" << endl << endl; //grava num ficheiro e sai definitvamente do programa

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		//chamam uma funcao que apenas vai corrigir o erro e chamar a função que se quer!!!
		switch (option) {
		case 1:
			clrscr();
			tutorManagement(dept);
			break;
		case 2:
			clrscr();
			studentManagement(dept);
			break;
		case 3:
			courseInfo(dept);
			break;
		case 4:
			classManagement(dept);
			break;
		case 0:
			dept.save_dept();
			exit_program=true;
			break;
		default: 
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
	return;
}

void tutorManagement(Department &dept) {
	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << BIG_TAB << "Gestao de Tutores" << endl << endl;
		cout << TAB << "1 - Novo Tutor" << endl;
		cout << TAB << "2 - Modificar Tutor" << endl;
		cout << TAB << "3 - Informacao de Tutor" << endl;
		cout << TAB << "0 - Sair" << endl << endl;

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		switch (option) {
		case 1:
			call_newtutor(dept);
			break;
		case 2:
			tutorNameChange(dept);
			break;
		case 3:
			tutorInfo(dept);
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

void studentManagement(Department &dept) {
	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << BIG_TAB << "Gestao de Estudantes" << endl << endl;
		cout << TAB << "1 - Novo Estudante" << endl;
		cout << TAB << "2 - Modificar Estudante" << endl;
		cout << TAB << "3 - Informacao de Estudante" << endl;
		cout << TAB << "4 - Listar Estudantes" << endl;
		cout << TAB << "5 - Inscricao de Estudante" << endl;
		cout << TAB << "6 - Aprovacao de Estudante" << endl;
		cout << TAB << "0 - Sair" << endl << endl;

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		switch (option) {
		case 1:
			call_newstudent(dept);
			break;
		case 2:
			studentChange(dept);
			break;
		case 3:
			studentInfo(dept);
			break;
		case 4:
			m_listStudents(dept);
			break;
		case 5:
			enrollStudent(dept);
			break;
		case 6:
			approveStudent(dept);
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

void tutorNameChange(Department &dept) {
	string tutorCode, newName;
	Tutor *tutor;

	while (true) {
		try {
			clrscr();
			cout << "Codigo do tutor (\"exit\" para sair): ";
			cin >> tutorCode;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			if (tutorCode == "exit") {
				return;
			}
			tutor = dept.getTutor(tutorCode);
			break;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("pause");
			clrscr();
		}
	}

	cout << *tutor << "\n\n";

	cout << "Novo nome do tutor: ";
	getline(cin, newName);

	tutor->setName(newName);
}

void tutorInfo(const Department &dept) {
	string tutorCode;
	const Tutor *tutor;

	while (true) {
		try {
			clrscr();
			cout << "Codigo do tutor (\"exit\" para sair): ";
			cin >> tutorCode;
			if (tutorCode == "exit") {
				return;
			}
			tutor = dept.getTutor(tutorCode);
			break;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("pause");
			clrscr();
		}
	}

	clrscr();
	cout << *tutor << "\n";

	system("pause");
}

void studentChange(Department &dept) {
	string studCode;
	Student *stud;

	while (true) {
		try {
			clrscr();
			cout << "Codigo do estudante (\"exit\" para sair): ";
			cin >> studCode;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (studCode == "exit") {
				return;
			}
			stud = dept.getStudent(studCode);
			break;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("pause");
			clrscr();
		}
	}

	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << BIG_TAB << "Alteracao de Estudante" << endl << endl;
		cout << TAB << "Modificar:" << endl;
		cout << TAB << "1 - Nome" << endl;
		cout << TAB << "2 - Email" << endl;
		cout << TAB << "3 - Estatuto" << endl;
		cout << TAB << "0 - Sair" << endl << endl;

		cout << "Escolha uma opcao: ";
		cin >> option;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (!cin.good()) {
			cin.clear();
		//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		string newName, newEmail, newStatus;
		switch (option) {
		case 1:
			cout << "Novo nome: ";
			getline(cin, newName);
			stud->setName(newName);
			break;
		case 2:
			cout << "Novo e-mail: ";
			getline(cin, newEmail);
			stud->setEmail(newEmail);
			break;
		case 3:
			cout << "Novo estatuto: ";
			getline(cin, newStatus);
			stud->setStatus(newStatus);
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

Department newDepartment(string name) {
	ifstream f;
	string cod;
	
	f.open(name + ".txt");
	if (f.is_open())
		throw exception_or_error("O input nao e valido");
	
	Department D(name);

	cout << "O departamento necessita de pelo menos um tutor, por favor insira o seu nome: ";
	getline(cin, name);
	cod=to_string(D.getNext_assigned_tutor(NEW_TUTOR));
	while (cod.length() < 9) {
		cod = '0' + cod;
	}
	cod = "tu" + cod;
	Tutor *T = new Tutor(cod, name);
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
		cout << "Tutor com o nome " << name << " criado com sucesso. O seu código é " << cod << endl;
		system("PAUSE");
	}
	catch (exception_or_error x) {
		cerr << x.get_reason() << ". Tente novamente!\n";
		system("PAUSE");
		clrscr();
	}
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
		cerr << "O input nao e valido. Tente novamente." << endl << endl;
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
		status_str = "Ordinario";
		break;
	case 3:
		status_str = "Atleta ";
		break;
	default:
		cerr << "O input nao e valido. Tente novamente." << endl << endl;
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
		Student *st = new Student(cod, name, cod + "@fe.up.pt", status_str, false, false);
		d.add_student(st);
		cout << "Estudante com o nome " << name << " criado com sucesso. O seu codigo e " << cod 
			<< ". Para mais informacoes use o sistema"<< endl;
		system("PAUSE");
	}
	catch (exception_or_error x) {
		cerr << x.get_reason() << ". Tente novamente!\n";
		system("PAUSE");
		clrscr();
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
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
	}

	clrscr();
	cout << *stud << "\n";
	cout << "Inscrito em:\n";
	for (size_t courseInd = 0; courseInd < stud->get_enrol_courses().size(); ++courseInd) {
		Course *course = stud->get_enrol_courses().at(courseInd);
		cout << " - " << course->get_name() << " | " << *(stud->get_enrol_dates().at(courseInd)) << "\n";
	}
	cout << "Aprovado em:\n";
	for (size_t courseInd = 0; courseInd < stud->get_approv_courses().size(); ++courseInd) {
		Course *course = stud->get_approv_courses().at(courseInd);
		cout << " - " << course->get_name() << " | " << *(stud->get_approv_dates().at(courseInd)) << "\n";
	}

	system("pause");
}

void m_listStudents(const Department &dept) {
	clrscr();
	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << TAB << "Listar Estudantes:\n";
		cout << "1 - Com curso em progresso\n";
		cout << "2 - Com curso interrompido\n";
		cout << "3 - Com curso terminado\n";
		cout << "4 - Todos\n";
		cout << "0 - Sair\n\n";

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		switch (option) {
		case 1:
			m_listCurrentStuds(dept);
			break;
		case 2:
			m_listIntStuds(dept);
			break;
		case 3:
			m_listFinishedStuds(dept);
			break;
		case 4:
			m_listAllStuds(dept);
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

bool studAlphabetical(Student *s1, Student *s2) {
	return (s1->get_name() < s2->get_name());
}

bool studCrescentCode(Student *s1, Student *s2) {
	return (s1->get_code() < s2->get_code());
}

void m_listCurrentStuds(const Department &dept) {
	clrscr();
	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << TAB << "Listar Estudantes Com Curso Em Progresso:\n";
		cout << "1 - Por ordem alfabetica\n";
		cout << "2 - Por ordem crescente de codigo\n";
		cout << "0 - Sair\n\n";

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}
		clrscr();

		switch (option) {
		case 1:
			dept.listCurrentStuds(studAlphabetical);
			system("pause");
			break;
		case 2:
			dept.listCurrentStuds(studCrescentCode);
			system("pause");
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

void m_listIntStuds(const Department &dept) {
	clrscr();
	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << TAB << "Listar Estudantes Com Curso Interrompido:\n";
		cout << "1 - Por ordem alfabetica\n";
		cout << "2 - Por ordem crescente de codigo\n";
		cout << "0 - Sair\n\n";

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}
		clrscr();

		switch (option) {
		case 1:
			dept.listIntStuds(studAlphabetical);
			system("pause");
			break;
		case 2:
			dept.listIntStuds(studCrescentCode);
			system("pause");
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

void m_listFinishedStuds(const Department &dept) {
	clrscr();
	unsigned short option;
	bool exitFunc = false;

	while (exitFunc == false) {
		cout << TAB << "Listar Estudantes Com Curso Terminado:\n";
		cout << "1 - Por ordem alfabetica\n";
		cout << "2 - Por ordem crescente de codigo\n";
		cout << "0 - Sair\n\n";

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}
		clrscr();

		switch (option) {
		case 1:
			dept.listFinishedStuds(studAlphabetical);
			system("pause");
			break;
		case 2:
			dept.listFinishedStuds(studCrescentCode);
			system("pause");
			break;
		case 0:
			exitFunc = true;
			break;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
		}
		clrscr();
	}
}

void m_listAllStuds(const Department &dept) {
	clrscr();
	unsigned short option;
	bool exitFunc = false;
	bool(*comp)(Student*, Student*) = nullptr;

	while (exitFunc == false) {
		cout << TAB << "Listar Todos Os Estudantes:\n";
		cout << "1 - Por ordem alfabetica\n";
		cout << "2 - Por ordem crescente de codigo\n";
		cout << "0 - Sair\n\n";

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}
		clrscr();

		switch (option) {
		case 1:
			comp = studAlphabetical;
			break;
		case 2:
			comp = studCrescentCode;
			system("pause");
			break;
		case 0:
			exitFunc = true;
			clrscr();
			continue;
		default:
			cerr << "O input nao e valido. Tente novamente." << endl << endl;
			system("PAUSE");
			clrscr();
			continue;
		}

		if (comp == nullptr) {
			throw exception_or_error("m_listAllStuds(): comp uninitialized");
		}

		cout << "Curso em progresso:\n";
		dept.listCurrentStuds(comp);
		cout << "Curso interrompido:\n";
		dept.listIntStuds(comp);
		cout << "Curso terminado:\n";
		dept.listFinishedStuds(comp);
		system("pause");

		clrscr();
	}
}

void courseInfo(const Department &dept) {
	const Course *course;
	string courseName;
	
	while (true) {
		try {
			clrscr();
			cout << "Nome da UC (\"exit\" para sair): ";
			cin >> courseName;
			if (courseName == "exit") {
				return;
			}
			course = dept.getCourse(courseName);
			break;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
	}
	
	cout << "Estudantes inscritos:\n";
	for (size_t studInd = 0; studInd < course->get_enrol_students().size(); ++studInd) {
		Student *stud = course->get_enrol_students().at(studInd);
		cout << " - " << stud->get_code() << " | " << stud->get_name() << " | " << *(course->get_date_enrolled().at(studInd)) << "\n";
	}

	cout << "Estudantes aprovados:\n";
	for (size_t studInd = 0; studInd < course->get_approv_students().size(); ++studInd) {
		Student *stud = course->get_approv_students().at(studInd);
		cout << " - " << stud->get_code() << " | " << stud->get_name() << " | " << *(course->get_date_approved().at(studInd)) << "\n";
	}

	system("pause");
}

void enrollStudent(Department &dept) {
	Student *stud;
	Course *course;
	string studName, courseName;

	while (true) {
		try {
			clrscr();
			cout << "\nCodigo do estudante (\"exit\" para sair): ";
			cin >> studName;
			if (studName == "exit") {
				return;
			}
			stud = dept.getStudent(studName);
			cout << "Nome da UC (\"exit\" para sair): ";
			cin >> courseName;
			if (courseName == "exit") {
				return;
			}
			course = dept.getCourse(courseName);

			bool isOptional = (!(dynamic_cast<OptionalCourse *>(course) == NULL));

			if (!isOptional) {
				if (!(dept.apply_for_course(stud, course))) {
					system("pause");
					continue;
				}
			}
			else {
				if (!(dept.apply_for_course(stud, (OptionalCourse *)course))) {
					system("pause");
					continue;
				}
			}
			continue;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente!\n";
			system("PAUSE");
			clrscr();
		}
	}
}

void approveStudent(Department &dept) {
	Student *stud;
	Course *course;
	string studName, courseName;

	while (true) {
		try {
			clrscr();
			cout << "Codigo do estudante (\"exit\" para sair): ";
			cin >> studName;
			if (studName == "exit") {
				return;
			}
			stud = dept.getStudent(studName);
			cout << "Nome da UC (\"exit\" para sair): ";
			cin >> courseName;
			if (courseName == "exit") {
				return;
			}
			course = dept.getCourse(courseName);
			dept.approve_student(stud, course);
			cout << "Estudante com o codigo " << studName << " foi aprovado ao curso " << courseName << " com sucesso." << endl;
			system("PAUSE");
			break;
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");			
		}
	}
}

void m_enrollInClass(Department &dept) {
	clrscr();
	string studCode;
	uint year;
	cout << "Codigo do estudante: ";
	cin >> studCode;

	Student *stud = dept.getStudent(studCode);

	cout << "Ano: ";
	cin >> year;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (year > 5 || year < 1) {
		cout << "Ano \"" << year << "\" invalido tente novamente.\n";
		system("pause");
		return;
	}
	
	dept.enrollInClass(stud, year);
}

void m_createClass(Department &dept) {
	uint year, slots, id;
	bool open = false;

	cout << "Ano (1-5): ";
	cin >> year;
	cout << "Vagas: ";
	cin >> slots;
	try {
		id = dept.getNewClassId(year);
	}
	catch (exception_or_error e) {
		cerr << e.get_reason() << ". Tente novamente.\n";
		system("pause");
		return;
	}

	dept.createClass(year, slots, id);
}

void m_delClass(Department &dept) {
	int classYear, classId;
	cout << "\nAno da turma(1-5): ";
	cin >> classYear;
	cout << "ID da turma: ";
	cin >> classId;

	if (classYear > 5 || classId < 1) {
		cout << "Ano da turma invalido.Tente novamente.\n";
		system("pause");
		return;
	}

	if (dept.deleteClass((uint)classYear, (uint)classId)) {
		cout << "Id da turma invalido.Tente novamente.\n";
		system("pause");
		return;
	}
}


void m_top_slots(Department &dept) {
	int classYear;
	cout << "\nAno da turma(1-5): ";
	cin >> classYear;

	dept.top_slots(classYear);
	system("pause");

	return;
}

void classManagement(Department &dept) {
	int option;
	while (true) {
		clrscr();
		cout << BIG_TAB << "Gestao de Turmas" << endl << endl;
		cout << TAB << "1 - Atribuir Turma" << endl;
		cout << TAB << "2 - Criar Turma" << endl;
		cout << TAB << "3 - Eleminar Turma" << endl;
		cout << TAB << "4 - Verificar Vagas" << endl;
		cout << TAB << "0 - Sair" << endl << endl;

		cout << "Escolha uma opcao: ";
		cin >> option;

		if (cin.bad()) {
			cin.clear();
			continue;
		}
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		try {
			switch (option) {
			case 1:
				m_enrollInClass(dept);
				break;
			case 2:
				m_createClass(dept);
				break;
			case 3:
				m_delClass(dept);
				break;
			case 4:
				m_top_slots(dept);
				break;
			case 0:
				return;
			}
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente.\n";
			system("PAUSE");
			clrscr();
		}
	}
}