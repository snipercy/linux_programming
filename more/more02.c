/*
 *version 2: 针对ls /etc/ | more01.o 出现bug改进
 * /dev/tty:1)向该文件写相当于输出数据到屏幕
 *          2)读相当于从键盘上读取用户的输入
 */
/*
+----> show 24 lines form inputs
| +--> print [more?] message
| |    Input Enter,SPACE,or q
| +--- if Enter, advance one line
+----- if SPACE
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
       FILE* fp_tty = fopen("/dev/tty","r");
       if(fp_tty == NULL)
              exit(1);
       while (fgets(line,512,fp)){               /*more input*/
              if(num_of_lines == 24) {           /*full screen? 此时才接收用户的输入*/
                  reply = see_more(fp_tty);            /*ask user*/
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

int see_more(FILE* cmd){
       int c;
       printf("\33[7m more? \33[m");
       while((c = getc(cmd))!=EOF){              /*get response*/
              if('q' == c) return 0;
              if(' ' == c) return 24;            /*' '->next page*/
              if('\n' == c) return 1;            /*enter->next line*/
              return 0;
       }
}
