Logical Circuit
=============

目录
-------------
* [English Documents](readme.md)
* [触发器文档](tri_readme.md)

文档
-------------
### 冒号表达式

#### input
设置电路的输入线路（自动定义线路变量）
```
input:A
```

#### output
设置电路的输出线路（现有线路变量）
```
output:r
```

#### set
设置输入导线变量的值
```
set: A 1
```

#### load
加载逻辑电路脚本文件(*.LC)。将直接执行。
```
load:D:/test.lc
```

### 命令
* **trueTable:** 穷举所有输入运行电路
* **statTable**  穷举所有输入和触发器状态运行电路
* **gateNum:** 输出电路中逻辑门的数量
* **stru:** 输出电路结构（不好看）
* **run:** 用当前设置的输入运行电路
* **clear:** 清除当前电路
* **middleVar:** 运行电路，输出所有导线中流过的值
* **multiplexing:** 统计所有导线使用次数
* **resetTri** 重置所有触发器的初始状态为0