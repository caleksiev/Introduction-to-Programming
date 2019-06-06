#include<iostream>
#include<ctime>
int len(const char*str)
{
	int length = 0;
	while (*str)
	{
		++length;
		++str;
	}
	return length;
}
int lenObjSbj(const char*str)
{
	int length = 0;
	while (*str)
	{
		if (*str != '_')
			++length;
		++str;
	}
	return length;
}
bool isWordObj(const char*str)
{
	size_t length = len(str);
	if (str[0] == '_'&&str[length] == '_')
		return true;
	if (str[0] == '_')
		return true;
	return false;
}
bool isWordSbj(const char*str)
{
	size_t length = len(str);
	if (str[0] == '_'&&str[length] == '_')
		return true;
	if (str[length] == '_')
		return true;
	return false;
}
//todo: optimize to work with more words(strcopy then strcat)
//in this case work only for the task(With 4 words)
void copy(size_t cntExcl , const char*str1, const char*str2, const char*str3,const char*str4, char*newstr)
{
	while (*str1)
	{
		*newstr = *str1;
		++newstr;
		++str1;
	}
	while (cntExcl)
	{
		*newstr = '!';
		--cntExcl;
		++newstr;
	}
	*newstr = ' ';
	++newstr;
	while (*str2)
	{
		if (*str2 != '_')
		{
			*newstr = *str2;
			++newstr;
		}
		++str2;
	}
	*newstr = ' ';
	++newstr;
	while (*str3)
	{
		*newstr = *str3;
		++newstr;
		++str3;
	}
	*newstr = ' ';
	++newstr;
	while (*str4)
	{
		if (*str4 != '_')
		{
			*newstr = *str4;
			++newstr;
		}
		++str4;
	}
	*newstr = '\0';
}
int main() {
	srand((size_t)time(NULL));
	const char*exclamation[] = { "SHOCK","Nechuvana naglost","Skandal","Neveroqtno","Izumotelno","POTRES",
		"Izvunredna glezotiq","MALEI","EBASI","Stranna neizkazanost" };
	const unsigned int ExclCount = 10;
	//strins with "_" at the beginning and at the end can be SbjObj,
	//only at the beginnig are Sbj and only at the end are Obj
	//в последствие разбрах, че може да ги запишем и в отделни масиви,но тъй като в условието 
	//пише че тр€бва да намери начин да ги различаваме 3-те категорий го оставих така
	const char*objectSubjec[] = { "_Rqpa_","_Baba_","_Kmet_","_Sklad","_Bager_","Pesho_","_Muha_",
		"Morkov_","_Chiniq","_Pantalon" };
	const unsigned int ObjSbjCount = 10;

	const char*action[] = { "sgazi","zadiga","namiga na","pretsakva","tarashi",
		"ubiva","se jeni za","rajda","otlita s","poluchava"};
	const unsigned int ActCount = 10;

	std::cout << "Enter number of heading:";
	size_t cntHead;
	std::cin >> cntHead;
	const size_t spaceAfterWord = 3, minExc = 3, maxExc = 10;
	size_t RandExcCnt, RandWordExc, RandWordObj, RandWordSbj, RandWordAct;
	size_t ExcLength, ActLen, ObJLen,SbjLen;
	size_t sumLengths;
	char*str;
	for (size_t i = 0; i < cntHead; i++)
	{
		RandExcCnt = (rand() % (maxExc - minExc+1)) + minExc;//[3;10]
		RandWordExc = rand() % ExclCount;//index:[0;ExclCount]
		RandWordObj = rand() % ObjSbjCount;//index:[0;ObjSbjCount]
		RandWordSbj = rand() % ObjSbjCount;//index:[0;ObjSbjCount]
		RandWordAct = rand() % ActCount;//index:[0;ActCount]
		ExcLength = len(exclamation[NULL + RandWordExc]);
		ActLen = len(action[NULL + RandWordAct]);
		while (!isWordObj(objectSubjec[NULL + RandWordObj]))
		{
			RandWordObj = rand() % ObjSbjCount;
		}
		ObJLen = lenObjSbj(objectSubjec[NULL + RandWordObj]);
		while ((!isWordSbj(objectSubjec[NULL + RandWordSbj]))&&(RandWordObj==RandWordSbj))
		{
			RandWordSbj = rand() % ObjSbjCount;
		}
		SbjLen = lenObjSbj(objectSubjec[NULL + RandWordSbj]);
		sumLengths = ExcLength + ActLen + ObJLen + SbjLen + spaceAfterWord + RandExcCnt;
		str = new(std::nothrow)char[sumLengths + 1];
		if (!str)
		{
			delete[]str;
			std::cout << "No memmory\n";
			return 1;
		}
		copy(RandExcCnt, exclamation[NULL + RandWordExc], objectSubjec[NULL + RandWordSbj], 
			action[NULL + RandWordAct], objectSubjec[NULL + RandWordObj], str);
		std::cout << str << std::endl;
		delete[]str;
	}
	system("pause");
	return 0;
}