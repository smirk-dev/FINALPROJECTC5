#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 100
int main() {
    char sentence[] = "The quick brown fox jumps over the lazy dog.";
    char input[BUFFER_SIZE];
    clock_t start, end;
    printf("Type the following sentence:\n");
    printf("\"%s\"\n\n", sentence);
    printf("Press Enter to start...\n");
    getchar();
    start = clock();
    printf("Start typing:\n");
    fgets(input, BUFFER_SIZE, stdin);
    end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    int word_count = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        word_count++;
        token = strtok(NULL, " ");
    }
    double wpm = (word_count / time_taken) * 60;
    printf("\nTime taken: %.2f seconds\n", time_taken);
    printf("You typed %d words.\n", word_count);
    printf("Your typing speed is: %.2f WPM\n", wpm);
    return 0;
}