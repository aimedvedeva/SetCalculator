#pragma once
#include "list.h"
#include "stringSet.h"

typedef struct tag_ListOfSetsData{
  Set SetPointer;
}ListOfSetsData;

Variants SetNameComparator(void *Data1, void *Data2);
void PrintSetList(void *ElementData);
Set *GetSetPointerByName(List *CurrentListOfSets, void *Name);
Variants SetNameWithStrComparator(void *Data1, void *Data2);
void ClearData(void *Data);