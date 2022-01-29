#include <stdlib.h>
#include "string.h"

void SkipSpaces(char **Str){
  while (**Str == ' '){
    (*Str) += sizeof(char);
  }
}

char *GetSubstrUntilChar(char *Str, char character, int *SubstrLenght){
  char *Substr = malloc((MAX_WORD_LENGHT + 1) * sizeof(char));
  char *Tmp = Substr;

  while (*Str != character && *Str != '\0'){
    *Tmp = *Str;
    Str += sizeof(char);
    Tmp += sizeof(char);
    (*SubstrLenght)++;
    if (*SubstrLenght > MAX_WORD_LENGHT){
      free(Substr);
      return NULL;
    }
  }
  if (*Str != character && (character != ' ')){
    free(Substr);
    return NULL;
  }
  *Tmp = '\0';
  if (!StrCmp(Substr, "")){
    free(Substr);
    return NULL;
  }
  return Substr;
}

int StrCmp(char *Str1, char *Str2){
  if (Str1 == NULL){
    return - 1;
  }
  else if (Str2 == NULL){
    return 1;
  }
  char *Tmp1, *Tmp2;
  Tmp1 = Str1;
  Tmp2 = Str2;
  while (*Tmp1 != '\0' || *Tmp2 != '\0'){
    if (*Tmp1 == *Tmp2){
      Tmp1++;
      Tmp2++;
    }
    else if (*Tmp1 > *Tmp2){
      return 1;
    }
    else if (*Tmp1 < *Tmp2){
      return -1;
    }
  }
  return 0;
}

void StrCopy(char *Str1, char *Str2){
  char *Tmp1, *Tmp2;
  Tmp1 = Str1;
  Tmp2 = Str2;
  while (*Tmp2 != '\0'){
    *Tmp1 = *Tmp2;
    Tmp1++;
    Tmp2++;
  }
  *Tmp1 = '\0';
}