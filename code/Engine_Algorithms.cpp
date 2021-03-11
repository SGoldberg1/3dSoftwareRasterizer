/*
THESE ALGORITHMS ARE FOR TESTING PURPASES ONLY
DO NOT USE IN RELEASE
*/

//FOR USER DEFINED COMPARISONS
typedef b32 Comparison(void* valueA, void* valueB);
//FOR USER DEFINED SWAPS
typedef void Swap(void* valueA, void* valueB);
//FOR USER DEFINED SORTING
typedef void Sort(void* collection, //THE COLLECTION TO BE SORTED
                  s32 collectionElementCount, //THE NUMBER OF ELEMENTS IN THE COLLECTION
                  s32 elementByteSize,//THE SIZE OF A SINGLE ELEMENT IN BYTES
                  Comparison* comparison,//USER DEFINED COMPARISON: HOW DO WE COMPARE ELEMENTS
                  Swap* swap);//USER DEFINED SWAP: HOW DO WE SWAP ELEMENTS

//////////////////////////////// SORTING ////////////////////////////////

//GENERIC BUBBLE SORT
void
BubbleSort(void* collection, //THE COLLECTION TO BE SORTED
           s32 collectionElementCount, //THE NUMBER OF ELEMENTS IN THE COLLECTION
           s32 elementByteSize,//THE SIZE OF A SINGLE ELEMENT IN BYTES
           Comparison* comparison,//USER DEFINED COMPARISON: HOW DO WE COMPARE ELEMENTS
           Swap* swap)//USER DEFINED SWAP: HOW DO WE SWAP ELEMENTS
{
    void* currentElement = 0;//CURRENT VALUE TO COMPARE
    void* nextElement = 0;//NEXT VALUE TO COMPARE WITH THE CURRENT VALUE
    
    for(s32 i = 0; i < collectionElementCount - 1; ++i)
    {
        for(s32 j = 0; j < collectionElementCount - 1; ++j)
        {
            //CURRENT VALUE = MEMORY LOCATION OF COLLECTION +
            //    OFFSET BY THE BYTE SIZE OF 'J' ELEMENTS
            currentElement = ((s8*)collection + (j * elementByteSize));
            //NEXT VALUE = CURRENT VALUE OFFSET BY THE BYTE SIZE OF A SINGLE ELEMENT
            nextElement = ((s8*)currentElement + elementByteSize);
            
            //USER DEFINED COMPARISON
            if(comparison(currentElement, nextElement) == TRUE)
            {
                //USER DEFINED SWAP
                swap(currentElement, nextElement);
            }
        }
    }
}

//GENERIC SELECTION SORT
void
SelectionSort(void* collection, //THE COLLECTION TO BE SORTED
              s32 collectionElementCount, //THE NUMBER OF ELEMENTS IN THE COLLECTION
              s32 elementByteSize,//THE SIZE OF A SINGLE ELEMENT IN BYTES
              Comparison* comparison,//USER DEFINED COMPARISON: HOW DO WE COMPARE ELEMENTS
              Swap* swap)//USER DEFINED SWAP: HOW DO WE SWAP ELEMENTS
{
    void* currentElement = 0;//ADDRESS OF THE ELEMENT BEING SORTED
    void* nextElement = 0;//ADDRESS OF THE ELEMENT BEING COMPARED
    void* swapLocation = 0;//ADDRESS OF THE BEST LOCATION TO SWAP WITH THE CURRENT ELEMENT
    
    for(s32 i = 0; i < collectionElementCount - 1; ++i)
    {
        //CURRENT ELEMENT = COLLECTION ADDRESS +
        //   OFFSET BY BYTE SIZE OF 'I' ELEMENTS
        currentElement = ((s8*)collection + (i * elementByteSize));
        swapLocation = currentElement;//INITIAL SWAP LOCATION
        
        for(s32 j = (i + 1); j < collectionElementCount; ++j)
        {
            //NEXT ELEMENT = COLLECTION ADDRESS +
            //  OFFSET BY BYTE SIZE OF 'J' ELEMENTS
            nextElement = ((s8*)collection + (j * elementByteSize));
            
            //USER DEFINED COMPARISON
            if(comparison(swapLocation, nextElement) == TRUE)
            {
                //USER DEFINED SWAP
                swapLocation = nextElement;
            }
        }
        
        //SWAP ELEMENTS IF SWAP LOCATION HAS CHANGED
        if(swapLocation != currentElement)
            swap(currentElement, swapLocation);
    }
}

//GENERIC SHELL SORT
void
ShellSort(void* collection, //THE COLLECTION TO BE SORTED
          s32 collectionElementCount, //THE NUMBER OF ELEMENTS IN THE COLLECTION
          s32 elementByteSize,//THE SIZE OF A SINGLE ELEMENT IN BYTES
          Comparison* comparison,//USER DEFINED COMPARISON: HOW DO WE COMPARE ELEMENTS
          Swap* swap)//USER DEFINED SWAP: HOW DO WE SWAP ELEMENTS
{
    s32 gap = (collectionElementCount >> 1);//GAP BETWEEN ELEMENTS TO COMPARE
    void* currentElement = 0;//CURRENT ELEMENT BEING COMPARED
    void* gapElement = 0;//THE ELEMENT TO COMPARE WITH THE CURRENT ELEMENT
    b32 hasSwapped = FALSE;//SWAP FLAG
    
    while(gap > 0)//GAP EXIST
    {
        do//WHILE NO MORE SWAPS
        {
            hasSwapped = FALSE;//ASSUME NO SWAP
            for(s32 i = 0; i < (collectionElementCount - gap); ++i)
            {
                //CURRENT ELEMENT = COLLECTION ADDRESS +
                //  OFFSET BY BYTE SIZE OF 'I' ELEMENTS
                currentElement = ((s8*)collection + (i * elementByteSize));
                //GAP ELEMENT = CURRENT ELEMENT +
                //  OFFSET BY BYTE SIZE OF GAP ELEMENTS
                gapElement = ((s8*)currentElement + (gap * elementByteSize));
                
                //USER DEFINED SWAP
                if(comparison(currentElement, gapElement) == TRUE)
                {
                    hasSwapped = TRUE;//UPDATE SWAP FLAG
                    //USER DEFINED SWAP
                    swap(currentElement, gapElement);
                }
            }
        }while(hasSwapped == TRUE);
        
        //HALF GAP SIZE
        gap = (gap >> 1);
    }
}

//////////////////////////////// SEARCHING ////////////////////////////////

//GENERIC LINEAR SEARCH
b32
LinearSearch(void* collection, //THE COLLECTION TO BE SORTED
             void* searchElement, //THE ELEMENT TO SEARCH FOR
             s32 collectionElementCount, //THE NUMBER OF ELEMENTS IN THE COLLECTION
             s32 elementByteSize, //THE SIZE OF A SINGLE ELEMENT IN BYTES
             Comparison* comparison)//USER DEFINED COMPARISON: HOW DO WE COMPARE ELEMENTS
{
    void* currentElement = collection;//CURRENT ELEMENT IS THE COLLECTION ADDRESS
    b32 result = FALSE;//ASSUME SEARCH HAS FAILED
    s32 currentIndex = 0;//TRACK THE NUMBER OF ELEMENTS TRAVERSED
    
    while((currentIndex < collectionElementCount) &&
          (comparison(currentElement, searchElement) == FALSE))
    {
        //CURRENT ELEMENT = CURRENT ELEMENT +
        // OFFSET BY BYTE SIZE OF ONE ELEMENT
        currentElement = ((s8*)currentElement + elementByteSize);
        ++currentIndex;//ACCOUNT FOR ELEMENT TRAVERSAL
    }
    
    //CHECK IF LOOP EXIT WAS CAUSED BY THE SEARCHING ELEMENT BEING FOUND
    if(comparison(currentElement, searchElement))
        result = TRUE;
    
    return(result);
}

b32
BinarySearch(void* collection, //THE COLLECTION TO BE SORTED
             void* searchElement, //THE ELEMENT TO SEARCH FOR
             s32 collectionElementCount, //THE NUMBER OF ELEMENTS IN THE COLLECTION
             s32 elementByteSize, //THE SIZE OF A SINGLE ELEMENT IN BYTES
             Comparison* comparison)//USER DEFINED COMPARISON: HOW DO WE COMPARE ELEMENTS
{
    b32 result = FALSE;//ASSUME NOT FOUND
    s32 startIndex = 0;//LEFT HAND SIDE OF SUB ARRAY
    s32 lastIndex = collectionElementCount;//RIGHT HAND SIDE OF SUB ARRAY
    s32 middleIndex = ((startIndex + lastIndex) >> 1);//MIDDLE OF SUB ARRAY
    s8* collectionBase = (s8*)collection;//CACHE MEMORY LOCATION OF COLLECTION
    void* currentElement = (collectionBase + (middleIndex * elementByteSize));//CURRENT ELEMENT FOR COMPARISON
    
    while((startIndex <= lastIndex) && //WHILE SUB ARRAY COUNT DOES NOT EQUAL 0
          (comparison(currentElement, searchElement) != 0))//WHILE ELEMENT NOT FOUND
    {
        //IF CURRENT VALUE LESS THAN SEARCH VALUE
        if(comparison(currentElement, searchElement) < 0)
        {
            //SHIFT START INDEX OF SUB ARRAY ONE UNIT TO THE RIGHT OF THE MID
            startIndex = (middleIndex + 1);
        }
        //IF CURRENT VALUE GREATER THAN SEARCH VALUE
        else if(comparison(currentElement, searchElement) > 0)
        {
            //SHIFT LAST INDEX OF SUB ARRAY ONE UNIT TO THE LEFT OF THE MID
            lastIndex = (middleIndex - 1);
        }
        
        //HALF THE SUME OF THE START AND LAST INDEX
        middleIndex = ((startIndex + lastIndex) >> 1);
        //CURRENT ELEMENT = COLLECTION ADDRESS +
        //  OFFSET BY BYTE SIZE OF MIDDLE INDEX ELEMENTS
        currentElement = (collectionBase + (middleIndex * elementByteSize));
    }
    
    //CHECK IF LOOP EXIT WAS CAUSED BY THE SEARCHING ELEMENT BEING FOUND
    result = (comparison(currentElement, searchElement) == 0);
    
    return(result);
}