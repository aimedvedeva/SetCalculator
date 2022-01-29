#pragma once
#include "stringSet.h"


typedef struct tag_UnarySystem{
  char *Data;
  Set *Set;
  Operations Operation;
}UnarySystem;

typedef struct tag_BinarySystem{
  Set *Set1;
  Set *Set2;
  char *Data;
  Operations Operation;
}BinarySystem;

void Parcer(char *UserStr, List *CurrentListOfSets);