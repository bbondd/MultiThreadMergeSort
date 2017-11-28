#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ku_tsort.h"

int dataLength;
int* data;

int threadNumber;
pthread_t* thread;

int* readDataFromFile(char* fileName)
{
	FILE* inputFile = fopen(fileName, "r");
	int* fileData = (int*)calloc(dataLength, sizeof(int));
	for(int i = 0; i < dataLength; i++) fscanf(inputFile, "%d", &fileData[i]);
	fclose(inputFile);
	
	return fileData;
}

void initialize(char* argv[])
{
	dataLength = atoi(argv[1]);
	data = readDataFromFile(argv[3]);
	
    threadNumber = atoi(argv[2]);
    thread = (pthread_t*)calloc(threadNumber, sizeof(pthread_t));
}

void mergeData(int start,int middle, int end)
{
    int arraySize = end - start;
    int left = start; int right = middle;
    int* tempArray = (int*)calloc(arraySize, sizeof(int));

    for(int i = 0; i < arraySize; i++)
    {
        if(data[left] < data[right] && left < middle && right < end) {
            tempArray[i] = data[left];    
            left++;
        }
        else if(data[right] <= data[left] && left < middle && right < end){
            tempArray[i] = data[right];
            right++;
        }
        else if(left == middle && right < end){
            tempArray[i] = data[right];
            right++;
        }
        else if(left < middle && right == end){
            tempArray[i] = data[left];
            left++;
        }
        else printf("function mergeData error");
    }

    for(int i = 0; i < arraySize; i++) data[start + i] = tempArray[i];
    
    free(tempArray);
}

void recursiveMergeSort(int start, int end)
{
    if (start + 1 == end) return;

    int middle = (start + end) / 2;
    recursiveMergeSort(start, middle);
    recursiveMergeSort(middle, end);

    mergeData(start, middle, end);
}

void threadMergeSort(StartAndEnd* startAndEnd) { recursiveMergeSort(startAndEnd->start, startAndEnd->end); }

void multiThreadMergeSort()
{
    StartAndEnd* startAndEnd = (StartAndEnd*)malloc(threadNumber * sizeof(StartAndEnd));

    for(int i = 0; i < threadNumber; i++) {
        startAndEnd[i].start = dataLength * i / threadNumber;
        startAndEnd[i].end = dataLength * (i + 1) / threadNumber;
        pthread_create(&thread[i], NULL, threadMergeSort, &startAndEnd[i]);
    }

    for(int i = 0; i < threadNumber; i++) pthread_join(thread[i], NULL);
    for(int i = 0; i < threadNumber; i++) mergeData(0, dataLength * i / threadNumber, dataLength * (i + 1) / threadNumber);
}

void writeDataToFile(char* fileName) {
    FILE* outputFile = fopen(fileName, "w");
    for(int i = 0; i < dataLength; i++) fprintf(outputFile, "%d\n", data[i]);
    fclose(outputFile);
}

int main(int argc, char* argv[]) {
	initialize(argv);
    multiThreadMergeSort();
    writeDataToFile(argv[4]);
}