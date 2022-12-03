#include "vectorEnv.h"
#include "dequeEnv.h"
#include "listEnv.h"
int main()
{
	int lTempVar = PreMenu();

	if (lTempVar == 1) {
		vector<Student> lRecords;
		ShowMenu(lRecords);
	}
	if (lTempVar == 2) {
		deque<Student> lRecords2;
		ShowMenu(lRecords2);
	}
	else if (lTempVar == 3) {
		list<Student> lRecords3;
		ShowMenu(lRecords3);
	}
	else {
		system("exit");
	}
}
