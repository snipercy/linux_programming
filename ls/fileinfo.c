/*
 * use stat() to obtain and print file properties
 * struct:stat
 */
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

void show_stat_info(char*,struct stat *);
void mode_to_letters(int mode, char* str);

int main(int argc, char* argv[]){
	struct stat info;
	if(argc > 1){
		if(stat(argv[1],&info) != -1){
			show_stat_info(argv[1],&info);
			return 0;
		}
		else
			perror(argv[1]);
	}
	return 1;
}

/*
 * show some info from stat in a "name = value" fomat
 */
void show_stat_info(char* fname,struct stat* buf){
    char modestr[11];
    mode_to_letters(buf->st_mode,modestr);
    printf("    mode: %s\n",modestr);    /*int mode -> str mode*/
	printf("    links: %d\n",buf->st_nlink);	/*links*/
	printf("    user: %d\n",buf->st_uid);	/*userid*/
	printf("    group: %d\n",buf->st_gid);	/*userid*/
	printf("    size: %lld\n",buf->st_size);	/*file size*/
	printf("    modtime: %ld\n",buf->st_mtime);	/*modified*/
	printf("    name: %s\n",fname);	/*filename*/
}

void mode_to_letters(int mode,char* str){
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

#if 0
struct stat {
	dev_t	 	st_dev;		/* [XSI] ID of device containing file */
	ino_t	  	st_ino;		/* [XSI] File serial number */
	mode_t	 	st_mode;	/* [XSI] Mode of file (see below) */
	nlink_t		st_nlink;	/* [XSI] Number of hard links */
	uid_t		st_uid;		/* [XSI] User ID of the file */
	gid_t		st_gid;		/* [XSI] Group ID of the file */
	dev_t		st_rdev;	/* [XSI] Device ID */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
	struct	timespec st_atimespec;	/* time of last access */
	struct	timespec st_mtimespec;	/* time of last data modification */
	struct	timespec st_ctimespec;	/* time of last status change */
#else
	time_t		st_atime;	/* [XSI] Time of last access */
	long		st_atimensec;	/* nsec of last access */
	time_t		st_mtime;	/* [XSI] Last data modification time */
	long		st_mtimensec;	/* last data modification nsec */
	time_t		st_ctime;	/* [XSI] Time of last status change */
	long		st_ctimensec;	/* nsec of last status change */
#endif
	off_t		st_size;	/* [XSI] file size, in bytes */
	blkcnt_t	st_blocks;	/* [XSI] blocks allocated for file */
	blksize_t	st_blksize;	/* [XSI] optimal blocksize for I/O */
	__uint32_t	st_flags;	/* user defined flags for file */
	__uint32_t	st_gen;		/* file generation number */
	__int32_t	st_lspare;	/* RESERVED: DO NOT USE! */
	__int64_t	st_qspare[2];	/* RESERVED: DO NOT USE! */
};
#endif

