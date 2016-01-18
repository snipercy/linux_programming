/*
 * 程序流程：
 * 	  open sourcefile for reading
 * 	  open copyfile for writing
 * +->read from source to buffer -- eof?-+
 * |				                     |
 * -- write from buffer to copy		     |
 * 					    			     |
 * 	  close sourcefile <-----------------+
 * 	  close copyfile
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE   0644

void oops(char*,char*);

int main(int argc, char* argv[]){
	int in_fd;
	int out_fd;
	int n_chars;
	char buf[BUFFERSIZE];

	if(argc != 3){
		fprintf(stderr,"useage:%s source destination\n",*argv);
		exit(1);
	}

	if( (in_fd = open(argv[1],O_RDONLY)) == -1){
		fprintf(stderr,"Error: connot open %s",argv[1]);
		exit(1);
	}

	if( (out_fd = creat(argv[2],COPYMODE)) == -1){
		fprintf(stderr,"Error: connot creat %s",argv[2]);
		exit(1);
	}

	while((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0){
//fprintf(stdout,"%s",buf);
		if( write(out_fd,buf,n_chars) != n_chars){
			fprintf(stderr,"Write error %s",argv[2]);
			exit(1);
		}
	}

	if( n_chars == -1){
		fprintf(stderr,"Read error from %s",argv[2]);
		exit(1);
	}

	if( close(in_fd) == -1 || close(out_fd) == -1){
		fprintf(stderr,"close error %s");
		exit(1);
	}
}
