#include "vectorEnv.h"
int lChoise;
RandInt ORnd1{ 1, MAX_GRADE };
Student::Student() {
	pfName = "";
	pfSurname = "";
	pfGradeAvg = 0;
	pfGradeMed = 0;
	pfHomeworkGrade = 0;
	pfExam = 0.0;
	pfFinalGrade = 0.0;
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
	pfFinalGrade = arg_st1.pfFinalGrade;
}
Student& Student::operator=(const Student& arg_st1) {

	pfName = arg_st1.pfName;
	pfSurname = arg_st1.pfSurname;
	pfHomeworkGrades = arg_st1.pfHomeworkGrades;
	pfGradeAvg = arg_st1.pfGradeAvg;
	pfGradeMed = arg_st1.pfGradeMed;
	pfExam = arg_st1.pfExam;
	pfFinalGrade = arg_st1.pfFinalGrade;

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

	while (lTemp <= 1 || lTemp > 10) {
		cout << "Pazymis turi buti nurodytas intervale [1-10]\n";
		arg_input >> lTemp;
	}

	arg_st1.pfExam = lTemp;
	cout << "Iveskite namu darbu pazymius:\n";
	cout << "Norint sustabdyti, iveskite skaiciu nepriklausanti intervalui [1-10]\n";

	arg_st1.SetHwGrades();
	arg_st1.SetGrade();
	arg_st1.SetMedian();
	arg_st1.SetFinalGrade();

	system("cls");
	return arg_input;
}
ostream& operator << (ostream& arg_output, Student& arg_st1) {


	if (lChoise == 1) {
		arg_output << left << setw(14) << arg_st1.GetSurname() << left << setw(14) <<
			arg_st1.GetName() << setprecision(2) << fixed << CalcFinalScore(arg_st1.GetGrade(), arg_st1.GetExam()) << endl;
	}

	if (lChoise == 2) {
		arg_output << left << setw(14) << arg_st1.GetSurname() << left << setw(14) <<
			arg_st1.GetName() << setprecision(2) << fixed << CalcFinalScore(arg_st1.GetMedian(), arg_st1.GetExam()) << endl;
	}

	if (lChoise == 3) {
		arg_output << left << setw(14) << arg_st1.GetSurname() << left << setw(14) <<
			arg_st1.GetName() << std::right << setw(14) << setprecision(2) << fixed <<
			CalcFinalScore(arg_st1.GetGrade(), arg_st1.GetExam()) << std::right << setw(14) <<
			setprecision(2) << fixed << CalcFinalScore(arg_st1.GetMedian(), arg_st1.GetExam()) << endl;
	}

	return arg_output;
}
ifstream& operator >> (ifstream& arg_ifstream, vector <Student>& arg_records) {
	vector <string> lRows;
	vector <string> lWords;												// To store full and splited strings
	string lRow;
	int lWordsLength;
	Timer time1;
	if (arg_ifstream.fail())											// Check did file had open
		throw "Failo atidaryti nepavyko";
	else {
		while (arg_ifstream) {											// Splitting file into strings and
			if (!arg_ifstream.eof()) {									// pushing them into vector
				getline(arg_ifstream, lRow);
				lRows.push_back(lRow);
			}
			else break;
		}
		cout << "Ikelimas i eiluciu vectoriu uztruko: " << time1.elapsed() << endl;

		istringstream iss(lRows[1]);
		for (string s; iss >> s; )									// splitting it to words 
			lWords.push_back(s);
		lWordsLength = lWords.size() - 1;
		for (int i = 1; i < lRows.size(); i++) {						// i = 1 because first line useless in file
			istringstream iss(lRows[i]);								// Itarating threw strings vector and
			for (string s; iss >> s; )									// splitting it to words 
				lWords.push_back(s);

			Student OStudent;													// Put string into stream and converting 
			OStudent.pfExam = stoi(lWords[lWordsLength]);
			OStudent.pfName = lWords[1];
			OStudent.pfSurname = lWords[0];
			OStudent.SetHwGrades(lWords);
			OStudent.SetGrade();
			OStudent.SetMedian();
			OStudent.SetFinalGrade();
			arg_records.push_back(OStudent);							// Check are this solution solved recent problem
			lWords.clear();
		}
	}
	return arg_ifstream;
}
string Student::GetName() const {
	return pfName;
}
string Student::GetSurname() const {
	return pfSurname;
}
double Student::GetGrade() const {
	return pfGradeAvg;
}
double Student::GetMedian() const {
	return pfGradeMed;
}

double Student::GetExam() const {
	return pfExam;
}
double Student::GetFinalGrade() const {
	return pfFinalGrade;
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
	int lGradeCount = ORnd1();
	for (int i = 0; i < lGradeCount; i++) {
		pfHomeworkGrade = ORnd1();
		pfHomeworkGrades.push_back(pfHomeworkGrade);
	}
}
vector <int> SetHwGradesRnd(int arg_hwcount) {
	vector<int> lGrades;
	for (int i = 0; i < arg_hwcount; i++)
		lGrades.push_back(ORnd1());

	return lGrades;
}
int SetGrade(vector<int> arg_grades) {
	return Average(arg_grades);
}
double Average(vector <int> arg_grade) {
	double lSum = 0.0;																			// Delete redundant methods
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
void Student::SetName(istream& inStream) {
	inStream >> pfName;
}
void Student::SetName(string arg_name) {
	pfName = arg_name;
}
void Student::SetSurname(istream& inStream) {
	inStream >> pfSurname;
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
void Student::SetFinalGrade() {
	pfFinalGrade = CalcFinalScore(pfGradeAvg, pfExam);
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
		OStudent.SetName(cin);
		cout << "Iveskite studento pavarde:\n";
		OStudent.SetSurname(cin);
		OStudent.SetExam(ORnd1());
		OStudent.SetHwGradesRnd();
		OStudent.SetGrade();
		OStudent.SetMedian();
		OStudent.SetFinalGrade();
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
void CreateFile(int arg_count) {
	Timer time1;

	ofstream of("studentai" + to_string(arg_count) + ".txt");
	vector<string> lRndStudents;

	int lHWCount = 15;

	of << VARDAS << setw(27) << PAVARDE << setw(27);
	for (int i = 0; i < lHWCount; i++) {
		of << "ND" << i + 1 << setw(10);
	}
	of << "Egz." << endl;
	vector<int> lTempGradesVector;

	for (int i = 0; i < arg_count; i++) {

		if (i >= 0 && i < 9)
			of << VARDAS << i + 1 << setw(26) << PAVARDE << i + 1 << setw(27);

		if (i >= 9 && i < 99)
			of << VARDAS << i + 1 << setw(25) << PAVARDE << i + 1 << setw(26);

		if (i >= 99 && i < 999)
			of << VARDAS << i + 1 << setw(24) << PAVARDE << i + 1 << setw(25);

		if (i >= 999 && i < 9999)
			of << VARDAS << i + 1 << setw(23) << PAVARDE << i + 1 << setw(24);

		if (i >= 9999 && i < 99999)
			of << VARDAS << i + 1 << setw(22) << PAVARDE << i + 1 << setw(23);

		if (i >= 99999 && i < 999999)
			of << VARDAS << i + 1 << setw(21) << PAVARDE << i + 1 << setw(22);

		if (i >= 999999 && i < 9999999)
			of << VARDAS << i + 1 << setw(20) << PAVARDE << i + 1 << setw(21);

		lTempGradesVector = SetHwGradesRnd(lHWCount);
		for (int i = 0; i < lTempGradesVector.size(); i++) {
			if (i < 8) of << lTempGradesVector[i] << setw(11);
			else of << lTempGradesVector[i] << setw(12);
		}
		if (i < arg_count - 1) of << ORnd1() << endl;
		else of << ORnd1();
	}

	cout << "Failo sukurimas uztruko : " << time1.elapsed() << endl;
}
void CreateSortedStudentsFilesFirstStr(vector<Student> arg_records) {
	Timer time1;
	ofstream of1("vargsiukai.txt");
	of1 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of1 << "--------------------------------------------------------" << endl;

	ofstream of2("kietiakai.txt");
	of2 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of2 << "--------------------------------------------------------" << endl;

	for (int i = 0; i < arg_records.size(); i++) {
		if (arg_records[i].pfFinalGrade < 5.00) {
			of1 << left << setw(14) << arg_records[i].pfSurname << left << setw(14) <<
				arg_records[i].pfName << setprecision(2) << fixed << arg_records[i].pfFinalGrade << endl;
		}
		else {
			of2 << left << setw(14) << arg_records[i].pfSurname << left << setw(14) <<
				arg_records[i].pfName << setprecision(2) << fixed << arg_records[i].pfFinalGrade << endl;
		}
	}

	cout << "Studentu irasymas i faila uztruko: " << time1.elapsed() << "s\n";

}

void CreateSortedStudentsFilesSecondStr(vector<Student>& arg_vargsiukai, vector<Student>& arg_records) {
	Timer time1;
	int badStudents = 0;
	auto iter = arg_records.begin();
	while (iter->pfFinalGrade < 5.0 && iter != arg_records.end()) {
		badStudents++;
		iter++;
	}
	int lSumOfStudents = arg_records.size();
	string lFileName = "";
	if (lSumOfStudents < 999) {
		lFileName = "studentai.txt";
	}
	else if (999 <= lSumOfStudents && lSumOfStudents < 9999) {
		lFileName = "studentai1000.txt";
	}
	else if (9999 <= lSumOfStudents && lSumOfStudents < 99999) {
		lFileName = "studentai10000.txt";
	}

	else if (99999 <= lSumOfStudents && lSumOfStudents < 999999) {
		lFileName = "studentai100000.txt";
	}
	else if (999999 <= lSumOfStudents && lSumOfStudents < 9999999) {
		lFileName = "studentai1000000.txt";
	}
	else {
		lFileName = "studentai10000000.txt";
	}

	arg_vargsiukai.assign(arg_records.begin(), iter);

	//copy(arg_records.begin(), arg_records.end(), std::back_inserter(arg_vargsiukai)); //

	arg_records.erase(arg_records.begin(), arg_records.begin() + badStudents);

	ofstream of1("vargsiukai.txt");
	of1 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of1 << "--------------------------------------------------------" << endl;


	ofstream of2(lFileName);
	of2 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of2 << "--------------------------------------------------------" << endl;

	for (int i = 0; i < arg_vargsiukai.size(); i++) {
		of1 << left << setw(14) << arg_vargsiukai[i].pfSurname << left << setw(14) <<
			arg_vargsiukai[i].pfName << setprecision(2) << fixed << arg_vargsiukai[i].pfFinalGrade << endl;
	}
	for (int i = 0; i < arg_records.size(); i++) {
		of2 << left << setw(14) << arg_records[i].pfSurname << left << setw(14) <<
			arg_records[i].pfName << setprecision(2) << fixed << arg_records[i].pfFinalGrade << endl;
	}

	cout << "Studentu irasymas i faila uztruko: " << time1.elapsed() << "s\n";
}

int PreMenu() {
	cout << "***********************************************\n";
	cout << "*     Studentu pazymiu vertinimo programa     *\n";
	cout << "*  Pasirinkite koki STL conteineri naudosite  *\n";
	cout << "***********************************************\n";
	cout << "* 1. Vector                                   *\n";
	cout << "* 2. Deque                                    *\n";
	cout << "* 3. List                                     *\n";
	cout << "*                                             *\n";
	cout << "*                                             *\n";
	cout << "*                                             *\n";
	cout << "*                                             *\n";
	cout << "***********************************************\n";

	int lVDL = 0;
	do {
		lVDL = ValidInput();
		if (!(1 <= lVDL && lVDL <= 3))
			cout << "Toks pasirinkimas negalimas, Iveskite skaiciu nuo 1 iki 3\n";
		else {
			system("cls");
			return lVDL;
		}
	} while (1 <= lVDL && lVDL <= 3);
}

void MenuText() {
	cout << "***********************************************\n";
	cout << "*     Studentu pazymiu vertinimo programa     *\n";
	cout << "*                                             *\n";
	cout << "***********************************************\n";
	cout << "* 1. Prideti studento irasa                   *\n";
	cout << "* 2. Rodyti studentu irasus                   *\n";
	cout << "* 3. Nuskenuoti studentu irasus is file       *\n";
	cout << "* 4. Generuoti atsitiktinius studentus        *\n";
	cout << "* 5. 1 strategija - studenetu rusiavimas      *\n";
	cout << "* 6. 2 strategija - studenetu rusiavimas      *\n";
	cout << "* 7. Uzdaryti programa                        *\n";
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

		cout << "Pasirinkite: " << endl;
		cout << "1. Galutinis pazymis pagal vidurki" << endl;
		cout << "2. Galutinis pazymis pagal mediana" << endl;
		cout << "3. Rikiuoti pagal varda ir rodyti vid./med." << endl;

		do {
			lChoise = ValidInput();
		} while (lChoise > 3 || lChoise < 1);

		if (lChoise == 1) {
			cout << left << setw(14) << VARDAS << left << setw(14) << PAVARDE << "Galutinis(Vid.)" << endl;
			cout << "--------------------------------------------------------" << endl;

			for (int i = 0; i < arg_records.size(); i++)
				cout << arg_records[i];
		}

		if (lChoise == 2) {
			cout << left << setw(14) << VARDAS << left << setw(14) << PAVARDE << "Galutinis(Med.)" << endl;
			cout << "--------------------------------------------------------" << endl;

			for (int i = 0; i < arg_records.size(); i++)
				cout << arg_records[i];
		}

		if (lChoise == 3) {
			cout << "Vyksta rusiavimas" << endl;
			sort(arg_records.begin(), arg_records.end(), [](const Student& lhs, const Student& rhs) { return lhs.GetName() < rhs.GetName(); });
			cout << left << setw(14) << VARDAS << left << setw(14) << PAVARDE << "Galutinis(Vid.)" << "Galutinis(Med.)" << endl;
			cout << "--------------------------------------------------------" << endl;

			for (int i = 0; i < arg_records.size(); i++)
				cout << arg_records[i];
		}

		cout << "\n\n\n";
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
		cout << "Pasirinkite kiek studentu noresite generuoti \n";
		cout << "1. 1 000\n";
		cout << "2. 10 000\n";
		cout << "3. 100 000\n";
		cout << "4. 1 000 000\n";
		cout << "5. 10 000 000\n";

		lSelect = 0;
		lSelect = ValidInput();
		system("cls");
		switch (lSelect) {
		case 1:
			CreateFile(1000);
			break;															// Fulfill this scope
		case 2:
			CreateFile(10000);
			break;
		case 3:
			CreateFile(100000);
			break;
		case 4:
			CreateFile(1000000);
			break;
		case 5:
			CreateFile(10000000);
			break;
		default:																// Default empty, fix it
			break;
		}

		ShowMenu(arg_records);

		break;
	}

	case 5: {
		system("cls");
		vector<Student> vargsiukai;
		vector<Student> kietiakai;
		SortStudentsByFinalGradeFirstStr(vargsiukai, kietiakai, arg_records);
		CreateSortedStudentsFilesFirstStr(arg_records);
		ShowMenu(arg_records);
		break;
	}

	case 6: {
		system("cls");
		vector<Student> vargsiukai2;
		SortStudentsByFinalGradeSecondStr(arg_records);
		CreateSortedStudentsFilesSecondStr(vargsiukai2, arg_records);
		ShowMenu(arg_records);

		break;
	}
	case 7: {
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

void FileInput(vector<Student>& arg_records) {
	try {
		cout << "Pasirinkite kuri faila nuskaityti: \n";
		cout << "1." << FILENAME0 << endl;
		cout << "2." << FILENAME1 << endl;
		cout << "3." << FILENAME2 << endl;
		cout << "4." << FILENAME3 << endl;
		cout << "5." << FILENAME4 << endl;

		int fileNr;
		string fileName;

		do {
			cin >> fileNr;
		} while (fileNr < 1 && fileNr > 3);

		switch (fileNr) {
		case 1:
			fileName = FILENAME0;
			break;
		case 2:
			fileName = FILENAME1;
			break;
		case 3:
			fileName = FILENAME2;
			break;
		case 4:
			fileName = FILENAME3;
			break;
		case 5:
			fileName = FILENAME4;
			break;
		default:
			cout << "Tokio pasirinkimo nera" << endl;
			system("exit");
		}
		Timer time1;
		ifstream inFile(fileName);
		inFile >> arg_records;
		inFile.close();
		system("cls");
		cout << "Failas nuskaitytas. Uztruko: " << time1.elapsed() << "s\n";
	}
	catch (const char* txtExeption) {
		cout << "Isimtis: " << txtExeption << endl;
		ShowMenu(arg_records);
	}
}

void SortStudentsByFinalGradeFirstStr(vector<Student>& arg_vargsiukai, vector<Student>& arg_kietiakai, vector<Student> arg_records) {
	Timer time1;
	for (int i = 0; i < arg_records.size(); i++) {
		if (arg_records[i].pfFinalGrade < 5.00)
			arg_vargsiukai.push_back(arg_records[i]);
		else
			arg_kietiakai.push_back(arg_records[i]);
	}

	cout << "Studentu skirstymas i vectorius pagal pazymi uztruko: " << time1.elapsed() << "s\n";
}

void SortStudentsByFinalGradeSecondStr(vector<Student>& arg_records) {
	Timer time1;
	sort(arg_records.begin(), arg_records.end(), [](const Student& lhs, const Student& rhs) {
		return lhs.GetFinalGrade() < rhs.GetFinalGrade();
		});
	cout << "Studentu skirstymas pagal pazymi uztruko: " << time1.elapsed() << "s\n";
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