#pragma once

typedef enum{
  ERRORS_WrongSetNameOrOperation,
  ERRORS_WrongOperations,
  ERRORS_WrongSyntax,
  ERRORS_TooLongNameForOneWord,
  ERRORS_NoNewNameForResultSet,
  ERRORS_NoConcreteElement,
}ERRORS;

void ShowErrorInfo(ERRORS ErrorType);