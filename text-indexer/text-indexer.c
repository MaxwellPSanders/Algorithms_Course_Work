
/*
	Name:Maxwell Sanders
	Date:9/14/16
	Function:This function reads a string, sorts it by index, and then allows the user to search it.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//this method is used to get the word at the properly given index and return that index
//also can be utilized to clean words if formatted (0, word, word);
char* wordatindex(int index, char string[], char word[]){
    int i = index, j = 0;
    while(1){
	//if it is the last character
	if(string[i + 1] == ' ' || string[i + 1] == '\0' || string[i + 1] == '\n'){
	    //if it is a letter or number
	    if((string[i] >= 65 && string[i] <= 90) || (string[i] >= 97 && string[i] <= 122) || (string[i] >= 48 && string[i] <= 57)){
		//if it is uppercase then change it
		if(string[i] >= 65 && string[i] <= 90){
	            word[j] = string[i] + 32;
		    j++;
		    i++;
		}
		//if it isn't it's good
		else{
		    word[j] = string[i];
		    j++;
		    i++;
		}
	    }
	    //breaks the while
	    break;
	}
	//if it is an uppercase letter
	else if(string[i] >= 65 && string[i] <= 90){
	    //store lowercase
	    word[j] = string[i] + 32;
            //increments counters
            j++;
            i++;
	} 
	//else accept it
	else{
	    word[j] = string[i];
	    j++;
	    i++;
	}
    }
    //fixing the word if it forgot to take off the period
    if(word[j-1] == '.'){
	word[j-1] = '\0';
    }

    //once the word is constructed add a terminating null to the end to make it official
    else{
        word[j] = '\0';    
    }

    //returns the word
    return word;
}

//this method prints out the cleaned words of the inputted texts
void printinds(int indices[], char text[]){
    int i = 0;
    char word[25];
    
    //header to the table
    printf(" i   |index[i]|  word\n");
    printf("-----|--------|------------------\n");  

    //forms the table
    while(1){
	//if it reached -1 that means there are no more values to display
	if(indices[i] == -1){
	    break;
	}
	//print the formatted table line
	printf(" %3d | %6d |  %-s\n", i, indices[i], wordatindex(indices[i], text, word));
    	i++;
    }
    //add a an empty line
    printf("\n");
}

//this method uses insertion sort to sort an array of indices corresponding to a string
void sortindices(int indices[], char text[]){
    char current[25];
    char comparitive[25];
    int i = 1;
    int j = 1;
    int temp = 0;
    //while not sorted
    while(1){
	//if it reached the end tag then exit
	if(indices[i] == -1){
	    break;
	}
	//get the main word
	strcpy(current,wordatindex(indices[i], text, current));
	for(j = i; j > 0; j --){
	    //get the word to be compared to
	    strcpy(comparitive,wordatindex(indices[j - 1], text, comparitive));
	    //if the current one is less, swap it
	    if(strcmp(current, comparitive) < 0){
	        temp = indices[j];	
		indices[j] = indices[j - 1];
		indices[j - 1] = temp;
	    }
	    //else it is good where it is at
	    else{
		break;
	    }
	}	
	i++;
    }
}

//this method searches through a sorted indices array for a given word
void searchwords(int indices[], char text[], char word[], int length){
    char found[10] = "not found";
    int i = 0;
    int high = length, low = 0;
    int mid;
    char temp[25];
    char plural[10] = "iteration";
    while(high >= low){
	mid = (high + low)/2;
	//get the word to be compared to
	strcpy(temp,wordatindex(indices[mid], text, temp));
        i ++;
	//if the word is found set found to found and exit
	if(strcmp(word, temp) == 0){
	    strcpy(found, "found");
	    break;
	}	
	//if the word is less than temp then check the bottom half
	else if(strcmp(word, temp) < 0){
	    high = mid - 1;
	}	
	//if the word is greater than temp then check the top half
	else if(strcmp(word, temp) > 0){
	    low = mid + 1;
	}
    }
    //if there was more than one iteration then state it
    if(i > 1){
	strcpy(plural,"iterations");
    }
    printf("cleaned : %s - %s (%d %s)\n", word, found, i, plural);
}

//this is my main
int main(void){
    char text[10000];
    int indices[1000];
    int i = 0, j = 0;
    int indlength;
    char input[25] = "1";

    //prompts the user to enter text
    printf("Please enter the text: ");

    //reads the text in and then places a new line on the end for 
    scanf("%[^\n]s", text);

    printf("\n\n");

    //fills the indices array
    indices[j] = 0;
    j++;
    //until the end keep incrementing and if you find whitespace one slot before, then mark this index as a new word start
    for(i = 1; text[i] != '\0' ; i ++){
	if(text[i-1] == ' '){
	    indices[j] = i;
	    j++;
	} 
    }
    //adds a -1 to make it easier to make a stopping point for later
    indices[j] = -1;
    
    //setting the index length to j - 1 (because of the -1 stopper at the end)
    indlength = j - 1;

    //print initial index, word combo
    printf("Words and indexes (the printed words are cleaned)\n");
    printinds(indices, text);

    //prints the indices
    sortindices(indices, text);

    //print sorted index, word combo
    printf("Sorted words and indexes (the printed words are cleaned)\n");
    printinds(indices, text);

    //asks the user for words to search
    printf("Binary search. ---- Enter words to search for. Stop with -1.\n");
    scanf(" %s", input);
    while(1){
	//if they enter exit statement exit
     	if(strcmp(input, "-1\n") == 0 || strcmp(input, "-1") == 0){
	    break;
	}
	//print original
	printf("(original: %s)\n", input);
	//search
	searchwords(indices, text, wordatindex(0,input,input), indlength);	
        scanf("%s", input);
    }
    printf("goodbye\n");
}
