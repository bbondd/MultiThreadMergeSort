typedef struct _StartAndEnd {
    int start, end;
}StartAndEnd;

int* readDataFromFile(char* fileName);
void initialize(char* argv[]);
void mergeData(int start,int middle, int end);
void recursiveMergeSort(int start, int end);
void threadMergeSort(StartAndEnd* startAndEnd);
void multiThreadMergeSort();
void writeDataToFile(char* fileName);