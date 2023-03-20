#ifndef ADAPTARRAY_H
#define ADAPTARRAY_H
typedef struct AdptArray_* PAdptArray;
typedef enum  {FAIL = 0, SUCCESS=1} Result;
typedef void* PElement;

typedef void(*DEL_FUNC)(PElement); // pointer to a func called  which getting void* and returns nothing 
typedef PElement(*COPY_FUNC)(PElement);// COPY_FUNC is type of pointer to function that takes void* as argument and returnes void*
typedef void(*PRINT_FUNC)(PElement); //PRINT_FUNC is type of pointer to function that takes void* as argument and returnes nothing

PAdptArray CreateAdptArray(COPY_FUNC, DEL_FUNC,PRINT_FUNC);
void DeleteAdptArray(PAdptArray);
Result SetAdptArrayAt(PAdptArray, int, PElement);
PElement GetAdptArrayAt(PAdptArray, int);
int GetAdptArraySize(PAdptArray);
 void PrintDB(PAdptArray);
#endif