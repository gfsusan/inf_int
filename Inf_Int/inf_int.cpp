#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "inf_int.h"


using namespace std;

inf_int::inf_int() {
	// ���� �Ҵ�
	this->digits = new char[2];

	// 0���� �ʱ�ȭ
	this->digits[0] = '0';
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n){
	char buf[100];

	if(n<0){		// ���� ó��
		this->thesign=false;
		n=-n;
	}else{
		this->thesign=true;
	}

	int i=0;
	while(n>0){			// ���ڸ� ���ڿ��� ��ȯ�ϴ� ����
		buf[i]=n%10+'0';

		n/=10;
		i++;
	}

	if(i==0){	// ������ ������ 0�� ���
		new (this) inf_int();	// ������ ��ȣ��...gcc���� �����Ͽ����� �ִٰ� ��. inf_int()�� ��� ������ �ν��Ͻ��� ������. 
	}else{
		buf[i]='\0';

		this->digits=new char[i+1];
		this->length=i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(const char* str) {
	string temp = str;
	int i;   // temp(����string)�� index 
	int j;   // this->digits�� index (�ڿ�������)

	if (str[0] == '-') {
		this->thesign = false;
		this->length = temp.length() - 1;
		i = 1;
	}
	else {
		this->thesign = true;
		this->length = temp.length();
		i = 0;
	}

	j = this->length - 1;
	this->digits = new char[this->length + 1];

	while (str[i] != '\0') {
		this->digits[j] = temp.at(i);
		i++;
		j--;
	}
	this->digits[this->length] = '\0';
	cout << temp << endl;
}

inf_int::inf_int(const inf_int& a) {
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() {
	delete digits;
}

inf_int& inf_int::operator=(const inf_int& a) {
	if (this->digits)
		delete digits;

	this->digits = new char[a.length + 1];
	this->length = a.length;
	this->thesign = a.thesign;

	strcpy(this->digits, a.digits);

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
	if (strcmp(a.digits, b.digits) == 0 && a.thesign == b.thesign)   // ��ȣ�� ����, ���� ��ġ
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {

	// ���� + > -
	// length ��� > ������ > ª����
	// ū�ڸ��� ��ū > ������
	if (a == b)
		return false;

	else if (a.thesign == true && b.thesign == true) {			  // �� �� ���
		if (a.length < b.length)
			return false;
		else if (a.length == b.length) {
			for (int i = a.length; i >= 0; i--)
				if (a.digits[i] < b.digits[i])
					return false;
		}
		else
			return true;
	}
	else if (a.thesign == false && b.thesign == true) {		 // a�� ����, b�� ���
		return false;
	}
	else if (a.thesign == false && b.thesign == false) {	// �� �� ����
		if (a.length > b.length)
			return false;
		else if (a.length == b.length) {
			for (int i = a.length; i >= 0; i--)
			if (a.digits[i] > b.digits[i])
				return false;
		}
		else {
			return true;
		}
	}
	else													// a�� ���, b�� ����
		return true;

}

bool operator<(const inf_int& a, const inf_int& b) {

	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
	return true;
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign){	// ������ ��ȣ�� ���� ��� + �����ڷ� ����
		for (i = 0; i<a.length; i++){
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i<b.length; i++){
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else{	// ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int&b) {	
	// ���� ū ������ ���� �� ���ٰ� ����
	inf_int big = a, small = b;

	if (a.thesign == b.thesign){	// ������ ��ȣ�� ���� ��� - �����ڷ� ����
		if (big.Abs() < small.Abs()){
			small = a;
			big = b;
		}
		for (int i = 0; i<small.length; i++){
			big.Sub(small.digits[i], i + 1);
		}

		return big;
	}
	else{	// ������ ��ȣ�� �ٸ� ��� + �����ڷ� ����
		small.thesign = a.thesign;	// ���⼭ small�� �ǹ̾��� temp

		return a + small;
	}
}

inf_int operator*(const inf_int& a, const inf_int& b) {
	inf_int c;

	

	return a;
}

ostream& operator<<(ostream& out, const inf_int& a) {
	int i;

	if (a.thesign == false)
		out << '-';

	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}


void inf_int::Add(const char num, const unsigned int index)	// a�� index �ڸ����� n�� ���Ѵ�. 0<=n<=9, ex) a�� 391�϶�, Add(a, 2, 2)�� ����� 411
{
	if (this->length<index){
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL){		// �Ҵ� ���� ����ó��
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// ���� ����
		this->digits[this->length] = '\0';	// �ι��� ����
	}

	if (this->digits[index - 1]<'0'){	// ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// �� ����


	if (this->digits[index - 1]>'9'){	// �ڸ��ø��� �߻��� ���
		this->digits[index - 1] -= 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ����
		Add('1', index + 1);			// ���ڸ��� 1�� ���Ѵ�
	}
}

void inf_int::Sub(const char num, const unsigned int index)	// a�� index �ڸ����� n�� ����. 0<=n<=9, ex) a�� 411�϶�, Sub(a, 2, 2)�� ����� 391
{
	this->digits[index - 1] -= num - '0';	// �� ����


	if (this->digits[index - 1]<'0'){	// �ڸ��ø��� �߻��� ���
		this->digits[index - 1] += 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ���ϰ�
		Sub('1', index + 1);			// ���ڸ��� 1�� ����
	}
}

inf_int inf_int::Abs(){
	inf_int temp(*this);
	if (temp.thesign == false)
		temp.thesign = true;
	return temp;
}

