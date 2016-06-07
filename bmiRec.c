#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

//Patient Record
struct rec
{
	double weight;
	double height;
	double bmi;
	char * name;
	struct rec * next;
};

//Prototypes
void insertEnd(struct rec **head, double weight, double height, double bmi, char * name, int recNum);
void addRecord(struct rec **head, double wNum, double hNum, double bmi, char * name, int recNum);
void removeRecord(struct rec **head, char * name);
struct rec * sortList(struct rec * head);
void toFile(struct rec * list);
void printRecs(struct rec * list);
void destroy(struct rec ** head);
double calcBmi(double weight, double height);

int main(int argc, char ** argv)
{
	struct rec * head = NULL;
	int recNum, i, input;
	int menu = 0;
	char name[100];
	char usrOption = 'y';
	double wNum, hNum, bmi;

	printf("How many records would you like to create?\n");
    scanf("%d",&recNum);

    for(i = 0; i < recNum; i++){
    	printf("Name: - ");
    	scanf("%s", name);
    	printf("Weight (kg): - ");
    	scanf("%lf", &wNum);
    	printf("Height (cm): - ");
    	scanf("%lf", &hNum);
    	bmi = calcBmi(wNum, hNum);
    	insertEnd(&head, wNum, hNum, bmi, name, recNum);
    }

    while(menu == 0){
	    printf("\n1. Print Records\n2. Add a record\n3. Send to file\n4. Sort List\n5. Delete a Record\n6. Quit\n");
	    scanf("%d", &input);
	    //If user would like to print the patient records
	    if(input == 1){
	    	printRecs(head);
	    }
	    //Add a new patient record
	    else if(input == 2){
	    	printf("Name: - ");
    		scanf("%s", name);
    		printf("Weight (kg): - ");
	    	scanf("%lf", &wNum);
	    	printf("Height (cm): - ");
	    	scanf("%lf", &hNum);
	    	bmi = calcBmi(wNum, hNum);
	    	recNum++;
	    	addRecord(&head, wNum, hNum, bmi, name, recNum);
	    }
		//Send records to a file
	    else if(input == 3){
			toFile(head);
	    }
		//If user would like to delete records
		else if(input == 4){
			if(head->next != NULL){
				printf("Which record would you like to delete?\n");
				scanf("%s", name);
			   	removeRecord(&head, name);
			}
			else{
				printf("Sorry! There was a problem with deleting the record!\n");
			}
		}
		//Sorts the list alphabetically
		else if(input == 5){
			head = sortList(head);
		}
		//User wishes to quit program
		else if(input == 6){
			printf("Closing Records.\n");
			menu = 1;
		}
		else{
			printf("Sorry! Please enter a valid input.\n");
		}
	}

    destroy(&head);

    return(0);
}

/*Inserts information into a record*/
void insertEnd(struct rec **head, double wNum, double hNum, double bmi, char * name, int recNum)
{
	struct rec *record = (struct rec *) malloc(sizeof(struct rec) * recNum);
	struct rec *current = *head;

	record->name = (char *) malloc(sizeof(char) * strlen(name));

	record->weight = wNum;
	record->height = hNum;
	record->bmi = bmi;
	strcpy(record->name, name);

	/*Check if list is empty -- set the first record equal to the head of the list*/
	if(*head == NULL){
		*head = record;
		return;
	}

	/*Traverse node until the last node*/
	while(current->next != NULL){
		current = current->next;
	}

	current->next = record;
}

void addRecord(struct rec **head, double wNum, double hNum, double bmi, char * name, int recNum)
{
	struct rec * record = (struct rec *) realloc(record, recNum * sizeof(struct rec)); 
	struct rec *current = *head;

	record->name = (char *) malloc(sizeof(char) * strlen(name));

	record->weight = wNum;
	record->height = hNum;
	record->bmi = bmi;
	strcpy(record->name, name);

	/*Traverse node until the last node*/
	while(current->next != NULL){
		current = current->next;
	}

	current->next = record;
}

void toFile(struct rec * list)
{
	char fName[100];
	FILE *fp;
	int num = 1;

	printf("Pleae enter the file\n");
    scanf("%s", fName);

    fp = fopen(fName, "w");

	while(list != NULL){
		fprintf(fp, "%d: Name: %s, Weight: %.2f, Height: %.2f\nBMI: %.2f\n\n", 
			num, list->name, list->weight, list->height, list->bmi);
		list = list->next;
		num++;
	}

}

void removeRecord(struct rec **head, char * name)
{
	struct rec * current = *head;
	struct rec * next;
	struct rec * previous;

	//Traverse record to find match
	while(current->next != NULL){

		if(strcmp(name, current->name) == 0){
			//First node
			if(current == *head){
				next = current->next;
				free(current);
				*head = next;
				return;
			}
			//Middle Nodes
			else{
				next = current->next;
				free(current);
				previous->next = next;
				current = previous->next;
				return;
			}
		}

		//Saving previous record place
		previous = current;
		current = current->next;
	}
	//Last Node !! problematic area? 
	/*if(current->next == NULL){
		if(strcmp(name, current->name) == 0){
			free(current);
			previous->next = NULL;
			return;
		}
	}*/
}

struct rec * sortList(struct rec * head)
{
	struct rec * temp = head;
	

}

/*Prints each record out in order*/
void printRecs(struct rec * list)
{
	int num = 1;

	printf("\n");

	while(list != NULL){
		printf("%d: Name: %s, Weight: %.2f, Height: %.2f\nBMI: %.2f\n\n", 
			num, list->name, list->weight, list->height, list->bmi);
		list = list->next;
		num++;
	}
}

void destroy(struct rec ** head)
{
	struct rec * current = *head;
	struct rec * next;

	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

double calcBmi(double weight, double height)
{
	double result;

	result = (weight/((height/100) * (height/100)));

	return (result);
}
