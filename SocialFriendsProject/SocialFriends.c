#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define NAME 40

//Function declaration
void Filling_names(int rows, int col,char Matrix[rows][col]);
void Filling_Relations(int row1,int name,int Matrix1[row1][row1], char Matrix2[row1][name]);
void Who_Will_Not_Come(int row,int col,int Rel[row][row],char Friends[row][col], int LikDis[]);
void find_max(int row, int col, int Rel[row][col], int LikDis[],int in);
void printresul(int row, int col, char Friends[row][col], int LikDis[], int index);



int main()
{
	int numfr;

	printf("Give the number of your friends:");
	scanf("%d", &numfr);

	char Friends[numfr][NAME];
	int Relations[numfr][numfr],LikDIs[numfr];

	Filling_names(numfr,NAME,Friends);
	Filling_Relations(numfr,NAME,Relations,Friends);
	Who_Will_Not_Come(numfr,NAME,Relations,Friends,LikDIs);

	return 0;

}

void Filling_names(int rows, int col,char Matrix[rows][col])
{
	int i;

	printf("Insert the names of your friends within %d characters each:\n", NAME);
	printf("\n");

	for(i=0; i<rows; i++)
	{
		printf("Enter your name of your friend no:%d ", i+1);
		scanf(" %[^\n]s", &Matrix[i]); //I put a space in the beginning of the first string argument of scanf to tell compiler to ignore white spaces
													  //and i used [^\n]s instead of s to tell compiler to read until the enter
	}
}


void Filling_Relations(int row1,int name,int Matrix1[row1][row1], char Matrix2[row1][name])
{
	int i,j;

	printf("\n");
	printf("Insert the number that indicates if someone likes/dislikes someone else...\nInsert 0 if he/she likes someone or insert 1 if he/she don't\n\n");
	for(i=0; i<row1; i++)
	{
		if(i<row1-1) printf("Relations for:%s\n", Matrix2[i]); //To teleutaio onoma den xreiazetai na ektipothei afou diamorfothikan oi sxeseis

		Matrix1[i][i]=0;
		for(j=i+1;j<row1;j++) //afou yparxei summetria os pros tin kiria diagonio douleuo mono ton ano trigoniko gia logous oikonomias
		{
				printf("Does he/she like %s?(0/1) ",Matrix2[j]);
				scanf("%d", &Matrix1[i][j]);
				Matrix1[j][i]=Matrix1[i][j];
			/*otan ftaso sto telos tou pinaka tha prepei na valo mono stoixeio stin kiria diagonio mou ara gia auto sthn mesa
			//for evala i+1 opote an px diastaseis=5 kai oi theseis ksekinane apo 0...4 tote otan i=4 to j=5 kai den tha isxuei oi sinthiki
			//ara teleiono mias kai to stoixeio ths diagoniou to evala prin mpo sthn mesa for...episis afou einai summetrika vazo kateutheian
			//kai to stoixeio ston kato trigoniko allazontas apla tous deiktes sthn entoli kataxorisis*/
		}
		printf("\n");
	}
}


void 	Who_Will_Not_Come(int row,int col,int Rel[row][row],char Friends[row][col], int LikDis[])
{
	int i,j,index;

	for(i=0; i<row; i++)
	{
		LikDis[i]=0;
		for(j=0; j<row; j++)
		{
			if(Rel[i][j]) (LikDis[i]++);  //Find for each person the amount of people who do not like
		}
	}

	find_max(row,col,Rel,LikDis,0);

	index=0;
	for(i=0;i<row;i++)
		if(LikDis[i]==0) (index++); //Finally find the amount of people who will attend to the party

	printresul(row,col,Friends,LikDis,index); //Print the names
}

void find_max(int row, int col, int Rel[row][col], int LikDis[],int in)
{
	int i,max,index;
	int l;

	for(l=in; l<row; l++)
	{
		if(LikDis[l]>0) //Den exei ousia to LikDis na exei to -1 kai na sugkrino tzampa epanalipseis...episis
		{
			max=LikDis[l];
			index=l;

			for(i=l+1; i<row; i++)
			{
				if(LikDis[i]>max )
				{
					max=LikDis[i]; //Every time I see the person who does not like the most of people
					index=i;
				}
			}

			LikDis[index]=-1;//Gia na ton apokleiso dil den tha erthei

			for(i=0; i<row;i++)
			{
				 if( LikDis[i]>0 ) (LikDis[i]--); //someone won’t come so if someone didn’t like him now he dislikes one person less than before
			}

		}

	}
}

void printresul(int row, int col, char Friends[row][col], int LikDis[], int index)
{
	int i;

	printf("Friends that will come to the party:%d\n", index);

	for(i=0; i<row; i++)
		if(LikDis[i]==0) printf("%s\n", Friends[i]);

}

