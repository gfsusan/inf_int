#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int A;
	inf_int B(1234567890);
	inf_int C("00012345678123456780000000012345678");
	inf_int D(C);
	inf_int E("12345678000000000000000012345678");
	
	cout << "Check1: constructor" << endl;
	cout << A << endl << B << endl << C << endl << D << endl;
	cout << endl;

	cout << "Check2: operator> " << endl;
	cout << "C > D ? " << endl;
	cout << "Expected Ans: Yes \t"; cout << "Ans: " << (C > D) ? "Yes" : "No";
	cout << endl;


	

	C = B*A;
	cout << "C = B * A = " << C << endl;

	cout << "A + B = " << A + B;
	

	


	return 0;

	inf_int a, e;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f = d;
	inf_int g(f);

	// cin >> g ;   // not required

	a = b*c;

	// e=g/f;       // not required

	b = c - d;

	if (f == d) {
	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "c : " << c << endl;
	cout << "d : " << d << endl;
	// cout << "e : " << e << endl;
	cout << "f : " << f << endl;
	// cout << "g : " << g << endl;
	}


	return 0;
}