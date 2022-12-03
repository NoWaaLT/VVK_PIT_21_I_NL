#include "dequeEnv.h"
RandInt ORnd2{ 1, MAX_GRADE };

ifstream& operator >> (ifstream& arg_ifstream, deque <Student>& arg_records) {
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
		for (int i = 2; i < lRows.size(); i++) {						// i = 1 because first line useless in file
			istringstream iss(lRows[i]);								// Itarating threw strings vector and
			for (string s; iss >> s; )									// splitting it to words 
				lWords.push_back(s);

			Student OStudent;													// Put string into stream and converting 
			OStudent.SetExam(stoi(lWords[lWordsLength]));
			OStudent.SetName(lWords[1]);
			OStudent.SetSurname(lWords[0]);
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

void CreateStudent(deque<Student>& arg_records) {
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
		OStudent.SetExam(ORnd2());
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

void FileInput(deque<Student>& arg_records) {
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

void ShowMenu(deque <Student> arg_records) {

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
		sort(arg_records.begin(), arg_records.end(), [](const Student& lhs, const Student& rhs) { return lhs.GetName() < rhs.GetName(); });	// Sorts vector by name alphabetically

		cout << "Pasirinkite: " << endl;
		cout << "1. Galutinis pazymis pagal vidurki" << endl;
		cout << "2. Galutinis pazymis pagal mediana" << endl;
		cout << "3. Surykiuoti ir rodyti visa informacija" << endl;

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
		deque<Student> vargsiukai;
		deque<Student> kietiakai;
		SortStudentsByFinalGrade(vargsiukai, kietiakai, arg_records);
		CreateSortedStudentsFiles(arg_records);
		ShowMenu(arg_records);
		break;
	}
	case 6: {
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

void SortStudentsByFinalGrade(deque<Student>& arg_vargsiukai, deque<Student>& arg_kietiakai, deque<Student> arg_records) {
	Timer time1;
	for (int i = 0; i < arg_records.size(); i++) {
		if (arg_records[i].GetFinalGrade() < 5.00)
			arg_vargsiukai.push_back(arg_records[i]);
		else
			arg_kietiakai.push_back(arg_records[i]);
	}

	cout << "Studentu skirstymas i vectorius pagal pazymi uztruko: " << time1.elapsed() << "s\n";
}
void CreateSortedStudentsFiles(deque<Student> arg_records) {
	Timer time1;
	ofstream of1("vargsiukai.txt");
	of1 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of1 << "--------------------------------------------------------" << endl;

	ofstream of2("kietiakai.txt");																					// <-----------------------
	of2 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of2 << "--------------------------------------------------------" << endl;

	for (int i = 0; i < arg_records.size(); i++) {
		if (arg_records[i].GetFinalGrade() < 5.00) {
			of1 << left << setw(14) << arg_records[i].GetSurname() << left << setw(14) <<
				arg_records[i].GetName() << setprecision(2) << fixed << arg_records[i].GetFinalGrade() << endl;
		}
		else {
			of2 << left << setw(14) << arg_records[i].GetSurname() << left << setw(14) <<
				arg_records[i].GetName() << setprecision(2) << fixed << arg_records[i].GetFinalGrade() << endl;
		}
	}

	cout << "Studentu irasymas i faila uztruko: " << time1.elapsed() << "s\n";

}
