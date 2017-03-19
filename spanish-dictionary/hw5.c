//maxwell Sanders

//this program makes both a binary search tree and a hash table
//it searches these for spanish expressions using english words

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define the node structure
typedef struct node {
    char* key;
    char* value;
    struct node* left;
    struct node* right;
} NODE;

//define the probe structure
typedef struct probe {
    char* key;
    char* value;
} PROBE;

//declare all the functions that are going to exist;
PROBE* addProbe();
PROBE** createTable(int size);
int mulHasher(char* key);
void placeBadHash(PROBE** table, PROBE* temp, int size, int* report);
int longHasher(char* key);
void placeGoodHash(PROBE** table, PROBE* temp, int size, int* report);
void printHashReport(int * report, int size, int total);
NODE* addNode();
void placeNode(NODE* current, NODE* temp, int* cost);
void searchTree(NODE* current, char* key, int count);
void searchBadHash(PROBE** table, char* key, int size);
void searchGoodHash(PROBE** table, char* key, int size);
void freeTree(NODE* current);
void freeTable(PROBE** table, int size);

//this is the main loop
int main(void){
    //instantiate the variables
    FILE *fp;
    char buffer[250];
    int i;
    int total = 0;
    PROBE* temp;
    NODE* badNode;
    NODE* goodNode;
    PROBE** badHash;
    PROBE** goodHash;
    int* badHashReport;
    int* goodHashReport;
    NODE* badRoot = NULL;
    NODE* goodRoot = NULL;
    char* english;
    char* spanish;
    int badCost = 0;
    int goodCost = 0;
    char choice[10];
    int badSize = 10000;
    int goodSize = 100000;

    //allocate variables
    badHash = createTable(badSize);
    goodHash = createTable(goodSize);
    badHashReport = calloc(150, sizeof(int));
    goodHashReport = calloc(75, sizeof(int));

    printf("tables created\n");

    //open up the file and get the data
    fp = fopen("Spanish.txt", "r");
    while(fgets(buffer, 250, fp)){
	//if it is a comment line skip it
	if(buffer[0] == '#'){}
	else{
	    //this part takes the strings
	    english = strtok(buffer, " \t");
	    spanish = strtok(NULL, "\n");

	    //create the structs
	    temp = addProbe();
	    badNode = addNode();

	    //put the  items into the struct
	    strcpy(temp->key,english);
	    strcpy(temp->value,spanish);
	    strcpy(badNode->key,english);
	    strcpy(badNode->value, spanish);

	    //place the hash values into the hash table and update the rpeort
	    placeBadHash(badHash, temp, badSize, badHashReport);
	    placeGoodHash(goodHash, temp, goodSize, goodHashReport);

	    //if this is the first time to place the node then it goes on the root
	    if(badRoot == NULL){
		badRoot = badNode;
		badCost = 1;
	    }
	    //else look through the tree
	    else{
		placeNode(badRoot, badNode, &badCost);
		badCost ++;
	    }

	    //increment the total to see what came in
	    total ++;
   	}
    }

    //go through the good hash table
    for(i = 0; i < goodSize; i ++){
	if(goodHash[i] != NULL){
	    goodNode = addNode();
	    strcpy(goodNode->key,goodHash[i]->key);
	    strcpy(goodNode->value,goodHash[i]->value);
	    if(goodRoot == NULL){
		goodRoot = goodNode;
		goodCost = 1;
	    }
	    else{
		placeNode(goodRoot, goodNode, &goodCost);
	        goodCost ++;
	    }
	}
    }

    printf("finished placing all the values\n\n");

    //print the hash table report
    printf("Bad hash table\n");
    printHashReport(badHashReport, 150, total);
    printf("Good hash table\n");
    printHashReport(goodHashReport, 75, total);

    //print the BST reports
    printf("Bad BST\n");
    printf("The average cost was %f\n", (double)badCost/total);
    printf("The total cost was %d\n\n", badCost);
    printf("Good BST\n");
    printf("The average cost was %f\n", (double)goodCost/total);
    printf("The total cost was %d\n\n", goodCost);

    //free the reports since they are no longer necessary
    free(goodHashReport);
    free(badHashReport);

    //check the words in all 4 functions and return
    while(1){
	printf("Welcome to the English to Spanish dictionary, choose an option below\n");
	printf("===========================\n");
	printf(" 1 - Bad implementations\n");
	printf(" 2 - Good implementations\n");
	printf(" 3 - All implementations\n");
	printf(" 0 - Exit Program\n");
	printf("===========================\n");
	printf("Your choice: ");
	fgets(buffer, 250, stdin);	

	//put chop off the \n and put it into choice
	strcpy(choice, strtok(buffer, "\n"));

	//if choice 1 - bad implementations
	while( strcmp(choice, "1") == 0){
	    printf("\nType in a word to search or '-1' to leave: ");
	    fgets(buffer, 250, stdin);
	    if(strcmp(buffer, "-1\n") == 0){
	        printf("\n");
	        break;
	    }
	    printf("Bad BST: ");
	    searchTree(badRoot, strtok(buffer, "\n"), 0);
	    printf("Bad Hash: ");
	    searchBadHash(badHash, strtok(buffer, "\n"), badSize);
	}
	//if choice 2 - good implementations
	while( strcmp(choice, "2") == 0){
	    printf("\nType in a word to search or '-1' to leave: ");
	    fgets(buffer, 250, stdin);
	    if(strcmp(buffer, "-1\n") == 0){
	        printf("\n");
	        break;
	    }
	    printf("Good BST: ");
	    searchTree(goodRoot, strtok(buffer, "\n"), 0);
	    printf("Good Hash: ");
	    searchGoodHash(goodHash, strtok(buffer, "\n"), goodSize);
	}
	//if choice 3 - all implementations
	while( strcmp(choice, "3") == 0){
	    printf("\nType in a word to search or '-1' to leave: ");
	    fgets(buffer, 250, stdin);
	    if(strcmp(buffer, "-1\n") == 0){
	        printf("\n");
	        break;
	    }
	    printf("Bad BST: ");
	    searchTree(badRoot, strtok(buffer, "\n"), 0);
	    printf("Bad Hash: ");
	    searchBadHash(badHash, strtok(buffer, "\n"), badSize);
	    printf("Good BST: ");
	    searchTree(goodRoot, strtok(buffer, "\n"), 0);
	    printf("Good Hash: ");
	    searchGoodHash(goodHash, strtok(buffer, "\n"), goodSize);
	}
	//if choice 0 - exit
	if(strcmp(choice, "0") == 0){
	    printf("Have a good day!\n\n");
	    break;
	}
	//if it isn't one of the choices then it isn't a valid response
	if(strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0 && strcmp(choice, "3")){
	    printf("That is not a valid response\n\n");
	}
    }

    //close and free everything
    fclose(fp);   
    freeTable(badHash, badSize);
    freeTree(badRoot);
    free(goodHash);
    free(goodRoot);
}

//this function creates a probe and returns the pointer to it
PROBE * addProbe(){
    //instantiate the probe
    PROBE * temp;

    //allocate all the space
    temp = malloc(sizeof(PROBE));
    temp->key = malloc(50*sizeof(char));
    temp->value = malloc(200*sizeof(char)); 

    //return the probe
    return temp;
}

//this function creates a node and returns the pointer to it
NODE * addNode(){
    //instantiate the probe
    NODE * temp;

    //allocate the space for it
    temp = malloc(sizeof(NODE));
    temp->key = malloc(50*sizeof(char));
    temp->value = malloc(200*sizeof(char)); 
    temp->left = NULL;
    temp->right = NULL;

    //return the node
    return temp;
}

//this function creates a dynamically allocated empty hash table
PROBE ** createTable(int size){
    //create the variables
    int i;
    PROBE ** table;

    //allocate the space for the table
    table = malloc(size*sizeof(PROBE*));

    //go through the table and set it all to NULL
    for(i = 0; i < size; i ++){
	table[i] = NULL;
    }

    return table;
}

//places a probe into the table
void placeBadHash(PROBE** table, PROBE* temp, int size, int* report){
    //create the variables
    int tries = 0;
    int index = 0;

    //hash
    index = mulHasher(temp->key);

    //look through the table for a place to put it
    for(;;tries++, index ++){
	if(index >= size){
	    index %= size;
	}
	if(table[index] == NULL){
	    table[index] = temp;
	    break;
	}
    }  
 
    //add how many times it took to hash 
    report[tries] ++;
}

//this creates the index for the hash table by adding the values of the characters
int mulHasher(char* key){
    //create the variables needed
    int i;
    int index = 1;
    int last = 237;

    //go through the word multiply everything
    for(i = 0; key[i] != '\0'; i++){
	index *= (key[i]) + last;
	index += 2*last;
	index %= 10000;
	last = key[i];
    }
    

    //return the hashed index
    return index;
}

//places a probe into the table
void placeGoodHash(PROBE** table, PROBE* temp, int size, int* report){
    //create the variables
    int tries = 0;
    int index = 0;
    int quad = 1;

    //hash
    index = (longHasher(temp->key));

    //look through the table for a place to put it
    for(;;tries++, quad ++){
	if(index >= size){
	   index %= size;
	}
	if(table[index] == NULL){
	    table[index] = temp;
	    break;
	}
	index+=quad;
    }
 
    //add how many times it took to hash 
    report[tries] ++;
}

//this creates the index for the hash table by adding the values of the characters
int longHasher(char* key){
    //create the variables needed
    int i;
    unsigned long index = 1;
    unsigned long last = 237;

    //go through the word multiply everything
    for(i = 0; key[i] != '\0'; i++){
	index *= (key[i]);
	index += 2*last;
	last = key[i];
    }
    index %= 100000;

    //return the hashed index
    return index;
}

//this prints the hash report
void printHashReport(int* report, int size, int total){
    //create the variables needed
    int i;
    int tot_probes = 0;
    double avg_probes = 0;
    int max_probes = 0;
    int miss_probes = total;

    //make the header
    printf("Probes| Keys\n");

    //go through the report and print it
    for(i = 0; i < size; i ++){
	printf("%6d|%5d\n", i + 1, report[i]);
	printf("------------\n");
	if(report[i] != 0){
	    miss_probes -= report[i];
	    max_probes = i + 1;
	}
	tot_probes += report[i] * (i + 1);
    }
    avg_probes = (double) tot_probes/total;

    printf("Total not hashed: %d out of %d items\n", miss_probes, total);
    printf("Total probes: %d out of %d items\n", tot_probes, total);
    printf("Max run of probes: %d\n", max_probes);
    printf("Average probes: %f\n\n", avg_probes);
}

//this adds a node randomly onto a binary search tree
void placeNode(NODE* current, NODE* temp, int* cost){
    //create a random number that is either even or odd
    (*cost) ++;

    //place the item
    if(strcmp(temp->key, current->key) < 0){
	if(current->left == NULL){
	    current->left = temp;
	}
	else{
	    placeNode(current->left, temp, cost);
	}
    }
    else{
	if(current->right == NULL){
	    current->right = temp;
	}
	else{
	    placeNode(current->right, temp, cost);
	}
    }
}	

//this one searches a tree for a word and 
void searchTree(NODE* current, char* key, int count){
    //increment the counter
    count++;

    //check to see the relationship this string has to the current key
    int relation = strcmp(key, current->key);
    //if this current node has it then print out the count and the value
    if(relation == 0){
	printf("%d nodes searched\n\t%s\n", count, current->value);
    }
    //if the key was lesser than the current key then go to the left of the tree
    if(relation < 0){
	if(current->left == NULL){
	    printf("%d nodes searched\n\tNOT FOUND\n", count);
	}
	else{
	    searchTree(current->left, key, count);
	}
    }
    //if the key was greater than the current key than go to the right of the tree
    if(relation > 0){
	if(current->right == NULL){
	    printf("%d nodes searched\n\tNOT FOUND\n", count);
	}
	else{
	    searchTree(current->right, key, count);
   	}
    }
}

//this function searches the bad hash table
void searchBadHash(PROBE ** table, char* key, int size){
    //create the needed variables
    int count = 0;
    int hash;

    //hash the value
    hash = mulHasher(key);

    //go through the hash table
    while(1){
	count ++;
	//if the value gets to an empty spot then it isn't found
	if(table[hash] == NULL){
	    printf("%d probes accessed\n\tNOT FOUND\n", count);
	    break;
	}
	//if the key is in there then get the value
	if(strcmp(table[hash]->key, key) == 0){
	    printf("%d probes accessed\n\t%s\n", count, table[hash]->value);
	    break;
	}
	//else increment the hash
	hash ++;
	if(hash == size){
	    hash = 0;
	}
    }
}

//this function searches the bad hash table
void searchGoodHash(PROBE ** table, char* key, int size){
    //create the needed variables
    int count = 0;
    int hash;
    int quad = 1;

    //hash the value
    hash = longHasher(key);
    hash %= 100000;

    //go through the hash table
    while(1){
	count ++;
	//if the value gets to an empty spot then it isn't found
	if(table[hash] == NULL){
	    printf("%d probes accessed\n\tNOT FOUND\n", count);
	    break;
	}
	//if the key is in there then get the value
	if(strcmp(table[hash]->key, key) == 0){
	    printf("%d probes accessed\n\t%s\n", count, table[hash]->value);
	    break;
	}
	//else increment the hash
	hash += quad;
	quad ++;
	if(hash >= size){
	    hash %= size;
	}
    }
}

//this function frees the entirety of the tree
void freeTree(NODE* current){
    //check to see if the left and right are empty first
    if(current->left!=NULL){
	freeTree(current->left);
    }
    if(current->right!=NULL){
	freeTree(current->right);
    }
    free(current);
}

//this function frees the entirety of the hash table
void freeTable(PROBE** table, int size){
    int i = 0;
    
    //go through the whole table and free what is there
    for(i = 0; i < size; i ++){
	if(table[i] != NULL){
	    free(table[i]);
	}
    }

    //once everything in the table is freed free the table itself
    free(table);
}
