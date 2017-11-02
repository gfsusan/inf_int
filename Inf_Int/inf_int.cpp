#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "inf_int.h"

using namespace std;

inf_int::inf_int() {
	init();
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// 음수 처리
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// 숫자를 문자열로 변환하는 과정
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {	// 숫자의 절댓값이 0일 경우
		init();
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

	// integer 문자열인지 체크
	char * p;
	strtol(temp.c_str(), &p, 10);

	if (*p != 0 || temp.empty()) {		// 정수 value가 아니거나 temp가 비었을 때
		init();
		return;
	}

	int i;   // temp(기존string)의 index 
	int j;   // this->digits의 index (뒤에서부터)

	if (str[0] == '-') {
		this->thesign = false;
		this->length = temp.length() - 1;
		i = 1;
	}
	else if (str[0] == '+') {
		this->thesign = true;
		this->length = temp.length() - 1;
		i = 1;
	}
	else {
		this->thesign = true;
		this->length = temp.length();
		i = 0;
	}

	this->digits = new char[this->length + 1];

	j = this->length - 1;
	while (str[i] != '\0') {
		this->digits[j] = temp.at(i);
		i++;
		j--;
	}

	this->digits[this->length] = '\0';
	this->simplify();
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

void inf_int::init() {	// initialize to zero
	
	// 동적 할당
	this->digits = new char[2];

	// 0으로 초기화
	this->digits[0] = '0';
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int& inf_int::simplify() {
	unsigned int ctr = 0;

	for (int i = this->length-1; i >= 0; i--) {
		if (this->digits[i] == '0')
			ctr++;
		else break;
	}
	if (ctr == 0)
		return *this;
	else if (ctr == this->length)
		init();
	else {
		this->digits = (char*)realloc(this->digits, this->length - ctr + 1);
		this->length-=ctr;
		this->digits[this->length] = '\0';
	}

	return *this;
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
	if (strcmp(a.digits, b.digits) == 0 && a.thesign == b.thesign)   // 부호가 같고, 절댓값 일치
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {

	// 절댓값 + > -
	// length 긴거 > 같은거 > 짧은거
	// 큰자리수 더큰 > 작은거
	if (a == b)
		return false;

	else if (a.thesign == true && b.thesign == true) {			  // 둘 다 양수
		if (a.length < b.length)
			return false;
		else if (a.length == b.length) {
			for (int i = a.length; i >= 0; i--)
				if (a.digits[i] < b.digits[i])
					return false;
		}
	}
	else if (a.thesign == false && b.thesign == true) {		 // a는 음수, b는 양수
		return false;
	}
	else if (a.thesign == false && b.thesign == false) {	// 둘 다 음수
		if (a.length > b.length)
			return false;
		else if (a.length == b.length) {
			for (int i = a.length; i >= 0; i--)
			if (a.digits[i] > b.digits[i])
				return false;
		}
	}
	return true;										// a는 양수, b는 음수

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

	if (a.thesign == b.thesign){	// 이항의 부호가 같을 경우 + 연산자로 연산
		for (i = 0; i<a.length; i++){
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i<b.length; i++){
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c.simplify();
	}
	else{	// 이항의 부호가 다를 경우 - 연산자로 연산
		c = b;
		c.thesign = a.thesign;

		return (a - c).simplify();
	}
}

inf_int operator-(const inf_int& a, const inf_int&b) {	
	// 절댓값 큰 수에서 작은 수 뺍시다
	inf_int big = a, small = b;

	if (a.thesign == b.thesign){	// 이항의 부호가 같을 경우 - 연산자로 연산
		if (big.Abs() < small.Abs()){
			small = a;
			big = b;
		}
		for (unsigned int i = 0; i<small.length; i++){
			big.Sub(small.digits[i], i + 1);
		}

		return big.simplify();
	}
	else{	// 이항의 부호가 다를 경우 + 연산자로 연산
		small.thesign = a.thesign;	// 여기서 small은 의미없음 temp

		return (a + small).simplify();
	}


}

inf_int operator*(const inf_int& a, const inf_int& b) {
	inf_int c;

	for (unsigned int i = 0; i < b.length; i++) {			// b의 각 자리
		for (unsigned int j = 0; j < a.length; j++) {		// a의 각 자리
			c.Add('0', i + j + 1);
			for (int k = 0; k < b.digits[i]-'0'; k++) {	// b의 j번째 자리 만큼 반복
				c.Add(a.digits[j], j + i + 1);
			}
		}
	}

	// 부호 결정
	c.thesign = a.thesign == b.thesign;

	return c.simplify();
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

void inf_int::Add(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
	if (this->length<index){
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL){		// 할당 실패 예외처리
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// 길이 지정
		this->digits[this->length] = '\0';	// 널문자 삽입
	}

	if (this->digits[index - 1]<'0'){	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// 값 연산


	if (this->digits[index - 1]>'9'){	// 자리올림이 발생할 경우
		this->digits[index - 1] -= 10;	// 현재 자릿수에서 (아스키값) 10을 빼고
		Add('1', index + 1);			// 윗자리에 1을 더한다
	}
}

void inf_int::Sub(const char num, const unsigned int index)	// a의 index 자리수에 n을 뺀다. 0<=n<=9, ex) a가 411일때, Sub(a, 2, 2)의 결과는 391
{
	// (절댓값이) 큰 수에서 작은 수를 빼야한다!
	this->digits[index - 1] -= num - '0';	// 값 연산


	if (this->digits[index - 1]<'0'){	// 자리올림이 발생할 경우
		this->digits[index - 1] += 10;	// 현재 자릿수에서 (아스키값) 10을 더하고
		Sub('1', index + 1);			// 윗자리에 1을 뺀다
	}
}

inf_int inf_int::Abs() const {
	inf_int temp(*this);
	if (temp.thesign == false)
		temp.thesign = true;
	return temp;
}