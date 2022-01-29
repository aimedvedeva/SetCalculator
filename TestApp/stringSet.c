#include <stdlib.h>
#include <stdio.h>
#include "stringSet.h"
#include "string.h"


Set *CreateSet(){
  Set *NewSet = (Set*)malloc(sizeof(Set));
  NewSet->List = CreateList();
  return NewSet;
}

void DeleteSet(Set *Set){
  DeleteList(Set->List, NULL);
  free(Set->SetName);
  free(Set);
}

int Power(Set *Set){
  return NumOfListElements(Set->List);
}

MyBool AddElementToSet(Set *Set, void *Data, Variants (*Comparator) (void *, void *)){
  return AddElement(Set->List, Data, Comparator);
}

void DelElementFromSet(Set *Set, void *Data, Variants(*Comparator) (void *, void *)){
  DeleteElement(Set->List, Data, Comparator, NULL);
  return;
}

MyBool IsElementInSet(Set *Set, void *Data, Variants(*Comparator) (void *, void *)){
  if (SearchElement(Set->List, Data, Comparator) != NULL){
    return MyBool_true;
  }
  return MyBool_false;
}

void ShowSet(Set *Set, void (*HowToShow) (void *Data)){
  ForEachElementOfList(Set->List, HowToShow);
}

Set *Union(Set *A, Set *B, Variants(*Comparator)(void *, void *), void *(*GetDataCopy) (void*)){
  Set *Union = CreateSet();
  Union->List = UnionOfLists(A->List, B->List, Union->List, Comparator, GetDataCopy);
  return Union;
}

Set *Intersection(Set *A, Set *B, Variants(*Comparator)(void *, void *), void *(*GetDataCopy) (void*)){
  Set *Intersection = CreateSet();
  Intersection->List = IntersectionOfLists(A->List, B->List, Intersection->List, Comparator, GetDataCopy);
  return Intersection;
}

MyBool TestInclusion(Set *A, Set *B, Variants(*Comparator) (void *, void *)){
  return IsFirstListInSecond(A->List, B->List, Comparator);
}

Set *Subtraction(Set *A, Set *B, Variants(*Comparator)(void *, void *), void *(*GetDataCopy) (void*)){
  Set *Subtraction = CreateSet();
  Subtraction->List = SubtractionOfLists(A->List, B->List,Subtraction->List, Comparator, GetDataCopy);
  return Subtraction;
}

Set *SymmetricSubtraction(Set *A, Set *B, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*)){
  Set *SymmetricSubtraction = CreateSet();
  SymmetricSubtraction->List = SymmetricSubtractionOfLists(A->List, B->List, SymmetricSubtraction->List, Comparator, GetDataCopy);
  return SymmetricSubtraction;
}

Variants SetElementComparator(void *Data1, void *Data2){
  int Tmp = StrCmp((char*)Data1, (char*)Data2);

  if (Tmp < 0){
    return Variants_Less;
  }
  else if (Tmp > 0){
    return Variants_Bigger;
  }
  else{
    return Variants_Equal;
  }
}

void PrintSetElement(void *ElementData){
  printf("%s\n", (char*)ElementData);
}

void *GetDataCopy(void *Data){
  char *CopyData = (char*)malloc(MAX_WORD_LENGHT * sizeof(char));
  StrCopy(CopyData, Data);
  return CopyData;
}