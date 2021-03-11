

struct data_queue
{
    s32 ElementCount;
    s32 First;
    s32 End;
    const s32 MaxSize = 10;
    void* Elements[10];
};

//TEST IF QUEUE IS FULL
inline b32
IsQueueFull(data_queue* queue)
{
    b32 result = (queue->ElementCount >= queue->MaxSize);
    return(result);
}

//TEST IF QUEUE IS EMPTY
inline b32
IsQueueEmpty(data_queue* queue)
{
    b32 result = (queue->ElementCount == 0);
    return(result);
}

//RETURN THE DATA FOR THE FIRST ELEMENT IN THE QUEUE
inline void*
PeekQueue(data_queue* queue)
{
    int first = queue->First;
    void* result = (queue->Elements[first]);
    return(result);
}

//ADDS AN ELEMENT TO THE QUEUE
//RETURNS FALSE IF UNSUCCEFULL
b32
Enqueue(data_queue* queue,
        void* element)
{
    int queueIndex = queue->End;//CACHE THE NEXT AVAILIBLE SPOT IN THE QUEUE
    b32 result = TRUE;//ASSUME ELEMENT CAN BE ADDED
    
    if(IsQueueFull(queue) == FALSE)//AVAILIBLE ROOM?
    {
        queue->Elements[queueIndex] = element;
        
        //MODULOS FOR WRAPPING
        //ARRAY LAYOUT (RIGHT-MOST = INDEX 0):
        //| ELEMENT 2 | ELEMENT 1 | END | ENQUEUED |
        queue->End = ((queueIndex + 1) % queue->MaxSize);
        
        ++queue->ElementCount;//INCREMENT SIZE
    }
    else
    {
        result = FALSE;//UNSUCCESFULL ADDITION TO QUEUE
    }
    
    return(result);
}

//REMOVED THE FIRST ELEMENT FROM THE QUEUE
void*
Dequeue(data_queue* queue)
{
    int queuePeek = (queue->First + 1);
    void* result = queue->Elements[(queue->First % queue->MaxSize)];
    
    if(queue->ElementCount)
    {
        --queue->ElementCount;
        //MODULOS FOR WRAPPING
        //ARRAY LAYOUT (RIGHT-MOST = INDEX 0):
        //|ELEMENT 2 | ELEMENT 1 | DEQUEUED | ELEMENT 3|
        queue->First = (queuePeek % queue->MaxSize);
    }
    
    return(result);
}
