#include <stdio.h>
#include "errorInfo.h"


void ShowErrorInfo(ERRORS ErrorType){
  if (ErrorType == ERRORS_WrongSetNameOrOperation){
    printf("%s", "Wrong Set Name Or/And Operation!\n");
  }
  else if (ErrorType == ERRORS_WrongOperations){
    printf("%s", "Wrong Operation!\n");
  }
  else if (ErrorType == ERRORS_WrongSyntax){
    printf("%s", "Wrong Syntax!\n");
  }
  else if (ErrorType == ERRORS_TooLongNameForOneWord){
    printf("%s", "Too Long Name For One Word!\n");
  }
  else if (ErrorType == ERRORS_NoNewNameForResultSet){
    printf("%s", "No New Name For Result Set!\n");
  }
  else if (ErrorType == ERRORS_NoConcreteElement){
    printf("%s", "No Concrete Element!\n");
  }
}