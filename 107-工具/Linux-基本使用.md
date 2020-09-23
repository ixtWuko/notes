# Linux 基本使用

### 常用站点
国内镜像
* [阿里云](https://developer.aliyun.com/mirror/)
* [中科大镜像](http://mirrors.ustc.edu.cn/)
* [清华Tuna](https://mirrors.tuna.tsinghua.edu.cn/)

Linux 命令查询：https://man.linuxde.net/

### 最常用的命令
目录： `\` 根目录， `.` 当前目录，`..` 上级目录，`-` 上一个目录
* pwd, cd, ls, tree
* mkdir, rmdir, touch, mv, cp, rm
* file, cat, vim, diff,  head, tail, more, less
* wget, curl
* reboot, shutdown -h now
* history

### 文件权限
文件权限用于控制 user, group, others 的读、写、执行权限，可以用 `rwxrwxrwx` 的形式表示，或对 `rwx` 分别赋值 4,2,1，这样可以用三个数字表示。

修改权限：
```bash
$ chmod 754 filename
```

### 文件查找
```bash
# find <dir> <type> <str>
$ find . -name "*.cc"
$ find . -atime -2     # 过去2天修改过的文件
$ find . -size +1000c  # 根据大小查找

$ which command
$ whereis command
$ whatis command    # 帮助
```

### 查看文件属性
```bash
$ df -h           # 查看磁盘空间
$ du -h filename  # 查看文件的空间占用
```

### 压缩文件
```bash
# 打包，参数 c 表示打包
$ tar -cvfz [file_name.tar.gz] [files]
$ tar -cvfj [file_name.tar.bz2] [files]
# 解包，参数 x 表示解包
$ tar -xvfz [file_name.tar.gz]
$ tar -xvfj [file_name.tar.bz2]
```

### 进程管理
```bash
$ ps aux | grep keyword
$ kill -9 <pid>

$ top
```

### 查看系统状态
```bash
$ free  # 内存使用
```