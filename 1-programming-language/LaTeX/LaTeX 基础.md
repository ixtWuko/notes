# LaTeX 基础

推荐的发行版是TeXlive，不推荐CTeX。对中文的支持使用CTeX宏包，这里发行版CTeX和CTeX宏包是两个不同的东西。

一个tex文件的基本结构如下：

```tex
\documentclass[utf8]{ctexart}
%导言部分
\begin{document}
%正文部分
\end{document}
```

文档类主要有三种： `article` , `report` , `book` ，CTeX中对应的是 `ctexart` , `ctexrep` , `ctexbook` 。

以下是常用的选项，如上述的 `utf8`  

![](https://static.notion-static.com/69475630-e294-4c77-9b8e-a95247c50655/2018-02-13_153203.jpg)

# 导言部分

## 声明标题、作者、日期

```tex
\title{文章标题}
\author{作者}
\date{\today}
%在正文区使用如下可以渲染以上内容
\maketitle
```

## 导入宏包

```tex
\usepackage{amsmath}
```

## 设置版面

```tex
%设置页边距，推荐使用宏包geometry
\geometry{papersize={20cm, 15cm}}
\geometry{left=2.5cm, right=2.5cm, top=3cm, bottom=2cm}

%设置页眉页脚，推荐使用宏包fancyhdr
\pagestyle{fancy}
\lhead{\author} %及\chead, \rhead
\lfoot{\thepage} %及\cfoot, \rfoot
\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\headwidth}{\textwidth}
\renewcommand{footrulewidth}{0pt}

%设置行间距，推荐使用宏包setspace
\singlespacing %1倍行距
\onehalfspacing %1.5倍行距
\doublespacing %2倍行距

%设置段间距，推荐使用宏包parskip
\addtolength{\parskip}{.4em}
```

# 正文部分

## 摘要，仅限article和report

```tex
\begin{abstract}
...
\end{abstract}
```

## 文章结构

```tex
\frontmatter %开始以罗马数字表示页码
\mainmatter %开始使用阿拉伯数字表示页码

\setcounter{tocdepth}{2} %设置目录深度
\tableofcontents %目录可能需要编译两次才能得到正确的结构

\part{part}
\chapter{chapter} %article中没有这一个
\section{section}
\subsection{subsection}
\subsubsection{subsubsection}
\paragraph{}
\subparagraph{}
%除了paragraph、subparagraph，其它的都会自动编号
%如果不想编号，可以在{左侧加一个*

\appendix %文章附录的开始
\backmatter %参考文献
```

## 符号

```tex
%需要转义的字符
\# \$ \^ \& \_ \{ \} \~ \textbackslash \%

%使用~输入空格。

%‘-’的使用
computer-aided %一个'-'用作连字符或数学负号
1840--1912 %两个'-'用于连接数字
你好--- %三个'-'用作破折号

%LaTeX用不同的符号分别表示左引号和右引号. 左引号用`表示(键盘左上角, Tab 键上面), 右引号用'表示(平时输引号的那个键). 双引号用过输入两个引号来得到.

%计数器--用于页码、列表等 (counter是变量名）
\arabic{counter} %1,2,3,...
\alph{counter} %a,b,c,...
\Alph{counter} %A,B,C,...
\roman{counter} %i,ii,iii,...
\Roman{counter} %I,II,III,...
```

## 格式

```tex
%英文文章中括号, 以及引用符号(如[1], [2]等)要与前一个词留有空格, 而中文文章通常则不同.

%段落对齐方式
\begin{flushleft}...\end{flushleft} %左对齐
\begin{flushright}...\end{flushright} %右对齐
\begin{center}...\end{center} %居中对齐

%字体
\mathrm{}
\mathbf{} %粗体
\mathbb{} %空心

%格式
\emph{emphasis} %斜体
\uline{underline} %下划线
\uwave{waveline} %波浪线
\sout{strike-out} %删除线

%盒子
\mbox %无边框
\fbox %有边框

%脚注
正文内容\footnote{脚注内容}

\newline %换行，使用 \\ 或者 \newline
\newpage %换页
```

## 引用

```tex
\begin{quote}...\end{quote} %引文两端都缩进
\begin{quotation}...\end{quotation} %引文两端都缩进，且首行增加缩进
\begin{verse}...\end{verse} %引文两端都缩进，且第二行起增加缩进
```

## 插入图片

```tex
%推荐使用宏包graphicx
\includegraphics{image.png}
\includegraphics[width=.8\textwidth]{image.png}
```

## 列表

```tex
%无序列表
\begin{itemize} \item x \item y \end{itemize}
%有序列表
\begin{enumerate} \item x \item y \end{enumerate}
%描述列表
\begin{description} \item[x] x \item[y] y \end{description}
%可以自定义列表的符号表示
\renewcommand{\labelitemi}{-} % - x - y
\renewcommand{\theenumi}{\alph{enumi}} % a x b y
```

## 表格

```tex
\begin{tabular}{|l|c|r|} %列的数量和对齐方式
 \hline
操作系统& 发行版& 编辑器\\
 \hline
Windows & MikTeX & TexMakerX \\
 \hline
Unix/Linux & teTeX & Kile \\
 \hline
Mac OS & MacTeX & TeXShop \\
 \hline
通用& TeX Live & TeXworks \\
 \hline
\end{tabular}
```

## 浮动体

```tex
%使用figure环境或table环境
\begin{figure}[htbp] %htbp指浮动体位置here,top,bottom,float page
\centering %插图居中
\includegraphics{image.png}
\caption{图片1}
\label{fig:myphoto}
\end{figure}
```

## 公式

```tex
%需要使用宏包amsmath
%行内公式使用$...$
这是一个行内公式$a=b+c$
%行间公式使用\[...\]或displaymath环境
这是一个行间公式 \[ a=b+c \]
%行间公式可以使用
\begin{equation}...\end{equation} %会自动编号
```

## 一个基础的LaTeX模板
```tex
\documentclass[UTF8, a4paper, notitlepage]{ctexart} % article
% ====================
% 导言区
\title{Article Title}
\author{Me}
\date{\today}

% ==== package including ====
\usepackage{fontspec} % 字体
\usepackage{geometry} % 页边距
\usepackage{fancyhdr} % 页眉页脚
\usepackage{setspace} % 行距
\usepackage{parskip} % 段间距
\usepackage{indentfirst} % 首行缩进

\usepackage{amsmath, amsfonts, amssymb} % 对数学元素的基本支持
\usepackage{bm} % 处理表示矩阵和向量的加粗符号，主要使用 bf-粗直体、bm-粗斜体
\usepackage{graphicx} % 图表
\usepackage{array} % 扩展的表格
\usepackage{diagbox} % 斜线表头
\usepackage{multirow} % 跨列合并单元格
\usepackage{listings} % 处理代码
\usepackage{cite} % 引用
\usepackage{gbt7714} %处理中英文文献的格式不同的问题，详见https://github.com/CTeX-org/gbt7714-bibtex-style
\usepackage{color} % 使用颜色名字指代颜色

% ==== setting ====
% == fontspec ==
%\setmainfont{Source Serif Pro}
%\setsansfont{Source Sans Pro}
%\setmonofont{Source Code Pro}
%\setCJKmainfont{Source Han Serif}
%\setCJKsansfont{Source Han Sans}
%\setCJKmonofont{Source Han Sans}
%\setCJKfamilyfont{boldsong}{Source Han Serif Heavy}
% == geometry ==
%\geometry{papersize={20cm, 15cm}} % usually not need
\geometry{left=2.5cm, right=2.5cm, top=3cm, bottom=2.5cm}
% == fancyhdr ==
\pagestyle{fancy}
\lhead{\author}
\chead{\title}
\rhead{}
\cfoot{\thepage} % page number
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}
% == setspace ==
\onehalfspacing
% == parskip ==
\addtolength{\parskip}{.4em}
% == indentfirst ==
\setlength{\parindent}{2.45em}

% == listings ==
\definecolor{mygreen}{rgb}{.0, .6, .0}
\definecolor{mygray}{rgb}{.5, .5, .5}
\definecolor{mymauve}{rgb}{.58, .0, .82}
\lstset{
    % 设置程序语言、行号，以及它们的字体
    language=,
    basicstyle=\footnotesize\ttfamily, % 这里的 ttfamily 字体设置在前面的英文字体设置中的 monofont
    numbers=none, % 可以是 left
    numberstyle=\tiny\ttfamily,
    breaklines=true,
    tabsize=4,
    % 设置边框和颜色，这里用到了 color 库
    frame=single,
    rulecolor=\color{black},
    backgroundcolor=\color{white},
    commentstyle=\color{mygreen},
    stringstyle=\color{mymauve},
    % keywordstyle=\color{blue},
}

% ====================
% 正文区
\begin{document}
\maketitle
\begin{abstract} \textbf{Key words:} \end{abstract} % 摘要
\frontmatter % 罗马字页码
\setcounter{tocdepth}{2}
\tableofcontents

% struct of the document 
\section*{section name} % 使用 * 取消自动编码
\subsection{subsection name}
\subsubsection{subsubsection name}
\paragraph{paragraph name}
\subparagraph{subparagraph name}
\par % new paragraph
\chapter{chapter name} % only exits in report/ctexrep
\part{part name} % only exits in boot/ctexbook
\appendix
\input{tex filename}
\newpage
\renewcommand\refname{参考文献}
\bibligraphy{bib filename}

\end{document}

% ====================
% math
This is an inline math symbol $\alpha$.
$$ display math symbol $$ % or using \begin ... \end

% graph
\includegraphics[width = .8\textwidth]{graph filename} % 甚至可以使用pdf格式的图形

% table: tablular, tabbing, array.
\begin{tablular}{|l|c|r|} % >{\columncolor[gray]{.9}}c 设置某一列的颜色
\toprule
head a & head b & head c \\
\midrule
element a & element b & element c \\
element d & element e & element f \\
\bottomrule
% 以上为一个基本的三线表的结构
\hline
\diagbox{head1}{head2}{head3} \\ % 斜线表头
\multicolumn{3}{|c|}{item} \\ % 在行方向上合并3个单元格为1个
\multirow{2}*{{item}} \\ % 在列方向上合并2个单元格为1个
\rowcolor[gray]{.9} item \\ % 设置某一行为灰色，后跟数字可以调节颜色深浅
\cellcolor[rgb]{.9, .8, .7}item \\ % 设置某一单元格的颜色
\hline
\end{tabular}

% float 控制图表或表格的浮动位置
\begin{figure}[htbp] % here, top, bottom, float page
    \centering
		\includegraphics{graph filename}
		\caption{graph description}
		\label{fig:firstphoto}
\end{figure}
\begin{table}
    \centering
    \caption{table description}
    \begin{tabular} ... \end{tabular}
\end{table}

% listings
\begin{lstlisting} items \end{lstlisting}

% cite
This is a cite of paper\cite{Author: Year}. % 需要Bib的支持

% footnote
This is a footnote\footnote{footnote contents}.
```