# Frog_fighter
一个由C++语言和cocos-2d框架开发的，飞机大战和捡金币游戏改版。


## 开发

开发者：Adam

邮箱:jokmingwong@gmail.com

开发工具：cocos2d-x与C++



## 打开游戏方式

将cocos2d-x的配置文件放在目录下。
游戏玩家直接打开：proj.win32文件下Release.win32下的HelloWorld.exe

代码查看以及编译运行：用Visual studio打开proj.win32目录下的HelloWorld.sln，若编译时候遇到缺少开发包错误，按编译报错提示 尝试Retarget the sulution后再编译运行



## 生成页面

主要代码在文件目录下的class文件夹里。其中页面代码是由Scene结尾的头文件和cpp文件组成，如：`HelloWorldScene.cpp`和`HelloWorldScene.h`。

每个页面都继承于cocos2d-x::Scene类，每个页面的头文件都有`init()`,`onEnterDidTransition()`,`onEnter()`,`onExit()`几个基础函数，分别代表页面的状态。制作游戏的任务加在这几个函数里面。



## cocos2d-x的API

[cocos2d-x的API链接](http://www.cocos.com/docs/native/)

在游戏中常用的API函数有`void update(float dt)`,`getInstance(),setPosition()`。

碰撞事件，子弹发射等监听器(Listener)，

重力模式或旋转模式的粒子系统

提供速度变化的物理引擎



## 常见问题（FAQ）

1. 背景音乐无法加载，音乐文件放在Resource\sound 文件目录下，加载背景音乐的函数`preLoadBackgroundMusic()`在`LoadingPageScene.cpp`中，播放音乐函数在`HelloWorldScene.cpp`中，确保播放时文件路径正确。

2. 游戏过程中会产生控制的主角连撞敌机导致游戏结束，代码缺少控制过渡时间的函数。



## 自定义游戏

若需要更改游戏的界面、游戏敌人或者游戏主角，则将需要将所需要图片放入plist生成软件，重新生成一张同名plist文件并替代原来文件。游戏的plist文件放在Resources/texture文件目录下，且plist与同名png文件需要同时存在。



## 开发者

更改HelloWorld文件下的classes文件的代码即可，欢迎参与本项目开发。

