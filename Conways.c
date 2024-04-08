#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "ezipcv2.h"

void produce(FILE *fp);
int squasher(char Line[],int i);
int printer(char Line[],int i);

int main()
{
	//pid_t producer;
	//pid_t squash;
	//pid_t print;'
 
	SETUP();
			 
	FILE *myFile;
 
	myFile=fopen("./helloWorld.txt", "r");
 
	if(myFile==NULL)
	{
		printf("Cannot open file...\n");
		return -1;
	}
 
	pid_t process=fork();
 
	if(process!=0)
	{      
		produce(myFile);
		
		sleep(2);
	}

	printf("\n");


	//closes the file
	fclose(myFile);

	return 0;
}
void produce(FILE *fp)
{
	char line[25];

	int myInt=0;

	int sema=SEMAPHORE(SEM_BIN,1);

	//loop to read in the text file line by line
	while(fgets(line,25,fp)!='\0')
	{
		//get the length of each line that we read in
		size_t length=strlen(line);

		p(sema);

		line[length-1]=NULL;

		myInt=squasher(line,myInt);

		v(sema);
	}     
} 

int squasher(char Line[],int i)
{
	char newString[25];
	int y=0;
	for(y=0;y<25;y++)
	{
		newString[y]=0;
	}
 
	size_t length=strlen(Line);
 
	int p=0;

	//makes counter point to the first character in the line each time we read in a line
	char *counter=&Line[0];

	//while we have not reached the null-terminator
	while(*counter!='\0')
	{
											 
		if(*counter!='*')
		{
			//add the asterisk to the new string
			newString[p]=*counter;
			p++;
			counter++;
		}
		else
		{
			//if the next character we look at is an *
			if(*(counter+1)=='*')
			{
				//add the # to the new string
				newString[p]='#';
				p++;
				counter++;
			}
			else
			{
				newString[p]='*';
				p++;
			}
				counter++;
		}
	}

	return printer(newString,i);
}
 
int printer(char Line[], int x)
{
	int q=0;

	int counter=0;

	char endOfLine[5]={'<','e','o','l','>'};

	while(Line[q]!='\0')
	{
		if(x>24)
		{								
			printf("\n");
			x=0;
		}

		printf("%c", Line[q]);

		q++;

		x++;
	}

	while(counter<5)
	{
		if(x>24)
		{									
			printf("\n");
			x=0;
		}

		printf("%c", endOfLine[counter]);

		counter++;

		x++;
	}

	return x;
}
