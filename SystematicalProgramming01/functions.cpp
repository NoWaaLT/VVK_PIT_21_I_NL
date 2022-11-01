#include "functions.h"

Student::Student() {
	name = "";
	surname = "";
	hwGrade = 0;
	gradeAvg = 0;
	gradeMed = 0;
	exam = 0.0;
	hwGrade = { 0 };
}

Student::~Student() {
}

// Copy Constructor

Student::Student(const Student& st1) {
	name = st1.name;
	surname = st1.surname;
	hwGrades = st1.hwGrades;
	gradeAvg = st1.gradeAvg;
	gradeMed = st1.gradeMed;
	exam = st1.exam;
}

// Overloaded Assignment Operator

Student& Student::operator=(const Student& st1) {

	name = st1.name;
	surname = st1.surname;
	hwGrades = st1.hwGrades;
	gradeAvg = st1.gradeAvg;
	gradeMed = st1.gradeMed;
	exam = st1.exam;

	return *this;
}

// >> Overload

istream& operator >> (istream& input, Student& in) {
	cout << "Iveskite studento varda: " << endl;
	input >> in.name;
	cout << "Iveskite studento pavarde: " << endl;
	input >> in.surname;
	cout << "Iveskite egzamino pazymi: " << endl;
	int temp = 0;
	input >> temp;
	while (temp <= 0 || temp > 10) {
		cout << "Pazymis turi buti nurodytas intervale [0-10]" << endl;
		input >> temp;
	}
	in.exam = temp;
	cout << "Iveskite namu darbu pazymius: " << endl;
	cout << "Norint sustabdyti, iveskite skaiciu nepriklausanti intervalui [1-10]" << endl;
	in.setHwGrades();

	system("cls");
	return input;
}

// << Overload

ostream& operator << (ostream& output, const vector <Student>& st) {
	int pChoise;
	cout << "Pasirinkite: " << endl;
	cout << "1. Galutinis pazymis pagal vidurki" << endl;
	cout << "2. Galutinis pazymis pagal mediana" << endl;

	do {
		cin >> pChoise;
	} while (pChoise > 2 || pChoise < 1);

	if (pChoise == 1) {
		cout << left << setw(14) << "Pavarde" << left << setw(14) << "Vardas" << "Galutinis(Vid.)" << endl;
		cout << "--------------------------------------------------------" << endl;
		for (int i = 0; i < st.size(); i++) {
			output << left << setw(14) << st[i].surname << left << setw(14) <<
				st[i].name << setprecision(2) << fixed << finalScore(st[i].gradeAvg, st[i].exam) << endl;
		}
	}

	if (pChoise == 2) {
		cout << left << setw(14) << "Pavarde" << left << setw(14) << "Vardas" << "Galutinis(Med.)" << endl;
		cout << "--------------------------------------------------------" << endl;
		for (int i = 0; i < st.size(); i++) {
			output << left << setw(14) << st[i].surname << left << setw(14) <<
				st[i].name << setprecision(2) << fixed << finalScore(st[i].gradeMed, st[i].exam) << endl;
		}
	}

	return output;
}

string Student::getName(vector <Student> st, int i) {
	return st[i].name;
}

string Student::getSurname(vector <Student> st, int i) {
	return st[i].surname;
}

double Student::getGrade(vector <Student> st, int i) {
	return st[i].gradeAvg;
}

double Student::getMedian(vector <Student> st, int i) {
	return st[i].gradeMed;
}

void Student::setHwGrades() {
	do {
		cin >> hwGrade;
		if (hwGrade >= 0 && hwGrade <= 10) {
			hwGrades.push_back(hwGrade);
		}
	} while (hwGrade >= 0 && hwGrade <= 10);
}

void Student::setHwGradesRnd() {
	const int MAX_GRADE = 10;
	const int MAX_LOOP_LENGTH = 10000;

	RandInt rnd{ 0, MAX_GRADE };
	RandInt rnd2{ 0, MAX_LOOP_LENGTH };
	int gradeCount = rnd2();
	for (int i = 0; i < gradeCount; i++) {
		hwGrade = rnd();
		hwGrades.push_back(hwGrade);
	}
}

double Student::average(vector <int> gr) {
	double sum = 0.0;
	for (int i = 0; i < gr.size(); i++) {
		sum += gr[i];
	}
	sum /= (double)gr.size();
	return sum;
}

double Student::median(vector <int> gr) {
	if (gr.size() == 1) {
		return gr[0];
	}
	else if (gr.size() < 1) {
		return 0;
	}
	else {
		sort(gr.begin(), gr.end());
		int  mid = gr.size() / 2;
		if (mid % 2 == 0) {
			return double((gr[mid - 1] + gr[mid]) / 2.0);
		}
		else
			return gr[mid];
	}
}

void Student::setGrade() {
	gradeAvg = average(hwGrades);
}

void Student::setMedian() {
	gradeMed = median(hwGrades);
}



double finalScore(double avg, double exam) {
	return (avg * 0.4) + (exam * 0.6);
}

void createStudent(vector<Student>& pVec) {
	Student st;
	int select;
	do {
		cout << "Studenta ivesime: " << endl;
		cout << "1. Rankiniu budu  " << endl;
		cout << "2. Random         " << endl;
		cin >> select;
	} while (select != 1 && select != 2);

	switch (select) {
	case 1: {
		cin >> st;
		st.setGrade();
		st.setMedian();
		pVec.push_back(st);
		cout << "Irasas issaugotas\n";
		break;
	}
	case 2:
	{
		cout << "Iveskite studento varda: " << endl;
		cin >> st.name;
		cout << "Iveskite studento pavarde: " << endl;
		cin >> st.surname;

		const int max = 10;
		RandInt rnd{ 0, max };
		st.exam = rnd();
		st.setHwGradesRnd();
		st.setGrade();
		st.setMedian();
		pVec.push_back(st);
		cout << "Irasas issaugotas\n";
		system("cls");
		break;
	}
	default:
	{
		cout << "Neteisingas pasirinkimas" << endl;
		showMenu(pVec);
		break;
	}
	}
}

void menuText() {
	cout << "***********************************************" << endl;
	cout << "*     Studentu pazymiu vertinimo programa     *" << endl;
	cout << "*                                             *" << endl;
	cout << "***********************************************" << endl;
	cout << "* 1. Prideti studento irasa                   *" << endl;
	cout << "* 2. Rodyti studentu irasus                   *" << endl;
	cout << "* 3. Uzdaryti programa                        *" << endl;
	cout << "*                                             *" << endl;
	cout << "***********************************************" << endl;
}

void showMenu(vector <Student> pRecords) {
	menuText();
	int select;
	cin >> select;
	system("cls");
	bool status = true;

	switch (select) {
	case 1: {
		createStudent(pRecords);
		do {
			cout << "Sukurti sekanti irasa? 1 - taip/2 - ne\n";
			cin >> select;
			if (select == 1) createStudent(pRecords);
			else if (select == 2) {
				system("cls");
				showMenu(pRecords);
				status = false;
			}
			else cout << "Iveskite tinkama skaiciu" << endl;
		} while (status);
		break;
	}

	case 2: {
		cout << pRecords;
		cout << endl << endl << endl;
		cout << "***********************************************" << endl;
		cout << "Pasirinkite sekanti veiksma: " << endl;
		cout << "1. Meniu                     " << endl;
		cout << "ANY. Norint isjungti           " << endl;
		cin >> select;
		if (select == 1) {
			system("cls");
			showMenu(pRecords);
		}
		else {
			system("exit");
		}
		break;
	}
	case 3: {
		system("exit");
		break;
	}
	default: {
		system("cls");
		cout << "Pasirinkimas negalimas" << endl;
		break;
	}
	}
}