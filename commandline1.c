#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - prototype
 *
 * command line to av, collaborative help.
 * Write a function that splits a string and
 * returns an array of each word of the string.
 * man strtok
 *
 * Return: Always 0.
 */

char **split_string(char *str) {
    int i = 0, j = 0, k = 0, count = 0;
    char **words = NULL;

    while (str[i]) {
        if (str[i] == ' ') {
            count++;
        }
        i++;
    }
    count++;

    words = malloc(count * sizeof(char *));
    if (!words) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }

    i = 0;
    while (str[i]) {
        if (str[i] != ' ') {
            j++;
        } else {
            if (j > 0) {
                words[k] = malloc(j + 1);
                if (!words[k]) {
                    fprintf(stderr, "Failed to allocate memory\n");
                    exit(1);
                }
                strncpy(words[k], &str[i - j], j);
                words[k][j] = '\0';
                k++;
                j = 0;
            }
        }
        i++;
    }
    if (j > 0) {
        words[k] = malloc(j + 1);
        if (!words[k]) {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(1);
        }
        strncpy(words[k], &str[i - j], j);
        words[k][j] = '\0';
        k++;
    }
    words[k] = NULL;

    return words;
}

int main(void)
{
	char *buffer = malloc(1024);
	size_t len = 1024;
       
	while (1){
		printf("$ ");
                getline(&buffer, &len, stdin);
                printf("buffer getline: %s", buffer);
		
		char **words = split_string(buffer);
		int i = 0;
		while (words[i]) {
			printf("%s\n", words[i]);
		        i++;
	}
	
	for (i = 0; words[i]; i++) {
		free(words[i]);
	}
	free(words);
	
	}
	
	free(buffer);
	return 0;
}
