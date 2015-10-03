#include "inf_int.h"



inf_int::inf_int() {

	this->digits = new char[2];
	this->digits[0] = '0';
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int inputValue) {
	
if (inputValue < 0) {
	this->thesign = false;
	inputValue = -inputValue;
}
else{
	this->thesign = true;
}

char tempDig[100];
unsigned int iter = 0;
while (inputValue > 0) {

	tempDig[iter] = inputValue % 10 + 48;
	inputValue = inputValue / 10;
	iter++;
}
if (iter == 0) {
	new (this) inf_int();
	//생성자로 호출
}
else{
	tempDig[iter] = '\0';
	this->length = iter;
	this->digits = new char[iter + 1];
	strcpy(this->digits, tempDig);
}
}

inf_int::inf_int(const char* inputstring){
	unsigned int negCheck = 0;

	//길이
	this->length = strlen(inputstring);

	//부호
	if (inputstring[0] == '-') {
		this->thesign = false;
		length = length - 1;
	}
	else {
		this->thesign = true;
		negCheck++;

	}

	//자리(digit)
	this->digits = new char[length + 1];
	digits[length] = '\0';
	for (unsigned int i = 0; i < length; i++) {
		digits[i] = inputstring[length - (i + negCheck)];
	}

}
inf_int::inf_int(const inf_int& copyInstace){

	this->digits = new char[copyInstace.length + 1];

	strcpy(this->digits, copyInstace.digits);
	this->length = copyInstace.length;
	this->thesign = copyInstace.thesign;

}
inf_int::~inf_int(){
	delete digits;
}


void inf_int::checkInstance(inf_int &checkValue) {
	printf("digits : %s\n length : %u \n the sign : %s\n", checkValue.digits,
		checkValue.length, checkValue.thesign ? "true" : "false");
}
inf_int& inf_int::operator=(const inf_int& inputInstance){

	if (this->digits) {
		delete this->digits;
	}

	this->digits = new char[inputInstance.length + 1];
	strcpy(this->digits, inputInstance.digits);
	this->length = inputInstance.length;
	this->thesign = inputInstance.thesign;

	return *this;
}

bool operator==(const inf_int& left, const inf_int& right){

	if ((strcmp(left.digits, right.digits) == 0) && left.thesign == right.thesign) {
		return true;
	}
	return false;
}
bool operator!=(const inf_int& left, const inf_int& right){
	return !operator==(left, right);
}
bool operator>(const inf_int& left, const inf_int& right){

	if (operator<(left, right) || operator==(left, right) ) {
		return false;
	}
	else {
		return true;
	}
 }
 bool operator<(const inf_int& left, const inf_int& right){

	 //부호가 같을경우
	 if (left.thesign == right.thesign) {

		 //posit_set
		 if (left.thesign == true) {
			 
			 if (left.length == right.length) {
				 unsigned int iter = left.length;
				 while (iter>0) {
					 if (left.digits[iter] == right.digits[iter]) {
						 iter--;
						 continue; 
					 }
					 else if (left.digits[iter] < right.digits[iter]) {
						 return true;
					 }
					 else {
						 return false;
					 }
				 }
				 return false;
			 }
		 
			else if (left.length < right.length){
				 return true;
			 }
			else {
				return false;
			}
		 }
		 //negtive_set
		 else {

			 if (left.length == right.length) {
				 unsigned int iter = left.length;
				 while (iter>0) {
					 if (left.digits[iter] == right.digits[iter]) {
						iter--;
						continue; 
					 }
					 else if (left.digits[iter] < right.digits[iter]) {
						 return false;
					 }
					 else {
						 return true;
					 }
					 iter--;
				 }
				 return false;
			 }

			 else if (left.length < right.length){
				 return false;
			 }
			 else {
				 return true;
			 }

		 }
	 }

	 //부호가 다를경우
	 else{

		 if (right.thesign == true) {
			 return true;
		 }

		 else {
			 return false;
		 }

	 }
 }

 void inf_int::Add(const char num, const unsigned int index){
	 if (this->length < index) {
		 this->digits = (char*)realloc(this->digits, index + 1);

		 if (this->digits == NULL) {
			 std::cout << "Memory alloc Fail" << std::endl;
			 exit(0);
		 }
		 this->length = index;
		 this->digits[this->length] = '\0';

	 }

	 if (this->digits[index - 1] < '0') {
		 this->digits[index - 1] = '0';
	 }

	 this->digits[index - 1] += num - '0';

	 if (this->digits[index - 1] > '9') {
		 this->digits[index - 1] -= 10;
		 Add('1', index + 1);
	 }
 }

 void inf_int::Sub(const char num, const unsigned int index){

	 if (this->length < index) {
		 this->digits = (char*)realloc(this->digits, index + 1);

		 if (this->digits == NULL) {
			 std::cout << "Memory alloc Fail" << std::endl;
			 exit(0);
		 }
		 this->length = index;
		 this->digits[this->length] = '\0';

	 }
		 this->digits[index - 1] -= num - '0';

		 if (this->digits[index - 1] < '0') {
			 this->digits[index - 1] += 10;
			 Sub('1', index + 1);
		 }

	 }


 inf_int operator+(const inf_int& left, const inf_int& right){

	 inf_int sumNum;
	 unsigned int iter;

	 //부호가 같을경우
	 if (left.thesign == right.thesign) {
		 for (iter = 0; iter < left.length; iter++){
			 sumNum.Add(left.digits[iter], iter + 1);
		 }
		 for (iter = 0; iter < right.length; iter++){
			 sumNum.Add(right.digits[iter], iter + 1);
		 }

		 sumNum.thesign = left.thesign;
		 return sumNum;
	 }

	 //부호가 다를경우
	 else{
		 if (right.thesign == true) {
			 sumNum = left;
			 sumNum.thesign = true;

			 return right - sumNum;
		 }
		 else {
			 sumNum = right;
			 sumNum.thesign = true;

			 return left - sumNum;
		 }
	 }

 }
 inf_int operator-(const inf_int& left, const inf_int& right){
	
	 inf_int subNum;
	 unsigned int iter;

	 //부호가 같을 경우 
	 if (left.thesign == right.thesign) {
		 //누가 큰지 비교한다. 

		 //두 숫자의 길이가 같을경우
		 if (left.length == right.length){
			 unsigned int iter = left.length;
			 while (iter>0) {
				 if (left.digits[iter-1] == right.digits[iter-1]) {
					 iter--;
					 continue;
				 }
				 else if (left.digits[iter-1] < right.digits[iter-1]) {
					 subNum = right;	//오른쪽값을 subNum 에 넣는다
					 if (subNum.thesign == true) {
						 subNum.thesign = false;
					 }
					 else {
						 subNum.thesign = true;
					 }
					 for (int i = 0; i < left.length; i++) {
						 subNum.Sub(left.digits[i], i + 1);
					 }
					 return subNum;
				 }
				 else {
					 subNum = left;		//왼쪽값을 subNum 에 넣는다
					 if (subNum.thesign == true) {
						 subNum.thesign = true;
					 }
					 else {
						 subNum.thesign = false;
					 }
					 
					 
					 for (int i = 0; i < right.length; i++) {
						 subNum.Sub(right.digits[i], i + 1);
					 }
					 return subNum;
				 }
			 }
			 return subNum;	// 두 값이 같은경우
		 }
		 // 오른쪽의 길이가 길 경우 
		 else if (left.length < right.length){
			 subNum = right;
			 if (subNum.thesign == true) {
				 subNum.thesign = false;
			 }
			 else {
				 subNum.thesign = true;
			 }
			 for (int i = 0; i < left.length; i++) {
				 subNum.Sub(left.digits[i], i + 1);
			 }
			 return subNum;

		 }

		 // 왼쪽의 길이가 길 경우 
		 else  {
			 subNum = left;
			 if (subNum.thesign == true) {
				 subNum.thesign = true;
			 }
			 else {
				 subNum.thesign = false;
			 }
			 for (int i = 0; i < right.length; i++) {
				 subNum.Sub(right.digits[i], i + 1);
			 }
			 return subNum;
		 }
	 }
	 //부호가 다른경우 (실질적으로 더하기 연산)
	 else {

		 subNum = right;

		 if (subNum.thesign == false) {
			 subNum.thesign = false;
		 }
		 else {
			 subNum.thesign = true;
		 }
		 subNum = subNum+left;

		 return subNum;
	 }

 }
 inf_int operator+(const inf_int& leftInst, int rightInt){
	 inf_int InputInst(rightInt);

	 return leftInst + InputInst;
 }


 inf_int operator*(const inf_int& left, const inf_int& right){
	 inf_int counter;
	 inf_int mulNum;
	 //양수
	 if (left.thesign == right.thesign) {

		 while (strcmp(counter.digits, left.digits) != 0) {
			 mulNum = mulNum + right;
			 counter = counter + 1;
		 }
		 mulNum.thesign = true;
		 return mulNum;
	 }

	 //음수
	 else {
		 while (strcmp(counter.digits, left.digits) != 0) {
			 mulNum = mulNum + right;
			 counter = counter + 1;
		 }
		 mulNum.thesign = false;
		 return mulNum;
	 }
 }


 std::ostream& operator<<(std::ostream& out, const inf_int& inst) {
	 int iter; 

	 if (inst.thesign == false) {
		 out << '-';
	 }
	 for (int i = inst.length - 1; i >= 0; i--) {
		 out << inst.digits[i];
	 }
	 return out;
 }