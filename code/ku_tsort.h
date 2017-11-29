typedef struct _StartAndEnd { int start, end; } StartAndEnd;

void readDataFromFile(char* fileName);
void writeDataToFile(char* fileName);

void merge(int start, int middle, int end);
void recursiveMergeSort(int start, int end);
void threadMergeSort(StartAndEnd* startAndEnd);
void multiThreadMergeSort(int threadNumber);
