#include<iostream>
const short MAX_DIGIT = 20;
void set(char*str, char sym, size_t pos)
{
	if (str)
	{
		str[pos] = sym;
	}
}char*GetStr1(size_t level)
{
	char symbol = std::cin.get();
	if (symbol == '\n')
	{
		char*res = new(std::nothrow)char[level + 1];
		set(res, '\0', level);
		return res;
	}
	char*res = GetStr1(level + 1);
	set(res, symbol, level);
	return res;
}
char* GetStr()
{
	return GetStr1(0);
}

size_t len(const char*str)
{
	if (!*str) return 0;
	return 1+ len(str + 1);
}
size_t Pow(size_t num, size_t deg)
{
	if (deg == 0)return 1;
		return num*Pow(num, deg - 1);
}
size_t FromStrToInt(const char*str)
{
	if (!*str)return 0;
	return (*str - '0')*Pow(10, len(str) - 1) + FromStrToInt(str + 1);
}
bool isDigit(char sym)
{
	return (sym >= '0' && sym <= '9');
}
bool isLetter(char s)
{
	return (s >= 'A' && s <= 'Z');
}
void FillArray(char*str, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		str[i] = '\0';
	}
}

char*Compressed(const char*str, size_t size, char*temp, size_t how)
{
	if (!*str)
	{
		char*res = new(std::nothrow)char[size + 1];
		set(res, '\0', size);
		return res;
	}
	if (isLetter(*str))
	{
			char*res = Compressed(str + 1, size + 1, temp, how);
			set(res, *str, size);
			return res;	
	}
	if (isDigit(*str))
	{
		size_t pos = 0;
		while (isDigit(*str))
		{
			temp[pos] = *str;
			++pos;
			++str;
		}
		how = FromStrToInt(temp);
		FillArray(temp, MAX_DIGIT);
		char*res = Compressed(str , size, temp, how);
		return res;
	}
	if (*str == '(')
	{
		char*res = Compressed(str + 1, size, temp, --how);
		return res;
	}
	if (*str == ')')
	{
		if (how)
		{
			while (*str !='(')
			{
				--str;
			}
			char*res = Compressed(str , size, temp, how);
			return res;
		}
		else 
		{
			char*res = Compressed(str+1, size, temp, how);
			return res;
		}
		
	}
	return NULL;
}

char*Result(const char*str)
{
	char temp[MAX_DIGIT];
	FillArray(temp, MAX_DIGIT);
	return Compressed(str, 0, temp,0);
}

int main()
{
	char*input = GetStr();
	char*res = Result(input);
	std::cout << res<<std::endl;
	delete[]res;
	delete[]input;
	system("pause");
	return 0;
}