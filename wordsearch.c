#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DO NOT INCLUDE OTHER LIBRARY!

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

void lrsearch(char** arr, int n, char** list, int listSize, int row, int col, int state);
void rlsearch(char** arr, int n, char** list, int listSize, int row, int col, int state);
void tbsearch(char** arr, int n, char** list, int listSize, int row, int col, int state);
void dlrsearch(char** arr, int n, char** list, int listSize, int row, int col, int state);
void drlsearch(char** arr, int n, char** list, int listSize, int row, int col, int state);

char toLower(char letter);
char toUpper(char letter);

// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
	
    return 0;
}

void printPuzzle(char** arr, int n){
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
	int i = 0, j=0;
	for(i;i<n;i++){
		for(j=0; j<n; j++){
			if (j == n-1)
				if (i == n-1 && i == j)
					printf("%c\n\n", *(*(arr+i)+j));
				else
					printf("%c\n", *(*(arr+i)+j));
			else
				printf("%c ", *(*(arr+i)+j));
		}
	}

}

void searchPuzzle(char** arr, int n, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
	int i = 0,j = 0, k = 0;
	for(i = 0; i<n; i++){
		for(j = 0; j<n; j++){
			for(k=0; k<listSize; k++){
				if (toUpper(*(*(arr+i)+j)) == *(*(list+k)+0)){
					lrsearch(arr, n, list, listSize, i, j, k);
					rlsearch(arr, n, list, listSize, i, j, k);
					tbsearch(arr, n, list, listSize, i, j, k);
					dlrsearch(arr, n, list, listSize, i, j, k);
					drlsearch(arr, n, list, listSize, i, j, k);
				}
			}
		}
	} 

}
char toLower(char letter){
	if(letter>64 && letter<91)
		letter+=32;
	return letter;
}
char toUpper(char letter){
	if(letter>96 && letter<123)
		letter-=32;
	return letter; 
}

void lrsearch(char** arr, int n, char** list, int listSize, int row, int col, int state){
	char* str;
	int i = 0, j = 0;
	int s_len = strlen(*(list+state));
	str = (char*)malloc(strlen(*(list+state)));
	for(j=0; j<s_len;j++)
		*(str+j) = 0;
	
	for(i=0; i < s_len; i++){
		if ((col+i) > n ){
			break;
		}else{
			*(str+i) = *(*(arr+row)+(col+i));
			*(*(list+state)+i) = toUpper(*(*(list+state)+i));
		}
	}
	if (col+s_len < n){
		if (strcmp(str, *(list+state)) == 0){
			for(i = 0; i < s_len; i++){
				*(*(arr+row)+(col+i)) = toLower(*(*(arr+row)+(col+i)));
				if(i == 0)
					*(str+i) = toUpper(*(str+i));
				else
					*(str+i) = toLower(*(str+i));
			}
			printf("Word Found: %s\n", str);
		}
	}
	free(str); 
}


void rlsearch(char** arr, int n, char** list, int listSize, int row, int col, int state){
	char* str;
	int i = 0, j = 0;
	int s_len = strlen(*(list+state));
	str = (char*)malloc(strlen(*(list+state)));
	for(j=0; j<s_len;j++)
		*(str+j) = 0;

	for(i=0; i < s_len; i++){
		if ((col-i) < 0 ){
			break;
		}else{
			*(str+i) = toUpper(*(*(arr+row)+(col-i)));
			*(*(list+state)+i) = toUpper(*(*(list+state)+i));
		}
	}

	if ((col-s_len) >= 0){
		if (strcmp(str, *(list+state)) == 0){
			for(i = 0; i < s_len; i++){
				*(*(arr+row)+(col-i)) = toLower(*(*(arr+row)+(col-i)));
				if(i == 0)
					*(str+i) = toUpper(*(str+i));
				else
					*(str+i) = toLower(*(str+i));
			}
			printf("Word Found: %s\n", str);
		}
	}

	free(str);
}
void tbsearch(char** arr, int n, char** list, int listSize, int row, int col, int state){
	char* str;
	int i = 0, j = 0;
	int s_len = strlen(*(list+state));
	str = (char*)malloc(strlen(*(list+state)+1));
	for(j=0; j<s_len;j++)
		*(str+j) = 0;

	for(i=0; i < s_len; i++){
		if ((row+i) >= n)
			break;
		else{
			*(str+i) = toUpper(*(*(arr+(row+i))+col));
			*(*(list+state)+i) = toUpper(*(*(list+state)+i));
		}
		
	}
	if (row+s_len < n){
		if (strcmp(str, *(list+state)) == 0){
			for(i = 0; i < s_len; i++){
				*(*(arr+(row+i))+(col)) = toLower(*(*(arr+(row+i))+(col)));
				if(i == 0)
					*(str+i) = toUpper(*(str+i));
				else
					*(str+i) = toLower(*(str+i));
			}
			printf("Word Found: %s\n", str);
		}
	}

	free(str);
}
void dlrsearch(char** arr, int n, char** list, int listSize, int row, int col, int state){

	char* str;
	int i = 0, j = 0;
	int s_len = strlen(*(list+state));
	str = (char*)malloc(strlen(*(list+state)+1));
	for(j=0; j<s_len;j++)
		*(str+j) = 0;

	for(i=0; i<s_len; i++){
		if((row+i)>= n || (col+i) >= n )
			break;
		else{
			*(str+i) = toUpper(*(*(arr+(row+i))+(col+i)));
			*(*(list+state)+i) = toUpper(*(*(list+state)+i));
		}
	}
	if ((row+s_len) < n && (col+s_len) < n){
		if(strcmp(str, *(list+state)) == 0){
			for(i=0; i<s_len; i++){
				*(*(arr+(row+i))+(col+i)) = toLower(*(*(arr+(row+i))+(col+i)));
				if(i == 0)
					*(str+i) = toUpper(*(str+i));
				else
					*(str+i) = toLower(*(str+i));
			}
			printf("Word Found: %s\n", str);
		}
	}
	
	free(str);
}
void drlsearch(char** arr, int n, char** list, int listSize, int row, int col, int state){
	char* str;
	int i = 0, j = 0;
	int s_len = strlen(*(list+state));
	str = (char*)malloc(strlen(*(list+state)+1));
	for(j=0; j<s_len;j++)
		*(str+j) = 0;
	
	for(i = 0; i<s_len; i++){
		if((row+i)>=n || (col-i)<0)
			break;
		else{
			*(str+i) = toUpper(*(*(arr+(row+i))+(col-i)));
			*(*(list+state)+i) = toUpper(*(*(list+state)+i));
		}
	}
	if((row+s_len) < n && (col-s_len)>=0){
		if(strcmp(str,*(list+state)) == 0){
			for(i=0; i<s_len;i++){
				*(*(arr+(row+i))+(col-i)) = toLower(*(*(arr+(row+i))+(col-i)));
				if(i == 0)
					*(str+i) = toUpper(*(str+i));
				else
					*(str+i) = toLower(*(str+i));
			}
			printf("Word Found: %s\n", str);
		}
	}
	free(str);
}