#include<stdio.h>
#include<utmpx.h>
#include<fcntl.h>
#include<unistd.h>

#ifdef N
struct utmpx {
	char ut_user[_UTX_USERSIZE];	/* login name */
	char ut_id[_UTX_IDSIZE];	/* id */
	char ut_line[_UTX_LINESIZE];	/* tty name */
	pid_t ut_pid;			/* process id creating the entry */
	short ut_type;			/* type of this entry */
	struct timeval ut_tv;		/* time entry was created */
	char ut_host[_UTX_HOSTSIZE];	/* host name */
	__uint32_t ut_pad[16];		/* reserved for future use */
};
#endif

void show_info(struct utmpx* );

int main(){
	struct utmpx current_record;		/*read info into here*/
	int utmpxfd;
	int reclen = sizeof(current_record);

	/*
	 * #define	UTMPX_FILE	_PATH_UTMPX
	 * #define	_PATH_UTMPX		"/var/run/utmpx"
	 * #define	O_RDONLY 0x0000
	 *****************************************************
	 * stderr 无缓存
	 * stdout 行缓存
	 *
	 */
	if( (utmpxfd = open(UTMPX_FILE,O_RDONLY)) == -1 ){
		perror(UTMPX_FILE);				/*输出字符串+strerror(errno)*/
		/*fprintf(stderr,"%s %s",UTMPX_FIFE,strerror(errno));*/
		exit(-1);
	}

	while(read(utmpxfd,&current_record,reclen) == reclen)
		show_info(&current_record);
	close(utmpxfd);
	return 0;
}

void show_info(struct utmpx* utmpxfd){
	printf("%-8.8s",utmpxfd->ut_user);
	printf(" ");
	printf("%-8.8s",utmpxfd->ut_line);
	printf(" ");
	printf("%10ld",utmpxfd->ut_tv);
	printf(" ");
#define SHOWHOST 1
#ifdef SHOWHOST
	printf("%s",utmpxfd->ut_host);
#endif
	printf(" ");
}
