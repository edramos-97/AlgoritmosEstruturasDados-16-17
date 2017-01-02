#include "person.h"

/*********************************
*CLASS PERSON
*********************************/

Person::Person(string code, string name) : code(code), name(name) {
	if (name.size() < 3)
		throw exception_or_error("Nome que tentou atribuir a esta pessoa é demasiado pequeno (" + name + ")");
	if (code.length() != 11)
		throw exception_or_error("Codigo de aluno ou tutor invalido (" + code + ")");
}

/*********************************
*CLASS TUTOR
*********************************/
Tutor::Tutor(string code, string name) : Person(code, name) {
	if (code.at(0) != 't' || code.at(1) != 'u')
		throw exception_or_error("Codigo de tutor invalido(" + code + ")");
	nextid = 1;
}

string Tutor::get_name() const { return name; }

string Tutor::get_code() const { return code; }

void Tutor::add_student(Student* x)
{
	students.push_back(x);
}

void Tutor::create_newMeeting(string studentCod, string topics, string dateStr)
{
	bool foundst = false;
	for (size_t i = 0; i < students.size() && !foundst; i++) {
		if (students.at(i)->get_code() == studentCod)
			foundst = true;
	}

	if (!foundst) {
		throw exception_or_error("Este tutor nao e mentor do estudante com o codigo: " + studentCod);
	}

	Date dateofmeeting(dateStr);
	Date date = Date();
	if (dateofmeeting < date)
		throw exception_or_error("Nao pode fazer uma reuniao numa data passada");

	Meeting * meeting = new Meeting(nextid, dateofmeeting, studentCod, topics);
	meetings.insert(meeting);
	cout << "A sua reuniao foi criada com sucesso e tem o ID: " << nextid << endl;
	nextid++;
	return;
}

void Tutor::add_meeting(Meeting * meeting)
{
	meetings.insert(meeting);
	if (nextid < meeting->getId())
		nextid = meeting->getId() + 1;
}

void Tutor::remove_meeting(uint IdMeeting)
{
	set <Meeting *>::iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		if ((*it)->getId() == IdMeeting) {
			Date date = Date();
			if (date < (*it)->getDate()) {
				meetings.erase(it);
				return;
			}
			else
				throw exception_or_error("Nao e possivel remover uma reuniao que ja aconteceu");
		}
	}
	throw exception_or_error("Nao ha nenhuma reuniao com o id: " + to_string(IdMeeting));
}

void Tutor::ChangeMeetingDescription(unsigned IdMeeting, string description)
{
	set <Meeting *,meetingComp>::iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		if ((*it)->getId() == IdMeeting) {
			Date date = Date();
			if ((*it)->getDate() < date || (*it)->getDate() == date) {
				(*it)->setDescription(description);
				return;
			}
			else
				throw exception_or_error("Nao e possivel alterar a descricao de uma reuniao que ainda nao aconteceu");
		}
	}
	throw exception_or_error("Nao ha nenhuma reuniao com o id: " + to_string(IdMeeting));
}

void Tutor::ListAllMeettings() const
{

	cout << "\t\t\t\t\t" << "Listagem de todas as reunioes do tutor " << code << endl << endl;
	set <Meeting *, meetingComp>::const_iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		cout << (*it) << endl << endl;
	}
	return;
}

void Tutor::ListPastMeetings() const
{
	cout << "\t\t\t\t" << "Listagem das reunioes ja ocorridas do tutor " << code << endl << endl;
	set <Meeting *, meetingComp>::const_iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		Date date = Date();
		if ((*it)->getDate() < date)
			cout << (*it) << endl << endl;
		else
			break;
	}
	return;
}

void Tutor::ListFutureMeetings() const
{
	cout << "\t\t\t\t\t" << "Listagem das futuras reunioes do tutor " << code << endl << endl;
	set <Meeting *, meetingComp>::const_iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		Date date = Date();
		if (!((*it)->getDate() < date))
			cout << (*it) << endl << endl;
	}
	return;
}

void Tutor::ListMeetingsBeetween2Dates(Date &date1, Date &date2) const
{
	set <Meeting *, meetingComp>::const_iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		if (((*it)->getDate() < date2 && date1 < (*it)->getDate())||
			(*it)->getDate()==date1|| (*it)->getDate() == date2)
			cout << (*it) << endl << endl;
	}
	return;
}

vector<uint> Tutor::PastMeetings_NoDescription() const
{
	vector <uint> Nodescription;

	set <Meeting *, meetingComp>::const_iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++) {
		Date date = Date();
		if ((*it)->getDate() < date) {
			if ((*it)->getDescription() == "No description")
				Nodescription.push_back((*it)->getId());
		}
		else
			break;
	}
	return Nodescription;
}


void Tutor::setName(string newName) {
	name = newName;
}

set<Meeting*, meetingComp> Tutor::getMeetings()
{
	return meetings;
}

bool Tutor::operator< (const Tutor &t) const {
	return students.size() < t.students.size();
}

ostream& operator<<(ostream &os, const Tutor &tutor) {
	os << tutor.code << " || " << tutor.name;
	return os;
}

/*********************************
*CLASS Student
*********************************/

Student::Student(string code, string name, string email, string status, string tutor) : Person(code, name), email(email), status(status), tutor(tutor) {
	interrupted = false;
	finished = false;
	approved_credits = 0;
	credits = 0;
	if (code.at(0) != 's' || code.at(1) != 't')
		throw exception_or_error("Codigo de estudante invalido(" + code + ")");
}

Student::Student(string code, string name, string email, string status, bool interrupted, bool fin) : Person(code, name), email(email), status(status) {
	this->interrupted = interrupted;
	finished = fin;
	approved_credits = 0;
	credits = 0;
	if (code.at(0) != 's' || code.at(1) != 't')
		throw exception_or_error("Codigo de estudante invalido(" + code + ")");
}

string Student::get_name() const { return name; }
string Student::get_code() const { return code; }
string Student::get_email() const { return email; }
string Student::get_status() const { return status; }
string Student::get_tutor() const { return tutor; }
bool Student::hasInterrupted() const { return interrupted; }
bool Student::hasFinished() const { return finished; }

vector<Course *> Student::get_enrol_courses() const {
	return enrolled_courses;
}

vector<Course *> Student::get_approv_courses() const {
	return approved_courses;
}

vector<Date *> Student::get_enrol_dates() const {
	return enrolled_dates;
}

vector<Date *> Student::get_approv_dates() const {
	return approved_dates;
}

double Student::get_appcredits() const { return approved_credits; }
double Student::get_credits() const { return credits; }

void Student::resumeDegree() {
	if (!interrupted) {
		throw exception_or_error("resumeDegree(): Degree wasn't interrupted\n");
	}
	interrupted = false;
}

void Student::setName(string newName) {
	name = newName;
}

void Student::setEmail(string newEmail) {
	email = newEmail;
}

void Student::setStatus(string newStatus) {
	status = newStatus;
}

void Student::add_approved_credits(double x) {
	approved_credits += x;
	credits -= x;
}
void Student::add_credits(double x) { credits += x; }
void Student::assign_tutor(Tutor * x) { tutor = x->get_code(); }

void Student::enroll_course(Course *course, Date *date) {
	enrolled_courses.push_back(course);
	enrolled_dates.push_back(date);
	credits += course->get_credits();
}

void Student::approve_course(Course *course, Date *date) {
	bool found = false;
	for (vector<Course *>::iterator it = enrolled_courses.begin(); it != enrolled_courses.end(); ++it) {
		if (*it == course) {
			enrolled_courses.erase(it);
			found = true;
			break;
		}
	}

	approved_courses.push_back(course);
	approved_dates.push_back(date);
	if (found) {
		credits -= course->get_credits();
	}
	approved_credits += course->get_credits();
}

ostream & operator<<(ostream &os, const Student &stud)
{
	os << stud.code << " || " << stud.name << " || " << stud.email << endl;
	os << "Estatuto: ";
	if (stud.hasInterrupted()) {
		os << "Curso interrompido";
	}
	else if (stud.hasFinished()) {
		os << "Curso terminado";
	}
	else {
		os << stud.status;
	}
	os << endl <<
		"Tutor: " << stud.tutor << endl <<
		"Creditos aprovados: " << stud.approved_credits << endl <<
		"Creditos inscritos: " << stud.credits;
	return os;
}

bool operator == (const Student &s1, const Student &s2) {
	return (s1.code == s2.code);
}

uint Student::get_year()
{
	vector<uint> v1(5,0);

	for  (auto x : enrolled_courses)
	{
		v1.at(x->get_year() - 1)++;
	}
	
	auto x = max_element(v1.begin(), v1.end());

	return distance(v1.begin(),x)+1;
}
