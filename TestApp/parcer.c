#include <stdlib.h>
#include "parcer.h"
#include "listOfSets.h"
#include "string.h"
#include "errorInfo.h"
#define MAX_NUM_OF_OPERANDS 4

/*
Эта функция принемает на вход пользовательскую строку, определяет в зависимости от ее содержания выполнить ряд необходимых действий.

  Допустимые строки:
  A B add
  "A" "B" "add"
  "A" B add
  A B "add"
  
  Недопустимые строки:
  "A B add"
  "A"" B add
  A"" B add
  A " " add
*/


Operations WhichWordOperation(char *Word){
  if (!StrCmp(Word, "create")){
    return Unary_Operation_Create;
  }
  else if (!StrCmp(Word, "destroy")){
    return Unary_Operation_Destroy;
  }
  else if (!StrCmp(Word, "show")){
    return Unary_Operation_Show;
  }
  else if (!StrCmp(Word, "contain")){
    return Unary_Operation_Contain;
  }
  else if (!StrCmp(Word, "delete")){
    return Unary_Operation_Delete;
  }
  else if (!StrCmp(Word, "add")){
    return Unary_Operation_Add;
  }
  else if (!StrCmp(Word, "power")){
    return Unary_Operation_Power;
  }
  else if (!StrCmp(Word, "union")){
    return Binary_Operations_Union;
  }
  else if (!StrCmp(Word, "intersection")){
    return Binary_Operations_Intersection;
  }
  else if (!StrCmp(Word, "subtraction")){
    return Binary_Operations_Subtraction;
  }
  else if (!StrCmp(Word, "subset")){
    return Binary_Operations_Subset;
  }
  else if (!StrCmp(Word, "symSubtraction")){
    return Binary_Operations_SymSubtraction;
  }
  else{
    return NoOperation;
  }
}

MyBool IsSetNameExist(char *SetName, List *CurrentListOfSets){
  if (SearchElement(CurrentListOfSets, SetName, SetNameWithStrComparator) != NULL){
    MyBool_true;
  }
  else {
    return MyBool_false;
  }
}

void ShiftPointerToNextWord(char **Str, int PrevWordLenght, char prevChar){
  (*Str) += PrevWordLenght * sizeof(char);
  if (!StrCmp(*Str, "") && prevChar != ' '){
    *Str = NULL;
    return;
  }
  if (prevChar == (char)(34)){
    (*Str) += 1;
  }
  
  SkipSpaces(Str);
  return;
}


MyBool DoUnaryOperation(UnarySystem System, List *CurrentListOfSets){
  if (System.Operation == NoOperation || (System.Set == NULL && System.Operation != Unary_Operation_Create)){
    return MyBool_false;
  }
  switch (System.Operation){
  case Unary_Operation_Add:{
    AddElementToSet(System.Set, System.Data, SetElementComparator);
    break;
  }
  case Unary_Operation_Contain:{
    MyBool Result = IsElementInSet(System.Set, System.Data, SetElementComparator);
    free(System.Data);
    if (Result == MyBool_true){
      printf("true\n");
    }
    else{
      printf("false\n");
    }
    break;
  }
  case Unary_Operation_Delete:{
    DelElementFromSet(System.Set, System.Data, SetElementComparator);
    free(System.Data);
    break;
  }
  case Unary_Operation_Create:{
    Set *NewSet = CreateSet();
    NewSet->SetName = System.Data;
    AddElement(CurrentListOfSets, (void*)NewSet, SetNameComparator);
    break;
  }
  case Unary_Operation_Destroy:{
    DeleteElement(CurrentListOfSets, System.Set, SetNameComparator, ClearData);
    break;
  }
  case Unary_Operation_Power:{
    int SetPower = Power(System.Set);
    printf("%i\n", SetPower);
    break;
  }
  case Unary_Operation_Show:{
    ShowSet(System.Set, PrintSetElement);
    break;
  }
  }
  return MyBool_true;
}

MyBool DoBinaryOperation(BinarySystem System, List *CurrentListOfSets){
  if (System.Operation == NoOperation || System.Set1 == NULL || System.Set2 == NULL || (System.Data == NULL && System.Operation != Binary_Operations_Subset)){
    return MyBool_false;
  }
  if (System.Operation != Binary_Operations_Subset && IsSetNameExist(System.Data, CurrentListOfSets)){
    return MyBool_false;
  }
  switch (System.Operation){
  case Binary_Operations_Intersection:{
    Set *NewSet = Intersection(System.Set1, System.Set2, SetElementComparator, GetDataCopy);
    NewSet->SetName = System.Data;
    AddElement(CurrentListOfSets, (void*)NewSet, SetNameComparator);
    break;
  }
  case Binary_Operations_Subtraction:{
    Set *NewSet = Subtraction(System.Set1, System.Set2, SetElementComparator, GetDataCopy);
    NewSet->SetName = System.Data;
    AddElement(CurrentListOfSets, (void*)NewSet, SetNameComparator);
    break;  
  }
  case Binary_Operations_SymSubtraction:{
    Set *NewSet = SymmetricSubtraction(System.Set1, System.Set2, SetElementComparator, GetDataCopy);
    NewSet->SetName = System.Data;
    AddElement(CurrentListOfSets, (void*)NewSet, SetNameComparator);
    break;
  }
  case Binary_Operations_Union:{
    Set *NewSet = Union(System.Set1, System.Set2, SetElementComparator, GetDataCopy);
    NewSet->SetName = System.Data;
    AddElement(CurrentListOfSets, (void*)NewSet, SetNameComparator);
    break;
  }
  case Binary_Operations_Subset:{
    MyBool Result = TestInclusion(System.Set1, System.Set2, SetElementComparator);
    if (Result == MyBool_true){
      printf("true\n");
    }
    else{
      printf("false\n");
    }
    break;
  }
  }
  return MyBool_true;
}
int GetValidOperandsNum(char **MasOfWords){
  int N = MAX_NUM_OF_OPERANDS;
  int realN = 0;
  while (N-- > 0){
    if (MasOfWords[N] != NULL && *MasOfWords[N] != '\0'){
      realN++;
    }
  }
  return realN;
}
void DestroyMasOfWords(char **MasOfWords){
  for (int i = 0; i < MAX_NUM_OF_OPERANDS; i++){
    free(MasOfWords[i]);
  }
}
void InitMasOfWords(char **MasOfWords){
  for (int i = 0; i < MAX_NUM_OF_OPERANDS; i++){
    MasOfWords[i] = NULL;
  }
}
void Parcer(char *UserStr, List *CurrentListOfSets){
  char *Tmp = UserStr;
  char **MasOfWords = (char **)malloc(sizeof(char*) * MAX_NUM_OF_OPERANDS);
  InitMasOfWords(MasOfWords);
  int CurrentWordsNum = 0;
  char PrevCharacter = '\0';
  int WordLenght = 0;
  MyBool IsFirstIteration = MyBool_true;
  while (CurrentWordsNum < MAX_NUM_OF_OPERANDS){
    ShiftPointerToNextWord(&Tmp, WordLenght, PrevCharacter);
    if (Tmp == NULL){
      DestroyMasOfWords(MasOfWords);
      ShowErrorInfo(ERRORS_WrongSetNameOrOperation);
      return;
    }
    WordLenght = 0;
    
    if (*Tmp == (char)(34)){
      PrevCharacter = (char)(34);
      Tmp += sizeof(char);
    }
    else{
      PrevCharacter = ' ';
    }

    MasOfWords[CurrentWordsNum] = GetSubstrUntilChar(Tmp, PrevCharacter, &WordLenght);
    CurrentWordsNum++;
  }

  int ValidOperandsNum = GetValidOperandsNum(MasOfWords);
  MyBool Result;
  Operations TestOp = WhichWordOperation(MasOfWords[2]);

  if (TestOp == Binary_Operations_Subset || ValidOperandsNum == 4){
    BinarySystem Var;
    Var.Set1 = GetSetPointerByName(CurrentListOfSets, MasOfWords[0]);
    free(MasOfWords[0]);
    Var.Set2 = GetSetPointerByName(CurrentListOfSets, MasOfWords[1]);
    free(MasOfWords[1]);
    Var.Operation = TestOp;
    free(MasOfWords[2]);
    Var.Data = MasOfWords[3];
    if (!StrCmp(Var.Set1->SetName, Var.Data) || (!StrCmp(Var.Set1->SetName, Var.Data))){
      ShowErrorInfo(ERRORS_WrongSetNameOrOperation);
      free(MasOfWords[3]);
      free(MasOfWords);
      return;
    }
    Result = DoBinaryOperation(Var, CurrentListOfSets);
  }
  else {
    UnarySystem Var;
    Var.Operation = WhichWordOperation(MasOfWords[1]);
    free(MasOfWords[1]);
    Var.Set = GetSetPointerByName(CurrentListOfSets, MasOfWords[0]);
    if (Var.Operation == Unary_Operation_Create){
      Var.Data = MasOfWords[0];
      free(MasOfWords[2]);
    }
    else {
      Var.Data = MasOfWords[2];
      if (Var.Data == NULL && (Var.Operation == Unary_Operation_Delete || Var.Operation == Unary_Operation_Add || Var.Operation == Unary_Operation_Contain) ){
        ShowErrorInfo(ERRORS_WrongSetNameOrOperation);
        free(MasOfWords[0]);
        free(MasOfWords[3]);
        free(MasOfWords);
        return;
      }
      free(MasOfWords[0]);
    }
    Result = DoUnaryOperation(Var, CurrentListOfSets);
  }
  if (Result == MyBool_false){
    ShowErrorInfo(ERRORS_WrongSetNameOrOperation);
  }
  free(MasOfWords);
}