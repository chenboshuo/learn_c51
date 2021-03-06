# learn_c51
学习51 单片机的代码

## 工具
-   Ubuntu
-   sdcc
-   stcgal
-   GNU make

## tools 内工具说明

### format.py

在文件夹新建一个等待美化的关于字模的代码，如
```c
unsigned char code image[] = {  //图片的字模表
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xC3, 0xFF, 0x99, 0x00, 0x00, 0x00,
    0x81, 0xC3, 0xE7, 0xFF, 0x99, 0x99, 0x99, 0x99, 0x99, 0x81,
    0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
```
在目录下直接运行
```bash
python format.py
```
自动新建`fotmatted_code.c`
如下
```c
unsigned char code image[] = {  //图片的字模表
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xC3, // ..@@@@..
  0xE7, // ...@@...
  0xE7, // ...@@...
  0xE7, // ...@@...
  0xE7, // ...@@...
  0xE7, // ...@@...
  0xC3, // ..@@@@..
  0xFF, // ........
  0x99, // .@@..@@.
  0x00, // @@@@@@@@
  0x00, // @@@@@@@@
  0x00, // @@@@@@@@
  0x81, // .@@@@@@.
  0xC3, // ..@@@@..
  0xE7, // ...@@...
  0xFF, // ........
  0x99, // .@@..@@.
  0x99, // .@@..@@.
  0x99, // .@@..@@.
  0x99, // .@@..@@.
  0x99, // .@@..@@.
  0x81, // .@@@@@@.
  0xC3, // ..@@@@..
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
  0xFF, // ........
};
```

同时生成图像文件`image_file.txt`
```plt
........
........
........
........
........
........
........
........
..@@@@..
...@@...
...@@...
...@@...
...@@...
...@@...
..@@@@..
........
.@@..@@.
@@@@@@@@
@@@@@@@@
@@@@@@@@
.@@@@@@.
..@@@@..
...@@...
........
.@@..@@.
.@@..@@.
.@@..@@.
.@@..@@.
.@@..@@.
.@@@@@@.
..@@@@..
........
........
........
........
........
........
........
........
........
```

## 参考
-   [macOS搭建51单片机开发环境](https://zhuanlan.zhihu.com/p/337744148)
