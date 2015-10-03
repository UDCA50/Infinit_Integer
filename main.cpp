#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int positive_test("-222222222222222222222");
	inf_int negative_test("-111111111111111111111");
	inf_int zero_test(0);
	
	zero_test = positive_test * negative_test;

	std::cout << zero_test;
	system("pause");
	return 0; 
}
