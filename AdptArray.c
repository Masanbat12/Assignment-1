#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

/*
In this assignment i got help from solution of test_A,
for the 3 first function, for the rest i got help from google,
and used the information for writing the logic of the code.
*/
typedef struct AdptArray_
{
	/*
	struct for the class.
	*/
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC prinfFunc_)
{
	/*
	fuction to create array of the object.
	*/
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
    pArr->pElemArr = NULL; //(void*) malloc(pArr->ArrSize * sizeof (PElement));
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = prinfFunc_;	
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr)
{
	/*
	fuction to delete the array's of the object, by using free function.
	*/
	int i;
	if (pArr == NULL)
	{
	printf("Error, there is problam with the array.");
		return;
	}	
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if(pArr->pElemArr[i] == NULL){
			continue;
		}
		pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int indx, PElement pNewElem)
{
	/*
	fuction to update the array of the object, in specific index.
	*/
    if(pArr == NULL ||indx < 0)
	{
		printf("Error, the function faild to set the array.");
        return FAIL;
    }
    if(indx >= pArr->ArrSize)
	{
        PElement* tmp = (PElement*)realloc(pArr->pElemArr,(indx+1)*sizeof (PElement));
        if(tmp == NULL){
        	exit(1);
        }
        pArr->pElemArr = tmp;
		pArr->ArrSize = indx+1;
    }
    if(pArr->pElemArr[indx])
	{
        pArr->delFunc(pArr->pElemArr[indx]);
    }
    pArr->pElemArr[indx] = pArr->copyFunc(pNewElem);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray Arr,int i)
{
	/*
	fuction to get copy of the object, in specific index.
	*/
    if (Arr == NULL || Arr->pElemArr == NULL || i < 0 || i >= Arr->ArrSize)
    {
	// Return NULL if any input is
	// invalid or if index is out of bounds
	printf("Error, there is problam with the array or index.");
        return NULL;
    }
	if (Arr->pElemArr[i])
	{
		return Arr->copyFunc(Arr->pElemArr[i]);
	}
    return NULL; 
}


int GetAdptArraySize(PAdptArray pArr)
{
	/*
	fuction to get the size of an array.
	*/
    if( pArr == NULL)
	{ 
	printf("Error, there is problam with the array.");
    return -1;
	}
int i;
i = pArr->ArrSize;
return i;
}

void PrintDB(PAdptArray pArr)
{
	/*
	fuction to print array of the object.
	*/
	if(!pArr)
	{
		printf("Error, there is problam with the array, so can't print.");
		return;
	}
	for(int i = 0 ; i<pArr->ArrSize;i++)
	{
		if(pArr->pElemArr[i])
		{
			pArr->printFunc(pArr->pElemArr[i]);
		}		
	}
 }
