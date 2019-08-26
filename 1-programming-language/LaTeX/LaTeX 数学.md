# LaTeX 公式

```tex
$$ a_i, b^n, \sqrt{a^2+b^2}, \frac{n}{m} $$
$$ \pm, \times, \div, \cdot, \cap, \cup $$ % pm = plus and minus
$$ \geq, \leq, \neq, \approx, \equiv $$
$$ \sum, \prod, \lim, \int, \iint, \iiint, \idotsint $$
$$ \big(, \Big{, \bigg}, \Bigg), \lvert, \rvert, \lVert, \rVert $$
$$ \dots, \cdots, \vdots, \ddots $$

% matrix
\begin{pmatrix} a&b\\c&d \end{pmatrix} % ( )
\begin{bmatrix} a&b\\c&d \end{bmatrix} % [ ]
\begin{Bmatrix} a&b\\c&d \end{Bmatrix} % { }
\begin{vmatrix} a&b\\c&d \end{vmatrix} % | |
\begin{Vmatrix} a&b\\c&d \end{Vmatrix} % || ||
\begin{smallmatrix} a&b\\c&d \end{smallmatrix} % inline matrix

% equation
\begin{multline} x=a+b+ \\ c+d \end{multline} % unaligned
\begin{aligned} x= &a+b+ \\ &c+d \end{aligned} % aligned by &
\begin{gather} x=a+b \\ y=c+c \end{gather} % unaligned equations
\begin{align} x &= a+b \\ y &= c+c \end{align} % aligned equations
\begin{cases} -x,\quad x \leq 0 \\ x,\quad x>0 \end{cases} % piecewise function
```

- 开方 `\sqrt[n]{a}`
- `\frac` 构建分式，在行内公式中小一些，在行间公式中大一些；
`\dfrac` 在行内公式中会大一些， `\tfrac` 在行间公式中会小一些。
- 集合等中的竖线 `|` 使用的是 `\mid` 命令。
- 优化问题中的 `*` 使用的是 `\star` 命令。
- 数学模式下输入文本的方式 `\text{} \mbox` 。
- 带方框的公式可以使用 `\boxed` ，和 `\fbox` 效果类似。
- 不同的省略号 `\ldots, \cdots, \vdots, \ddots` ，文字中推荐使用 `\ldots` ，数学中推荐使用 `\cdots` 。
- 数学模式下的间隔控制 `\, \: \; \quad \qquad \!` 。

  ![](https://static.notion-static.com/0a0055f0-cf48-4e9d-9f83-9dd47b2f54d8/2018-02-16_203042.jpg)

- `\sum \prod \lim \int \iint \iiint` ，可以用 `\limits` 和 `\nolimits` 来指定是否压缩上下标。微分符号的 `d` 可以使用 `\ud` 。
- 组合数使用 `\binom{}{}` 命令。
- 向量使用 `\vec` 来放置上面的箭头，而矩阵等的粗体，可以使用 `bm` 宏包的 `\bm` 命令。
- amsmath中推荐使用 `\lvert, \rvert, \lVert, \rVert` 代替左右的 `|` ；推荐使用 `\big(, \Big(, \bigg(, \Bigg(` 来实现不同大小的括号 ，不推荐 `\left, \right` 。
- 矩阵环境 `array` ，使用 `&` 分隔元素。除此之外还有 `pmatrix bmatrix Bmatrix vmatrix Vmatrix` ，对应小括号、中括号、大括号、竖线、双竖线。 `smallmatrix` 用于行内的矩阵。
- 空心的字体使用 `\mathbb{}` ，需要 `amssymb` 宏包。
- 无须对齐的长公式使用 `multline` 环境，需要对齐的长公式使用 `split` 环境。无须对齐的公式组使用 `gather`  环境，需要对齐的公式组使用 `align`  环境。分支公式使用 `cases` 环境。
- 定义、定理、引理等

  ```latex
  \newtheorem{name}[counter]{text}[section]`
  \begin{name}[text]
  This is my interesting theorem
  \end{name}
  ```

- 证明使用 `proof` 环境。
