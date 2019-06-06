#include<iostream>
#include<ctime>
int len(const char * str)
{
	int len = 0;
	while (*str)
	{
		++len;
		++str;
	}
	return len;
}
void copy(const char*read, char*write)
{
	while (*read)
	{
		*write = *read;
		++read;
		++write;
	}
	*write = '\0';
}
char*duplicate(const char* str)
{
	size_t length = len(str);
	if (!str) return (char*)str;
	char*new_str = new(std::nothrow)char[length + 1];
	if (new_str)
		copy(str, new_str);
		return new_str;
}
bool isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A'&& ch <= 'Z');
}
bool isUpperLetter(char ch)
{
	return ch >= 'A'&& ch <= 'Z';
}
char toLowerCase(char* ch)
{
	return (*ch + ('a' - 'A'));
}
char ReadValidlLetter ()
{
	char letter;
	bool enterLoopFirst = false;
	std::cout << "Choose a letter:";
	do
	{
		if (enterLoopFirst)
		{
			std::cout << "Wrong input!\n";
			std::cout << "Choose a letter:";
		}
		std::cin >> letter;
		enterLoopFirst = true;
	} while (!isLetter(letter));
	if (isUpperLetter(letter))
		letter=toLowerCase(&letter);
	return letter;
}
void fillStringWith(char* str, char ch, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		*str = ch;
		++str;
	}
	*str = '\0';
}
void PrintUseLetters(bool arr[],size_t length,char letter)
{
	int index = letter - 'a';
	arr[index] = 1;
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i])
			std::cout << (char)(i + 'a')<<" ";
	}
}
bool checkIsAlreadyEnter(bool arr[], char letter)
{
	int index = letter - 'a';
	if (arr[index] == 1)
		return true;
	return false;
}
bool IswordContainLetter(const char*str, char p)
{
	while (*str)
	{
		if (*str == p)
		{
			return true;
		}
		++str;
	}
	return false;
}
void ReplaceWordWithLetter(const char* str, char* str1,char letter)
{
	while (*str)
	{
		if (*str == letter)
			*str1 = letter;
		++str;
		++str1;
	}
}
void PrintStrWithSpaces(const char* str, size_t length)
{
	for (size_t i = 0; i <length; ++i)
	{
		std::cout << str[i] << " ";
	}
}
int main() {
	srand((size_t)(time(0)));
	const char * Words[] = { "apple" , "orange", "month", "vehicle","generation",
		"valuable","jealous","identification","imagination","warning" };
	const unsigned int WordsCount = 10, cntEnglLett = 27, maxMist = 7;
	int currMist = 0;
	char curLetter = '0';
	bool arr[cntEnglLett] = { 0, };
	bool firstEnter = false;
	int RandWord = rand() % WordsCount;
	size_t size = len(Words[NULL+ RandWord]);
	char*Word = duplicate(Words[NULL + RandWord]);
	if (!Word) {
		std::cout << "Error\n";
		return -1;
	}
	char*EmptyWord = new(std::nothrow)char[size + 1];
	if (!EmptyWord) {
		std::cout << "Error\n";
		return -1;
	}	
	fillStringWith(EmptyWord, '_',size);
	std::cout << "Guess the word (max "<< maxMist<< " mistakes):\n";
	for (int i = 0; i <= maxMist; i++)
	{
		std::cout << "[" << currMist << "/" << maxMist << "]" << " ";
		PrintStrWithSpaces(EmptyWord, size);
		std::cout << "History: ";
		if (firstEnter)
		{
			PrintUseLetters(arr, cntEnglLett, curLetter);
		}
		std::cout << std::endl;
		if (i == maxMist)
		{
			std::cout << "Sorry you did not guess the word!\n";
			std::cout << "The word was " << Word << std::endl;
			break;
		}
		curLetter = ReadValidlLetter();
		while (checkIsAlreadyEnter(arr, curLetter))
		{
			std::cout << "Already enter!Try again!\n";
			curLetter = ReadValidlLetter();
		}
		if (IswordContainLetter(Word, curLetter))
		{
			std::cout << "OK!\n";
			ReplaceWordWithLetter(Word, EmptyWord, curLetter);
			--i;
			if (!IswordContainLetter(EmptyWord, '_'))
			{
				PrintStrWithSpaces(EmptyWord, size);
				std::cout << std::endl;
				std::cout << "Yes!!! You guess he word\n";
				break;
			}
		}
		else
		{
			std::cout << "No such letter!\n";
			++currMist;
		}
		firstEnter=true;
	}
	delete[]Word;
	delete[]EmptyWord;
	system("pause");
	return 0;
}