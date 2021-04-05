#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*Initializes list.*/
void StringListInit(char*** list);
/**/
bool isStringListEmpty(char*** list);
/**/
void StringListPrint(char*** list);
/*Destroy list and set pointer to nullptr.*/
void StringListDestroy(char*** list);
/*Inserts value at the end of the list.*/
void StringListAdd(char*** list, char* str);
/*Removes all occurrences of str in the list,except first if boolean true.*/
void StringListRemove(char*** list, char* str, bool first = false);
/*Returns the number of items in the list.*/
int StringListSize(char*** list);
/*Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(char*** list, char* str);
/*Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char*** list);
/*Replaces every occurrence of the before, in each of the string lists's strings, with after.*/
void StringListReplaceInStrings(char*** list, char* before, char* after);
/*Sorts the list of strings in ascending order.*/
void StringListSort(char*** list);

/*Removes node when between two nodes.*/
void StringListSwitchBetween(char** tmp, char** next, char** prev);
/*Removes node when it is last node.*/
void StringListSwitchLast(char** tmp, char** next, char** prev, char*** list);
/*Removes node when it is first node.*/
void StringListSwitchFirst(char** tmp, char** next, char** prev);
/*Detects node state (first,between,last) and calls switch function for it.*/
void StringListSwitch(char** tmp, char** next, char** prev, char*** list);
/*Looks for first occurence of str.*/
bool StringListFirstWord(char** tmp, char* str, bool first);
/*Prints commands list for UI.*/
void StringListCommandList();
/*Starts UI.*/
void StringListUI();