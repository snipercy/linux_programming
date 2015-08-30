#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>//directory entry
#include<sys/types.h>
#include<string.h>

void do_ls(char[]);
void do_stat(char*);
void show_file_info(char*,struct stat*);
void mode_to_letters(int,char*);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char* argv[]){
	if(argc == 1){
		do_ls(".");
	}
	else{
		while(--argc){
			/* '*' and '++'优先级相同，由于右结合,
			 故*++argv = *(++argv)*/
			printf("%s:\n",*++argv);
			do_ls(*argv);

		}
	}
}

/*DIR dirent struct defined*/
#if 0
/* structure describing an open directory. */
typedef struct {
	int	__dd_fd;	/* file descriptor associated with directory */
	long	__dd_loc;	/* offset in current buffer */
	long	__dd_size;	/* amount of data returned */
	char	*__dd_buf;	/* data buffer */
	int	__dd_len;	/* size of data buffer */
	long	__dd_seek;	/* magic cookie returned */
	long	__dd_rewind;	/* magic cookie for rewinding */
	int	__dd_flags;	/* flags for readdir */
	__darwin_pthread_mutex_t __dd_lock; /* for thread locking */
	struct _telldir *__dd_td; /* telldir position recording */
} DIR;

struct dirent __DARWIN_STRUCT_DIRENTRY;
#define __DARWIN_STRUCT_DIRENTRY { \
	__uint64_t  d_ino;      /* file number of entry */ \
	__uint64_t  d_seekoff;  /* seek offset (optional, used by servers) */ \
	__uint16_t  d_reclen;   /* length of this record */ \
	__uint16_t  d_namlen;   /* length of string in d_name */ \
	__uint8_t   d_type;     /* file type, see below */ \
	char      d_name[__DARWIN_MAXPATHLEN]; /* entry name (up to MAXPATHLEN bytes) */ \
}
#endif
/*
 * list files in directory called dirname
 */
void do_ls(char dirname[]){
	DIR *dir_ptr;		   /*dir file*/
	struct dirent *direntp;/*each entry*/

	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr,"cannot open %s\n",dirname);
	else{
		while((direntp = readdir(dir_ptr)) != NULL){
			do_stat(direntp->d_name);
		}
		closedir(dir_ptr);
	}
}

void do_stat(char *filename){
//printf("do_stat hhhhhhhhh\n");
	struct stat info;
	if(stat(filename,&info) == -1)
		perror(filename);
	else
		show_file_info(filename,&info);
}

void show_file_info(char *filename,struct stat *info_p){
	char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
	void mode_to_letters();
	char modestr[11];

	mode_to_letters(info_p->st_mode,modestr);

	printf("%s",modestr);
	printf("%4d",(int)info_p->st_nlink);
	printf("%8s",uid_to_name(info_p->st_uid));/*左对齐右补空格*/
	printf("%8s",gid_to_name(info_p->st_gid));
	printf("%8ld",(long)info_p->st_size);
	printf("%.12s",4+ctime(&info_p->st_mtime));
	printf("%s\n",filename);
}

void mode_to_letters(int mode,char str[]){
    strcpy(str,"----------")/*10 * '-'*/;
    if(S_ISDIR(mode)) str[0] = 'd';     /*directory*/
    if(S_ISCHR(mode)) str[0] = 'c';     /*char dev*/
    if(S_ISBLK(mode)) str[0] = 'b';     /*block dev:disk dev*/

    if(mode & S_IRUSR) str[1] = 'r';    /*3 bits for user*/
    if(mode & S_IWUSR) str[2] = 'w';
    if(mode & S_IXUSR) str[3] = 'x';

    if(mode & S_IRGRP) str[4] = 'r';    /*3 bits for group*/
    if(mode & S_IWGRP) str[5] = 'w';
    if(mode & S_IXGRP) str[6] = 'x';

    if(mode & S_IROTH) str[7] = 'r';    /*3 bits for other*/
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';
}

#include<pwd.h>
/*get info from /etc/passwd*/
char *uid_to_name(uid_t uid){/*uid_t:unsigned int*/
	//hhhhhhhh
	//struct passwd *getpwuid();
	struct	passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if( (pw_ptr = getpwuid(uid) ) == NULL){
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

#include<grp.h>
/*get info from /etc/group*/
char *gid_to_name(gid_t gid){
	struct group *grp_ptr,*getgrgid();
	static char numstr[10];

	if( (grp_ptr = getgrgid(gid) ) == NULL ){
		sprintf(numstr,"%d",gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
