/*more01.c -version 0.1 of more
 * read and print 24 lines then pause for a few special commands
 */

/*

+----> show 24 lines form inputs
| +--> print [more?] message
| |    Input Enter,SPACE,or q
| +--> if Enter, advance one line
+----> if SPACE
       if q --> exit
*/

#include<stdio.h>
#include<stdlib.h>

void do_more(FILE*);

int see_more();

int main(int argc, char* argv[]){
       FILE* fp;/*FIFE */
       if(argc == 1){
              do_more(stdin);
       }
       else{
              while (--argc){
                     if( (fp = fopen(*++argv,"r")) != NULL){
                            do_more(fp);
                            fclose(fp);
                     }
                     else
                            exit(1);
              }
       }
       return 0;
}

/*
 * read 24 lines, then call see_more() for further instructions
 */
void
do_more(FILE* fp){
       char line[512];
       int num_of_lines = 0;
       //int see_more();
       int reply;
       while (fgets(line,512,fp)){               /*more input*/
              if(num_of_lines == 24) {           /*full screen? 此时才接收用户的输入*/
                  reply = see_more();            /*ask user*/
                  if (reply == 0)                /*done*/
                         break;
                  num_of_lines -= reply;         /*reset count*/
              }
              if(fputs(line,stdout) == EOF){     /*show line*/
                     exit(1);
              }
              num_of_lines++;
       }
}

int see_more(){
       int c;
       printf("\33[7m more? \33[m");
       while((c = getchar())!=EOF){              /*get response*/
              if('q' == c) return 0;
              if(' ' == c) return 24;            /*' '->next page*/
              if('\n' == c) return 1;            /*enter->next line*/
              return 0;
       }
}
