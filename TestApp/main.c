#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include "parcer.h"
#include "string.h"
#include "listOfSets.h"
#define MAX_LINE_LENGHT 300

char *GetLine(FILE *F){
  char *Line = (char*)malloc(MAX_LINE_LENGHT * sizeof(char));
  char *Tmp = Line;

  Tmp -= sizeof(char);
  do{
    Tmp += sizeof(char);
    scanf("%c", Tmp);
    if (*Tmp == (char)(-51)){
      free(Line);
      return NULL;
    }
  } while (*Tmp != '\n' && *Tmp != (char)(-51));

  
  *Tmp = '\0';
  return Line;
}
void PrintHelp(){
  FILE *help = fopen("help.txt", "r");
  
  char *str = (char*)malloc(1000 * sizeof(char));
  char *tmp = str;
  tmp -= 1;
  do{
    tmp += 1;
    fscanf(help, "%c", tmp);
    if (*tmp == (char)(-51)){
      free(str);
      return;
    }
    printf("%c", *tmp);
  } while (*tmp != (char)(-51) && *tmp );
  free(str);
}

int main(void){
  List *setOfLists = CreateList();
  FILE *F = fopen("input.txt", "r");
  while (1){
    char *str = GetLine(F);
    if (!StrCmp(str, "help")){
      PrintHelp();
      free(str);
      continue;
    }
    if (!StrCmp(str, "all sets list")){
      ForEachElementOfList(setOfLists, PrintSetList);
      free(str);
      continue;
    }
    if (str == NULL){
      break;
    }
    Parcer(str, setOfLists);
    free(str);
  }
  DeleteList(setOfLists, ClearData);

  fclose(F);
  _CrtDumpMemoryLeaks();
}