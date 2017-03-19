//maxwell Sanders 1001069652
//this program takes in two words at a time and calculates edit distance

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getInput(char * one, char * two);
void calculateED(int ** mat, char * one, char * two, int rows, int cols);
void calculateTrace(int ** mat, char ** matT, char * one, char * two, int rows, int cols);
void printMat(int ** mat, char * one, char * two, int row, int col);
void printMatTrace(char ** mat, char * one, char * two, int row, int col);
void freeMat(int ** mat, int row);
void freeMatTrace(char ** matT, int row);
void printWords(char ** matT, char * one, char * two, int rows, int cols);
void traceMat(char ** matT, char * one, char * two, int rows, int cols, char * temp1, char * temp2);
int min(int a, int b, int c);

int main(void){
    //string one and two have 100 characters allocated
    char one[100];
    char two[100];
    int ** mat = malloc(100*sizeof(int*));
    char ** matT = malloc(100*sizeof(char*));
    int rows, cols;

    while(1){
	//gets the input
	getInput(one,two);	

	//checks to see if it should end	
	if(strcmp(one, "-1") == 0 && strcmp(two, "-1") == 0){
	    break;
	}	

	//sets the row and columns
	rows = strlen(one);
	cols = strlen(two);

	//spacing
	printf("\n");

	//populates the table
	calculateED(mat, one, two, rows, cols);
	calculateTrace(mat, matT, one, two, rows, cols);

	//prints the table in all of its beauty
	printMat(mat, one, two, rows, cols);
	printf("\n");
	printMatTrace(matT, one, two, rows, cols);

	//spacing
	printf("\n");

	//prints the two words
	printWords(matT, one, two, rows, cols);

	//spacing
	printf("\n");	

	//prints the edit distance between 2 words
	printf("The edit distance is: %d\n", mat[rows][cols]);

 	//frees the rows
	freeMat(mat, rows);	
        freeMatTrace(matT, rows);

	//spacing
	printf("\n");
    }
    free(mat);
    free(matT);
    printf("Goodbye!\n");
}

//gets the inputs necessary
void getInput(char * one, char * two){
    //prompts and takes in the first word
    printf("First: ");
    fgets(one,100,stdin);
    one[strlen(one) - 1] = '\0';
 
    //prompts and takes in the second word
    printf("Second: ");
    fgets(two,100,stdin);
    two[strlen(two) - 1] = '\0';
}

//populates the DP mat
void calculateED(int ** mat, char * one, char * two, int rows, int cols){
    //make the appropriate variables
    int i, j;

    //allocate all the space for the rows
    for(i = 0; i <= rows; i ++){
	mat[i] = malloc(sizeof(int)*(cols + 1));
    }
 
    // fill the mat 
    for (i = 0; i <= rows; i++){
        for (j = 0; j <= cols; j++){
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i==0){
                mat[i][j] = j;  
 	    }

            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j==0){
                mat[i][j] = i; 
	    } 

            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (one[i-1] == two[j-1]){
                mat[i][j] = mat[i-1][j-1];
	    } 

            // If last character are different, consider all
            // possibilities and find minimum
            else{
                mat[i][j] = 1 + min(mat[i][j-1],  // Insert
                                    mat[i-1][j],  // Remove
                                    mat[i-1][j-1]); // Replace
	    }
        }
    }
}

//populates the DP mat
void calculateTrace(int ** mat, char ** matT, char * one, char * two, int rows, int cols){
    //make the appropriate variables
    int i, j, mini;

    //allocate all the space for the rows
    for(i = 0; i <= rows; i ++){
	matT[i] = malloc(sizeof(char)*(cols + 1));
    }
 
    // fill the mat 
    for (i = 0; i <= rows; i++){
        for (j = 0; j <= cols; j++){
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i==0){
                matT[i][j] = '<';  
 	    }

            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j==0){
                matT[i][j] = '^'; 
	    } 


            // If last character are different, consider all
            // possibilities and find minimum
            else{
		mini = min(mat[i][j-1],mat[i-1][j-1],mat[i-1][j]);
		if(mat[i-1][j-1] == mini){
		    matT[i][j] = '\\';
		}
		else if(mini == mat[i][j-1]){
		    matT[i][j] = '<';
		}
		else if(mini == mat[i-1][j]){
		    matT[i][j] = '^';
		}
	    }
        }
    }
}

//gets the minimum of 3 values
int min(int a, int b , int c){
    if(a <= b && a <= c){
	return a;
    }
    if(b <= a && b <= c){
	return b;
    }
    return c;
}

//prints the mat
void printMat(int ** mat, char * one, char * two, int rows, int cols){
    int i, j;

    //header
    printf("  |   |");
    for(i = 0; i < cols; i++){
	printf("%3c|", two[i]);
    }
    printf("\n---");
    for(i = 0; i <= cols; i++){
	printf("----");		
    }
    printf("\n");

    //actual meat of the printing
    printf("  |");
    for(i = 0; i <= rows; i ++){
	
	//print the row of values
	if(i >= 1){
	    printf("%2c|",one[i-1]);
	}
	for(j = 0; j <= cols; j ++){
	    printf("%3d|",mat[i][j]); 
	}
	printf("\n");

	//print a row of dashes
	printf("---");
	for(j = 0; j <= cols; j ++){
	    printf("----"); 
	}
	printf("\n");
    }
}

//prints the mat
void printMatTrace(char ** mat, char * one, char * two, int rows, int cols){
    int i, j;

    //header
    printf("  |   |");
    for(i = 0; i < cols; i++){
	printf("%3c|", two[i]);
    }
    printf("\n---");
    for(i = 0; i <= cols; i++){
	printf("----");		
    }
    printf("\n");

    //actual meat of the printing
    printf("  |");
    for(i = 0; i <= rows; i ++){
	
	//print the row of values
	if(i >= 1){
	    printf("%2c|",one[i-1]);
	}
	for(j = 0; j <= cols; j ++){
	    printf("%3c|",mat[i][j]); 
	}
	printf("\n");

	//print a row of dashes
	printf("---");
	for(j = 0; j <= cols; j ++){
	    printf("----"); 
	}
	printf("\n");
    }
}

//frees the rows in the mat
void freeMatTrace(char ** mat, int rows){
    int i;
    
    //goes through the rows and frees them
    for(i = 0; i <= rows; i ++){
	free(mat[i]);
    }
}

//frees the rows in the mat
void freeMat(int ** mat, int rows){
    int i;
    
    //goes through the rows and frees them
    for(i = 0; i <= rows; i ++){
	free(mat[i]);
    }
}

//traces through the mat recursively and fills the strings
void traceMat(char ** matT, char * one, char * two, int rows, int cols, char * temp1, char * temp2){
	    
    if(rows == 0 && cols == 0){}
    else{
	if(matT[rows][cols] == '\\'){
	    traceMat(matT, one, two, rows - 1, cols - 1, temp1, temp2);
	    sprintf(temp1, "%s%c", temp1, one[rows - 1]);
	    sprintf(temp2, "%s%c", temp2, two[cols - 1]);
	}
	else if(matT[rows][cols] == '<'){
	    traceMat(matT, one, two, rows, cols - 1, temp1, temp2);
	    sprintf(temp1, "%s%c", temp1, '-');
	    sprintf(temp2, "%s%c", temp2, two[cols - 1]);
	}
	else if(matT[rows][cols] == '^'){
	    traceMat(matT, one, two, rows - 1, cols, temp1, temp2);
	    sprintf(temp1, "%s%c", temp1, one[rows - 1]);
	    sprintf(temp2, "%s%c", temp2, '-');
	}
    }
}

//wrapper function to print the words
void printWords(char ** matT, char * one, char * two, int rows, int cols){
    int i;
    int len;
    char temp1[100];
    char temp2[100];
    
    temp1[0] = '\0';
    temp2[0] = '\0';

    traceMat(matT, one, two, rows, cols, temp1, temp2);
    
    printf("%s\n", temp2);
    printf("%s\n", temp1);

    len = strlen(temp1); 
   
    for(i = 0; i < len; i++){
	if(temp1[i] == temp2[i]){
	    printf(".");
        }
	else{
	    printf("x");
   	}
    }
    printf("\n");
}



