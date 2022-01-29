#pragma once

#define MAX_WORD_LENGHT 80

int StrCmp(char *Str1, char *Str2);
char *GetSubstrUntilChar(char *Str, char character, int *SubstrLenght);
void SkipSpaces(char **Str);
void StrCopy(char *Str1, char *Str2);