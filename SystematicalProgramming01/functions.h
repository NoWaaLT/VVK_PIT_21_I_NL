#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include "RandInt.h"
#include "Timer.h"
#include <fstream>
#include <sstream>
#include <iterator>

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::left;
using std::setw;
using std::setprecision;
using std::sort;
using std::fixed;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::ofstream;
using std::stringstream;
using std::to_string;

const char FILENAME0[] = "studentai1000.txt";
const char FILENAME1[] = "studentai10000.txt";
const char FILENAME2[] = "studentai100000.txt";
const char FILENAME3[] = "studentai1000000.txt";
const char FILENAME4[] = "studentai10000000.txt";
const int MAX_GRADE = 10;
const string VARDAS = "Vardas";
const string PAVARDE = "Pavarde";

class Student {
	string pfName, pfSurname;
	int pfHomeworkGrade;
	double pfExam, pfGradeAvg, pfGradeMed, pfFinalGrade;;
	vector<int> pfHomeworkGrades;
public:
	Student();
	~Student();
	Student(const Student&);

	Student& operator=(const Student&);
	friend istream& operator >> (istream&, Student&);
	friend ifstream& operator >> (ifstream&, vector<Student>&);
	friend ostream& operator << (ostream&, const vector <Student>&);
	//friend ofstream& operator << (ofstream&, vector <Student>&);

	friend void CreateStudent(vector<Student>&);
	friend void FileInput(vector<Student>&);
	
	void SetHwGrades();
	void SetHwGrades(vector<string>);
	void SetHwGradesRnd();

	/*double Average(vector <int>);*/
	double Median(vector <int>);

	void SetName(string);
	void SetSurname(string);
	void SetExam(int);
	void SetGrade();
	void SetMedian();
	void SetFinalGrade();

	string GetName(vector <Student>, int);
	string GetName() const;
	string GetSurname(vector <Student>, int);
	double GetGrade(vector <Student>, int);
	double GetMedian(vector <Student>, int);
	double GetFinalGrade(vector <Student>, int);

	friend void ShowMenu(vector <Student>);

	friend void SortStudentsByFinalGrade(vector<Student>&, vector<Student>&, vector<Student>);

	friend void CreateSortedStudentsFiles(vector<Student>);
};


double CalcFinalScore(double, double);
void MenuText();
int ValidInput();
void CreateFile(int arg_count);

vector<int> SetHwGradesRnd(int);

int SetGrade(vector<int>);
double Average(vector <int> arg_grade);