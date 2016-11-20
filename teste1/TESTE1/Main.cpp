#include "exceptions.h"
#include "faculdade.h"
#include "utils.h"
#include "Menus.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#undef max  //To use numeric_limits<streamsize>::max()




int main() {
	bool stop_program = false;
	while (!stop_program) {

		try {
			stop_program = Menu_department();
		}
		catch (exception_or_error x) {
			cerr << x.get_reason() << ". Tente novamente!\n";
			system("PAUSE");
			clrscr();
		}
	}
	return 0;
}