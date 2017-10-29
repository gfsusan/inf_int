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

inf_int::inf_int(int n) {
	char buf[100];
	int i = 0;

	if (n < 0) {
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	// ���ڸ� ���ڿ��� ��ȯ
	while (n > 0) {
		buf[i] = n % 10 + '0';
		n /= 10;
		i++;
	}

	if (i == 0) {
		new (this) inf_int();
	}
	else {
		buf[i] = '\0';
		this->digits = new char[i + 1];
		this->length = i;
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
		j = this->length;
	}
	else {
		this->thesign = true;
		this->length = temp.length();
		i = 0;
		j = this->length - 1;
	}

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
	//if(this->digits)
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
	// length ��� > ª����
	// ū�ڸ��� ��ū > ������
	if (a.thesign == true && b.thesign == true) {      // �� �� ���
		if (a.length > b.length)
		for (int i = a.length; i >= 0; i--)
		if (a.digits[i] < b.digits[i])
			return false;
		else
			return false;
	}
	else if (a.thesign == true && b.thesign == false) {   // a�� ���, b�� ����
		return true;
	}
	else if (a.thesign == false && b.thesign == true) {   // a�� ����, b�� ���
		return false;
	}
	else if (a.thesign == false && b.thesign == false) {// �� �� ����
		if (a.length < b.length) {
			for (int i = a.length; i >= 0; i--)
			if (a.digits[i] > b.digits[i])
				return true;
		}
		else {
			return false;
		}
	}
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

inf_int operator+(const inf_int&a, const inf_int& b) {

	inf_int result;

	//
	return result;
}

inf_int operator-(const inf_int& a, const inf_int&b) {

	//
	return a;
}

inf_int operator*(const inf_int& a, const inf_int& b) {

	//
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