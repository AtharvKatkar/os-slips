/*
 *	Work in progress do not run!!!
 *	Write the simulation program to implement demand paging and show the
	page scheduling and total number of page faults according to the LFU page
	replacement algorithm. Assume the memory of n frames.
	Reference String : 3,4,5,4,3,4,7,2,4
*/

#include <stdio.h>

#define MAX_FRAMES 100
#define MAX_STR_LEN 100

int main() {
    int fc, sl;

    printf("Enter frame count: ");
    scanf("%d", &fc);
    printf("Enter string length: ");
    scanf("%d", &sl);

    int str[MAX_STR_LEN], frame[MAX_FRAMES], frequency[MAX_FRAMES] = {0};
    int hc = 0, pageFaults = 0;

    // Take user input string
    for (int i = 0; i < sl; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &str[i]);
    }

    // Initialize cache frames
    for (int i = 0; i < fc; i++)
        frame[i] = -1;

    for (int i = 0; i < sl; i++) {
        int currentElement = str[i], cacheHit = 0;

        // Check for cache hit
        for (int j = 0; j < fc; j++) {
            if (frame[j] == currentElement) {
                frequency[j]++;
                hc++;
                cacheHit = 1;
                printf("Cache hit for %d\n", currentElement);
                break;
            }
        }

        // Page fault handling
        if (!cacheHit) {
            pageFaults++;
            int replaceIndex = -1, minFreq = MAX_STR_LEN;

            // Find the index with the least frequency or an empty frame
            for (int j = 0; j < fc; j++) {
                if (frame[j] == -1) {
                    replaceIndex = j;
                    break;
                }

                if (frequency[j] < minFreq) {
                    minFreq = frequency[j];
                    replaceIndex = j;
                }
            }

            // Replace the frame and update frequency
            frame[replaceIndex] = currentElement;
            frequency[replaceIndex] = 1;  // Reset frequency for the new page
            printf("Page fault for %d, replacing frame index %d\n", currentElement, replaceIndex);
        }

        // Display current frames
        printf("Current frame: ");
        for (int j = 0; j < fc; j++)
            printf("%d\t", frame[j]);
        printf("\n\n");
    }

    printf("\nCache hit: %d\nPage Faults: %d\n", hc, pageFaults);
    return 0;
}

