#pragma once
#include "vectorEnv.h"
#include <list>

using std::list;
using std::advance;

ifstream& operator >> (ifstream& arg_ifstream, list <Student>& arg_records);
void CreateStudent(list<Student>& arg_records);
void FileInput(list<Student>&);
void ShowMenu(list <Student>);

void SortStudentsByFinalGrade(list<Student>&, list<Student>&, list<Student>);

void CreateSortedStudentsFiles(list<Student>);

bool CampareByName(const Student&, const Student&);