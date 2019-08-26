# Linux Command

```bash
# help
$ whatis command
$ info command
$ man command
$ which command # return the path of this command

# directory
$ mkdir dirname
$ rm filename
$ rm -rf dirname
$ mv file1 file2 # move file or change name
$ cp file1 file2
$ cp -r dir1 dir2

# file management
$ cd dirname # .. up; - last; ~ /home/user
$ pwd
$ ls 
$ ls -lrt # order by time
$ tree

# file read
$ find /home -name "*.txt"
$ cat filename && more filename && tail filename
$ diff file1 file2
$ grep keywords

$ tar -zcvf file.tar.gz /path/of/files
$ tar -xvf file.tar.gz

# disk management
$ du -sh# disk usage
$ df -h
$ fdisk # 分区
$ mkfs # make filesystem 
$ mkfs.ext3 /dec/sda1
$ mount /dec/sda1 /data

# user management
$ chmod a+x myscript
$ chown -R username userdir/
$ useradd && userdel && usermod
$ passwd
$ groupadd && groupdel && groupmod

# processing management
$ ps -ef && ps -ajx
$ kill -9 pid
$ jobs && fg && bg
$ pstree -p # 更优雅的进程树
$ top or htop

# network
$ ifconfig 
$ netstat
$ route
$ ping IP
$ traceroute IP
$ host doman
$ host IP

$ ssh id@host
$ sftp id@host # get file, put file
$ scp localpath id@host:path
$ wget url

$ shutdown -h now
$ reboot
$ date
$ uptime # 系统已经运行的时间
$ uname

$ > # 覆盖
$ >> # 添加
$ | # pipeline
$ ; # one by one
$ && # 前命令成功，执行后命令
$ || # 前命令失败，执行后命令

$ history # print the history command
```