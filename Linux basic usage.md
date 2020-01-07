# Linux basic usage

以CentOS 8为例，其它发行版会有区别。


### 输入输出重定向\管道
```bash
command < file    # 以file的内容作为command的标准输入
command > file    # 将command的标准输出存入file
command >> file    # 将command的标准输出追加到file
command &>> file    # 将command的标准输出和错位输出追加到file
command 2> file    # 将command的错误输出存入file
command 2>> file    # 将command的错误输入追加到file

command | command    # 管道

# 通配符
*    # 零个或多个字符
?    # 单个字符
[0-9] [a-z]    # 范围内的单个字符
```

### 环境变量
```bash
$HOME    # 主目录
$SHELL    # shell解释器
$PATH    # shell解释器搜索用户命令的目录
$LANG    # 语言
$MAIL    # 邮件保存路径
$EDITOR    # 文本编辑器
```

### 常用系统工作命令
```bash
$ echo [$var_name]
$ date "+%Y-%m-%d %H:%M:%S"
$ reboot
$ poweroff
$ wget [url]
$ ps -aux    # 进程状态
$ top    # 动态监视进程活动和负载信息
$ pidof [service_name]
$ kill [pid]
$ killall [service_name]
```

### 系统状态检测命令
```bash
$ ifconfig    # 网卡配置与网络状态
$ netstat    # 查看各端口的开放情况
$ uname -a    # 系统内核、版本等信息
$ uptime    # 系统负载
$ free -h    # 内存使用
$ who    # 当前登入用户信息
$ last    # 所有的登录信息
$ history    # 执行过的命令
```

### 工作目录切换命令
```bash
$ pwd    # 当前所在目录
$ cd [directory]
$ ls -al
$ tree
```

### 文本文件编辑命令
```bash
$ cat -n [file_name]
$ more [file_name]
$ head -n 20 [file_name]
$ tail -n 20 [file_name]
$ wc -lwc [file_name]    # 统计文本的行数、字数、字节数
$ stat [file_name]    # 查看文件的存储信息和创建修改等时间
$ diff --brief [file_name] [another_file_name]    # 是否相同
$ diff -c [file_name] [another_file_name]    # 不同之处
```

### 文件目录管理命令
```bash
$ touch [new_file]
$ touch -d [time_string] [file_name]    # 设置文件的读取时间和修改时间
$ mkdir [directory]
$ cp
$ mv
$ rm
$ dd if=/dev/cdrom of=system_setup.iso    # 块复制，可以用来制作光盘镜像
$ file [file_name]    # 查看文件类型
```

### 打包压缩与搜索命令
```bash
$ tar -czvf [file_name.tar.gz] [files]    # 创建压缩包
$ tar -cjvf [file_name.tar.bz2] [files]    # 创建压缩包
$ tar -xzvf [file_name.tar.gz]    # 解压缩
$ tar -xjvf [file_name.tar.bz2]    # 解压缩
$ grep -n [file_name]
$ find [directory] -name "keyword*" -print
```

### 用户权限管理命令
```bash
$ id [user_name]    # 查看用户信息
$ useradd [new_user] -d [home_directory]
$ groupadd [group_name]
$ usermod [username]    # 修改用户信息
$ passwd    # 修改自己的密码
$ passwd [user_name]    # 修改某个用户的密码
$ userdel [username]
$ su - [another_user]    # 建议带-，完全切换
$ sudo command
$ chmod [a+x] [file_name]
$ chown -R [user] [file_name]
```

### 磁盘设备管理命令
```bash
$ mount /dev/sdb2 /data
$ umount /dev/sdb2
$ fdisk /dev/sdb    # 分区后出现sdb1
$ file /dev/sdb1
$ mkfs.xfs /dev/sdb1    # 创建文件系统
$ mkdir /data
$ mount /dev/sdb1 /data
$ du -sh /data    # 查看占用情况
$ ln -s [source_file] [target_file]    # 建立软链接
```

### 远程访问命令
```bash
$ ssh root@ip
$ scp [local_file] [root@ip:directory]

# 如果没有ftp，可以安装ftp
$ sudo yum install vsftpd
$ sudo firewall-cmd --zone=public add-port=21/tcp --permanent
$ sudo firewall-cmd --zone=public add-service=ftp --permanent
$ sudo firewall-cmd --reload
$ sudo systemctl start vsftpd && systemctl enable vsftpd
# 此时可以使用除root外的linux账户登录
```