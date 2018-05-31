#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

int score=0;

void alarm_handler(int signum);

int main()
{
  FILE* fd=fopen("/usr/share/dict/words","r");
  int i=0,lines=0,random=0,counter;
  char ch;
  char word[30],line[200],input[200];

  while(!feof(fd)){
    ch = fgetc(fd);
    if(ch == '\n') lines++;
  }

system("clear");
printf("\n\n*************** WELCOME TO THE TYPING GAME ***************\n\n");
printf("You Got 60 Seconds! Typing Each Line Correct adds 10 to your Score.\n");
printf("\nPress ENTER to Start! ");
getchar();

  srand(time(NULL));

  signal(SIGALRM,alarm_handler);
  alarm(60);

  while(1){
    counter=4;
    memset(&line,0,200);
    memset(&input,0,200);

    while(counter--){
      random=rand()%lines;
      fseek(fd,0,SEEK_SET);
      i=0;
      while(fgets(word,sizeof(word),fd)){
        i++;
        if(i==random){
          word[strlen(word)-1]='\0';
          strcat(line,word);
          line[strlen(line)]=' ';
        }
      }
    }
    line[strlen(line)-1]='\0';

    do{
      printf("\nPLEASE TYPE!\n%s\n\n",line);
      scanf("%[^\n]%*c", input);
    } while(strcmp(line,input)!=0);

    score+=10;
    printf("\nCorrect!! Current Score: %d\n",score);
  }
}

void alarm_handler(int signum)
{
  printf("\n\nCongrats!! Your Final Score is %d!\n\n",score);
  printf("_____________EXITING GAME_____________\n\n");
  exit(EXIT_SUCCESS);
}
