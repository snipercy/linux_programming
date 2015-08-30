#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

void do_ls(char[]);

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
		fprintf(stderr,"ls1:cannot open %s\n",dirname);
	else{
		while((direntp = readdir(dir_ptr)) != NULL){
			printf("%s\n",direntp->d_name);
		}
		closedir(dir_ptr);
	}
}
