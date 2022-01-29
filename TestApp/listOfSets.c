#include <stdlib.h>
#include <stdio.h>
#include "listOfSets.h"
#include "string.h"

Variants SetNameComparator(void *Data1, void *Data2){
  
  int Tmp = StrCmp(((ListOfSetsData*)Data1)->SetPointer.SetName, ((ListOfSetsData*)Data2)->SetPointer.SetName);

  if (Tmp < 0){
    return Variants_Less;
  }
  else if (Tmp > 0){
    return Variants_Bigger;
  }
  else {
    return Variants_Equal;
  }
}

void ClearData(void *Data){
  DeleteSet(Data);
}

Variants SetNameWithStrComparator(void *Data1, void *Data2){

  int Tmp = StrCmp(((ListOfSetsData*)Data1)->SetPointer.SetName, Data2);

  if (Tmp < 0){
    return Variants_Less;
  }
  else if (Tmp > 0){
    return Variants_Bigger;
  }
  else {
    return Variants_Equal;
  }
}

void PrintSetList(void *ElementData){
  printf("%s\n", ((ListOfSetsData*)ElementData)->SetPointer.SetName);
}

Set *GetSetPointerByName(List *CurrentListOfSets, void *Name){
  ListElement *Tmp = SearchElement(CurrentListOfSets, Name, SetNameWithStrComparator);

  if (Tmp == NULL){
    return NULL;
  }
  else{
    return &(((ListOfSetsData*)(Tmp->Data))->SetPointer);
  }
}
