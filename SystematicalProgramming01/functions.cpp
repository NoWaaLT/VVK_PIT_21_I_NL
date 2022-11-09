#include "functions.h"

Student::Student() {
	pfName = "";
	pfSurname = "";
	pfGradeAvg = 0;
	pfGradeMed = 0;
	pfHomeworkGrade = 0;
	pfExam = 0.0;
}
Student::~Student() {
}
Student::Student(const Student& arg_st1) {
	pfName = arg_st1.pfName;
	pfSurname = arg_st1.pfSurname;
	pfHomeworkGrades = arg_st1.pfHomeworkGrades;
	pfGradeAvg = arg_st1.pfGradeAvg;
	pfGradeMed = arg_st1.pfGradeMed;
	pfExam = arg_st1.pfExam;
}
Student& Student::operator=(const Student& arg_st1) {

	pfName = arg_st1.pfName;
	pfSurname = arg_st1.pfSurname;
	pfHomeworkGrades = arg_st1.pfHomeworkGrades;
	pfGradeAvg = arg_st1.pfGradeAvg;
	pfGradeMed = arg_st1.pfGradeMed;
	pfExam = arg_st1.pfExam;

	return *this;
}

istream& operator >> (istream& arg_input, Student& arg_st1) {
	cout << "Iveskite studento varda:\n";
	arg_input >> arg_st1.pfName;
	cout << "Iveskite studento pavarde:\n";
	arg_input >> arg_st1.pfSurname;
	cout << "Iveskite egzamino pazymi: \n";

	int lTemp = 0;
	arg_input >> lTemp;

	while (lTemp <= 0 || lTemp > 10) {
		cout << "Pazymis turi buti nurodytas intervale [0-10]\n";
		arg_input >> lTemp;
	}

	arg_st1.pfExam = lTemp;
	cout << "Iveskite namu darbu pazymius:\n";
	cout << "Norint sustabdyti, iveskite skaiciu nepriklausanti intervalui [1-10]\n";

	arg_st1.SetHwGrades();

	arg_st1.SetGrade();
	arg_st1.SetMedian();

	system("cls");
	return arg_input;
}
ostream& operator << (ostream& arg_output, const vector <Student>& arg_st1) {
	
	int lChoise;

	cout << "Pasirinkite: " << endl;
	cout << "1. Galutinis pazymis pagal vidurki" << endl;
	cout << "2. Galutinis pazymis pagal mediana" << endl;
	cout << "3. Surykiuoti ir rodyti visa informacija" << endl;

	do {
		lChoise = ValidInput();
	} while (lChoise > 3 || lChoise < 1);

	if (lChoise == 1) {
		cout << left << setw(14) << "Pavarde" << left << setw(14) << "Vardas" << "Galutinis(Vid.)" << endl;
		cout << "--------------------------------------------------------" << endl;
	
	for (int i = 0; i < arg_st1.size(); i++) {
		arg_output << left << setw(14) << arg_st1[i].pfSurname << left << setw(14) <<
		arg_st1[i].pfName << setprecision(2) << fixed << CalcFinalScore(arg_st1[i].pfGradeAvg, arg_st1[i].pfExam) << endl;
		}
	}

	if (lChoise == 2) {
		cout << left << setw(14) << "Pavarde" << left << setw(14) << "Vardas" << "Galutinis(Med.)" << endl;
		cout << "--------------------------------------------------------" << endl;
		for (int i = 0; i < arg_st1.size(); i++) {
			arg_output << left << setw(14) << arg_st1[i].pfSurname << left << setw(14) <<
			arg_st1[i].pfName << setprecision(2) << fixed << CalcFinalScore(arg_st1[i].pfGradeMed, arg_st1[i].pfExam) << endl;
		}
	}

	if (lChoise == 3) {

		cout << left << setw(14) << "Pavarde" << left << setw(14) << "Vardas" << "Galutinis(Vid.)" << "Galutinis(Med.)" << endl;
		cout << "--------------------------------------------------------" << endl;

		for (int i = 0; i < arg_st1.size(); i++) {
			arg_output << left << setw(14) << arg_st1[i].pfSurname << left << setw(14) <<
			arg_st1[i].pfName << std::right << setw(14) << setprecision(2) << fixed <<
			CalcFinalScore(arg_st1[i].pfGradeAvg, arg_st1[i].pfExam) << std::right << setw(14) <<
			setprecision(2) << fixed << CalcFinalScore(arg_st1[i].pfGradeMed, arg_st1[i].pfExam) << endl;
		}
	}

	return arg_output;
}
ifstream& operator >> (ifstream& arg_ifstream, vector <Student>& arg_records) {
	vector <string> lRows;
	vector <string> lWords;								// To store full and splited strings
	string lRow;

	if (arg_ifstream.fail())											// Check did file had open
		throw "Failo atidaryti nepavyko";
	else {
		while (arg_ifstream) {										// Splitting file into strings and
			if (!arg_ifstream.eof()) {								// pushing them into vector
				getline(arg_ifstream, lRow);
				lRows.push_back(lRow);
			}
			else break;
		}

		for (int i = 1; i < lRows.size(); i++) {				// i = 1 because first line useless in file
			istringstream iss(lRows[i]);						// Itarating threw strings vector and
			for (string s; iss >> s; )						// splitting it to words 
				lWords.push_back(s);

			int lWordsLength = lWords.size();

			Student OStudent;
			stringstream ss;
			int lTemp;										// Put string into stream and converting 
			ss << lWords[lWordsLength - 1];
			ss >> lTemp;
			OStudent.SetExam(lTemp);
			OStudent.SetName(lWords[0]);
			OStudent.SetSurname(lWords[1]);
			OStudent.SetHwGrades(lWords);
			OStudent.SetGrade();
			OStudent.SetMedian();
			arg_records.push_back(OStudent);						// Check are this solution solved recent problem
			lWords.clear();
		}
	}
	return arg_ifstream;
}

string Student::GetName() const {
	return pfName;
}
string Student::GetName(vector <Student> arg_records, int arg_index) {
	return arg_records[arg_index].pfName;
}
string Student::GetSurname(vector <Student> arg_records, int arg_index) {
	return arg_records[arg_index].pfSurname;
}
double Student::GetGrade(vector <Student> arg_records, int arg_index) {
	return arg_records[arg_index].pfGradeAvg;
}
double Student::GetMedian(vector <Student> arg_records, int arg_index) {
	return arg_records[arg_index].pfGradeMed;
}

void Student::SetHwGrades() {
	do {
		pfHomeworkGrade = ValidInput();
		if (pfHomeworkGrade >= 0 && pfHomeworkGrade <= 10) {
			pfHomeworkGrades.push_back(pfHomeworkGrade);
		}
	} while (pfHomeworkGrade >= 0 && pfHomeworkGrade <= 10);
}
void Student::SetHwGrades(vector<string> arg_words) {
	stringstream ss;
	for (int i = 2; i < arg_words.size() - 1; i++) {
		ss << arg_words[i];
		ss >> Student::pfHomeworkGrade;
		pfHomeworkGrades.push_back(pfHomeworkGrade);
		ss = stringstream();
	}
}
void Student::SetHwGradesRnd() {
	const int MAX_GRADE = 10;
	const int MAX_LOOP_LENGTH = 10000;

	RandInt ORnd1{ 0, MAX_GRADE };
	RandInt ORnd2{ 0, MAX_LOOP_LENGTH };

	int lGradeCount = ORnd1();
	for (int i = 0; i < lGradeCount; i++) {
		pfHomeworkGrade = ORnd1();
		pfHomeworkGrades.push_back(pfHomeworkGrade);
	}
}

double Student::Average(vector <int> arg_grade) {
	double lSum = 0.0;
	for (int i = 0; i < arg_grade.size(); i++) {
		lSum += arg_grade[i];
	}
	lSum /= (double)arg_grade.size();
	return lSum;
}
double Student::Median(vector <int> arg_grade) {
	if (arg_grade.size() == 1) {
		return arg_grade[0];
	}
	else if (arg_grade.size() < 1) {
		return 0;
	}
	else {
		sort(arg_grade.begin(), arg_grade.end());
		int  lMid = arg_grade.size() / 2;

		if (lMid % 2 == 0)
			return double((arg_grade[lMid - 1] + arg_grade[lMid]) / 2.0);
		else
			return arg_grade[lMid];
	}
}

void Student::SetName(string arg_name) {
	pfName = arg_name;
}
void Student::SetSurname(string arg_surname) {
	pfSurname = arg_surname;
}
void Student::SetExam(int arg_exam) {
	pfExam = arg_exam;
}
void Student::SetGrade() {
	pfGradeAvg = Average(pfHomeworkGrades);
}
void Student::SetMedian() {
	pfGradeMed = Median(pfHomeworkGrades);
}

double CalcFinalScore(double arg_average, double arg_exam) {
	return (arg_average * 0.4) + (arg_exam * 0.6);
}
void CreateStudent(vector<Student>& arg_records) {
	Student OStudent;
	int lSelect;

	while (true) {
		cout << "Studenta ivesime:\n";
		cout << "1. Rankiniu budu\n";
		cout << "2. Random\n";
		lSelect = ValidInput();
		break;
	}

	switch (lSelect) {
	case 1: {
		cin >> OStudent;
		arg_records.push_back(OStudent);
		cout << "Irasas issaugotas\n";
		break;
	}
	case 2:
	{
		cout << "Iveskite studento varda:\n";
		cin >> OStudent.pfName;
		cout << "Iveskite studento pavarde:\n";
		cin >> OStudent.pfSurname;

		const int MAX_RANDOM = 10;
		RandInt rnd{ 0, MAX_RANDOM };
		OStudent.pfExam = rnd();
		OStudent.SetHwGradesRnd();
		OStudent.SetGrade();
		OStudent.SetMedian();
		arg_records.push_back(OStudent);
		cout << "Irasas issaugotas\n";
		system("cls");
		break;
	}
	default:
	{
		cout << "Neteisingas pasirinkimas\n";
		ShowMenu(arg_records);
		break;
	}
	}
}

void MenuText() {
	cout << "***********************************************\n";
	cout << "*     Studentu pazymiu vertinimo programa     *\n";
	cout << "*                                             *\n";
	cout << "***********************************************\n";
	cout << "* 1. Prideti studento irasa                   *\n";
	cout << "* 2. Rodyti studentu irasus                   *\n";
	cout << "* 3. Nuskenuoti studentu irasus is file       *\n";
	cout << "* 4. Uzdaryti programa                        *\n";
	cout << "*                                             *\n";
	cout << "***********************************************\n";
}

void ShowMenu(vector <Student> arg_records) {

	MenuText();

	int lSelect;
	cin >> lSelect;
	system("cls");

	switch (lSelect) {
	case 1: {
		CreateStudent(arg_records);
		do {
			cout << "Sukurti sekanti irasa? 1 - taip/2 - ne\n";
			lSelect = ValidInput();
			if (lSelect == 1) CreateStudent(arg_records);
			else if (lSelect == 2) {
				system("cls");
				ShowMenu(arg_records);
				break;
			}
			else cout << "Iveskite tinkama skaiciu\n";
		} while (true);
		break;
	}

	case 2: {
		cout << "Vyksta rusiavimas" << endl;
		sort(arg_records.begin(), arg_records.end(), [](const Student& lhs, const Student& rhs) { return lhs.GetName() < rhs.GetName();});	// Sorts vector by name alphabetically

		cout << arg_records;
		cout << endl << endl << endl;
		cout << "***********************************************\n";;
		cout << "Pasirinkite sekanti veiksma:					\n";
		cout << "1. Meniu										\n";
		cout << "*. Norint isjungti								\n";

		lSelect = ValidInput();

		if (lSelect == 1) {
			system("cls");
			ShowMenu(arg_records);
		}
		else {
			system("exit");
		}
		break;
	}

	case 3: {
		FileInput(arg_records);
		ShowMenu(arg_records);

		break;
	}
	case 4: {
		system("exit");
		break;
	}
	default: {
		system("cls");
		cout << "Pasirinkimas negalimas\n";
		break;
	}
	}
}

void FileInput(vector<Student>& pVec) {
	try {
		cout << "Pasirinkite kur faila nuskaityti: \n";
		cout << "1." << FILENAME1 << endl;
		cout << "2." << FILENAME2 << endl;
		cout << "3." << FILENAME3 << endl;
		int fileNr;
		string fileName;
		do {
			cin >> fileNr;
		} while (fileNr < 1 && fileNr > 3);

		switch (fileNr) {
		case 1: 
			fileName = FILENAME1;
			break;
		case 2:
			fileName = FILENAME2;
			break;
		case 3:
			fileName = FILENAME3;
			break;
		default:
			cout << "Tokio pasirinkimo nera" << endl;
			system("exit");
		}
		ifstream inFile(fileName);
		inFile >> pVec;
		inFile.close();
		system("cls");
		cout << "Failas nuskaitytas\n";
	}
	catch (const char * txtExeption) {
		cout << "Isimtis: " << txtExeption << endl;
		ShowMenu(pVec);
	}
}

int ValidInput()
{
	int x;
	cin >> x;
	while (std::cin.fail())																	// Checks input is numeric or not, if true, repeat cin
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Bloga ivestis. Iveskite skaiciu: ";
		cin >> x;
	}
	return x;
}