#pragma once
#include "list.h"


typedef struct tag_Set{
  char *SetName;
  List *List;
}Set;

typedef enum{
  NoOperation,
  Binary_Operations_SymSubtraction,
  Binary_Operations_Union,
  Binary_Operations_Intersection,
  Binary_Operations_Subtraction,
  Binary_Operations_Subset,
  Unary_Operation_Power,
  Unary_Operation_Add,
  Unary_Operation_Delete,
  Unary_Operation_Contain,
  Unary_Operation_Destroy,
  Unary_Operation_Create,
  Unary_Operation_Show
}Operations;

Set *CreateSet();
void DeleteSet(Set *Set);
MyBool AddElementToSet(Set *Set, void *Data, Variants (*Comparator) (void *, void *));
void DelElementFromSet(Set *Set, void *Data, Variants (*Comparator) (void *, void *));
MyBool IsElementInSet(Set *Set, void *Data, Variants (*Comparator) (void *, void *));
int Power(Set *Set);
void ShowSet(Set *Set, void(*HowToShow) (void *Data));

Set *Union(Set *A, Set *B, Variants(*Comparator)(void *, void *), void *(*GetDataCopy) (void*));
Set *Intersection(Set *A, Set *B, Variants(*Comparator)(void *, void *), void *(*GetDataCopy) (void*));
MyBool TestInclusion(Set *A, Set *B, Variants(*Comparator) (void *, void *));
Set *Subtraction(Set *A, Set *B, Variants(*Comparator)(void *, void *), void *(*GetDataCopy) (void*));
Set *SymmetricSubtraction(Set *A, Set *B, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*));

Variants SetElementComparator(void *Data1, void *Data2);
void PrintSetElement(void *ElementData);
void *GetDataCopy(void *Data);