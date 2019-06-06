#include<iostream>
const short MAX_SIZE = 10;
void ReadArray(int arr[][MAX_SIZE], unsigned int size)
{
	for (unsigned int row = 0; row < size; ++row)
	{
		for (unsigned int colum = 0; colum < size; ++colum)
		{
		std::cin >> arr[row][colum];
		}
	}
}
int findFirstDiagonalSum(int arr[][MAX_SIZE],unsigned int size) 
{
	int sum_first_diagonal=0;
	for (unsigned int row = 0; row < size; ++row)
	{
		sum_first_diagonal += arr[row][row];
	}
	return sum_first_diagonal;
}

int findSecondDiagonalSum(int arr[][MAX_SIZE], unsigned int size)
{
	int sum_second_diagonal = 0;
	for (unsigned int row = 0; row < size; ++row)
	{
		sum_second_diagonal += arr[size - 1 - row][row];
	}
	return sum_second_diagonal;
}
int findFisrtSumRow(int arr[][MAX_SIZE], unsigned int size) {
	int firs_sum_row = 0;
	for (unsigned int row = 0; row < size; row++)
	{
		firs_sum_row += arr[0][row];
	}
	return firs_sum_row;
}
int findFisrtSumColum(int arr[][MAX_SIZE], unsigned int size) {
	int firs_sum_colum = 0;
	for (unsigned int col = 0; col < size; col++)
	{
		firs_sum_colum += arr[col][0];
	}
	return firs_sum_colum;
}
bool CheckEveryRowSumIsSame(int arr[][MAX_SIZE], unsigned int size)
{
	int sum_row = 0;
	int first_sum_row = findFisrtSumRow(arr, size);
	for (unsigned int row = 0; row < size; ++row)
	{
		for (unsigned int colum = 0; colum < size; ++colum)
		{
			sum_row += arr[row][colum];
		}
		if (sum_row != first_sum_row)
		{
			return false;
		}
		sum_row = 0;
	}
	return true;
}
bool CheckEveryColumSumIsSame(int arr[][MAX_SIZE], unsigned int size)
{
	int sum_colum = 0;
	int first_sum_colum = findFisrtSumColum(arr, size);
	for (unsigned int row = 0; row < size; ++row)
	{
		for (unsigned int colum = 0; colum < size; ++colum)
		{
			sum_colum += arr[colum][row];
		}
		if (sum_colum != first_sum_colum)
		{
			return false;
		}
		sum_colum = 0;
	}
	return true;
}
bool IsMagicSquare(int arr[][MAX_SIZE], unsigned int size)
{
	int result1 = findFirstDiagonalSum(arr, size);
	int result2 = findSecondDiagonalSum(arr, size);
	int result3 = findFisrtSumColum(arr, size);
	int result4 = findFisrtSumRow(arr, size);

	bool Result =
		((result1 == result2)&& 
		(result1 == result3) &&
		(result1 == result4) &&
		(result2 == result3) &&
		(result3 == result4) && 
		(result2 == result4));
	bool Result1 = CheckEveryColumSumIsSame(arr, size);
	bool Result2 = CheckEveryRowSumIsSame(arr, size);
	if (Result && Result1 && Result2)
		return true;
	else 
		return false;
}
int main() {
	unsigned short N=0;
	std::cout << "Enter N: ";
	do {
		std::cin >> N;
	} while (N > 10||N==0);
	int matrix[MAX_SIZE][MAX_SIZE];
	std::cout << "Enter table elements: ";
	ReadArray(matrix, N);
	std::cout << ((IsMagicSquare(matrix,N) )? "True" : "False") << std::endl;
	return 0;
}