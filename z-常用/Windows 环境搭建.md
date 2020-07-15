# Windows 环境搭建

## 开发环境

开发用的第三方库和某些软件可以放入 C 盘根目录下的 dev-env 文件夹中，便于维护开发环境和系统的 path。

## WSL

1. 控制面板 > 程序和功能 > 启用或关闭 Windows 功能 > 适用于 Linux 的 Windows 子系统。
2. 在应用商店搜索 Ubuntu 等发行版安装即可。
3. 其它操作与直接安装的 linux 发行版相同。

## 基础设施

- git
- Visual Studio Code
- Visual Studio Installer
- MobaXterm
- Windows terminal

## Cpp

1. 安装 IDE，Visual Studio Community
2. 安装 Mingw-w64（主要是提供标准库）
3. 安装 Clang（可以在 VS 中安装）
4. 安装 CMake

### Cpp Libraries

- [eigen]()
- [matplotlib-cpp](https://github.com/lava/matplotlib-cpp)：在 Cpp 中使用 matplotlib 绘图。

## Python

1. 在应用商店搜索 Python 安装即可。
2. 需要环境控制时，安装 Anaconda。
3. 可以安装 IDE，如 PyCharm。

### Python Modules

默认能够使用 conda 或 pip 安装，否则需做出说明。

- [rich](https://github.com/willmcgugan/rich)：在终端中渲染富文本，以及进度条、markdown、代码高亮、表格等。
- [gpustat](https://github.com/wookayin/gpustat)：代替 nvidia-smi，查看显卡状态的工具
- [scalene](https://github.com/emeryberger/scalene)：python 的 cpu 和 memary 分析工具。
- [faker](https://github.com/joke2k/faker)：python 中快速生成假的业务数据，用于进行测试等。

# Windows Software

以下为本人在 windows 下使用过的软件和工具，可根据需要选择。

## 常用软件

| 功能       | 软件                                                      |
| ---------- | --------------------------------------------------------- |
| 浏览器     | Chrome / new Microsoft Edge                               |
| 梯子       | ShadowsocksR / Clash                                      |
| 下载       | IDM / Mortix / uTorrent / 百度网盘                        |
| 解压缩     | BandZip / 7-Zip                                           |
| 快捷入口   | PowerToys/ Quicker                                        |
| 密码管理   | 1Password / Keepass XC                                    |
| 图影音查看 | XnView / Potplayer /QQ 音乐 / QuickLook                   |
| 图影音获取 | Snipaste / FastStone Capture / ScreenToGif / OBS Studio   |
| 电子书     | Calibre / Knotes / Book Bazaar Reader / Cover             |
| 联络       | 微信 / TIM / QQ / 腾讯会议                                |
| 工具       | 老司机锁屏 / Rime 输入法                                  |
| 游戏       | Steam / epic game / 暴雪战网                              |
| 远程连接   | Barrier / Teamviewer / VNC viewer T                       |
| 文件传输   | Feem / FileZilla                                          |
| 系统工具   | AIDA64 / Dism++ / DiskGenius / Diskinternals linux reader |
| U 盘烧录   | Ventoy / Rufus                                            |
| 系统拯救   | 微 PE / 优启通 / GParted                                  |
| 其它       | Office Tool Plus / 12306ByPass                            |
| 字体       | 思源宋体 / 思源黑体 / iosevka                             |

## 学习学术

| 功能 | 软件                                                       |
| ---- | ---------------------------------------------------------- |
| 笔记 | OneNote UWP/ EverNote/ Typora / Gridea                     |
| 日程 | Microsoft To Do/ 邮件/ 日历                                |
| 写作 | Onedrive/ Microsoft 365/ Adobe Acrobat/ SumatraPDF         |
| 学术 | Zotero/ TexLive/ 欧路词典                                  |
| 绘图 | Adobe Illustrator/ draw.io/yEd Graph Editor/ MeshLab/ Maya |
