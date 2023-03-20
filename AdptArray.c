
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "book.h"
#include "AdptArray.h"


typedef struct AdptArray_ {
    void** ArrayOfElements;
    int capacity ;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
}AdptArray_;


Result putDeepCopyInsideADT(PAdptArray pAdt ,int index , PElement pTOelement ){  
        PElement copyP= pAdt->copy_func(pTOelement);
        if(copyP != NULL){                         
                pAdt->ArrayOfElements[index] = copyP;   
                return SUCCESS;
             }
        else
            return FAIL; 
} 

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC dell_func ,PRINT_FUNC print_func ){
     PAdptArray pAD= malloc(sizeof(AdptArray_)) ;
     if(pAD != NULL){
        pAD->ArrayOfElements =NULL;
        pAD->capacity =0;
        pAD->del_func = dell_func;
        pAD->print_func = print_func;       
        pAD->copy_func = copy_func;
        return pAD; 
     }
     return NULL;
}
            

Result SetAdptArrayAt(PAdptArray pAdt, int index, PElement pTOelement){
                  if(pTOelement == NULL)
                      return FAIL;
       // *** in case there is no more place fore the current index inside the pAdt 
                  if(index >= pAdt->capacity){
                      int newCpacity = index + 1   ;
                      //* reallocating new memory and initialize the new allocting memory to Null    
                      pAdt->ArrayOfElements = (void**)realloc(pAdt->ArrayOfElements, newCpacity*sizeof(PElement) ); 
                      if(pAdt->ArrayOfElements != NULL){ 
                        memset(pAdt->ArrayOfElements +  pAdt->capacity   , 0,  (newCpacity -pAdt->capacity)*sizeof(PElement));
                      // and updating the ADT capacity and put a copy of the element inside the ADT 
                        pAdt->capacity = newCpacity;
                        return (putDeepCopyInsideADT( pAdt, index, pTOelement));
                      }
                       return FAIL;}

                 //*** if the array leangth > index 
                  else{      
                     /*IN CASE : the there is already pelement in that specific index :
                     1. free the memory at that index ,2.put a copy of the  and put a copy of the specify element in the ADT */ 
                      if(pAdt->ArrayOfElements[index] != NULL  ) { 
                           pAdt->del_func(pAdt->ArrayOfElements[index]);
                           return (putDeepCopyInsideADT( pAdt, index, pTOelement));
                      }
                      // IN CASE : there is nothing inside the array at that specify index 
                      else {
                          pAdt->ArrayOfElements[index] = pTOelement; 
                          return SUCCESS;
                      } 
                  }
} 
     PElement GetAdptArrayAt(PAdptArray pAdt, int index){
               PElement pTOelement = pAdt->ArrayOfElements[index];
               if(pTOelement ==NULL)
                   return NULL;
               PElement copyP= pAdt->copy_func(pTOelement);
               if(copyP != NULL)
                    return copyP;  
                return NULL;        
     }  
     
    
     void DeleteAdptArray(PAdptArray pADT){
        PElement* ptoArray  = pADT->ArrayOfElements ;
         // looping all the not-NULL pointers and free them 
        for(int i = 0 ; i < pADT->capacity; i++){
            if(ptoArray[i] !=NULL )
                pADT->del_func(ptoArray[i]);
        }
        // free the array and the struct itself
        free(ptoArray);
        free(pADT);
     }
     ///function to comupte the size of the array 
     int GetAdptArraySize(PAdptArray pAdt){
        if(pAdt == NULL)
            return -1 ; 
        return pAdt->capacity;
     } 
     // print all elements inside the ADT 
     void PrintDB(PAdptArray pADT){
        if(pADT == NULL)
            return ;
        // looping all the not-NULL pointers and print the content of the inside adress. 
        PElement* ptoArray  = pADT->ArrayOfElements ;
        for(int i = 0 ; i < pADT->capacity; i++){
            if(ptoArray[i] !=NULL )
                pADT->print_func(ptoArray[i]);
        }
     }




                  
                  
                        
         
