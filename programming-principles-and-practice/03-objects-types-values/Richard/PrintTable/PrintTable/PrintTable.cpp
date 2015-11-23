// PrintTable.cpp
//

#include "stdafx.h"
#include "std_lib_facilities.h"

void write_sorry() {
	cout << "sorry\n";
}

int main()
{
	

	for (int i = 'a'; i <= 'z'; i++) {
		char c = i;
		cout << c << '\t' << i << '\n';
		
			
	}
	//cout << '\n';
	write_sorry();



    return 0;
}

