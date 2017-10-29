#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "inf_int.h"


using namespace std;

inf_int::inf_int() {
	// 동적 할당
	this->digits = new char[2];

	// 0으로 초기화
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

	// 숫자를 문자열로 변환
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
	int i;   // temp(기존string)의 index 
	int j;   // this->digits의 index (뒤에서부터)

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
	if (strcmp(a.digits, b.digits) == 0 && a.thesign == b.thesign)   // 부호가 같고, 절댓값 일치
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {

	// 절댓값 + > -
	// length 긴거 > 짧은거
	// 큰자리수 더큰 > 작은거
	if (a.thesign == true && b.thesign == true) {      // 둘 다 양수
		if (a.length > b.length)
		for (int i = a.length; i >= 0; i--)
		if (a.digits[i] < b.digits[i])
			return false;
		else
			return false;
	}
	else if (a.thesign == true && b.thesign == false) {   // a는 양수, b는 음수
		return true;
	}
	else if (a.thesign == false && b.thesign == true) {   // a는 음수, b는 양수
		return false;
	}
	else if (a.thesign == false && b.thesign == false) {// 둘 다 음수
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