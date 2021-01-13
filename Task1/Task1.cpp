#include <stdlib.h>
#include <string.h>
#include <iostream>

void StringListInit(char*** list);
void StringListDestroy(char*** list);
void StringListAdd(char** list, char* str);

void StringListInit(char*** list)
{
	*list = (char**)malloc(3 * sizeof(char*));
	**list = nullptr;
}

bool isStringListEmpty(char** list)
{
	if (list != nullptr)
	{
		if (*list != nullptr)
		{
			return false;
		}
	}
	return true;
}

void StringListPrint(char** list)
{
	
	char** tmp = list;
	while (tmp != nullptr)
	{
		if (*tmp != nullptr)
		{
			std::cout << "Output:" << *tmp << "\n";
			tmp = (char**)*(tmp + 1);
		}
		else
		{
			return;
		}
	}
}

void StringListDestroy(char*** list)
{
	char** tmp;
	if (**list != nullptr)
	{
		while (*(*list + 1))
		{
			tmp = (char**)*(*list + 1);
			free(**list);
			free(*list);
			*list = tmp;
		}
		free(**list);
	}
	free(*list);
	list = nullptr;
}


void StringListAdd(char** list, char* str)
{
	char** tmp = list;
	//if (*list == nullptr)
	if(isStringListEmpty(list))
	{
		*list = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy_s(*list, (strlen(str) + 1), str);
		*(list + 1) = nullptr;
		*(list + 2) = nullptr;
	}
	else
	{
		while (*(tmp + 1) != nullptr)
		{
			tmp = (char**)*(tmp + 1);
		}
		char** node = (char**)malloc(3 * sizeof(char*));
		*node = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy_s(*node, strlen(str) + 1, str);
		*(node + 1) = nullptr;
		*(node + 2) = (char*)tmp;
		*(tmp + 1) = (char*)node;
	}
}

void StringListRemove(char*** list, char* str, bool first = false)
{
	if (isStringListEmpty(*list))
	{
		return;
	}
	char** prev;
	char** tmp = *list;
	char** next;
	while (tmp != nullptr )
	{
		if (strcmp(*tmp,str) == 0 && !first)
		{
			if (*(tmp + 1) && *(tmp + 2))
			{
				next = (char**)*(tmp + 1);
				prev = (char**)*(tmp + 2);

				*(prev + 1) = (char*)next;
				*(next + 2) = (char*)prev;
			}
			else if (*(tmp + 1))
			{
				next = (char**)*(tmp + 1);
				prev = nullptr;

				*(next + 2) = nullptr;
				*list = (char**)*(*list + 1);
			}
			else if (*(tmp + 2))
			{
				next = nullptr;
				prev = (char**)*(tmp + 2);

				*(prev + 1) = nullptr;
			}
			else
			{
				free(*tmp);
				**list = nullptr;
				break;
			}

			free(*tmp);
			free(tmp);

			tmp = next;
		}
		else
		{
			if (first && strcmp(*tmp, str) == 0)
			{
				first = false;
			}
			tmp = (char**)*(tmp + 1);
		}
	}
}

int StringListSize(char** list)
{
	char** tmp = list;
	int res = 0;
	while (tmp != nullptr)
	{
		if (*tmp == nullptr)
		{
			break;
		}
		res++;
		tmp = (char**)*(tmp + 1);
	}
	return res;
}


int StringListIndexOf(char** list, char* str)
{
	char** tmp = list;
	int res = 0;
	while (tmp != nullptr)
	{
		if (strcmp(*tmp, str) == 0)
		{
			return res;
		}
		tmp = (char**)*(tmp + 1);
		res++;
	}
	return -1;
}

void StringListRemoveDuplicates(char*** list)
{
	if (isStringListEmpty)
	{
		return;
	}
	char** tmp = *list;
	while (*(tmp + 1) != nullptr)
	{
		StringListRemove(list, *tmp, true);
		tmp = (char**)*(tmp + 1);
		if (tmp == nullptr)
		{
			break;
		}
	}
}

void StringListReplaceInStrings(char** list, char* before, char* after)
{
	if (isStringListEmpty(list) || strcmp(after, before) == 0)
	{
		return;
	}
	char** tmp = list;
	while (tmp != nullptr)
	{
		StringListPrint(list);
		std::cout << "\n\n";
		if (strcmp(*tmp, before) == 0)
		{
			free(*tmp);
			*tmp = (char*)malloc(sizeof(char) * (strlen(after) + 1));
			strcpy_s(*tmp, (strlen(after) + 1), after);
		}
		tmp = (char**)*(tmp + 1);
	}
}

void StringListSort(char** list)
{
	if (isStringListEmpty(list))
	{
		return;
	}
	char** check = list;
	char** comp;
	char* tmp;
	while (check != nullptr)
	{
		comp = (char**)*(check + 1);
		while (comp != nullptr)
		{
			if (strcmp(*check, *comp) > 0)
			{
				tmp = *check;
				*check = *comp;
				*comp = tmp;
			}
			comp = (char**)*(comp + 1);
		}
		check = (char**)*(check + 1);
	}
}


int main()
{
	char*** list = (char***)malloc(sizeof(char**));
	char str1[] = "word1";
	char str2[] = "word2";
	char str3[] = "word3";
	StringListInit(list);
	/*
	StringListAdd(*list, str1);
	StringListAdd(*list, str3);
	StringListAdd(*list, str2);
	StringListAdd(*list, str1);
	StringListAdd(*list, str2);
	StringListAdd(*list, str3);
	*/
	std::cout << isStringListEmpty(*list);
	//StringListPrint(*list);
	//StringListSort(*list);
	StringListRemoveDuplicates(list);
	//std::cout << StringListSize(*list) << "\n\n";
	StringListPrint(*list);
	StringListDestroy(list);
	return 0;
}