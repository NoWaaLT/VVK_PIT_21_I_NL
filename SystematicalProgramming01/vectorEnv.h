#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "RandInt.h"
#include "Timer.h"
#include <fstream>
#include <sstream>
#include <iterator>

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

extern int lChoise;

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
	/*friend ostream& operator << (ostream&, const vector <Student>&);*/
	friend ostream& operator << (ostream& arg_output, Student&);
	//friend ofstream& operator << (ofstream&, vector <Student>&);

	friend void CreateStudent(vector<Student>&);										// I removed reference sign after Student
	friend void FileInput(vector<Student>&);
	
	void SetHwGrades();
	void SetHwGrades(vector<string>);
	void SetHwGradesRnd();

	/*double Average(vector <int>);*/
	double Median(vector <int>);

	void SetName(istream&);
	void SetName(string arg_name);
	void SetSurname(istream&);
	void SetSurname(string arg_surname);
	void SetExam(int);
	void SetGrade();
	void SetMedian();
	void SetFinalGrade();

	string GetName() const;
	string GetSurname() const;
	double GetGrade() const;
	double GetMedian() const;
	double GetExam() const;
	double GetFinalGrade() const;

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

int PreMenu();