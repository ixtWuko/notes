# Linux-or-WSL-环境搭建

## 一 系统设置

### Ubuntu 系统安装

临时的无需大规模计算的任务场景建议使用虚拟机或 WSL。

对于直接安装，这里简要叙述 Ubuntu + Windows 的安装方法，安装顺序为 Windows > Ubuntu，在支持 UEFI 的 PC 上可行。对于直接安装 Ubuntu 单系统的，也可以参考此方法。

1. 下载 Ubuntu 镜像并制作 U 盘安装盘。可使用免费开源的软件 Ventoy，无需烧录即可，但实际测试可能会发生BUG。对于想要烧录 U 盘，在 Windows 下可以使用 Rufus 等软件将镜像烧录到 U 盘，在 Ubuntu 下可使用如下方法：
   ```bash
   # find your USB flash memory's path
   $ sudo fdisk -l
   # write the iso file into USB flash memory
   $ sudo dd in=/path/to/image.iso of=/dev/sdx
   ```
2. 为 Ubuntu 准备磁盘空间。在 Windows 下使用系统自带的磁盘管理工具，为 Ubuntu 的安装整理出一整块的磁盘空间。
3. 重启并设置 U 盘为启动项，开始 Ubuntu 系统的安装。建议的分区方式如下，主分区与 home 分区的大小可以根据实际情况调整，主分区中主要占据空间的是各类软件，home 分区中占据空间的是个人软件和数据。
   ```bash
   /      ext4  150G
   swap   swap  #depend on the size of memary
   /boot  ext4  512M
   /home  ext4  #remain
   # 8G内存可以划分4G的swap，16G内存可以划分其1/3大小的swap
   # 根据实际需要，可以将一些可能会很大的文件夹单独分区，如
   /var  ext4
   /usr  ext4
   ```
4. 选择不同的系统引导方式，如果希望开机直接引导 windows 而不是出现选择系统的菜单，将 Ubuntu 的引导设置到 boot 分区。

注意：删除 Ubuntu 时，不能直接删除分区，直接删除会导致错误的引导项。如果引导设置在 boot 分区，除删除所有的 ubuntu 分区外，还需删除 esp 分区中的 Ubuntu 文件夹，以及使用 bootice 删除 Ubuntu 的启动项。**需要注意的是，这些都是非常危险的操作。**

### 更换软件源并更新

1. 为 Ubuntu 设置国内源：
   在安装桌面系统的 Ubuntu 中，可以在“软件与更新”应用中找到修改源的设置项，建议使用国内的镜像源，速度快。或通过直接修改文件的形式。
   ```bash
   # backup and modify source.list
   $ cp /etc/apt/source.list /etc/apt/source.list.backup
   $ sudo vim /etc/apt/source.list
   # add aliyun source
   :0,$ s/cn.archive.ubuntu.com/mirrors.aliyun.com/
   :wq
   ```
2. 更新系统
   ```bash
   $ sudo apt update && sudo apt upgrade -y
   ```

### 更改系统时间

1. 在安装 Ubuntu + Windows 后，可能会出现某个系统的时间不对的情况，是由于 Ubuntu 将机器时间作为 UTC 时间，而 Windows 将机器时间作为本地时间导致的，可以手动进行如下修改并重启。
   ```bash
   $ timedatectl set-local-rtc 1
   ```

### 安装其它语言

1. 以中文语言包为例。
   ```bash
   $ sudo apt install language-pack-zh-hans language-pack-zh-hant
   ```
   为开发方便，在安装 Ubuntu 系统时可以选择英文作为默认语言，之后再安装中文，设置界面等元素使用中文而保持 `~` 中文件夹均为英文名。

### 安装 ssh

1. 使用 openssh
   ```bash
   $ apt install openssh-server
   $ service ssh start
   ```

### 替换 Shell

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
   # open a web server for fish's config
   $ fish_config
   ```

### 安装输入法

1. 推荐使用 rime 输入法
   ```bash
   $ apt install ibus-rime
   ```
   在设置 -> 区域与语言 -> 输入源 -> +，选择 rime 即可。

### 处理数据盘

1. Ubuntu 无法像 Windows 一样自动挂载所有的数据盘，尤其是在服务器上使用ubuntu时，常需要自己挂载数据盘。数据盘挂载方法如下：
   ```bash
   # show the device and find the data disk, for example /dev/vdb
   $ fdisk -l
   # partition
   $ fdisk /dev/vdb
   # formating
   $ mkfs.ext4 /dev/vdb1
   # add the partition info into system
   $ echo /dev/vdb1 /data ext4 defaults 0 0 >> /etc/fstab # you can change /data to other file such like /mnt
   # mount
   $ mount -a
   ```

### 免密登录

1. 远程服务器的密码登录存在被暴力破解的风险，即使设置复杂的密码，服务器仍会被频繁尝试登录造成问题。对于远程服务器建立使用私钥登录。
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
   $ sudo apt install openssh-server
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

1. Ubuntu 的版本优先选择 LTS 即长期支持的版本，系统安装多年后需要更新大版本时，可以使用如下命令更新。
   ```bash
   $ do-release-upgrade
   # if you want to upgrade to the latest non-LTS develoment release,
   # set Prompt=normal in /etc/update-manager/release-upgrades.
   ```

## 二 编译环境

这里的编译环境主要是以 Cpp 和 Python 为主。

### Cpp 环境

1. 安装一些常用的软件

   ```bash
   # git, wget, curl, unzip, vim
   $ sudo apt install git wget curl unzip vim
   # gcc g++ make ... cmake clang
   $ sudo apt install build-essential cmake clang llvm
   ```

2. 安装 IDE 如 CLion(付费)，或者使用 Visual Studio Code + CMake/make。
3. 安装需要的第三方库

### Python 环境

1. 下载 Anaconda 并安装，推荐使用 conda 管理 package，当 conda 中没有某个 package 时，使用工作虚拟环境中的 pip 安装该 package，不推荐使用系统默认的 pip 安装 package。
2. 某些软件可能在编译过程中调用 python，可以为系统单独安装 python。
3. 安装 IDE，推荐 PyCharm。

## 三 其它软件

- WPS， FOXIT
- Team Viewer， VNC Viewer
- GoldenDict
- timeshift
- electron-SSR