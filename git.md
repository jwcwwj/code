# 1.git简介：

git是一个免费和开源的分布式版本控系统。

git主要解决三个问题：
①代码被别人覆盖掉；

②产品经理反复修改需求，需要同时维护多个版本代码；

③多人协同开发；

# 2.安装git及配置环境：

打开浏览器搜索git，找到git官网点击进去，找到download进行下载自己需要的版本；

官网： https://git-scm.com/

官网下载太慢，找到镜像进行下载

这里是淘宝镜像   http://npm.taobao.org/mirrors/git-for-windows/

点击镜像链接找到稳定版本进行下载：

![image-20230322182456080](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230322182456080.png)

稳定版本：
![image-20230322182511356](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230322182511356.png)

windows下载exe的，64位下载64位的，linux下载tar.bz的

windows的：

![image-20230322182833775](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230322182833775.png)



下载好的windows的：

![image-20230323150351730](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323150351730.png)





一直点击下一步：
选择安装目录：
![image-20230322185025784](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230322185025784.png)

选择编译器：

![image-20230322185050281](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230322185050281.png)



安装完成之后检查是否安装好：

①开始菜单界面查看： 

![image-20230323150624203](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323150624203.png)



②桌面右键查看是否有Git GUI here和Git Bash here；

③任意文件夹下也可以以看到Git GUI here和Git Bash here；



# 3.安装git图形化界面：

①git图形化界面下载链接：	https://tortoisegit.org/download/  

②下载之后在下载的文件夹点击，如果git for windows安装了就一直next（中间选择安装位置，配置姓名和邮箱）；

③安装之后检查，在开始界面出现下图内容表示安装成功；

![image-20230323180756237](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323180756237.png)

④要想使用中文：点击网站	https://tortoisegit.org/download/

下拉下载中文简易语言，安装的时候直接勾选配置使用中文语言；



# 4.删除git及环境变量：安装新版本之前先删除旧版本

①清理环境变量：在我的电脑右键属性中找到高级系统设置，点击找到环境变量，进去找到path查看是否有和git相关的，找到和git相关的先删除环境变量；

②卸载软件：搜索控制面板，找到程序点击进去搜索git进行卸载；



# 5.git配置：

 查看配置的linux命令：

①查看配置:	 

git config -l

![image-20230323154406951](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323154406951.png)

②查看系统config：	

git config --system --list

![image-20230323154654510](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323154654510.png)

③查看当前用户(global)配置：

git config --global --list

![image-20230323154818172](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323154818172.png)



git相关的配置文件：

①系统配置文件路径（没有用户内容）：（系统级）

F:\git\Git\etc\gitconfig   

![image-20230323155722526](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323155722526.png)

![image-20230323155645538](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323155645538.png)

②用户配置文件路径：（当前用户）

C:\Users\19827\.gitconfig

![image-20230323155803516](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323155803516.png)

![image-20230323155335312](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323155335312.png)

③设置用户名与邮箱（用户级、必要的）：当你安装Git后首先要做的事情是设置你的用户名称和e-mail地址。这是非常重要的，因为每次Git提交都会使用该信息。它被永远的嵌入到了你的提交中；

git config --global user.name "jwcwwj"

git config --global user.email "1982782238@qq.com"

只需要做一次这个设置，如果你传递了--global 选项，因为Git将总是会使用该信息来处理你在系统中所做的一切操作。如果你希望在一个特定的项目中使用不同的名称或e-mail地址，你可以在该项目中运行该命令而不要--global选项。总之--global为全局配置，不加为某个项目的特定配置。

# 

# 6.github注册：

①进入github官网：	www.github.com

②点击

![image-20230323184610572](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230323184610572.png)



# 7.git基本理论和命令：





# 8.参考狂神说git文档：

https://mp.weixin.qq.com/s/Bf7uVhGiu47uOELjmC5uXQ

里面的专有名词解析：

并行（并行开发）：两个任务同时执行；（多人协同开发）

并发：时间片调度一个CPU执行两个程序；







# git的重点和学习路线：

①git基础：

目标：

了解git基本概念和常用命令的作用（理论）；		

能够使用git命令来管理和提交项目代码（实践）；



基本概念：

什么是git（版本控制系统）

什么是github（代码托管平台）

git和github的作用

git和github的联系与区别



git的概念：

工作区

暂存区（索引）

本地版本库

远程仓库

git文件状态

版本

HEAD

分支



git的安装：



git常见配置（git config）：修改配置 （个人信息）  查看配置



git基本操作（开发流程）：

初始化仓库（git init）

克隆（git clone）

暂存（git add）

提交（git commit）

推送（git push）

拉取（git fetch）

拉取合并（git pull）

查看状态（git status）

查看历史（git log）



猴子都能懂的GIT入门（熟悉git操作流程和命令）



分支操作：（可以用Learning Git Branching在线游戏来学习和理解分支）

创建分支

查看分支

切换分支

删除分支

合并分支（git merge）





②guthub基础：

目标：

熟悉github基本操作，并能够使用github来管理代码

了解如何利用github搜索和下载项目代码

了解github协作流程，了解开源，并能向开源项目提交代码；



知识点：

什么是github

如何访问github



基本概念：

仓库

分支	主分支

README

Star

Follow

账户类型（个人/组织）



必备操作：

搜索仓库/代码

创建仓库（公开和私有）

Fork仓库

Watch仓库

上传本地代码

修改个人信息



github Flow协作流程：

克隆/Fork仓库

创建分支

修改代码

发起Pull Request

Code Review

Merge分支

删除分支



了解github lssues：

贡献代码流程：



刚开始跟着官方的hello world入门教程来实操一遍提交代码的流程就可以了

读一下github的漫游指南，一位大佬总结的经验技巧，能加深对github的认识

阅读开源指北来了解开源





③git进阶：

目标：

学习git的高级操作，尤其是能够熟练的规避和解决冲突

了解企业常用的git协作流程和规范，能独立管理项目



高级操作：

标签(git tag)

检出（git cheakout）

贮藏（git stash）

清理（git clean）

变基（git rebase）

重置（git reset）

还原（git revert）

检索（git grep）

展示差异（git diff）

溯源（git blame）

参考日志（git reflog）

交互式命令行（-l参数）



预防冲突：

解决冲突：

配置SSH：

子模块：

git钩子：  提交钩子（pre-commit）

忽略提交（gitignore）

cherry-pick：

分布式工作流程：

git worktree：

git flow：

git内部原理：

Monorepo：

了解其他版本控制系统，和git对比：



直接看git的官方文档



④github进阶：

目标：

按需学习github功能，提升研发效率、更好的管理项目；

尝试用心维护和推广自己的github项目；



知识点：

开发：

配置SSH拉取

github快捷键

github命令面板

github Apps

代码安全



协作：

github Codespaces

github Discussions

Pull Requests



项目管理：

Organizations组织

github lssues问题反馈

github Projects项目管理

Insights数据分析

贡献者管理

开源协议



DevOps：

github Pages网站托管

Gitpod代码托管

github Actions

github packages

github Webhook



git私服搭建:

gitlab

Gogs



进阶最好的学习方式最好是阅读官方文档，尤其是github的官网文档。



面试题：
1．分享下你在团队中使用Git协作开发的流程；

2．如何控制某些文件不被提交?

3．什么情况下提交会冲突，如何解决冲突?

4．不小心改错了代码、删除了文件，如何恢复?

5．如果让你负责团队，会怎么管理项目的代码?

6．如何防止错误的代码提交?

























