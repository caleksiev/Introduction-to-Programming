/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2017/2018
*
* @author Tsvetan Alexiev
* @idnumber 45297
* @task 1B
* @compiler VC
*
*/
#include<iostream>
int main() {
	unsigned int number = 0;
	int SequenceOf1 = 0;
	int SequenceOf0 = 0;
	int temp1 = 0;
	int temp2 = 0;
	int change0to1 = 0;
	int change1to0 = 0;
	int digits = 0;
	const short mask = 1;
	std::cin >> number;
	int CopyNumber = number;
	number = CopyNumber;

	for (digits = 0; CopyNumber > 0; CopyNumber >>= 1)//calculate how many digit has a number in binary 
		digits++;

	while (SequenceOf0 + SequenceOf1 <digits)//the loop is break when we read all of the digits of the number
	{
		for (int i = digits-SequenceOf1-SequenceOf0;i>0; i--)//find the sequence of 111..1 end replaced it with 1010...10
		{
			temp1 = number | (mask << (i - 1));
			if (temp1 == number)
			{
				++change1to0;
				++SequenceOf1;
				if (change1to0 % 2 == 0)
				{
					number = number ^ (mask << (i - 1));
				}

			}
			else
				break;
		}
		change1to0 = 0;
		change0to1 = 0;
		temp2 = 0;
		for (int j = digits - SequenceOf1 - SequenceOf0; (temp2 == 0) && (j > 0); j--)//find the sequence of 000..00 end replaced it with 010...101
		{
			temp2 = number & (mask << (j - 1));
			if (temp2 == 0)
			{
				++change0to1;
				++SequenceOf0;
				if (change0to1 % 2 == 0)
				{
					number = number ^ (mask << (j - 1));
				}
			}	
		}
	}
	std::cout << number << std::endl;
	return 0;
}