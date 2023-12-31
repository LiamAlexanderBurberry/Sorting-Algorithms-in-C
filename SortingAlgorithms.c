#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
      case BUBBLE_SORT:
//      case INSERTION_SORT:
      case SELECTION_SORT:
      case QUICK_SORT:
//      case MERGE_SORT:
            return 1;
        default:
            return 0;
	}
}

/*Antalet byten i en och samma algoritm kan vara olika beroende p� implementationen. Ibland ligger datat redan p� r�tt plats och d� kan man v�lja att testa det och inte g�ra ett byte (vilket ger extra j�mf�relse) eller s� kan man �nd� g�ra ett byte (med sig sj�lv). F�ljer man de algoritmer som vi g�tt igenom p� f�rel�sningarna exakt s� g�r man en swap �ven p� ett element som ligger p� r�tt plats
 
    N�r du analyserar det data som genereras (result.txt) s� beh�ver du ha detta i �tanke */

/******************************************************************************************/
/* Era algoritmer har: */

static void bubbleSort(ElementType* arrayToSort, int size, Statistics* statistics)
{
    
    
    for(int i = 0; lessThan(i, size, statistics); i++)
    {
        for(int j = 0; lessThan(j, (size-1), statistics); j++)
        {
            if (greaterThanOrEqualTo(arrayToSort[j], arrayToSort[j+1], statistics))
            {
                swapElements(&arrayToSort[j+1], &arrayToSort[j], statistics);
                //int storedValue = arrayToSort[j+1];
               // arrayToSort[j+1] = arrayToSort[j];
               // arrayToSort[j] = storedValue;
                //statistics->swaps = statistics->swaps+1;
                
            }
            
        }
    }
}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
    
    int tempVar = 0;
    for(int i = 0; lessThan(i, (size-1), statistics); i++)
    {
        int lowestInArr = i;
        for(int j = i+1; lessThan(j, size, statistics); j++)
        {
            if(lessThan(arrayToSort[j], arrayToSort[lowestInArr], statistics))
            {
                lowestInArr = j;
            }
            
        }
        
        if(notEqualTo(lowestInArr, i, statistics))
        {
            swapElements(&arrayToSort[i], &arrayToSort[lowestInArr], statistics);
            //tempVar = arrayToSort[i];
           // arrayToSort[i] = arrayToSort[lowestInArr];
           // arrayToSort[lowestInArr] = tempVar;
            //statistics->swaps = statistics->swaps+1;
        }
        
    }
}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
    
    rekursionFunk(arrayToSort, 0, (size-1), statistics);
    
}
 
 void rekursionFunk(ElementType* arrayToSort, int min, int max, Statistics* statistics)
{
    
    if(lessThan(min, max, statistics))
    {
        int middle = findMiddle(arrayToSort, min, max, statistics);
        rekursionFunk(arrayToSort, min, middle-1, statistics);
        rekursionFunk(arrayToSort, middle+1, max, statistics);
    }
    else
    {
        
    }
     /*if(lessThan(min, max, statistics))
    {
        if(greaterThan(arrayToSort[min], arrayToSort[min+1], statistics))
        {
            swapElements(&arrayToSort[min], &arrayToSort[min+1], statistics);
            //helpfunk(&arrayToSort[min], &arrayToSort[min+1], statistics);
            rekursionFunk(arrayToSort, (min + 1), max, statistics);
        }
        else
        {
            rekursionFunk(arrayToSort, (min + 1), max, statistics);
        }
        
    }
    else
    {
         
    }*/
}
/*void rekursionHigh(ElementType* arrayToSort, int min, int max, Statistics* statistics)
{
  if(lessThan(min, max, statistics))
  {
      if(greaterThan(arrayToSort[min], arrayToSort[min+1], statistics))
      {
          swapElements(&arrayToSort[min], &arrayToSort[min+1], statistics);
          //helpfunk(&arrayToSort[min], &arrayToSort[min+1], statistics);
          rekursionFunk(arrayToSort, min+1, max, statistics);
      }
      else
      {
          rekursionFunk(arrayToSort, min+1, max, statistics);
          
      }
  }
}
*/
int findMiddle(ElementType* arrayToSort, int min, int max, Statistics* statistics)
{
    int j = min;
    int middleValue = arrayToSort[max];
    
    for (int i = min; lessThan(i, max, statistics); i++)
    {
       if(lessThanOrEqualTo(arrayToSort[i], middleValue, statistics))
       {
           swapElements(&arrayToSort[j], &arrayToSort[i], statistics);
           //helpfunk(&arrayToSort[j], &arrayToSort[i], statistics);
           j++;
       }
    }
    swapElements(&arrayToSort[j], &arrayToSort[max], statistics);
    //helpfunk(&arrayToSort[j], &arrayToSort[middleValue], statistics);
    return j;
    
}
/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/* Ar inte strangen vi allokerar lokal for funktionen?
	   Nej, inte i detta fall. Strangkonstanter ar ett speciallfall i C */
	switch (algorithm)
	{
        case BUBBLE_SORT:	 return "  Bubble sort ";
        case SELECTION_SORT: return "Selection sort";
        case INSERTION_SORT: return "Insertion sort";
        case MERGE_SORT:	 return "  Merge sort  ";
        case QUICK_SORT:	 return "  Quick sort  ";
        default: assert(0 && "Ogiltig algoritm!"); return "";
	}
}

// Sorterar 'arrayToSort' med 'algorithmToUse'. Statistik for antal byten och jamforelser hamnar i *statistics
static void sortArray(ElementType* arrayToSort, unsigned int size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if(statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:	 bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:	 mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:	 quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Ogiltig algoritm!");
	}
}

// Forbereder arrayer for sortering genom att allokera minne for dem, samt intialisera dem
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType)*sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

// Sorterar arrayerna
static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);
	
		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Fel! Algoritmen %s har inte sorterat korrekt!\n", getAlgorithmName(current->algorithm));
			printf("Resultatet �r: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4d element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}
