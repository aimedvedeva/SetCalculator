#pragma once

typedef struct tag_ListElement{
  struct tag_ListElement *Next;
  struct tag_ListElement *Prev;

  union{
    void *Data;

    struct tag_AdditionInfo{
      int ListElementsNum;
      struct tag_ListElement *End;
    }AdditionInfo;

  };
  
}ListElement;

typedef struct tag_List{
  ListElement *AdditionalElement;
}List;

typedef enum{
  Variants_Less = -1,
  Variants_Bigger = 1,
  Variants_Equal = 0
}Variants;

typedef enum{
  MyBool_false,
  MyBool_true
}MyBool;

List *CreateList();
void DeleteList(List *ListHead, void(*ClearData) (void *));
void AddElementAtEnd(List *ListHead, void *Data);
MyBool AddElement(List *ListHead, void *Data, Variants (*Comparator) (void *, void *));
void DeleteElement(List *ListHead, void *Data, Variants(*Comparator) (void *, void *), void(*ClearData) (void *));
ListElement *SearchElement(List *ListHead, void *Data, Variants(*Comparator) (void *, void *));
void ForEachElementOfList(List *ListHead, void (*Do) (void *));
int NumOfListElements(List *ListHead);

ListElement *GetFirstElement(List *List);
void *GetElementData(ListElement *Element);
ListElement *NextElement(ListElement *Element);
MyBool IsListEmpty(List *ListHead);

List *UnionOfLists(List *A, List *B, List *Union, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*));
List *IntersectionOfLists(List *A, List *B, List *Intersection, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void *));
MyBool IsFirstListInSecond(List *A, List *B, Variants(*Comparator) (void *, void *));
List *SubtractionOfLists(List *A, List *B, List *Subtraction, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*));
List *SymmetricSubtractionOfLists(List *A, List *B, List *SymmetricSubtraction, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*));