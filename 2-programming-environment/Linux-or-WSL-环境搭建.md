# Linux or WSL 环境搭建

Created: Jun 03, 2019 10:49 AM

## 一 系统设置

### Ubuntu系统安装

无需大规模计算的任务场景建议使用虚拟机或WSL。

对于直接安装，这里简要叙述Ubuntu + Windows的安装方法，安装顺序为Windows > Ubuntu。

1. 下载Ubuntu镜像并制作U盘启动盘。在Windows下可以使用Rufus等软件将镜像刻录到U盘，在Ubuntu下使用如下方法：
    ```bash
    # find your USB flash memory's path
    $ sudo fdisk -l
    # write the iso file into USB flash memory
    $ sudo dd in=/path/to/image.iso of=/dev/sdx
    ```
2. 为Ubuntu准备磁盘空间。在Windows下使用系统自带的分区工具，为Ubuntu的安装整理出一整块的空间。
3. 重启并设置U盘为启动项，开始Ubuntu系统的安装。建议的分区方式如下，主分区与home分区的大小可以根据实际情况调整，主分区中占据空间的是软件，home分区中占据空间的个人软件和数据。
    ```bash
    /    ext4    150G
    /swap    swap    2048M
    /boot    ext4    200M
    /home    ext4    remain  
    ```
4. 选择不同的系统引导方式，如果不希望拖慢Windows的启动速度，将引导设置到boot分区。

### 更换软件源并更新

1. 为Ubuntu设置国内源：
    ```bash
    # backup and modify source.list
    $ cp /etc/apt/source.list /etc/apt/source.list.backup
    $ sudo vim /etc/apt/source.list
    # add aliyun source
    :0,$ s/archive.ubuntu.com/mirrors.aliyun.com/
    :wq
    ```
2. 更新系统
    ```bash
    $ sudo apt update && sudo apt upgrade -y
    ```

### 更改系统时间

1. 在安装Ubuntu + Windows后，可能会出现某个系统的时间不对的情况，是由于Ubuntu将机器时间作为UTC时间，而Windows将机器时间作为本地时间导致的，可以手动进行如下修改并重启。

    ```bash
    $ timedatectl set-local-rtc 1
    ```

### 安装其它语言

1. 以中文语言包为例。
    ```bash
    $ sudo apt install language-pack-zh-hans language-pack-zh-hant
    ```
### 安装ssh
1. 
    ```bash
    $ apt install openssh-server
    $ service ssh start
    ```
### 替换Shell

1. oh-my-zsh
    ```bash
    # install zsh and change default shell to zsh
    $ apt install zsh
    $ chsh -s /usr/bin/zsh
    # install oh-my-zsh
    $ sh -c "$(wget -O- https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
    # change theme of oh-my-zsh
    $ vim ~/.zshrc
    --------------------
    .zshrc
    ZSH_THEME="ys"
    --------------------
    $ source ~/.zshrc
    ```
2. fish shell
    ```bash
    # install fish and change default shell to fish
    $ apt install fish
    # open a web server for fish config
    $ fish_config
    ```

### 处理数据盘

1. Ubuntu无法像Windows一样自动挂载所有的数据盘，数据盘挂载方法如下：

    ```bash
    # show the device
    $ fdisk -l
    # find the data disk, for example /dev/vdb
    # partition
    $ fdisk /dev/vdb
    # formating
    $ mkfs.ext4 /dev/vdb1
    # add the partition info into system
    $ echo /dev/vdb1 /data ext4 defaults 0 0 >> /etc/fstab
    # you can change /data to other file such like /mnt
    # mount
    $ mount -a
    ```
### 免密登录

1. 远程服务器的密码登录存在被暴力破解的风险，即使设置复杂的密码，服务器仍会被频繁尝试登录而消耗计算资源。对于远程服务器建立使用私钥登录。

    ```bash
    # upload authorized_key file to the server.
    $ scp local/path/of/authorized_keys root@server_address:/root/.ssh/
    # modify the config
    $ sudo vim /etc/ssh/sshd_config
    --------------------
    # sshd_config
    RSAAuthentication yes
    PubkeyAuthentication yes
    AuthorizedKeysFile .ssh/authorized_keys
    --------------------
    # restart ssh service and test
    $ sudo service ssh restart
    # if system don't have ssh server, install it using
    # sudo apt install openssh-server
    # disable password login
    $ sudo vim /etc/ssh/sshd_config
    --------------------
    # sshd_config
    PasswordAuthentication no
    ChallengeResponseAuthentication no
    --------------------
    # restart ssh service and test
    $ sudo service ssh restart
    ```
### 跨大版本升级

1. Ubuntu的版本优先选择LTS即长期支持的版本，系统安装多年后需要更新大版时，可以使用如下命令更新。
    ```bash
    $ do-release-upgrade
    # if you want to upgrade to the latest non-LTS develoment release, 
    # set Prompt=normal in /etc/update-manager/release-upgrades.
    ```

## 二 编译环境

这里的编译环境主要是以Cpp和Python为主。

### Cpp 环境

1. 安装一些常用的软件
    ```bash
    # git, wget, curl, unzip, vim
    $ sudo apt install git wget curl unzip vim
    # gcc g++ make ... cmake clang
    $ sudo apt install build-essential cmake clang 
    # change default compiler to clang
    # run these command and choose the clang
    $ sudo update-alternatives --config cc
    $ sudo update-alternatives --config c++
    ```
2. 安装IDE如CLion(付费)，或者使用Visual Studio Code + CMake。
3. 安装需要的第三方库  

### Python环境

1. 下载Anaconda并安装，推荐使用conda管理package，当conda中没有某个package时，使用工作虚拟环境中的pip安装该package，不推荐使用系统默认的pip安装package。
2. 某些软件可能在编译过程中调用python，可以为系统单独安装python。 
3. 安装IDE，推荐PyCharm。

## 三 其它软件

- 在有桌面环境的Ubuntu中，SSR梯子推荐使用electron-SSR，订阅功能目前可能有Bug。
- 在有桌面环境的Ubuntu中，数据备份推荐使用timeshift。

### 参考内容

[Ubuntu 18.04 安装笔记](https://zhuanlan.zhihu.com/p/64151896)