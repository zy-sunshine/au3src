将AutoIt 功能函数与脚本引擎拆开，确保以下几点

* 功能函数与AutoIt文档基本一致
* 功能函数独立性好，可封装成Python模块暴露使用
* 功能函数的状态，如线程执行等与脚本引擎状态相关
* 脚本引擎非全局，可多实例化，并有剥离到沙箱的结构预留
* 除脚本引擎运行状态，脚本引擎的脚本执行非必要，即可以与类似Python第三方语言共存
* 功能函数拆分成模块，模块可以加载使用

这里脚本引擎剥离后基本不会大面积使用，而是作为基础模块研究存在

engine 作为引擎封装，向Modules 提供标准访问借口，尽量将脚本引擎内部细节屏蔽。

## engine 设计
#### engine 接口原则
* engine 中include 的 h 文件必须谨慎，因为提供第三方开发Module 会提供该文件
  * 不暴露脚本引擎解析状态，因此所有 Parser 头文件不会暴露，执行状态不能被外部调用打乱。
  * Type 文件可以暴露，因为Module 会对取出的类型做操作(Ref)
  * 只提供原子类操作，因此除了函数调用封装之外都不会涉及 vResult参数传递。
### engine 与 Parser边界划分
* engine 在某些方面与 Parser 联系很紧密，特别是Execute
* Parser 包含两层功能
    * 第一层为脚本语法解析，此时会调用 Lexer 相关特性
        * 将解析后的函数存储 UserFuncList
        * 支持 builtin、plugin函数设置和解析调用
        * 支持解析每一行脚本为 Token
    * 第二层为脚本运行
        * 调用 ParserExp，并管理堆栈 StackStatement
        * 管理变量作用域切换 VariableTable
* 而 engine作为一个脚本运行与外界的沟通，屏蔽脚本引擎内部的运行细节，向外部提供鲁棒性的原子性接口
* engine 也作为联通各个模块的运行环境，包括引擎级别的全局变量，

## 例子
### 打开notepad 并关闭
test.au3
```
Dim $var1 = 1
Dim $pid=RUN("notepad.exe")
Sleep(1000)
ProcessClose($pid)
```
AutoIt.exe test.au3

## 进展
### 已完成特性
* module 的拆分
* engine 的拆分(Parser ParserExp Lexer)
* module 的实例化向 engine 注册内置函数
* 根据 module 头文件生成可注册的 C++ 头文件
### 待做
* 补全一些必要函数，如 DllOpen DllClose
* 补全所有 module function 的`参数注释配置`
* 内存泄露检查

## 扩展内置函数
* 目前内置函数与 AutoIt原有 script.h 一个文件包含所有函数不同，是由多个 Module 模块组成
* 因此Module 注册时，函数的类型来自多个C++类函数类型，因此需要一个类C中间层函数封装来辅助
### 运行生成函数脚本
```
python scripts\genFuncInfoCpp.py src\Modules
```
### 参数注释配置
* 内置函数注册参数中包括几个要素：
    * 函数来源类、function名称
    * 注册时函数对应的module实例指针
    * 注册到 engine内部的内置函数名称
    * 函数的最小、最大参数数量
* 其他均可以从module 头文件中解析得出，但最小、最大参数数量并没有在 C++ 头文件语法中描述
* 因此我们定义了一个注释格式用来描述 `参数注释配置`
    * 即在函数定义之后加入一组类似 csv 格式逗号分隔的参数
    * 如 F_Run(...); // 1, 3，来标识最小参数1，最大参数3

## 编译
### 工具准备
* windows 安装 qmake
* 安装 vs2015
* 执行 vs2015 vs脚本，nmake cl 等工具环境
```
CALL "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
```
* 执行编译
```
cd au3src
qmake
nmake
```

AutoIt v3
=========

AutoIt v3 is a work in progress.  Bugs to support at hiddensoft dot com


NOTE: For obvious reasons this archive doesn't contain all the new features in the current
version of AutoIt.  The code for these features may be made available at a later date.

Excluded features are:
- GUI
- DllCall
- ControlListView
- InetGet

However, as the primary goal of releasing this source is to help people contribute to the AutoIt
project, the missing features aren't so important. 



Compiling AutoIt
================

To compile AutoIt you need one of the following compilers
- Visual C++ .NET 2003 (VC 7.1) - Use AutoIt_VC7.sln
- Visual C++ v6 - Use AutoIt_VC6.dsw
- DevC++ - Use AutoIt_DevC.dev (Must be updated with at least the WinApi 3.1 package)

Note: The main compilers used (and checked) are Visual C++ 6 and 7.  MingW is not the main
development environment.  Public releases of AutoIt will be compiled with VC6 as it currently gives
the smallest executable. 

Things not working under DevC++ (commented out with #ifdef statements): 
- "new" handler,


Visual C++
----------
Select "Build All" from the menus.  Make sure to build both projects "AutoIt" and "AutoItSC"


DevC++
------
AutoIt has been tested with DevC++ 4.9.9

Select "Rebuild All" from the "Execute" menu to clean and compile everything.

To run the DevC/MinGW compiled file you will need the DLLs "mingwm10.dll" and "msvcrt.dll" in your
path.


Have fun.
Jonathan <jon at hiddensoft dot com>
