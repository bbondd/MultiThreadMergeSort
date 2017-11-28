typedef struct _StartAndEnd {
    int start, end;
}StartAndEnd;

void readDataFromFile(char* fileName);
void mergeData(int start,int middle, int end);
void recursiveMergeSort(int start, int end);
void threadMergeSort(StartAndEnd* startAndEnd);
void multiThreadMergeSort(int threadNumber);
void writeDataToFile(char* fileName);