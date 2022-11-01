#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include "RandInt.h";


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

class Student {
	string name, surname;
	int hwGrade;
	double exam, gradeAvg, gradeMed;
	vector<int> hwGrades;
public:
	Student();
	~Student();
	Student(const Student& st);

	Student& operator=(const Student&);
	friend istream& operator >> (istream& input, Student& in);
	friend ostream& operator << (ostream& output, const vector <Student>& st);

	friend void createStudent(vector<Student>&); // Had deleted adress name

	void setHwGrades();
	void setHwGradesRnd();
	double average(vector <int>);
	double median(vector <int>);
	void setGrade();
	void setMedian();

	string getName(vector <Student>, int);
	string getSurname(vector <Student>, int);
	double getGrade(vector <Student>, int);
	double getMedian(vector <Student>, int);

	friend void showMenu(vector <Student>);
};

double finalScore(double, double);

void menuText();