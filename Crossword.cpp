#include <iostream>
const int MaxWordLen = 40;
int len(const char* str)
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

void clearMemory(char**str, size_t length);
char** ReadWords(size_t size)
{
	char buffer[MaxWordLen + 1];
	char**str = new(std::nothrow)char*[size];
	if (!str)
	{
		std::cout << "No memort\n";
		return str;
	}
	for (size_t i = 0; i < size; i++)
	{
		//getline is better but in this task the input have no space
		std::cin >> buffer;
		int t = len(buffer);
		str[i] = new(std::nothrow) char[t + 1];
		if (!str[i])
		{
			clearMemory(str, i );
			return NULL;
		}
		copy(buffer, str[i]);
	}
	return str;
}
char**ReadCrossWord(size_t n,size_t m)
{
	char**str = new(std::nothrow)char*[n];
	if (!str)
	{
		std::cout << "No memmory\n";
		return str;
	}
	for (size_t i = 0; i < n; i++)
	{
		str[i] = new(std::nothrow)char[m + 1];
		if (!str[i])
		{
			clearMemory(str, i );
			return NULL;
		}
	}
	return str;
}
void Read(char**CrossWord, size_t n, size_t m)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			std::cin >> CrossWord[i][j];
		}
	}
}
void clearMemory(char**str, size_t length)
{
	for (int i = length-1; i >=0 ; i--)
	{
		delete[]str[i];
	}
	delete[]str;
}
//the function search the word from CrosssWord with the input
//todo:optimize to be not so ugly
bool compare(char**str1, const char*text,size_t size)
{
	bool isCorr = false;
	int resize = 0, resize1 = 0;
	while(size)
	{
		while (*text||**str1)
		{
			if (**str1 == *text)
			{
				++resize1;
				++text;
				++*str1;
			}
			else
			{
				isCorr=true;
				break;
			}
		}
		if (!isCorr)
		{
			*str1 -= resize1;//return ptr to the begin
			str1 -= resize;//
			return true;
		}
		else
		{
			--size;
			if (size)
			{
				*str1 -= resize1;//return ptr to the begin
				++str1;
				++resize;
				text -= resize1;
			}
			else
				*str1 -= resize1;//return ptr to the begin
			isCorr = false;
		}
		resize1 = 0;
	}
	str1 -= resize;
	return false;
}
void EmptyArray(char*text, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		text[i] = '\0';
	}
}
bool CroosWordContEveryWords( char**CrossWord, char**Word,size_t size,size_t row,size_t col)
{
	char text[MaxWordLen + 1] = { '\0', };
	int cnt = 0;
	int counter = 0;
	for (size_t i = 0; i < row; i++)
	{
		cnt = 0;
		counter = 0;
		for (size_t j = 0; j < col; j++)
		{
			if (CrossWord[i][j] != '*')
			{
				++cnt;
				text[counter] = CrossWord[i][j];
				++counter;
			}
			else
			{
				if (cnt == 1)
				{
					EmptyArray(text, MaxWordLen + 1);
					cnt = 0;
					counter = 0;
				}
				else
				{
					if (cnt>1 && !compare(Word, text, size))
					{
						return false;
					}
					cnt = 0;
					counter = 0;
					EmptyArray(text, MaxWordLen + 1);
				}
			}
		}
		if (text[1] != '\0')//if we enter here the word is at the end of the row and is longer than 1 char
		{
			if (!compare(Word, text, size))
			{
				return false;
			}
		}
		EmptyArray(text, MaxWordLen + 1);
	}
	return true;
}
bool CroosWordContEveryWordsIn1(char**CrossWord, char**Word, size_t size, size_t row, size_t col)
{
	char text[MaxWordLen + 1] = { '\0', };
	int cnt = 0;
	int counter = 0;
	for (size_t j = 0; j < col; j++)
	{
		cnt = 0;
		counter = 0;
		for (size_t i = 0; i < row; i++)
		{
			if (CrossWord[i][j] != '*')
			{
				++cnt;
				text[counter] = CrossWord[i][j];
				++counter;
			}
			else
			{
				if (cnt == 1)
				{
					EmptyArray(text, MaxWordLen + 1);
					cnt = 0;
					counter = 0;
				}
				else
				{
					if (cnt>1 && !compare(Word, text, size))
					{
						return false;
					}
					cnt = 0;
					counter = 0;
					EmptyArray(text, MaxWordLen + 1);
				}
			}
		}
		if (text[1] != '\0')//if we enter here the word is at the end of the row and is longer than 1 char
		{
			if (!compare(Word, text, size))
			{
				return false;
			}
		}
		EmptyArray(text, MaxWordLen + 1);
	}
	return true;
}
int main()
{
	size_t size;
	std::cin >> size;
	char** Word = ReadWords(size);
	size_t n, m;
	std::cin >> n >> m;
	char**CrossWord = ReadCrossWord(n, m);
	Read(CrossWord,n, m);
	bool res = CroosWordContEveryWords(CrossWord, Word, size, n, m) && 
		CroosWordContEveryWordsIn1(CrossWord, Word, size, n, m);
	std::cout << (res ? "true" : "false") << std::endl;
	clearMemory(Word, size);
	clearMemory(CrossWord, n);
	system("pause");
	return 0;
}
