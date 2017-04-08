#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct student
{
char name[50];
int roll;
float marks;
}s;
void Address_records();
void List_records();
void Delete_records();
void Modify_records();
void Search_records();
char filename[50];
int main(void)
{
	char choice;
	clrscr();
	printf("Enter filename for this program:");
	scanf("%s",filename);
	while(1)
	{
		printf("\n\nEnter A for adding new records on file=\n");

		printf("Enter L for displaying list of all records on file=\n");

		printf("Enter M  for modifying a record on file=\n");

		printf("Enter D for deleting a record on file=\n");

		printf("Enter S for searching a record on file=\n");

      printf("Enter other character to exit from program=");
		fflush(stdin);
		choice=getchar();
		switch(choice)
		{
			case 'A':
				Address_records();
				break;
			case 'L':
				List_records();
				break;
			case 'M':
				Modify_records();
				break;
			case 'D':
				Delete_records();
				break;
			case 'S':
				Search_records();
				break;
			default:
				exit(0);

		}
	}

	return 0;
}
void Address_records()
{
	FILE *f;
	char test;
	if((f=fopen(filename,"ab+"))==NULL)
	{

		if((f=fopen(filename,"wb+"))==NULL)
		{
			printf("File can not open\n");
			getch();
			exit(0);
		}
	}
	while(1)
	{
		fflush(stdin);
		printf("\n Enter Name:");
		scanf("%[^\n]",s.name);
		printf("\n Enter Roll Number:");
		scanf("%d",&s.roll);
		printf("\n Enter Marks:");
		scanf("%f",&s.marks);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		printf("\n If you don't want to add another record then enter N :");
		scanf("%c",&test);
		if(test=='N')
			break;
	}
	fclose(f);
}
void List_records()
{
	FILE *f;

	if((f=fopen(filename,"rb"))==NULL)
		{
			printf("File can not open\n");
			getch();
			exit(0);
		}

	printf("--------------------------------------------");
	printf("\n Name			Roll Number			Marks \n");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-50s%-10d%10.2f",s.name,s.roll,s.marks);
	}
	fclose(f);
	getch();
	}

void Modify_records()
{
	FILE *f;
	char name[50];
	long int size =sizeof(s);
	if((f=fopen(filename,"rb+"))==NULL)
		exit(0);
	printf("Enter name of student to modify record=");
   fflush(stdin);
	scanf("%[^\n]",name);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.name,name)==0)
		{
			printf("\n Enter Name, Roll Number and Marks to modify:");
			scanf("%s %d %f",s.name,&s.roll,&s.marks);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
	getch();
}
void Delete_records()
{
	FILE *f,*temp;
	char name[50];
	if((f=fopen(filename,"rb"))==NULL)
		exit(0);
	if((temp=fopen("temporary","wb+"))==NULL)
		exit(0);
	printf("Enter Name of student to delete record:");
   fflush(stdin);
	scanf("%[^\n]",name);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.name,name)==0)
			continue;
		else
			fwrite(&s,sizeof(s),1,temp);
	}
  	remove(filename);
	rename("temporary",filename);
	fclose(f);
	fclose(temp);
	getch();
	}
void Search_records()
{
	FILE *f;
	char name[50];
	int flag=1;
	if((f=fopen(filename,"rb"))==NULL)
		exit(0);
	printf("\n Enter Name of student to search:");
   fflush(stdin);
	scanf("%s",name);
	while(fread(&s,sizeof(s),1,f)==1)
	{                                                               
		if(strcmp(s.name,name)==0)
		{
			printf("\n Name=",s.name);
			printf("\n Roll Number=",s.roll);
			printf("\n Marks=",s.marks);
			flag=0;
		}

	}
	if(flag==1)
		printf("\n Record is not found.");

	fclose(f);
   getch();
}