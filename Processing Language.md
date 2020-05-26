# Processing Language

Processing 本身的代码并不重要，主要是利用他的框架编译运行 glsl 的 shader。

### 程序结构

```java
class Type {
attributes;
Type() {}
methods() {}
}

// initialize vars;
int g = 0;
float x = 0;
color c = color(0, 0, 0);
char c = 'C';
String message = "message";
className var = new className(...);
// setup
void setup() {
// things never change while program running
frameRate(30);
}
// draw
void draw() {
// running this function in every frame
}
```

### 数值

```java
random()
map(value, nowMin, nowMax, newMin, newMax)
```

### 数组

```java
int[] data; // 自定的对象也可以；二维数组也可以
data = new int[5];
data[0] = 15;
append(data, 20);
printArray(data)
shorten(data); // decrease one element at end
expend(data); // double
expend(data, 5); // +5

int[] data_backup = int[data.length];
arrayCopy(data, data_backup);

halve(data); // half value
```

### 向量类型

```java
PVector v = new PVertor(x, y);
v.add(other);
v.sub(other);
v.mult(2);
v.div(2);
v.mag(); // length
v.normalize();
v.limit(5); // make length = 5
v.heading(); // 朝向
v.dist(other); // distance
v.angleBetween(other);
v.dot(other);
v.cross(other);
```

### 基本图形

```java
// point
point(x, y);
// line
line(x1, y1, x2, y2);
// rectangle
rectMode(CENTER);
rect(x, y, width, height);
rectMode(CORNER);
rect(x, y, width, height);
rectMode(CORNERS);
rect(x1, y1, x2, y2);
// ellipse
ellipseMode(CENTER);
ellipse(x, y, width, height);
ellipseMode(CORNER);
ellipse(x, y, width, height);
ellipseMode(CORNERS);
ellipse(x1, y1, x2, y2);

// outline
stroke(255); // gray
stroke(r, g, b); //rgb
stroke(r, g, b, a); // rgb + alpha
strokeSize(4);
noStroke();
// interior
fill(255);
fill(r, g, b);
fill(r, g, b, a);
nofill(); // 透明的

pushMatrix(); // 保存当前得坐标系
// 移动和旋转都是对坐标系的操作
translate(width/2, height/2);
rotate(theta); // right is 0, left is PI
rotate(radians(120));
scale(2.0);
popMatrix(); // 恢复之前的坐标系
atan2(diffY, diffX); // 计算角度

// 3d shapes
box(length);
box(width, height, deepth);
sphere(radius);
// or using beginShape() endShape() vertex()

// 材质与光源
texture(img);
lights();
ambientLight(r, g, b);
directionalLight(r, g, b, x, y, z); // x,y,z is direction
spotLight(r, g, b,             // color
    width/2, height/2, 400,    // location
    0, 0, -1,                  // direction
    PI/4,                      // angle
    2);                        // concentration
pointLight(r, g, b, width/2, height/2, 400); // color and location

// 透视
prespective(fov, float(width)/float(height), cameraZ/2.0, cameraZ*2.0); // 前后视锥面
ortho(-width/2, width/2, -height/2, height/2); // 无透视
camera(width/2, height/2m (height/2) / tan(PI/6),    // eye position
    width/2, height/2,                               // center of scene
    0, 1, 0);                                        // upwards axis
```

### 文本

```java
// String Type
String message = "message";
message.charAt(3);
message.length();
message.toUpperCaes();
message.toLowerCase();
message.indexOf(substring);
message.substring(start, end);
message == message;
message + message;
println(message); // 在调试窗口输出

text("string", x, y);
text("string", x, y, width, height); // show text in a rect box

// using font
PFont varFont;
void setup() {
    varFont = createFont("fontName", 32);
}
void draw() {
    textFont(varFont);
    text("string", x, y);
}

textsize(32); // 字号
fill(255); // 也可以改变文本的颜色
textLeading(10); // 行距
textAlign(LEFT); // 对齐
tw = textWidth(string); // 获取文本的长度，可以用来画与文本同宽的图形

textMode(MODEL); // or SHAPE

split(string, " ");
splitTokens(string, " &+,.");
```

### 键鼠交互

```java
// 键鼠的内置变量
mouseX, mouseY;
pmouseX, pmouseY; // 上一帧的鼠标坐标
mousePressed; // true or false
mouseButton; // LEFT or RIGHT
keyPressed; // true or false
key; // 对应的 ASCII or COEDE， CODED = {UP, DOWN, LEFT, RIGHT, ALT, CONTROL, SHIFT}

// 构建事件处理函数来处理键鼠动作
void mousePressed()
void mouseReleased()
void mouseMoved()
void mouseDragged()
void keyPressed()
void keyReleased()

// 在事件处理函数中经常使用的
noLoop(); // stop main loop
loop(); // start main loop
reDraw();
noCursor();
cursor();
```

### 图像

```java
PImage img;
void setup() {
    size(320, 240);
    img = loadImage("imageFilePath");
}
void draw() {
    background(0);
    image(img, x, y);
}

PImage img = createImage(width, height, RGB);
tint(lightness);
tint(lightness, alpha);
tint(r, g, b);
tint(r, g, b, alpha);
image(img, x, y, resizeWidth, resizeHeight); // resize is optional
// or using
background(img);

loadPixels(); // or img.loadPixels()
// 会生成名为pixels的一维数组
// 会生成名为width和height的变量
// code to change pixels
float r = red(img.pixels[loc]);
float g = green(img.pixels[loc]);
float b = blue(img.pixels[loc]);
// code to change r, g, b
r = constrain(r, 0, 255);
g = constrain(g, 0, 255);
b = constrain(b, 0, 255);
updatePixels(); // or img.updatePixels()
```

### 曲线

```java
arc(x, y, width, height, startAngle, stopAngle); // x,y is the center, the right is 0 and left is PI
curve(cpx1, cpy1, x1, y1, x2, y2, cpx2, cpy2); // cp is the control point

// a curve with many control point
beginShape();
curveVertex(20, 20);
...
curveVertex(30, 30);
endShape();

bezier(x1, y1, cpx1, cpy1, cpx2, cpy2, x2, y2);

// a bezier with many point
beginShape();
vertex(30, 30);
bezierVertex(cpx1, cpy1, cpx2, cpy2, x, y);
...
endShape();
```

### PShape

```java
PShape shapeName;
void setup() {
    shapeName = createShape();
    shapeName.beginShape();
    shapeName.fill(128);
    shapeName.stroke(255);
    shapeName.strokeWeight(2);
    shapeName.vertex(x, y);
    ...
    shapeName.vertex(x, y);
    // optional
    shapeName.beginContour();
    shapeName.vertex(x, y);
    ...
    shapeName.endContour();
    // optional end
    shapeName.endShape(CLOSE);
}
void draw() {
    shape(shapeName);
}

// group
PShape alien = createShape(GROUP);
PShape head = createShape(ELLIPSE, 0, 0, 50, 50);
PShape body = createShape(RECT, 0, 50, 50, 100);
alien.addChild(head);
alien.addChild(body);
```

### PGraphics

```java
PGraphics g;
void setup() {
    g = createGraphics(width, height;
    g.beginDraw();
    g.background(0);
    g.noStroke();
    g.fill(255, 100);
    g.ellipse(mouseX, mouseY, 40, 40);
    g.endDraw();
}
// 可以在任意位置使用 beginDraw() endDraw() 对 PGraphics 对象操作。

PGraphics cube;
void setup() {
    size(100, 100, P3D); // 三维图形
    cube = createGraphics(width, height, P3D);
}
woid draw() {
    background(0);
    cube.beginDraw();
    cube.lights();
    cube.background(0);
    cube.noStroke();
    cube.translate(width/2, height/2);
    cube.rotateX(frameCount/100.0);
    cube.rotateY(frameCount/200.0);
    cube.box(40); // 边长40的方盒
    cube.endDraw();
    image(cube, 0, 0);
}
```

### Shader

```java
// shader class
PShader toon;
void setup() {
    size(640, 360, P3D);
    noStroke();
    fill(200);
    toon = loadShader("toonFrag.glsl", "toonVert.glsl");
    toon.set("fraction", 1.0); // 这是shader中的 uniform 变量
}
void draw() {
    shader(toon);
    background(0);
    float dirY = (mouseY / float(height) - 0.5) * 2;
    float dirX = (mouseX / float(width) - 0.5) * 2;
    directionalLight(204, 204, 204, -dirX, -dirY, -1);
    translate(width/2, height/2);
    sphere(120);
}
// toonVert.glsl
// the uniform vars below is define by processing
uniform mat4 transform;
uniform mat3 normalMatrix;
uniform vec3 lightNormal;

// 自带的shader
shader(pointShader, POINTS);
shader(lineShader, LINES);
shader(polyShader);
beginShape(POLYGON);
...

// 渲染的四种情况
// COLOR: no light and no textures
// LIGHT: light but no textures
// TEXTURE: textures but no light
// TEXLIGHT: light and textures
// 除了模型，还可以自定义point和line的shader生成云雾等效果
```

### 导出

```java
import processing.pdf.*;

size(600, 600);
beginRecord(PDF, "line.pdf");
background(255);
stroke(0);
line(200, 0, width/2, height);
endRecord();

import gifAnimation.*;
GifMaker gif;
void setup() {
    frameRate(25);
    gif = new GifMaker(this, "filename.gif");
    gif.setRepeat(0);
    gif.setDelay(40); // 40ms per frame
}
void draw() {
    gif.addFrame();
    if (frameCount >= frameCountYouLike) {
        gif.finish();
    }
}
```
