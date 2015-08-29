# cp
## version 1
- 打开源文件；int in_fd = open(char* filename,mode_t mode)
- 创建新文件，若文件不存在则创建，否则将它内容情况，长度设为0；   
(int out_fd = create(char* filename, mode_t mode);
- 读源文件；
- 写入新文件，write函数返回实际写入的字节数
实际写入的字节数会少于所要求的原因：
-- 1、系统对文件的最大尺寸有限制
-- 2、磁盘接近满了

## version 2 提高文件I/O效率的方法：使用缓存
###  应用缓存技术：由于系统调用慢，一次读入大量的数据放入缓冲区，减少系统调用
运行环境的切换开销大，比如：超人-普通人之间切换：换衣服开销
### 系统缓存技术
I/O比系统调用还慢，所以需要缓存技术提高对磁盘访问速度。当进程所要求的数据块不在内核缓冲区时，内核会把相应的数据块加入到请求数据队列表中，然后把该进程挂起，接着为其他进程服务。
一段时间后，内核把相应数据块从磁盘读到内核缓冲区，然后再把数据复制到进程缓冲区中，最后唤醒被挂起的进程。
read把数据从内核缓冲区复制到进程缓冲区，write把数据从进程过程区写到内核缓冲区。
#### 应用内核缓冲技术导致的结果
- 提高磁盘I/O效率
- 优化磁盘的写操作
- 需要及时地将缓冲数据写入磁盘
# ls 
## ls1.c version1.0
- opendir(const char*)-->readdir(DIR)-->printf(dirent->d_name)-->closedir(DIR);
## ls2.c :version2.0 show file status
- 用stat得到文件信息


