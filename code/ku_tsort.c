#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ku_tsort.h"

int dataLength;
int* data;

void readDataFromFile(char* fileName) {
	FILE* inputFile = fopen(fileName, "r");
	int* fileData = (int*)calloc(dataLength, sizeof(int));
	for(int i = 0; i < dataLength; i++) fscanf(inputFile, "%d", &fileData[i]);
	fclose(inputFile);
	
    data = fileData;
}

void writeDataToFile(char* fileName) {
    FILE* outputFile = fopen(fileName, "w");
    for(int i = 0; i < dataLength; i++) fprintf(outputFile, "%d\n", data[i]);
    fclose(outputFile);
}


void merge(int start, int middle, int end) {
    int i = 0, left = start, right = middle;
    int* tempArray = (int*)calloc(end - start, sizeof(int));

    while(left < middle && right < end) 
        if(data[left] < data[right]) tempArray[i++] = data[left++];
        else tempArray[i++] = data[right++];

    while(left < middle) tempArray[i++] = data[left++];
    while(right < end) tempArray[i++] = data[right++];

    for(int j = 0; j < end - start; j++) data[start + j] = tempArray[j];
    free(tempArray);
}

void recursiveMergeSort(int start, int end) {
    if (start + 1 == end) return;

    int middle = (start + end) / 2;
    recursiveMergeSort(start, middle);
    recursiveMergeSort(middle, end);

    merge(start, middle, end);
}

void threadMergeSort(StartAndEnd* startAndEnd) { recursiveMergeSort(startAndEnd->start, startAndEnd->end); }

void multiThreadMergeSort(int threadNumber) {        
    pthread_t* thread = (pthread_t*)calloc(threadNumber, sizeof(pthread_t));
    StartAndEnd* startAndEnd = (StartAndEnd*)calloc(threadNumber, sizeof(StartAndEnd));

    for(int i = 0; i < threadNumber; i++) {
        startAndEnd[i].start = dataLength * i / threadNumber;
        startAndEnd[i].end = dataLength * (i + 1) / threadNumber;
        pthread_create(&thread[i], NULL, threadMergeSort, &startAndEnd[i]);
    }

    for(int i = 0; i < threadNumber; i++) pthread_join(thread[i], NULL);
    for(int i = 0; i < threadNumber; i++) merge(0, dataLength * i / threadNumber, dataLength * (i + 1) / threadNumber);
}


void main(int argc, char* argv[]) {
    dataLength = atoi(argv[1]);
    readDataFromFile(argv[3]);
    multiThreadMergeSort(atoi(argv[2]));
    writeDataToFile(argv[4]);
}