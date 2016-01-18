# ls
## ls1.c
主要步骤:

```c
DIR dir = opendir(const char *)
readdir(dir)
printf(dirent->d_name)
closedir(dir)

```

## ls2.c

- 不仅仅显示文件名，同时也可以显示出文件的属性，文件的属性信息可以通过stat函数获得。

```java
.
..
a.out
fileinfo.c
ls1.c
ls2.c
README.md
```
