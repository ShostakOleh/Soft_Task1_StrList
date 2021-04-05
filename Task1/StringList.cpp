#include "StringList.h"

#define MAX_STR       30
#define NEXT         + 1
#define PREV         + 2

void StringListInit(char*** list)
{
	if (list != nullptr)
	{
		*list = (char**)malloc(3 * sizeof(char*));
		**list = nullptr;
	}
}

bool isStringListEmpty(char*** list)
{
	return list == nullptr || *list == nullptr || **list == nullptr;
}

void StringListPrint(char*** list)
{

	char** tmp = *list;
	while (tmp != nullptr && *tmp != nullptr)
	{
		printf("Value: %s\n", *tmp);
		tmp = (char**)*(tmp NEXT);
	}
}

void StringListDestroy(char*** list)
{
	char** tmp;
	if (**list != nullptr)
	{
		//Destroys list from HEAD to TAIL
		while (*(*list NEXT))
		{
			tmp = (char**)*(*list NEXT);
			free(**list);
			free(*list);
			*list = tmp;
		}
		free(**list);
	}
	free(*list);
	list = nullptr;
}


void StringListAdd(char*** list, char* str)
{
	char** tmp = *list;
	//Adds first element
	if (isStringListEmpty(list))
	{
		**list = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy_s(**list, (strlen(str) + 1), str);
		*((*list) NEXT) = nullptr;
		*((*list) PREV) = nullptr;
	}
	//Adds other elements
	else
	{
		//Searches last node
		while (*(tmp NEXT) != nullptr)
		{
			tmp = (char**)*(tmp NEXT);
		}
		char** node = (char**)malloc(3 * sizeof(char*));
		*node = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy_s(*node, strlen(str) + 1, str);
		*(node NEXT) = nullptr;
		*(node PREV) = (char*)tmp;
		*(tmp NEXT) = (char*)node;
	}
}

void StringListSwitchBetween(char** tmp, char** next, char** prev)
{
	next = (char**)*(tmp NEXT);
	prev = (char**)*(tmp PREV);
	*(prev NEXT) = (char*)next;
	*(next PREV) = (char*)prev;
}

void StringListSwitchLast(char** tmp, char** next, char** prev, char*** list)
{
	next = (char**)*(tmp NEXT);
	prev = nullptr;
	*(next PREV) = nullptr;
	*list = (char**)*(*list NEXT);
}

void StringListSwitchFirst(char** tmp, char** next, char** prev)
{
	next = nullptr;
	prev = (char**)*(tmp PREV);
	*(prev NEXT) = nullptr;
}

void StringListSwitch(char** tmp, char** next, char** prev, char*** list)
{
	if (*(tmp NEXT) && *(tmp PREV))
	{
		StringListSwitchBetween(tmp, next, prev);
	}
	else if (*(tmp NEXT))
	{
		StringListSwitchLast(tmp, next, prev, list);
	}
	else if (*(tmp PREV))
	{
		StringListSwitchFirst(tmp, next, prev);
	}
}

bool StringListFirstWord(char** tmp, char* str, const bool first)
{
	bool result = first;
	if (first && strcmp(*tmp, str) == 0)
	{
		result = false;
	}
	return result;
}

void StringListRemove(char*** list, char* str, bool first)
{
	if (isStringListEmpty(list))
	{
		return;
	}
	char** prev = nullptr;
	char** tmp = *list;
	char** next = nullptr;
	while (tmp != nullptr)
	{
		if (strcmp(*tmp, str) == 0 && !first)
		{
			if (*(tmp NEXT) || *(tmp PREV))
			{
				StringListSwitch(tmp, next, prev, list);
			}
			//Calls when list has only node with str
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
			first = StringListFirstWord(tmp, str, first);
			tmp = (char**)*(tmp NEXT);
		}
	}
}

int StringListSize(char*** list)
{
	char** tmp = *list;
	int result = 0;
	while (tmp != nullptr && *tmp != nullptr)
	{
		result++;
		tmp = (char**)*(tmp NEXT);
	}
	return result;
}


int StringListIndexOf(char*** list, char* str)
{
	if (!isStringListEmpty(list))
	{
		char** tmp = *list;
		int result = 0;
		while (tmp != nullptr)
		{
			if (strcmp(*tmp, str) == 0)
			{
				return result;
			}
			tmp = (char**)*(tmp NEXT);
			result++;
		}
	}
	return -1;
}

void StringListRemoveDuplicates(char*** list)
{
	if (isStringListEmpty(list))
	{
		return;
	}
	char** tmp = *list;
	while (*(tmp NEXT) != nullptr)
	{
		StringListRemove(list, *tmp, true);
		tmp = (char**)*(tmp NEXT);
		if (tmp == nullptr)
		{
			break;
		}
	}
}

void StringListReplaceInStrings(char*** list, char* before, char* after)
{
	if (isStringListEmpty(list) || strcmp(after, before) == 0)
	{
		return;
	}
	char** tmp = *list;
	while (tmp != nullptr)
	{
		if (strcmp(*tmp, before) == 0)
		{
			free(*tmp);
			*tmp = (char*)malloc(sizeof(char) * (strlen(after) + 1));
			strcpy_s(*tmp, (strlen(after) + 1), after);
		}
		tmp = (char**)*(tmp NEXT);
	}
}

void StringListSort(char*** list)
{
	if (isStringListEmpty(list))
	{
		return;
	}
	char** check = *list;
	char** comp;
	char* tmp;
	while (check != nullptr)
	{
		comp = (char**)*(check NEXT);
		while (comp != nullptr)
		{
			if (strcmp(*check, *comp) > 0)
			{
				tmp = *check;
				*check = *comp;
				*comp = tmp;
			}
			comp = (char**)*(comp NEXT);
		}
		check = (char**)*(check NEXT);
	}
}

void StringListCommandList()
{
	printf("a - add string\nd - remove duplicates\nl - command list\ns - sort\np - print list\nr - remove string\nf - replace \"before\" with \"after\"\ni - get index\ne - exit\n");
}

void StringListUI()
{
	char*** list = (char***)malloc(sizeof(char**));
	char str1[MAX_STR];
	char str2[MAX_STR];
	char state;
	bool exit = false;
	StringListInit(list);
	StringListCommandList();
	while (!exit)
	{
		printf("Input operation: ");
		scanf_s(" %c", &state, 1);
		getchar();
		switch (state)
		{
		case 'a':
		{
			printf("Input word to add: ");
			if (scanf_s("%s", &str1, MAX_STR) != -1)
			{
				StringListAdd(list, str1);
			}
			else
			{
				printf("ERROR:Empty input, operation cancelled.");
			}
		}
		break;
		case 'd':
		{
			StringListRemoveDuplicates(list);
		}
		break;
		case 'l':
		{
			StringListCommandList();
		}
		break;
		case 's':
		{
			StringListSort(list);
		}
		break;
		case 'p':
		{
			StringListPrint(list);
		}
		break;
		case 'e':
		{
			exit = true;
		}
		break;
		case 'r':
		{
			printf("Input word to remove: ");
			if (scanf_s("%s", &str1, MAX_STR) != -1)
			{
				StringListRemove(list, str1);
			}
			else
			{
				printf("ERROR:Empty input, operation cancelled.");
			}
		}
		break;
		case 'f':
		{
			printf("Input word for \"before\": ");
			if (scanf_s("%s", &str1, MAX_STR) != -1)
			{
				printf("Input word for \"after\": ");
				if (scanf_s("%s", &str2, MAX_STR) != -1)
				{
					StringListReplaceInStrings(list, str1, str2);
					break;
				}
			}
			printf("ERROR:Empty input, operation cancelled.");
		}
		break;
		case 'i':
		{
			printf("Input word to get index: ");
			if (scanf_s("%s", &str1, MAX_STR) != -1)
			{
				printf("%i\n", StringListIndexOf(list, str1));
			}
			else
			{
				printf("ERROR:Empty input, operation cancelled.");
			}
		}
		break;
		default:
			break;
		}
	}
	StringListDestroy(list);
}
