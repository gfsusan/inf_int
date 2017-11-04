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
	
	inf_int F("1111");
	inf_int G("-1234");
	inf_int H("-1111");
	inf_int I("1234");
	
	inf_int J("12340000");
	inf_int K("-12340000");
	inf_int L("12345678");
	inf_int M("-12345678");

	inf_int X("0");
	inf_int Y("-0");

	cout << "Check1: constructor" << endl;

	cout << A << endl << B << endl << C << endl << D << endl;
	cout << endl;

	cout << "Check2: operator> " << endl;
	
	cout << "* 부호가 다른 경우\t" << endl;
	cout << "1111 > -1234 ?\t";
	cout << (F > G) << endl;
	cout << "-1111 > 1234 ?\t";
	cout << (H > I) << endl;
	cout << endl;

	cout << "* 부호가 같고 길이가 다른 경우" << endl;
	cout << "1111 > 12340000 ?\t"; 
	cout << (F > J) << endl;
	cout << "11110000 > 1234 ?\t";
	cout << (inf_int("11110000") > I) << endl;
	cout << "-1111 > -12340000 ?\t";
	cout << (H > K) << endl;
	cout << "-11110000 > -1234? \t" ;
	cout << (inf_int("-11110000") > G) << endl;
	cout << endl;

	cout << "* 부호가 같고 길이가 같은 경우" << endl;
	cout << "1111 > 1234 ?\t";
	cout << (F > I) << endl;
	cout << "1234 > 1111 ?\t";
	cout << (I > F) << endl;
	cout << "-1111 > -1234 ?\t";
	cout << (H > G) << endl;
	cout << "-1234 > -1111 ?\t";
	cout << (G > H) << endl;
	cout << endl;

	cout << "* 숫자가 같은 경우" << endl;
	cout << "1111 > 1111 ?\t";
	cout << (F > F) << endl;
	cout << "-1234 > -1234 ?\t";
	cout << (G > G) << endl;
	cout << "0 > -0 ?\t";
	cout << (X > Y) << endl;
	cout << endl;

	cout << "Check3: operator-" << endl;
	cout << "* 부호가 같고, a의 절댓값이 b보다 큰 경우" << endl;
	cout << "12345678 - 12340000 = " << L - J << endl;
	cout << "-12345678 - (-12340000) = " << M - K << endl;
	cout << endl;

	cout << "* 부호가 같고, a의 절댓값이 b보다 작은 경우" << endl;
	cout << "12340000 - 12345678 = " << J - L << endl;
	cout << "-1234000 - (-12345678) = " << K - M << endl;
	cout << endl;

	cout << "* 부호가 다르고, a의 절댓값이 b보다 큰 경우" << endl;
	cout << "12345678 - (-12340000) = " << L - K << endl;
	cout << "-12345678 - (12340000) = " << M - J << endl;
	cout << endl;

	cout << "* 부호가 다르고, a의 절댓값이 b보다 작은 경우" << endl;
	cout << "12340000 - 12345678 = " << J - L << endl;
	cout << "-1234000 - (-12345678) = " << K - M << endl;
	cout << endl;

	cout << "Check4: operator* " << endl;
	cout << J*J << endl;
	cout << J*K << endl;
	cout << K*J << endl;
	cout << K*K << endl;
	cout << endl;
	cout << J*X << endl;
	cout << Y*X << endl;

	return 0;
}