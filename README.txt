将AutoIt 功能函数与脚本引擎拆开，确保以下几点

* 功能函数与AutoIt文档基本一致
* 功能函数独立性好，可封装成Python模块暴露使用
* 功能函数的状态，如线程执行等与脚本引擎状态相关
* 脚本引擎非全局，可多实例化，并有剥离到沙箱的结构预留
* 除脚本引擎运行状态，脚本引擎的脚本执行非必要，即可以与类似Python第三方语言共存
* 功能函数拆分成模块，模块可以加载使用

这里脚本引擎剥离后基本不会大面积使用，而是作为基础模块研究存在

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
