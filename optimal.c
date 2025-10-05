/*
 *	Write the simulation program for demand paging and show the page
 *	scheduling and total number of page faults according the optimal page
 *	replacement algorithm. Assume the memory of n frames.
 *	Reference String : 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2
 *
 * */

#include <stdio.h>

#define MAX_FRAMES 100
#define MAX_STR_LEN 100

int main() {
    int fc, sl;
    
    printf("Enter frame count: ");
    scanf("%d", &fc);
    printf("Enter string length: ");
    scanf("%d", &sl);
    
    int str[MAX_STR_LEN], frame[MAX_FRAMES];
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
                hc++;
                cacheHit = 1;
                printf("Cache hit for %d\n", currentElement);
                break;
            }
        }

        // Page fault handling
        if (!cacheHit) {
            pageFaults++;
            int replaceIndex = -1, farthest = -1;

            // Find the optimal frame to replace
            for (int j = 0; j < fc; j++) {
                if (frame[j] == -1) {
                    replaceIndex = j; // Replace an empty frame if found
                    break;
                }
            }

            // If no empty frame, find the optimal page to replace
            if (replaceIndex == -1) {
                for (int j = 0; j < fc; j++) {
                    int k;
                    for (k = i + 1; k < sl; k++) {
                        if (frame[j] == str[k]) {
                            break; // Page is found in future references
                        }
                    }
                    // If we didn't find the page, it means it's not going to be used again
                    if (k == sl) {
                        replaceIndex = j;
                        break;
                    }
                    // Track the farthest index
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }
            }

            // Replace the frame
            frame[replaceIndex] = currentElement;
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
