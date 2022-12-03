#pragma once
#include <deque>
#include "vectorEnv.h"

using std::deque;

//int lChoise;

ifstream& operator >> (ifstream&, deque<Student>&);
void CreateStudent(deque<Student>&);
void FileInput(deque<Student>&);
void ShowMenu(deque <Student>);

void SortStudentsByFinalGrade(deque<Student>&, deque<Student>&, deque<Student>);

void CreateSortedStudentsFiles(deque<Student>);