/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2017/2018
*
* @author Tsvetan Alexiev
* @idnumber 45297
* @task 1A
* @compiler VC
*
*/

#include<iostream>
int main() {
	unsigned int N;
	int NumberRow1 = 0;
	int NumberRow2 = 0;
	int NumberRow3 = 0;
	int if_is_trion = 0;
	std::cin >> N;
	if (N == 0)
		std::cout << "yes" << std::endl;
	else if (N == 1)
	{
		int NumberRow1;
		std::cin >> NumberRow1;
		std::cout << "yes" << std::endl;
	}
	else if (N == 2)
	{
		int NumberRow1, NumberRow2;
		std::cin >> NumberRow1 >> NumberRow2;
		std::cout << "yes" << std::endl;
	}
	else
	{
		for (int i = 1; i <= N; i++)
		{
		
			NumberRow1 = NumberRow2;
			NumberRow2 = NumberRow3;
			std::cin >> NumberRow3;
			if (i >=3)//chech after we enter 3 number from the row
			{
				bool result = (((NumberRow2 >= NumberRow1) && (NumberRow2 >= NumberRow3)) || ((NumberRow2 <= NumberRow1) && (NumberRow2 <= NumberRow3)));
				if (!result) 
				{
					++if_is_trion;

				}
			}	
		}
		std::cout << ((if_is_trion) ? "no" : "yes") << std::endl;
	}
	return 0;
}