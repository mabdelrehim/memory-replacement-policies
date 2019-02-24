#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

int search(int arr[], int n, int x);
int getMinTime(int times[], int n);

int main() {

    int pagesAllocated = 0;
    scanf("%d", &pagesAllocated);
    int inMemory[pagesAllocated];
    int LRUtimes[pagesAllocated];
    bool clockBits[pagesAllocated];
    int memoryFull = 0;
    int currentIndex = 0;
    int fifoIndexToReplace = 0;
    int clockPointer = 0;
    int numberOfPageFaults = 0;
    int currentTime = 0;

    // initialize array in memory
    for (int i = 0; i < pagesAllocated; i++) {
        inMemory[i] = -1;
    }

    char policy[10];
    scanf("%s",policy);

    printf("Replacement Policy = %s\n", policy);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");



    int memoryReference;
    scanf("%d", &memoryReference);
    while (memoryReference != -1) {
        // look first in memory
        int indexOfFrame = search(inMemory, pagesAllocated, memoryReference);
        if (indexOfFrame != -1) {
            // found
            LRUtimes[indexOfFrame] = currentTime++;
            clockBits[indexOfFrame] = true;

            printf("%02d     ", memoryReference);
            for (int i = 0; i < pagesAllocated; i++) {
                if (inMemory[i] < 0)
                    break;
                else
                    printf("%02d ",inMemory[i]);

            }
            printf("\n");

        } else {
            // i-o needed

            if(memoryFull < pagesAllocated) {
                // no replacement needed
                // page fault but will not print f

                inMemory[currentIndex] = memoryReference;
                LRUtimes[currentIndex] = currentTime++;
                clockBits[clockPointer] = true;
                clockPointer = (clockPointer + 1)%pagesAllocated;
                currentIndex++;
                memoryFull++;
                printf("%02d     ", memoryReference);
                for (int i = 0; i < pagesAllocated; i++) {
                    if (inMemory[i] < 0)
                        break;
                    else
                        printf("%02d ",inMemory[i]);
                }
                printf("\n");

            } else {
                // replacement needed
                // page fault

                if(!strcasecmp(policy, "LRU")) {
                    // LRU
                    int indexOfMinTime = getMinTime(LRUtimes, pagesAllocated);
                    // replace
                    inMemory[indexOfMinTime] = memoryReference;
                    LRUtimes[indexOfMinTime] = currentTime++;


                } else if(!strcasecmp(policy, "CLOCK")) {
                    // CLOCK
                    while (clockBits[clockPointer]) {
                        clockBits[clockPointer] = false;
                        clockPointer = (clockPointer + 1)%pagesAllocated;
                    }
                    inMemory[clockPointer] = memoryReference;
                    clockBits[clockPointer] = true;
                    clockPointer = (clockPointer + 1)%pagesAllocated;



                } else if(!strcasecmp(policy, "FIFO")) {
                    // FIFO
                    inMemory[fifoIndexToReplace] = memoryReference;
                    fifoIndexToReplace = (fifoIndexToReplace + 1) % pagesAllocated;

                }
                printf("%02d F   ", memoryReference);
                for (int i = 0; i < pagesAllocated; i++) {
                    if (inMemory[i] < 0)
                        break;
                    else
                        printf("%02d ",inMemory[i]);

                }
                printf("\n");
                numberOfPageFaults++;
            }
        }
        scanf("%d", &memoryReference);
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", numberOfPageFaults);




    return 0;
}

int search(int arr[], int n, int x) {
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

int getMinTime(int times[], int n) {
    long int min = INT_MAX;
    int indexOfMin = -1;
    for(int i = 0; i < n; i++) {
        if (times[i] < min) {
            min = times[i];
            indexOfMin = i;
        }
    }
    return indexOfMin;
}