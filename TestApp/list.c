#include <stdlib.h>
#include "list.h"

ListElement *f_CreateAdditionalElement();
ListElement *f_CreateListElement(void *Data);
void f_ClearElementMemory(void *ElementData, void (*DeleteElementData) (void *));
ListElement *f_PlaceForNewElement(List *ListHead, void *Data, Variants (*Comparator) (void *, void *));


List *CreateList(){
  List *NewList = (List*)malloc(sizeof(List));
  ListElement *AdditionalElement = f_CreateAdditionalElement();
  NewList->AdditionalElement = AdditionalElement;
  return NewList;
}
void DeleteList(List *ListHead, void (*ClearData) (void *)){
  ListElement *Iterator = GetFirstElement(ListHead);

  while (Iterator != NULL){
    ListElement *Tmp = Iterator->Next;
    f_ClearElementMemory(Iterator->Data, ClearData);
    free(Iterator);
    Iterator = Tmp;
  }

  free(ListHead->AdditionalElement);
  free(ListHead);
}

void AddElementAtEnd(List *ListHead, void *Data){
  ListElement *NewElement = f_CreateListElement(Data);

  if (ListHead->AdditionalElement->AdditionInfo.End != NULL){
    ListHead->AdditionalElement->AdditionInfo.End->Next = NewElement;
    NewElement->Prev = ListHead->AdditionalElement->AdditionInfo.End;
  }
  else if (ListHead->AdditionalElement->AdditionInfo.End == NULL){
    ListHead->AdditionalElement->Next = NewElement;
    NewElement->Prev = ListHead->AdditionalElement;

  }
  NewElement->Next = NULL;
  ListHead->AdditionalElement->AdditionInfo.End = NewElement;
  ListHead->AdditionalElement->AdditionInfo.ListElementsNum++;
}

MyBool AddElement(List *ListHead, void *Data, Variants (*Comparator) (void *, void *)){
  ListElement *PrevElement = f_PlaceForNewElement(ListHead, Data, Comparator);

  if (PrevElement == NULL){
    return MyBool_false;
  }

  ListElement *NewElement = f_CreateListElement(Data);


  if (PrevElement->Next == NULL){
    ListHead->AdditionalElement->AdditionInfo.End = NewElement;
  }

  NewElement->Next = PrevElement->Next;
  NewElement->Prev = PrevElement;
  if (PrevElement->Next != NULL){
    PrevElement->Next->Prev = NewElement;
  }
  PrevElement->Next = NewElement;

  ListHead->AdditionalElement->AdditionInfo.ListElementsNum += 1;

  return MyBool_true;
}
void DeleteElement(List *ListHead, void *Data, Variants (*Comparator) (void *, void *), void (*ClearData) (void *)){
  if (IsListEmpty(ListHead)){
    return;
  }

  if (SearchElement(ListHead, Data, Comparator) == NULL){
    return;
  }

  ListElement *Element = SearchElement(ListHead, Data, Comparator);
  
  if (Element->Next == NULL){
    ListHead->AdditionalElement->AdditionInfo.End = Element->Prev;
  }

  f_ClearElementMemory(Element->Data, ClearData);
  if (Element->Prev != NULL){
    Element->Prev->Next = Element->Next;
  }
  if (Element->Next != NULL){
    Element->Next->Prev = Element->Prev;
  }
  
  free(Element);

  ListHead->AdditionalElement->AdditionInfo.ListElementsNum -= 1;
}

ListElement *SearchElement(List *ListHead, void *Data, Variants(*Comparator) (void *, void *)){
  ListElement *Iterator = GetFirstElement(ListHead);

  while (Iterator != NULL){
    if (Comparator(Iterator->Data, Data) == Variants_Equal){
      return Iterator;
    }
    Iterator = Iterator->Next;
  }

  return NULL;
}
void ForEachElementOfList(List *ListHead, void (*Do) (void *)){
  ListElement *Iterator = GetFirstElement(ListHead);

  while (Iterator != NULL){
    Do(Iterator->Data);
    Iterator = Iterator->Next;
  }
}

int NumOfListElements(List *ListHead){
  return ListHead->AdditionalElement->AdditionInfo.ListElementsNum;
}
void *GetElementData(ListElement *Element){
  return Element->Data;
}
ListElement *NextElement(ListElement *Element){
  return Element->Next;
}
ListElement *GetFirstElement(List *List){
  return List->AdditionalElement->Next;
}
MyBool IsListEmpty(List *ListHead){
  if (GetFirstElement(ListHead) == NULL){
    return MyBool_true;
  }
  return MyBool_false;
}

List *UnionOfLists(List *A, List *B, List *Union, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*)){

  ListElement *IteratorA = GetFirstElement(A);
  ListElement *IteratorB = GetFirstElement(B);


  while (IteratorA != NULL && IteratorB != NULL){
    void *NewUnionElementData = NULL;
    Variants ResultOfComparing = Comparator(GetElementData(IteratorA), GetElementData(IteratorB));
    if (ResultOfComparing == Variants_Bigger){
      NewUnionElementData = GetElementData(IteratorB);
      IteratorB = NextElement(IteratorB);
    }
    else if (ResultOfComparing == Variants_Less){
      NewUnionElementData = GetElementData(IteratorA);
      IteratorA = NextElement(IteratorA);
    }
    else if (ResultOfComparing == Variants_Equal){
      NewUnionElementData = GetElementData(IteratorB);
      IteratorB = NextElement(IteratorB);
      IteratorA = NextElement(IteratorA);
    }
    AddElementAtEnd(Union, GetDataCopy(NewUnionElementData));
  }


  while (IteratorA != NULL){
    AddElementAtEnd(Union, GetDataCopy(GetElementData(IteratorA)));
    IteratorA = NextElement(IteratorA);
  }


  while (IteratorB != NULL){
    AddElementAtEnd(Union, GetDataCopy(GetElementData(IteratorB)));
    IteratorB = NextElement(IteratorB);
  }

  return Union;
}

List *IntersectionOfLists(List *A, List *B, List *Intersection, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void *)){
  ListElement *IteratorA = GetFirstElement(A);
  ListElement *IteratorB = GetFirstElement(B);


  while (IteratorA != NULL && IteratorB != NULL){
    Variants ResultOfComparing = Comparator(GetElementData(IteratorA), GetElementData(IteratorB));
    if (ResultOfComparing == Variants_Less){
      IteratorA = NextElement(IteratorA);
    }
    else if (ResultOfComparing == Variants_Bigger){
      IteratorB = NextElement(IteratorB);
    }
    else if (ResultOfComparing == Variants_Equal){
      void *CopyData = GetDataCopy(GetElementData(IteratorB));
      AddElementAtEnd(Intersection, CopyData);
      IteratorB = NextElement(IteratorB);
      IteratorA = NextElement(IteratorA);
    }
  }
  return Intersection;
}

MyBool IsFirstListInSecond(List *A, List *B, Variants(*Comparator) (void *, void *)){
  ListElement *IteratorA = GetFirstElement(A);
  ListElement *IteratorB = GetFirstElement(B);


  while (IteratorA != NULL && IteratorB != NULL){
    Variants ResultOfComparing = Comparator(GetElementData(IteratorA), GetElementData(IteratorB));
    if (ResultOfComparing == Variants_Less){
      return MyBool_false;
    }
    else if (ResultOfComparing == Variants_Bigger){
      IteratorB = NextElement(IteratorB);
    }
    else if (ResultOfComparing == Variants_Equal){
      IteratorB = NextElement(IteratorB);
      IteratorA = NextElement(IteratorA);
    }
  }
  if (IteratorA != NULL){
    return MyBool_false;
  }
  else {
    return MyBool_true;
  }
}
List *SubtractionOfLists(List *A, List *B, List *Subtraction, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*)){

  ListElement *IteratorA = GetFirstElement(A);
  ListElement *IteratorB = GetFirstElement(B);


  while (IteratorA != NULL && IteratorB != NULL){
    Variants ResultOfComparing = Comparator(GetElementData(IteratorA), GetElementData(IteratorB));
    if (ResultOfComparing == Variants_Less){
      AddElementAtEnd(Subtraction, GetDataCopy(GetElementData(IteratorA)));
      IteratorA = NextElement(IteratorA);
    }
    else if (ResultOfComparing == Variants_Bigger){
      IteratorB = NextElement(IteratorB);
    }
    else if (ResultOfComparing == Variants_Equal){
      IteratorB = NextElement(IteratorB);
      IteratorA = NextElement(IteratorA);
    }
  }

  while (IteratorA != NULL){
    AddElementAtEnd(Subtraction, GetDataCopy(GetElementData(IteratorA)));
    IteratorA = NextElement(IteratorA);
  }

  return Subtraction;
}
List *SymmetricSubtractionOfLists(List *A, List *B, List *SymmetricSubtraction, Variants(*Comparator) (void *, void *), void *(*GetDataCopy) (void*)){
  

  ListElement *IteratorA = GetFirstElement(A);
  ListElement *IteratorB = GetFirstElement(B);


  while (IteratorA != NULL && IteratorB != NULL){
    Variants ResultOfComparing = Comparator(GetElementData(IteratorA), GetElementData(IteratorB));
    if (ResultOfComparing == Variants_Less){
      AddElementAtEnd(SymmetricSubtraction, GetDataCopy(GetElementData(IteratorA)));
      IteratorA = NextElement(IteratorA);
    }
    else if (ResultOfComparing == Variants_Bigger){
      AddElementAtEnd(SymmetricSubtraction, GetDataCopy(GetElementData(IteratorB)));
      IteratorB = NextElement(IteratorB);
    }
    else if (ResultOfComparing == Variants_Equal){
      IteratorB = NextElement(IteratorB);
      IteratorA = NextElement(IteratorA);
    }
  }

  while (IteratorA != NULL){
    AddElementAtEnd(SymmetricSubtraction, GetDataCopy(GetElementData(IteratorA)));
    IteratorA = NextElement(IteratorA);
  }

  while (IteratorB != NULL){
    AddElementAtEnd(SymmetricSubtraction, GetDataCopy(GetElementData(IteratorB)));
    IteratorB = NextElement(IteratorB);
  }

  return SymmetricSubtraction;
}

ListElement *f_PlaceForNewElement(List *ListHead, void *Data, Variants (*Comparator) (void *, void *)){
  if (IsListEmpty(ListHead)){
    return ListHead->AdditionalElement;
  }
  if (SearchElement(ListHead, Data, Comparator) != NULL){
    return NULL;
  }
  
  ListElement *Iterator = GetFirstElement(ListHead);
  while (Comparator(GetElementData(Iterator), Data) == Variants_Less){
    if (Iterator->Next == NULL){
      return Iterator;
    }
    Iterator = Iterator->Next;
  }
  return Iterator->Prev;
}
ListElement *f_CreateAdditionalElement(){
  ListElement *AdditionalElement = (ListElement*)malloc(sizeof(ListElement));
  AdditionalElement->AdditionInfo.ListElementsNum = 0;
  AdditionalElement->AdditionInfo.End = NULL;
  AdditionalElement->Next = NULL;
  AdditionalElement->Prev = NULL;
  return AdditionalElement;
}
ListElement *f_CreateListElement(void *Data){
  ListElement *Element = (ListElement*)malloc(sizeof(ListElement));
  Element->Next = NULL;
  Element->Prev = NULL;
  Element->Data = Data;
  return Element;
}
void f_ClearElementMemory(void *ElementData, void (*DeleteElementData) (void *)){
  if (DeleteElementData == NULL){
    free(ElementData);
  }
  else{
    DeleteElementData(ElementData);
  }
}
