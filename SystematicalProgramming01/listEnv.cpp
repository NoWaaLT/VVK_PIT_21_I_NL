#include "listEnv.h"
RandInt ORnd3{ 1, MAX_GRADE };
ifstream& operator >> (ifstream& arg_ifstream, list <Student>& arg_records) {
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

void CreateStudent(list<Student>& arg_records) {
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
		OStudent.SetExam(ORnd3());
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

void FileInput(list<Student>& arg_records) {
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

void ShowMenu(list <Student> arg_records) {

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
		arg_records.sort([](const Student& lhs, const Student& rhs) { return lhs.GetName() < rhs.GetName(); });	// Sorts vector by name alphabetically


		//void sortList(std::list<Student> &S, std::list<Student> &GS, char sortType) {
		//	if (sortType == 'v') {
		//		S.sort([](Student& s1, Student& s2) {return s1.name < s2.name; });
		//		GS.sort([](Student& s1, Student& s2) {return s1.name < s2.name; });
		//	}
		//	else if (sortType == 'p') {
		//		S.sort([](Student& s1, Student& s2) {return s1.surname < s2.surname; });
		//		GS.sort([](Student& s1, Student& s2) {return s1.surname < s2.surname; });
		//	}
		//}


		cout << "Pasirinkite: " << endl;
		cout << "1. Galutinis pazymis pagal vidurki" << endl;
		cout << "2. Galutinis pazymis pagal mediana" << endl;
		cout << "3. Surykiuoti ir rodyti visa informacija" << endl;

		do {
			lChoise = ValidInput();
		} while (lChoise > 3 || lChoise < 1);

		//list<Student>::iterator iter = arg_records.begin();

		if (lChoise == 1) {
			cout << left << setw(14) << VARDAS << left << setw(14) << PAVARDE << "Galutinis(Vid.)" << endl;
			cout << "--------------------------------------------------------" << endl;

			for (auto it = arg_records.begin(); it != arg_records.end(); ++it)
				cout << *it;

			//for (int i = 0; i < arg_records.size(); i++) {
			//	advance(iter, i);
			//	cout << *iter;
			//}
		}

		if (lChoise == 2) {
			cout << left << setw(14) << VARDAS << left << setw(14) << PAVARDE << "Galutinis(Med.)" << endl;
			cout << "--------------------------------------------------------" << endl;

			for (auto it = arg_records.begin(); it != arg_records.end(); ++it)
				cout << *it;

			//for (int i = 0; i < arg_records.size(); i++) {
			//	advance(iter, i);
			//	cout << *iter;
			//}
		}

		if (lChoise == 3) {

			cout << left << setw(14) << VARDAS << left << setw(14) << PAVARDE << "Galutinis(Vid.)" << "Galutinis(Med.)" << endl;
			cout << "--------------------------------------------------------" << endl;


			for (auto it = arg_records.begin(); it != arg_records.end(); ++it)
				cout << *it;

			//for (int i = 0; i < arg_records.size(); i++) {
			//	advance(iter, i);
			//	cout << *iter;
			//}
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
		list<Student> vargsiukai;
		list<Student> kietiakai;
		SortStudentsByFinalGradeFirstStr(vargsiukai, kietiakai, arg_records);
		CreateSortedStudentsFiles(arg_records);
		ShowMenu(arg_records);
		break;
	}

	case 6: {
		system("cls");
		list<Student> vargsiukai3;
		SortStudentsByFinalGradeSecondStr(arg_records);
		CreateSortedStudentsFilesSecondStr(vargsiukai3, arg_records);
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

void SortStudentsByFinalGradeFirstStr(list<Student>& arg_vargsiukai, list<Student>& arg_kietiakai, list<Student> arg_records) {
	Timer time1;
	/*list <Student> ::iterator iter = arg_records.begin();


	for (int i = 0; i < arg_records.size(); i++) {
		advance(iter, i);
		if ((*iter).GetFinalGrade() < 5.00)
			arg_vargsiukai.push_back(*iter);
		else
			arg_kietiakai.push_back(*iter);
	}*/

	for (auto it = arg_records.begin(); it != arg_records.end(); ++it) {
		if ((*it).GetFinalGrade() < 5.00)
			arg_vargsiukai.push_back(*it);
		else
			arg_kietiakai.push_back(*it);
	}
	cout << "Studentu skirstymas i vectorius pagal pazymi uztruko: " << time1.elapsed() << "s\n";
}
void CreateSortedStudentsFiles(list<Student> arg_records) {
	Timer time1;
	ofstream of1("vargsiukai.txt");
	of1 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of1 << "--------------------------------------------------------" << endl;

	ofstream of2("kietiakai.txt");																					// <-----------------------
	of2 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of2 << "--------------------------------------------------------" << endl;


	//list <Student> ::iterator iter = arg_records.begin();
	//for (int i = 0; i < arg_records.size(); i++) {
	//	advance(iter, i);
	//	if ((*iter).GetFinalGrade() < 5.00) {
	//		of1 << left << setw(14) << (*iter).GetSurname() << left << setw(14) <<
	//			(*iter).GetName() << setprecision(2) << fixed << (*iter).GetFinalGrade() << endl;
	//	}
	//	else {
	//		of2 << left << setw(14) << (*iter).GetSurname() << left << setw(14) <<
	//			(*iter).GetName() << setprecision(2) << fixed << (*iter).GetFinalGrade() << endl;
	//	}
	//}

	for (auto it = arg_records.begin(); it != arg_records.end(); ++it) {
		if ((*it).GetFinalGrade() < 5.00) {
			of1 << left << setw(14) << (*it).GetSurname() << left << setw(14) <<
				(*it).GetName() << setprecision(2) << fixed << (*it).GetFinalGrade() << endl;
		}
		else {
			of2 << left << setw(14) << (*it).GetSurname() << left << setw(14) <<
				(*it).GetName() << setprecision(2) << fixed << (*it).GetFinalGrade() << endl;
		}
	}

	cout << "Studentu irasymas i faila uztruko: " << time1.elapsed() << "s\n";

}

void CreateSortedStudentsFilesSecondStr(list<Student>& arg_vargsiukai, list<Student>& arg_records) {
	Timer time1;
	int badStudents = 0;
	auto iter = arg_records.begin();
	while (iter->GetFinalGrade() < 5.0 && iter != arg_records.end()) {
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

	copy(arg_records.begin(), arg_records.end(), std::back_inserter(arg_vargsiukai));

	//arg_vargsiukai.assign(arg_records.begin(), iter);


	ofstream of1("vargsiukai.txt");
	of1 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of1 << "--------------------------------------------------------" << endl;


	ofstream of2(lFileName);
	of2 << left << setw(14) << PAVARDE << left << setw(14) << VARDAS << "Galutinis(Vid.)" << endl;
	of2 << "--------------------------------------------------------" << endl;

	for (auto it = arg_records.begin(); it != iter; ++it) {
		of1 << left << setw(14) << (*it).GetSurname() << left << setw(14) <<
			(*it).GetName() << setprecision(2) << fixed << (*it).GetFinalGrade() << endl;
	}

	arg_records.erase(arg_records.begin(), iter);


	for (auto it = arg_records.begin(); it != arg_records.end(); ++it)
	{
		of2 << left << setw(14) << (*it).GetSurname() << left << setw(14) <<
			(*it).GetName() << setprecision(2) << fixed << (*it).GetFinalGrade() << endl;
	}

	cout << "Studentu irasymas i faila uztruko: " << time1.elapsed() << "s\n";
}

void SortStudentsByFinalGradeSecondStr(list<Student>& arg_records) {
	Timer time1;

	arg_records.sort([](const Student& lhs, const Student& rhs) { return lhs.GetFinalGrade() < rhs.GetFinalGrade(); });

	cout << "Studentu skirstymas pagal pazymi uztruko: " << time1.elapsed() << "s\n";
}