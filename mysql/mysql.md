# 1.数据库介绍：

数据库分类：关系型数据库和非关系型数据库。

存储介质：磁盘、文件。

相较于文件存储：

文件存储安全性低。

文件对数据的查询和管理效率较为低下。

文件不利于海量存储与查询。

文件在程序中控制不方便。

SQL：结构化查询语言

数据库的分类：以一种关系模型（二维表格模型）组织数据的数据库。

分类：oracle、mysql、sql server、mariadb、sqlite

非关系型数据库：不基于sql实现的数据库。

分类：redis、memcached、mongodb



# 2.mysql安装与配置：

![image-20231113000845255](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113000845255.png)

![image-20231113000927484](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113000927484.png)

![image-20231113001226538](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113001226538.png)

![image-20231113001301163](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113001301163.png)

![image-20231113001431731](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113001431731.png)

# 3.客户端连接mysql服务器

![image-20231113001701091](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113001701091.png)

mysql数据库的安装：

安装：yum install -y mariadb

配置：https://zhuanlan.zhihu.com/p/49046496

登录：mysql -uroot

查看配置：show variables like '%char%';

![image-20231105083424120](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105083424120.png)

# 3.数据库基本操作

数据库基本操作：库的操作、数据类型，表的操作。

库的操作：

sql：结构化查询语言：有具体格式与语法规则。

每一条sql都要以一个英文分号结尾。

库表字段名称不能使用关键字，如果非要使用则需要使用反引号括起来。

不区分大小写。

查看数据库：show databases;

创建：create database `	dbname`;			CHARACTER SET: 指定数据库采用的字符集

create database if not exists `dbname`;

CREATE DATABASE IF NOT EXISTS db_test CHARACTER SET utf8mb4;  	

**说明：MySQL的utf8编码不是真正的utf8，没有包含某些复杂的中文字符。MySQL真正的utf8是使用utf8mb4，建议大家都使用utf8mb4。**

使用数据库：use 数据库名;

删除：drop database [IF EXISTS] `dbname`

**说明：数据库删除以后，内部看不到对应的数据库，里边的表和数据全部被删除。**

查看创建数据库的创建语句：show create database `dbname_912`;

使用指定数据库：use `db_name`;

查看当前所选择使用的数据库：select database();

查看库中的所有表：use 表名称;	show tables;



# 4.常用数据类型：

分为整形和浮点型：
![image-20231113061554058](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113061554058.png)

![image-20231113064104073](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113064104073.png)

![image-20231113064713767](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231113064713767.png)

整形：bit(16)、tinyint、int、bigint

浮点型：float(m,d)、double(数字个数,数字中小数的个数)、decimal(m,d)、numeric(m,d)、

double(5,2)表示5位数中小数占2位比如888.88

字符串型：varchar(32)最多存储32个字符（不定长）、text、mediumtext、blob

日期类：datetime



# 5.数据库表的操作

在mysql中单引号和双引号是一样的

1.使用指定的数据库：：use 数据库名;

2.在指定的数据库中创建表：

```sql
CREATE TABLE IF NOT EXISTS stu
(
	sn INT,
	NAME VARCHAR(32),
	age INT,
	sex VARCHAR(1),
	height INT,
	weight DECIMAL(4,1)
);
//或者加注释：comment，增加字段说明
CREATE TABLE IF NOT EXISTS stu
(
sn INT comment ‘学号’,
NAME VARCHAR(32),
age INT,
sex VARCHAR(1),
height INT,
weight DECIMAL(4,1)
);
```

如何查看注释：查看表结构是看不见的，只有查看创建语句才可以看见。

3.查看指定数据库中的所有表：use jwc;	show tables；

4.查看表的结构：use jwc;	desc stu;	/	describe stu;

![image-20231105085900032](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105085900032.png)

第一行分别表示：字段、类型、是否可以位空、是否是某一个特殊的键值、是否有默认的值、是否有扩展属性。

或者desc stu\G;		显示的更好看

![image-20231105090519657](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105090519657.png)

5.查看表的创建语句：show create table stu;

![image-20231105090753830](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105090753830.png)

6.修改表结构：alter table stu add birth datetime;（这里是添加，还有删除、改变字段的类型、改变字段的属性等...）（不常用）

![image-20231105092307059](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105092307059.png)

7.删除表：drop table [if exists] stu;

在MySQL中，DROP TABLE 语句用于删除表，而 temporary 关键字用于指定要删除的是临时表。临时表是一种特殊类型的表，它们只在当前的数据库会话中存在，并且在会话结束时会自动被删除。

使用 DROP TEMPORARY TABLE 语句可以删除一个或多个临时表，而不会影响其他会话中的同名表。临时表通常用于临时存储数据或者进行临时计算，其作用范围仅限于创建它们的会话。

语法中的 [TEMPORARY] 关键字表示可选项，意味着你可以选择性地在 DROP TABLE 中加入 TEMPORARY 关键字来指定删除临时表，如果省略了 TEMPORARY，则默认删除的是普通表而非临时表。



# 6.表中数据的增删改查(对数据库中的表结构的操作)

1.简单查询（全列查询）：select * from stu;

2.新增：insert [into]			[]表示可以省略，into可有可没有

insert into stu values(1001,'张三',18,'男',165,55.55,'2003-12-12 12:10:38');

![image-20231105103023913](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105103023913.png)

insert into stu(name,sn,sex) value('李四',1002,'女');

![image-20231105103533199](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105103533199.png)

insert into stu values

(1003,'王五',17,'男',170,55.55,'2004-12-12 12:10:38'),

(1004,'赵六',16,'女',165,55.55,'2005-12-12 12:10:38');

![image-20231105104215166](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105104215166.png)

![image-20231105104227439](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105104227439.png)

补充：多行数据 + 指定列插入

INSERT INTO student (id, sn, name) 

VALUES(102, 20001, '曹孟德'),

​			  (103, 20002, '孙仲谋');  

3.修改：update

```sql
SELECT
[DISTINCT] {* | {column [, column] ...}
[FROM table_name]
[WHERE ...]
[ORDER BY column [ASC | DESC], ...]
LIMIT ...
```

```sql
-- 将孙悟空同学的数学成绩变更为 80 分
UPDATE exam_result SET math = 80 WHERE name = '孙悟空';
-- 将曹孟德同学的数学成绩变更为 60 分，语文成绩变更为 70 分
UPDATE exam_result SET math = 60, chinese = 70 WHERE name = '曹孟德';
-- 将总成绩倒数前三的 3 位同学的数学成绩加上 30 分
UPDATE exam_result SET math = math + 30 ORDER BY chinese + math + english LIMIT 3;
-- 将所有同学的语文成绩更新为原来的 2 倍
UPDATE exam_result SET chinese = chinese * 2;
```

update stu set weight=55.5,birth='2004-12-12 9:10:38';			修改所有

update stu set weight=55.5,birth='2004-12-12 9:10:38' where sn=1003;			修改sn=1003的

![image-20231105121800982](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105121800982.png)

4.删除：delete

delete from stu where sn = 1003;

![image-20231105121827597](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105121827597.png)

update stu set age=19,height=169,weight=77.8,birth='2002-12-12 21:45:34' where sn=1002;

![image-20231105122129984](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231105122129984.png)

删除整张表：delete form 表名字;

```sql
delete from 数据库表名字;			-- 用于删除表中的数据，不会对表结构产生影响，表还存在
drop table 数据库表名字;			-- 用于删除整个数据库表，是针对表本身进行操作，彻底删除整个表及其内容，包括表结构、所有数据以及相关的索引，表不存在
```

5.查询：select

默认全列：select * from stu;

指定列查询：指定列的顺序不需要按定义表的顺序来

​	select height,weight,name from stu;

指定字段为表达式 + 取别名：as（as也可以不写）

​	select height+weight as hw,name from stu;

**去重：distinct**

​	select distinct height,weight from stu;		把height和weight作为一个整体进行去重（height和weight只要有一个不一样就当做查询结果的一条）

排序：order by	desc/asc			desc是降序，asc是升序，默认是升序排序。

​	select * from stu order by height desc,age asc;		先按height降序排序，再按age升序排序。

分页查询：limit

​	select * from stu order by height desc limit 3;

​	select * from stu order by height desc limit count offset page*count;		count表示要显示的条数，offset是偏移，page是页数

​	select *from stu order by height desc limit 3 offset 3;

条件查询：where

​	select * from stu where name='王五';

关系运算符：

​	比较：>、>=、<、<=、=、!=、<=>、<>			其中<=>和<>和NULL联系在一起

​		select * from stu where name='王五';	

​	空值：is null、is not null

​		select * from stu where sn is null;

​	范围：between...and...

​		select * from stu where height between 170 and 180;

​	子集匹配：in（集合）

​		select * from stu where name in('王五','赵五','李五');

```sql
-- 查询数学成绩是 58 或者 59 或者 98 或者 99 分的同学及数学成绩
SELECT name, math FROM exam_result WHERE math IN (58, 59, 98, 99);
-- 使用 OR 也可以实现
SELECT name, math FROM exam_result WHERE math=58 OR math=59 OR math=98 OR math=99;
```

模糊匹配：like

​		select * from stu where name like '%五%';

逻辑运算符：

​	与：双目，and-连续两个比较条件，两者同为真则结果为真。

​		select * from stu where height>=170 and height<=175;

​	或：双目，or-连接两个比较条件，两者任意一个位真，则结果为真。

​		select * from stu where weight>=70 or height>=170;

​	非：单目，not针对单个比较条件，条件为真，则结果位假。

​		select * from stu where not weight>=70;

```sql
-- 查询 qq_mail 已知的同学姓名
SELECT name, qq_mail FROM student WHERE qq_mail IS NOT NULL;
-- 查询 qq_mail 未知的同学姓名
SELECT name, qq_mail FROM student WHERE qq_mail IS NULL;
```

```sql
-- 问题：
-- 有一个商店的数据，记录客户及购物情况，有以下三个表组成：
-- 商品goods(商品编号goods_id，商品名goods_name, 单价unitprice, 商品类别category, 供应商provider)
-- 客户customer(客户号customer_id,姓名name,住址address,邮箱email,性别sex，身份证card_id)
-- 购买purchase(购买订单号order_id,客户号customer_id,商品号goods_id,购买数量nums)

-- 答案：
-- 创建数据库
create database if not exists bit32mall default character set utf8;

-- 选择数据库
use bit32mall;

-- 创建数据库表
-- 商品
create table if not exists goods
(
	goods_id int comment '商品编号',
	goods_name varchar(32) comment '商品名称',
	unitprice int comment '单价，单位分',
	category varchar(12) comment '商品分类',
	provider varchar(64) comment '供应商名称'
);

-- 客户
create table if not exists customer
(
	customer_id int comment '客户编号',
	name varchar(32) comment '客户姓名',
	address varchar(256) comment '客户地址',
	email varchar(64) comment '电子邮箱',
	sex bit comment '性别',
	card_id varchar(18) comment '身份证'
);

-- 购买
create table if not exists purchase
(
	order_id int comment '订单号',
	customer_id int comment '客户编号',
	goods_id int comment '商品编号',
	nums int comment '购买数量'
);
```



表中数据的增删改查进阶：

​	键值约束与扩展属性：ER关系图+三大范式、分组查询、多表联查。

​	键值约束与扩展属性：

​		键值约束：约束表中指定字段的数据必须符合某种规则。

​		种类：

​			非空约束：NOT NULL					约定指定字段的数据不能为NULL。

​			唯一约束：UNIQUE						约定指定字段的数据不能出现重复。

​			主键约束：primary key		 		NOT NULL和UNIQUE的结合，约定字段数据非空且唯一，一张表只有一个主键。（主键可以是一列，也可以是多个列的结合）

​			外键约束：foreign key		  		表中指定字段的数据受副表数据约束。（保证一个表中的数据匹配另一个表中的值的参照完整性。）

​			默认值：DEFAULT 				 		为指定字段没有赋值时候设置默认值。

​			自增属性：AUTO_INCREMENT	 整形字段数据自动+1，只能用于主键，必须为整形。		对于整数类型的主键，常配搭自增长auto_increment来使用。

插入数据对应字段不给值时，使用最大值 + 1。

​			check	保证列中的值符合指定的条件。	

​			check在mysql中忽略的，不会报错。		check(sex = '男' or sex='女')		会检测插入的语句sex值，只有是男或女才能插入。

```mysql
-- 注释
use jwc;

create table if not exists class
(
	id int primary key,				-- 主键
	name varchar(32)
);

create table if not exists student
(
	id int primary key auto_increment,
	sn int not null unique,
	name varchar(32),
	class_id int,
	sex varchar(1) default '男',
	foreign key (class_id) references class(id)		-- class_id的值必须是class表中id的值
);
```

```sql
-- 将学生表中的所有数据复制到用户表
insert into test_user(name, email) select name, qq_mail from student;
```



分组查询：group by having

SELECT 中使用 GROUP BY 子句可以对指定列进行分组查询。需要满足：使用 GROUP BY 进行分组查询时，SELECT指定的字段必须是“分组依据字段”，其他字段

若想出现在SELECT 中则必须包含在聚合函数中。

```mysql
create table emp
(
	id int primary key auto_increment,
	name varchar(20) not null,
	role varchar(20) not null,
	salary numeric(11,2)
);

insert into emp(name, role, salary) values
	('马云','服务员', 1000.20),
	('马化腾','游戏陪玩', 2000.99),
	('孙悟空','游戏角色', 999.11),
	('猪无能','游戏角色', 333.5),
	('沙和尚','游戏角色', 700.33),
	('隔壁老王','董事长', 12000.66);
```

分组查询的字段只能是分组依据字段以及聚合函数。

分组查询中不能使用where条件查询，如果要条件过滤使用having。

select role,sum(salary),max(salary),min(salary),avg(salary) from emp group by role having avg(salary) >1500;

聚合函数：针对结果中的数据的某个字段进行某种统计运算。

count(*)					统计数据条数

sum(fields)			   统计指定字段的和

max(fields)			   统计指定字段中的最大值

min(fields)				统计指定字段中的最小值

avg(fields)				 统计指定字段中的平均值





ER关系图：

一对一：一个学生只有一个学生证（各项信息）。

一对多：向学生实体（多的一方）添加一个班级ID。

能够唯一标识学生的字段就是主键。

![image-20231106043617506](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231106043617506.png)

多对多：一个学生可以学多门课程，一个课程可以有多个学生上。

设计一个中间表包含两个实体ID，通过中间表将两个实体关联。

![image-20231106045753092](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231106045753092.png)

 

三大范式：数据库表设计的三大范式。

1nf：表中每个字段都必须具有不可分割原子特性。

第一范式是其他范式的前提，并且如果不遵守第一范式会导致按照某个非原子字段进行查询时降低效率。

2nf：表中每个字段都应该与主键完全关联，而不是部分关联。

若不遵循第二范式：则表中有可能会存在大量冗余数据。

3nf：表中每个字段都应该与主键直接关联，而不是间接关联。



多表联查：将多张表合在一起进行查询。

将多张表合在一起：笛卡尔积。

连接方式：内连接 + 外连接（左连接 + 右连接）

1.内连接：取数据交集	inner join on

select stu.name,class.name from stu inner join class on stu.class_id=class.id;

2.右连接：以左表作为基表在右表中查询符合条件的数据。

select stu.name,class.name from stu left join class on stu.class_id=class.id;

3.右连接：以右表作为基表在左表中查询符合条件的数据进行连接。

select stu.name,class.name from stu right join class on stu.class_id=class.id;

4.子查询：多条sql语句嵌套查询。（常用于一条sql的查询条件是另一条sql的执行结果。）

子条件in和子条件exists。

在MySQL中，`IN`和`EXISTS`是两种常用的查询语句，它们可以用于检查一个值或子查询结果是否存在于另一个查询结果中。但是，在不同的情况下，它们的执行效率可能会有所不同。

一般来说，当需要比较的数据集较小时，`IN`语句的执行效率更高。这是因为`IN`语句可以直接将比较的数据列表加载到内存中进行比较，而不需要进行额外的查询操作。此外，`IN`语句还可以使用哈希表或二叉树等数据结构来加速查找过程，从而提高效率。

相比之下，当需要比较的数据集较大时，`EXISTS`语句的执行效率更高。这是因为`EXISTS`语句可以使用半连接（semi-join）方法来进行优化，该方法可以在比较大的数据集上执行更快的查询操作。具体来说，`EXISTS`语句只需要检查子查询中是否存在符合条件的记录，而不需要将整个子查询结果加载到内存中进行比较。

需要注意的是，实际的执行效率可能会受到多种因素的影响，例如索引和数据分布等。因此，在选择使用`IN`或`EXISTS`语句时，应该根据实际情况进行评估和测试，以确定哪种方法更适合你的应用场景。

5.合并查询：取两个查询结果的并集。

union：将多条sql语句的执行结果合并到一起，去重。

union all：全部合并，并不去除重复数据。



# 7.索引

作用：类似于一本书的目录，提高查询效率。

原理：给一张表创建一个索引，相当于又创建了一个索引表存储索引信息。因此索引并不是适用于所有的字段，不是越多越好，因此索引多了，会影响插入和删除

的效率。

1.不经常作为条件用于查询依据的字段不适合，

2.字段修改评率较高的字段不适合。

3.索引会额外占据磁盘空间。

索引是如何提高查询效率的：数据结构。

索引采用特殊的数据结构组织可以提高检索效率（尽快找到索引项，通过索引项找到实际数据的存储位置，然后取出数据。）

innodb使用的是B+树作为检索类型。

B树与B+树：

B树：是一个多叉树。

B+树：也是一个多叉树。		降低树的高度来提高查询效率。

B+树相较于B树的差别：B树的数据与索引存储在一起，B+树数据与索引分离，一次性可以从磁盘中读取出更多索引信息，更利于索引检索B+树数据顺序存储，在

连续查询或范围查询时可以连续IO取出数据，效率较高。

聚簇索引/非聚簇索引：

聚簇索引：以主键作为主索引，数据节点在磁盘中顺序进行存储，其他的索引作为辅助索引，其中辅助索引保存的是主键索引的字段值。

非聚簇索引：主键索引与普通索引区别不大，都是最终索引项中存储数据在磁盘中的存放位置，数据节点在磁盘中并非顺序存储。

使用场景：

聚簇索引：索引与数据都是顺序存储的，因此中间插入/删除需要调整索引的存储结构。

聚簇索引的数据都是顺序存储的，因此在连续/范围查询的时候效率较高。

聚簇索引通常针对主键创建，一张表只有一个。

非聚簇索引：中间插入数据，只需要将数据存储到磁盘新的位置，中间调整索引信息即可，因为索引与数据存储顺序不一致，导致在范围查询时，与单个查询效率

没有差别都需要一个个去找出来。

innodb索引类型默认是聚簇索引，中间数据的插入与删除会涉及索引与数据的位置调整，因此大多数情况都是使用自增主键作为聚簇索引，这样的话数据与索引

总是在最后添加，而不涉及中间插入的调整。

在数据库操作中的索引类型：

主键索引：一个字段被设置为主键，则默认就会为主键字段创建主键索引。

唯一键索引：	一个字段被设置了唯一约束，也会默认创建唯一键索引。

外键索引：一个字段被设置外键约束，也会默认创建外键索引。

普通索引：并非默认创建的索引。

查看索引：show index from tbname\G;

创建索引：create index idx_name on tbname(fields_name);

删除索引：drop index idx_name on tbname;



# 8.事务

概念：一个或多个sql的组合。

示例：

银行转账：给同学转账1000，你的账户少了1000，对方账户多了1000。

特性：

原子性：一个事务要么一次完成要么一个都不做。

一致性：在事务前与事务后，数据完整性都要符合预设规则，依赖原子性。

持久性：事务之后，数据的修改是永久的。（持久化存储）

隔离性：允许多个事务并发执行，不会因为交叉执行导致数据不一致。

并发情况下若无隔离性保护，则有可能出现的情况：

脏写：事务A对数据的修改，在事务提交之前被其他事务覆盖。

脏读：一个事务中读取到的数据是其他事务中未提交的数据。

不可重复读：在一个事务的不同阶段所读取的数据不一致。		针对：update

幻读：在一个事务内的不同时间段读取到的数据条数不一致。	 针对：insert/delete

解决方案：事务的隔离性。

读未提交：有可能出现脏读、不可重复读。

读提交：

可重复读：

串行化：

可重复读实现依赖mvcc。

mvcc：多版本并发控制。

说白了就是给每个事务分配一个事务id。

事务中对数据进行操作时，都临时拷贝出一份数据进行操作。

在本次事务对数据再次进行访问时访问的都是这个指定事务id的临时拷贝。

事务提交时将事务操作持久化存储。



总结：

mysql认识与安装：

数据库的认识：存储数据的仓库。

数据库与文件存储的区别：管理、访问、安全。

数据库的种类：

关系型数据库：oracle、sql server、mysql、sqlite

非关系型数据库：nosql-redis、memcached、mongodb

mysql安装：

mysql库的操作：

库的查看：show databases;

库的创建：create database if not exists dbname;

库的删除：drop database dbname;

库的选择：use dbname;

mysql常见数据类型：

整形：bit()、tinyint、int、bigint

浮点型：float(m,d)、double、decimal、numeric

字符串：varchar(n)、text、blob

日期：datetime

表的操作：create table if not exists `tbname` (id int,name varchar(32));

表结构的查看：desc tbname;

库中表的查看：show tables;

表中字段的修改：alter table tbname add get it;

表的删除：drop table tbname;

表中数据的基础增删查改：

数据的插入：insert [into]

全列插入：insert into tbname values(1,"张三",18);

指定列插入：insert into tbname(name) values("李四");

多列插入：insert into tbname(name) values("李四"),("王五");

数据的更新：update ... set

update tbname set name=“张文超” where id=1;

数据的删除：delete

delete from tbname where id=1;

数据的查询：select

全列查询：select * from tbname;

指定列查询：select name,age from tbname;

去重查询：select distinct age from tbname;

排序查询：select * from tbname order by age [desc/asc];

分页查询：select * from tbname order by age limit 3;

​				   select * from tbname order by age limit 3 offset 3;

条件查询：select * from tbname where age<18;

关系运算符：<、>、<=、>=、==、!=、<>、<=>

between ... and ...、in(a,b,c)、like

is null、is not null

数据库表中字段约束：

非空约束：NOT NULL，字段值不能为NULL

唯一约束：UNIQUE，字段值必须唯一，不能重复

主键约束：PRIMARY KEY，字段值必须非空且唯一（一张表只能有一个）

外键约束：FOREIGN KEY，字段值受父表指定字段数据约束

默认值：DEFAULT，向指定字段设置默认值

自增属性：AUTO_INCREMENT，字段值每次添加自动+1（用于整形主键字段）

聚合函数与分组查询：

聚合函数：mysql内置的数据统计函数。

sum()、avg()、max()、min()、count(*)

分组查询：以某个字段作为依据对数据进行分组实现数据的统计查询。

select role,avg(salary) from tmp group by role having avg(salary)>10;

数据库表的设计：

ER关系图：根据实体与实体之间的关系决定数据库表如何设计。

一对一：每个实体设计表的时候都应该具有一个唯一主键。

一对多：多的一方表中应该单一一方的主键作为表中字段。（实例：每个学生信息中都会包含一个班级id。）

多对多：创建一个中间表关联两个实体。

三大范式：数据表的设计规范。

1nf：表中每个字段都应该是不可分割的原子数据。

2nf：表中每个字段都应该完整关联主键，而不能部分关联。

3nf：表中每个字段都应该直接与主键关联，而不能间接关联。

多表联查：

表的连接方式：

内连接：取两张表的符合条件的交集数据进行查询。		inner join tbname on...

外连接：左连接/右连接，以其中一张表作为基表在另一张表中查询符合条件的数据进行连接。		left/right join tbname on...







# 8.面试题

## 8.1存储数据用文件就可以，为啥还需要数据库？

答：相比较文件，数据库存储数据更加安全，文件不利于存储海量数据，文件不利于数据查询和管理，文件在程序中控制不方便。

加问，为啥数据库比文件更安全？

答：

数据库相对于简单的文件存储在安全性方面具有一些优势，主要体现在以下几个方面：

1. 访问控制：数据库系统提供了灵活的用户和权限管理机制，可以对不同的用户设置不同的访问权限，并且可以精细到表、字段级别的权限控制。这意味着只有经过授权的用户才能够访问特定的数据，从而确保数据不被未经授权的人员访问。
2. 数据加密：现代的数据库系统通常支持对数据进行加密存储，包括数据文件、日志文件和备份文件等。这意味着即使数据库的物理介质被盗取或者泄露，数据也不会被轻易解析或者访问。
3. 审计与监控：数据库系统提供了丰富的审计和监控功能，可以记录用户操作、数据修改和访问历史，以便进行事后审计和安全事件追踪。这有助于及时发现异常操作和安全漏洞。
4. 防止数据丢失：数据库系统通常提供了事务处理和日志功能，能够确保数据的一致性和持久性。即使发生意外故障或者系统崩溃，数据库也能够通过日志恢复等机制来避免数据丢失。
5. 防止数据篡改：数据库系统能够通过访问控制、数据完整性约束等机制来防止数据的恶意篡改或者破坏。相比之下，简单的文件存储可能缺乏这些保护机制。

综上所述，数据库系统在访问控制、数据加密、审计监控、数据持久性和数据完整性等方面提供了更为全面的安全保护，能够更好地保护数据免受未经授权的访问和恶意操作。因此，在对数据安全性要求较高的应用场景下，使用数据库相对于简单的文件存储更为安全可靠。



## 8.2关系型数据库与非关系型数据库的区别

|              | 关系型数据库         | 非关系型数据库                           |
| ------------ | -------------------- | ---------------------------------------- |
| 使用SQL      | 是                   | 不强制要求，一般不急于SQL实现            |
| 事务支持     | 支持                 | 不支持                                   |
| 复杂操作     | 支持                 | 不支持                                   |
| 海量读写操作 | 效率低               | 效率高                                   |
| 基本结构     | 基于表和列，结构稳定 | 灵活性比较高                             |
| 使用场景     | 业务方面的OLTP系统   | 用于数据的缓存、或基于统计分析的OLAP系统 |

注：OLTP（On-Line Transaction Processing）是指联机事务处理，OLAP（On-Line Analytical Processing）是指联机分析处理。

## 8.3mysql关键字执行顺序

[mysql - select语句执行顺序/where语句执行顺序_select join where执行顺序-CSDN博客](https://blog.csdn.net/helunqu2017/article/details/113360655)



# 9.补充函数

```sql
if()函数：3个参数，如果参数1的值为true，则返回参数2的值，否则返回参数3的值。
ifnull()函数：2个参数，如果参数1的值为null，则返回参数2的值，否则返回参数1的值。
nullif()函数：2个参数，如果参数1与参数2的值相等，返回NULL，否则返回参数1的值。
isnull()函数：1个参数，如果参数1为null，返回1，否则返回0。
```

case when语句：

```sql
CASE 字段 WHEN 预期值 THEN 结果1 ELSE 结果2 END
如果字段值等于预期值，则返回结果1，否则返回结果2。下面通过一个简单的示例来看一下具体用法。

-- 举个例子：
SELECT name,(CASE sex WHEN 0 THEN '女' ELSE '男' END) sex FROM score;
-- 意思是0表示女的，1表示男的。

CASE 
	WHEN condition THEN result1  ELSE result2
END
-- 语句中的condition是条件判断，如果该判断结果为true，那么CASE语句将返回result，否则返回result2，如果没有ELSE，则返回null。
-- CASE与END之间可以有多个WHEN…THEN…ELSE语句。END表示CASE语句结束。
-- 实际使用：score 大于等于90为优秀，80-90为良好，60-80为及格，小于60为不及格，用SQL语句统计出每个学生的成绩级别。
SELECT name,score,(CASE 
	WHEN score>=90 THEN '优秀' 
	WHEN score>=80 THEN '良好' 
	WHEN score>=60 THEN '及格' 
	ELSE '不及格' END) level 
FROM score;
```

```sql
-- distinct函数只有一个参数，参数是字段，作用和distinct关键字一样。
-- DATE_ADD(data, INTERVAL expr)函数：data是日期，一般使用now函数获取当前日期和时间，
-- expr表示数量，可以是正的，也可以是负的，
-- unit表示日期类型，可以是yy.ww.dd等分别表示年、周、天等，还可以有hour表示时间
-- now()函数：返回当前日期和时间。
-- hour()函数：返回小时数字。
-- second()函数：返回秒数字。
```

```sql
-- DATEDIFF函数：求日期的差值，第一个参数值 - 第二个参数值，可以是正值，也可以是负值。
-- 重点：日期要加双引号。
```

```sql
/* 
over的定义：OVER用于为行定义一个窗口，它对一组值进行操作，不需要使用GROUP BY子句对数据进行分组，
能够在同一行中同时返回基础行的列和聚合列。

over()：
count(*) over(partition by employee_id) order by o as cnt
解释：对employee_id分组，统计分组之后每组有多少行，然后根据o字段进行增序排序，将这个新的字段命名为cnt
over函数这样做和group by的区别：group by是分组之后，
*/


```

![image-20231124044027094](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20231124044027094.png)

[SQL窗口函数OVER详细用法，一学就会-CSDN博客](https://blog.csdn.net/liyue071714118/article/details/111714057)

```sql
-- 解释group by关键字和over窗口函数的区别：
表：Employee
+---------------+---------+
| Column Name   |  Type   |
+---------------+---------+
| employee_id   | int     |
| department_id | int     |
| primary_flag  | varchar |
+---------------+---------+
这张表的主键为 employee_id, department_id (具有唯一值的列的组合)
employee_id 是员工的ID
department_id 是部门的ID，表示员工与该部门有关系
primary_flag 是一个枚举类型，值分别为('Y', 'N'). 如果值为'Y',表示该部门是员工的直属部门。 如果值是'N',则否
 
一个员工可以属于多个部门。当一个员工加入超过一个部门的时候，他需要决定哪个部门是他的直属部门。请注意，当员工只加入一个部门的时候，那这个部门将默认为他的直属部门，虽然表记录的值为'N'.

输入：
Employee table:
+-------------+---------------+--------------+
| employee_id | department_id | primary_flag |
+-------------+---------------+--------------+
| 1           | 1             | N            |
| 2           | 1             | Y            |
| 2           | 2             | N            |
| 3           | 3             | N            |
| 4           | 2             | N            |
| 4           | 3             | Y            |
| 4           | 4             | N            |
+-------------+---------------+--------------+
输出：
+-------------+---------------+
| employee_id | department_id |
+-------------+---------------+
| 1           | 1             |
| 2           | 1             |
| 3           | 3             |
| 4           | 3             |
+-------------+---------------+
解释：
- 员工 1 的直属部门是 1
- 员工 2 的直属部门是 1
- 员工 3 的直属部门是 3
- 员工 4 的直属部门是 3

测试表：
Employee =
| employee_id | department_id | primary_flag |
| ----------- | ------------- | ------------ |
| 1           | 1             | N            |
| 2           | 1             | Y            |
| 2           | 2             | N            |
| 3           | 3             | N            |
| 4           | 2             | N            |
| 4           | 3             | Y            |...

over测试语句：
select 
    employee_id,
    department_id,
    primary_flag,
    count(*) over(partition by employee_id) cnt 
from 
    Employee

结果：
| employee_id | department_id | primary_flag | cnt |
| ----------- | ------------- | ------------ | --- |
| 1           | 1             | N            | 1   |
| 2           | 1             | Y            | 2   |
| 2           | 2             | N            | 2   |
| 3           | 3             | N            | 1   |
| 4           | 2             | N            | 3   |
| 4           | 3             | Y            | 3   |
| 4           | 4             | N            | 3   |

group by测试语句：
输出
| employee_id | department_id | primary_flag | cnt |
| ----------- | ------------- | ------------ | --- |
| 1           | 1             | N            | 1   |
| 2           | 1             | Y            | 2   |
| 3           | 3             | N            | 1   |
| 4           | 2             | N            | 3   |
总结：group by的显示结果只能按照组进行展示查询结果，ove窗口函数的显示结果可以按照每一行显示结果。
```

 

```sql
-- 题目名字：180.连续出现的数字
-- 题目链接：https://leetcode.cn/problems/consecutive-numbers/description/?envType=study-plan-v2&envId=sql-free-50
表：Logs
+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| id          | int     |
| num         | varchar |
+-------------+---------+
在 SQL 中，id 是该表的主键。
id 是一个自增列。
找出所有至少连续出现三次的数字。
返回的结果表中的数据可以按 任意顺序 排列。
结果格式如下面的例子所示：
示例 1:
输入：
Logs 表：
+----+-----+
| id | num |
+----+-----+
| 1  | 1   |
| 2  | 1   |
| 3  | 1   |
| 4  | 2   |
| 5  | 1   |
| 6  | 2   |
| 7  | 2   |
+----+-----+
输出：
Result 表：
+-----------------+
| ConsecutiveNums |
+-----------------+
| 1               |
+-----------------+
解释：1 是唯一连续出现至少三次的数字。

使用会话解法：
SELECT 
    num AS ConsecutiveNums
FROM 
(
    SELECT 
        *, 
        @count := IF(@prev = num, @count + 1, 1) AS count, 
        @prev := num
    FROM 
        Logs, 
        (SELECT @count := 0, @prev := NULL) AS vars
    ORDER BY 
        id
) AS tmp
WHERE 
    count >= 3
GROUP BY 
    num;

解释：
在MySQL中，“@”符号表示用户变量。用户变量是一种在会话期间持久存在的变量，可以用于存储和操作数据。
在这个SQL查询语句中，“@count”和“@prev”都是用户变量。它们的作用是：
@count用于计算连续数字序列的长度，即数字连续出现的次数。
@prev用于存储前一个数字，以便与当前数字进行比较，从而确定数字是否连续。
具体地说，在内部查询中，使用了IF函数将当前数字与前一个数字进行比较，如果相等，则将@count的值加1，否则将其重置为1。同时，将当前数字存储在@prev中。通过这种方式，我们可以确定数字是否连续，并计算连续数字序列的长度。
最后，在外部查询中，我们使用WHERE子句过滤掉长度小于3的序列，并使用GROUP BY子句按数字分组输出结果。

详细解释：
详细解释：
当我们使用SQL查询来处理数据时，有时需要使用变量来存储和操作数据。在MySQL中，使用“@”符号表示用户变量。
在这个SQL查询语句中，我们使用了两个用户变量：@count和@prev。
@count变量用于计算连续数字序列的长度。它的初始值为0，表示序列的长度为0。
@prev变量用于存储前一个数字。在查询的开始时，它的值为NULL，表示当前还没有前一个数字。
接下来，我们将详细解释内部查询中的逻辑：
SELECT *,
   @count := IF(@prev = num, @count + 1, 1) AS count,
   @prev := num
FROM
    Logs, 
    (SELECT @count := 0, @prev := NULL) AS vars
ORDER BY
    id
这个查询从表Logs中检索数据，并在每一行记录中计算连续数字序列的长度。
首先，在子查询(SELECT @count := 0, @prev := NULL) AS vars中，我们初始化了用户变量@count和@prev的值。这保证了在主查询的每次执行之前，这两个变量都会被重置为初始值。
然后，我们使用SELECT语句选择了所有的字段（*表示选择所有字段），同时计算了@count和@prev的新值。具体来说：
@count := IF(@prev = num, @count + 1, 1)是一个赋值表达式，用于更新@count的值。它使用了IF函数来判断当前数字num是否与前一个数字@prev相等。如果相等，则将@count的值加1，表示连续数字序列的长度增加；如果不相等，则将@count重置为1，表示重新计算连续数字序列的长度。
@prev := num将当前数字num的值赋给@prev变量，以便在下一次迭代中与新的数字进行比较。
通过这种方式，在查询的执行过程中，我们不断更新@count和@prev的值，以计算连续数字序列的长度。
最后，我们使用外部查询对结果进行过滤和分组：
SELECT 
    num AS ConsecutiveNums
FROM 
(
  -- 内部查询逻辑
) AS tmp
WHERE 
    count >= 3
GROUP BY 
    num
在外部查询中，我们从内部查询的结果中选择了字段num，并根据条件count >= 3过滤掉长度小于3的连续数字序列。然后，我们使用GROUP BY子句按num字段进行分组，以输出每个连续数字序列的唯一数字。

Logs =
| id | num |
| -- | --- |
| 1  | 1   |
| 2  | 1   |
| 3  | 1   |
| 4  | 2   |
| 5  | 1   |
| 6  | 2   |...
内部代码演示：
SELECT 
    *, 
    @count := IF(@prev = num, @count + 1, 1) AS count, 
    @prev := num
FROM 
    Logs, 
    (SELECT @count := 0, @prev := NULL) AS vars
ORDER BY 
    id

输出：输出
| id | num | @count := 0 | @prev := NULL | count | @prev := num |
| -- | --- | ----------- | ------------- | ----- | ------------ |
| 1  | 1   | 0           | null          | 1     | 1            |
| 2  | 1   | 0           | null          | 2     | 1            |
| 3  | 1   | 0           | null          | 3     | 1            |
| 4  | 2   | 0           | null          | 1     | 2            |
| 5  | 1   | 0           | null          | 1     | 1            |
| 6  | 2   | 0           | null          | 1     | 2            |
| 7  | 2   | 0           | null          | 2     | 2            |

全部代码输出：
| ConsecutiveNums |
| --------------- |
| 1               |
```

```sql
-- 第一种方法：三表连接
select
    distinct l1.num as ConsecutiveNums
from
    Logs l1,
    Logs l2,
    Logs l3
where
    l1.id = l2.id - 1
    and l2.id = l3.id - 1
    and l1.num = l2.num
    and l2.num = l3.num;
```

```sql
-- 第二种方法：使用窗口函数：lag函数 或者 lead函数 和over子句
-- over并不是一个函数，而是用来定义窗口函数的子句。
-- 窗口函数和over的用法：<窗口函数> OVER (PARTITION BY <分区列> ORDER BY <排序列>)
-- lag函数：用于获取前一行的值，通过将当前行与前一行的num进行比较，我们可以计算出两个差异值。用于和lag函数进行计算的值有一个是null，计算结果就是null。
/*
lag函数是一种在数据库中常用的窗口函数，它用于访问前一行（相对于当前行）的数据。该函数可以在查询结果中返回指定列的前一行值，从而方便进行比较和计算。
lag函数通常用于分析时间序列数据或进行比较分析。例如，可以使用lag函数计算每个月销售额的增长率，或者计算每个员工的薪资增长情况。
lag函数的语法如下：
LAG(column, offset, default)
其中，column是要获取前一行值的列名或表达式，offset是指定相对于当前行向前的行数（默认为1），default是如果没有前一行时返回的默认值（可选）。
通过使用lag函数，我们可以更方便地进行数据分析和比较计算，提供了更多灵活性和功能性。
*/

-- lead函数：用于获取后一行的数据。
/*
lead函数是数据库中常用的窗口函数之一，它与lag函数相反，用于访问后一行（相对于当前行）的数据。也就是说，lead函数可以在查询结果中返回指定列的后一行值，从而方便进行比较和计算。
lead函数通常用于分析时间序列数据或进行比较分析，类似于lag函数的用途。例如，可以使用lead函数计算每个月销售额的下个月预测值，或者计算每个员工的下个季度的绩效目标。
lead函数的语法如下：
LEAD(column, offset, default)
其中，column是要获取后一行值的列名或表达式，offset是指定相对于当前行向后的行数（默认为1），default是如果没有后一行时返回的默认值（可选）。
通过使用lead函数，我们可以更方便地进行数据分析和比较计算，提供了更多灵活性和功能性。
*/

select
    distinct num ConsecutiveNums
from
(
    select 
        num,
        num - lag(num) over() d1,
        num - lag(num, 2) over() d2
    from 
        logs
) as t1
where 
    d1=0 
    and d2=0;

或者

select
    distinct num ConsecutiveNums
from
(
    select 
        num,
        num - lead(num) over() d1,
        num - lead(num, 2) over() d2
    from 
        logs
) as t1
where 
    d1=0 
    and d2=0;
```

```sql
-- 方法4：使用ROW_NUMBER函数 和 over函数
-- ROW_NUMBER函数：给每行数据添加一个序号。
/*
解释下面的代码：
这段代码的作用是找出连续出现三次及以上的数字。下面是代码的解释：
首先，在子查询中，使用了 ROW_NUMBER() 函数来给每行数据添加一个序号，同时使用 PARTITION BY Num 来确保在每个不同的 Num 值内部按照 Id 的顺序进行排序，并将这些序号作为新的列 rownum。
然后，在主查询中，使用 GROUP BY 子句按照 (id + 1 - rownum), Num 进行分组，其中 id + 1 - rownum 是用来判断连续出现的条件。如果连续出现的数字，它们的 id 和 rownum 之差应该是相等的。同时还有对 Num 进行分组，确保统计的是同一个数字的连续出现情况。
接着使用 HAVING 子句来筛选出满足条件 COUNT(*) >= 3 的分组结果，即连续出现三次及以上的数字。
总的来说，这段代码的逻辑是通过对原始数据进行编号和分组，在分组的基础上判断连续出现的情况，并最终筛选出连续出现三次及以上的数字。
*/
SELECT
    DISTINCT Num ConsecutiveNums
FROM
(
    SELECT 
        *,
        ROW_NUMBER() OVER(PARTITION BY Num ORDER BY Id) rownum
    FROM LOGS
) as t
GROUP BY 
    (id + 1 - rownum), Num    -- 改为(id - rownum), Num 就是错的，错误好像是溢出了，不太懂
HAVING
    COUNT(*) >= 3
    
或者

-- COALESCE函数：并不是将结果转换为有符号整数类型，用于返回参数列表中第一个非空值，并不执行数据类型转换
-- COALESCE函数接受多个参数，返回第一个非空参数的值
-- 如果你需要将结果转换为有符号整数类型，你可以使用数据库系统提供的特定函数来进行类型转换，例如在大多数数据库中可以使用CAST或CONVERT函数。
-- 
SELECT DISTINCT Num AS ConsecutiveNums
FROM
(
    SELECT 
        *,
        ROW_NUMBER() OVER(PARTITION BY Num ORDER BY Id) AS rownum
    FROM LOGS
) AS t
GROUP BY 
    COALESCE(IF(id >= rownum, id - rownum, NULL), 0), Num 
HAVING
    COUNT(*) >= 3;
```

```sql
-- rank窗口函数：用于按照指定的列对结果集中的行进行排名，返回每一行在结果集中的排名。该函数可以根据指定的列的值进行升序或降序排名，并可处理排名值并列的情况。
-- 函数的基本语法：RANK() OVER (PARTITION BY column_name ORDER BY column_name DESC) AS rank
-- RANK()函数需要与OVER子句结合使用，而OVER子句包括PARTITION BY和ORDER BY两个部分：
-- PARTITION BY：可选的，用于按照指定列的值进行分组，排名将在每个分组内独立计算。
-- ORDER BY：必选的，用于指定排名所依据的列，可以指定升序（ASC）或降序（DESC）排名。

-- 力扣：https://leetcode.cn/problems/product-price-at-a-given-date/submissions/?envType=study-plan-v2&envId=sql-free-50
-- 注意点：在MySQL 8.0版本之前，并没有内置的RANK()函数，但可以通过使用用户定义变量来模拟实现排名功能。
-- 思路：
-- 首先，内部最深层的查询将Products表中的数据进行处理，并为每个产品按照filter_date字段的降序排名，使用了RANK()函数来实现。
-- 同时，使用IF()函数判断change_date是否大于'2019-08-16'，如果是，则将filter_date设置为NULL，否则保留原值。
-- 接着，在外层的查询中，从内部查询的结果集中选取排名为1的行，即每个产品中filter_date最大的行。同时，使用DISTINCT关键字来保证product_id与price的唯一性。
SELECT
    distinct product_id, 
    IF(filter_date IS NULL, 10, new_price) AS price
FROM 
(
    SELECT 
        *, 
        RANK() OVER(PARTITION BY product_id ORDER BY filter_date DESC) AS 'rank'     -- 使用的时候需要注意这里不能使用rank，必须加引号
    FROM
    (
        SELECT 
            *, 
            IF(change_date > '2019-08-16', NULL, change_date) AS filter_date
        FROM 
            Products
    ) as T
) as TT
WHERE 
    TT.rank = 1
*/
```

介绍rank和row_number的区别：

RANK()和ROW_NUMBER()是用于在SQL查询中生成行号的窗口函数。它们的主要区别在于如何处理并列的行。

1. RANK():
   - RANK()函数将为具有相同值的行分配相同的排名，并跳过下一个排名。
   - 如果有两个行具有相同的值，并列排名将被分配给它们，而下一个排名将被跳过。
   - 例如，如果有两个行排名第1，则下一个排名将是3，而不是2。
2. ROW_NUMBER():
   - ROW_NUMBER()函数为每一行分配唯一的行号，不存在并列的行。
   - 对于具有相同值的行，它们都将获得不同的行号。
   - 不分组的话，不存在相同的行号。

因此，主要区别在于对于并列的行，RANK()函数会跳过下一个排名，而ROW_NUMBER()函数会继续递增行号。

总结：rank相同的值存在相同的行号，row_number不存在相同的行号。

DENSE_RANK与rank的区别：

`RANK()` 和 `DENSE_RANK()` 函数都可以用于计算排名，但它们在处理分数相同时的行为不同。以下是它们的区别：

1. `RANK()` 函数在分数相同时会跳过相等数量的排名。例如，如果有两个人分数相同并且都排名第一，则下一个人的排名将是第三名，而不是第二名。因此，使用 `RANK()` 函数可能会导致排名出现空缺。
2. `DENSE_RANK()` 函数在分数相同时不会跳过任何排名。例如，如果有两个人分数相同并且都排名第一，则下一个人的排名将是第二名，而不是第三名。因此，使用 `DENSE_RANK()` 函数可以确保没有排名出现空缺，每个人都有一个唯一的排名。

```sql
-- coalesce窗口函数：用于返回参数列表中的第一个非NULL值。如果所有参数都为NULL，则coalesce函数返回NULL。
-- coalesce语法：COALESCE(value1, value2, ..., valuen)
-- 参数可以是任意表达式或者列明
/*
-- 实际例子：
表；
Name    Exam1   Exam2
---------------------
John    85      NULL
Alice   90      88
Bob     NULL    75
Emily   92      NULL

sql语句：
Name    Exam1   Exam2
---------------------
John    85      NULL
Alice   90      88
Bob     NULL    75
Emily   92      NULL

结果：
Name    Exam1   Exam2
---------------------
John    85      NULL
Alice   90      88
Bob     NULL    75
Emily   92      NULL
*/
```

```sql
-- mod函数：是一种用于取模运算的函数，是用于求模运算的标量函数，并不是窗口函数，比如：mod(id, 2)就是取id / 2的余数
-- 结果是1表示是奇数，结果是0表示是偶数

-- 解释一下窗口函数：
-- 窗口函数通常与OVER子句一起使用，它可以对查询结果集中的行进行分组、排序，并计算与当前行相关联的其他行的聚合值，
-- 而不会改变查询结果的行数。一些常见的窗口函数包括ROW_NUMBER、RANK、DENSE_RANK、SUM、AVG等。
```

```sql
-- DATE_FORMAT() 函数是 MySQL 中用于将日期和时间值格式化为指定的字符串的函数。它接受两个参数：日期/时间和格式字符串。
-- 基本语法：DATE_FORMAT(date, format)
-- 参数：date：要格式化的日期或者时间值		format：指定日期或者时间的格式的字符串
/* 
format 字符串包含特定的占位符，当 DATE_FORMAT() 函数应用到 date 参数时，会将这些占位符替换为相应的日期/时间部分。
以下是一些常用的格式占位符：
%Y：四位数的年份（例如：2023）
%y：两位数的年份（例如：23）
%m：月份（01 到 12）
%d：月份中的天数（01 到 31）
%H：小时（00 到 23，24 小时制）
%h：小时（01 到 12，12 小时制）
%i：分钟（00 到 59）
%s：秒（00 到 59）
%p：AM 或 PM（仅适用于 12 小时制）
*/
-- 示例：
SELECT DATE_FORMAT(NOW(), '%Y-%m-%d') AS formatted_date;
-- 输出类似：2023-12-07

SELECT DATE_FORMAT(NOW(), '%Y-%m-%d %H:%i:%s') AS formatted_datetime;
-- 输出类似：2023-12-07 14:20:42

SELECT DATE_FORMAT(NOW(), '%W, %M %e, %Y') AS formatted_date;
-- 输出类似：Wednesday, December 7, 2023
-- 通过使用不同的格式字符串，可以根据需要将日期和时间值格式化为不同的形式，以便在查询结果中使用或显示。
```

```sql
-- to_days函数：是一个mysql内置函数，用于将日期转换为对应的天数表示。
-- 语法：TO_DAYS(date)
-- 参数：date是一个日期值或者日期表达式。
-- 返回值：返回从公元 0 年（0000-00-00）开始计算的指定日期所经过的天数。这个值是一个整数，表示指定日期与公元 0 年之间的天数差。
-- 例子：
SELECT TO_DAYS('2023-01-01');
-- 返回：738050（公元 0 年至 2023-01-01 的天数差）

SELECT TO_DAYS('2023-12-31') - TO_DAYS('2023-01-01');
-- 返回：364（2023 年的天数）

SELECT TO_DAYS(NOW());
-- 返回：738104（公元 0 年至当前日期的天数差）

-- TO_DAYS() 函数只能接受日期值作为参数，它不适用于时间戳或时间类型的值。如果需要将时间戳转换为天数表示，
-- 可以先使用 FROM_UNIXTIME() 函数将时间戳转换为日期，然后再使用 TO_DAYS() 函数进行转换。
-- 此外，也有一些其他的日期和时间函数可用于获取日期和时间的部分信息，例如 YEAR()、MONTH()、DAY() 等函数可以用于提取日期的年份、月份和日期等信息。
```

```sql
-- FROM_UNIXTIME()函数是一个MySQL内置函数，用于将UNIX时间戳转换为对应的日期时间格式。它的语法如下：FROM_UNIXTIME(unix_timestamp, format)
-- 其中unix_timestamp是一个整数值，表示从UNIX纪元（1970年1月1日00:00:00UTC）开始计算的秒数。
-- format 是一个可选参数，用于指定输出的日期时间格式，默认为 %Y-%m-%d %H:%i:%s。
-- FROM_UNIXTIME()函数会根据指定的UNIX时间戳和日期时间格式，返回一个对应的日期时间字符串。

-- 以下是一些示例：
SELECT FROM_UNIXTIME(1638960000);
-- 返回：2021-12-09 00:00:00（默认格式）

SELECT FROM_UNIXTIME(1638960000, '%Y-%m-%d');
-- 返回：2021-12-09（指定格式）

SELECT FROM_UNIXTIME(1638960000, '%W, %M %e, %Y');
-- 返回：Thursday, December 9, 2021

-- 需要注意的是，UNIX时间戳是一个以秒为单位的整数值，表示从UNIX纪元开始到指定时间点经过的秒数。
-- 如果需要将日期时间转换为UNIX时间戳，可以使用 UNIX_TIMESTAMP()函数。

-- 此外，还可以通过在日期时间格式中使用不同的占位符来自定义输出的日期时间格式。
-- 常用的占位符包括%Y（四位数的年份）、%m（两位数的月份）、%d（两位数的日期）、%H（24 小时制的小时数）、%i（分钟数）等，具体可以根据需求选择合适的占位符组合。

-- 总之，FROM_UNIXTIME() 函数是一个用于将 UNIX 时间戳转换为日期时间格式的 MySQL 函数，可以根据指定的时间戳和日期时间格式返回对应的日期时间字符串。
```

```sql
-- CONCAT 函数用于将两个或多个字符串合并成一个字符串。在 MySQL 中，你可以使用 CONCAT 函数来连接列值或者字符串常量。
-- 下面是 CONCAT 函数的基本用法：
SELECT 
	CONCAT(column1, column2) AS concatenated_column
FROM 
	your_table;
-- 在这个例子中，column1 和 column2 的值将被连接在一起，并且作为 concatenated_column 列的输出。

-- 你还可以使用 CONCAT 来连接字符串常量，比如：
SELECT 
	CONCAT('Hello', 'World') AS greeting;
-- 这将输出 Hello World。
```

```sql
-- SUBSTRING函数：是用来提取字符串的一部分。

-- 语法：SUBSTRING(str, start, length)

-- 参数：
-- str是要提取子字符串的原始字符串。
-- start是要开始提取的位置，可以是一个正整数或负整数。如果是正整数，表示从字符串的左侧开始计数；如果是负整数，表示从字符串的右侧开始计数。
-- length 是要提取的字符数量。length省略了，，不写默认为空，就会返回第二个参数后面的所有字符构成的字符串。（第二个参数到字符串结尾）

-- 使用SUBSTRING函数可以从一个字符串中提取指定长度的子字符串。
-- 例如，SUBSTRING('Hello World', 1, 5) 将返回 'Hello'，因为它从第一个字符开始提取了 5 个字符。
-- SUBSTRING(name, 1, 1) 的作用是从名字字段中提取第一个字符作为子字符串，即名字的首字母。
```

```sql
-- UPPER函数：是用来将字符串转换为大写字母形式的函数。

-- 语法：UPPER(str)
-- 参数：str是要进行大小写转换的字符串。

-- 使用UPPER函数可以将字符串中的所有字符都转换为大写形式。
-- 例如，UPPER('hello') 将返回 'HELLO'。

-- UPPER(SUBSTRING(name, 1, 1)) 的作用是将名字的首字母转换为大写形式。
```

```sql
-- LOWER函数：是用来将字符串转换为小写字母形式的函数。

-- 语法：LOWER(str)
-- 参数：str是要进行大小写转换的字符串。

-- 使用LOWER函数可以将字符串中的所有字符都转换为小写形式。
-- 例如，LOWER('HELLO') 将返回 'hello'。

-- LOWER(SUBSTRING(name, 2)) 的作用是将名字除了首字母以外的部分转换为小写形式。
```

```sql
-- LENGTH(str) : 获取字符串的长度
-- LEFT(str,len) : 获取字符串左边 len 个字符
-- RIGHT(str,len) : 获取字符串右边 len 个字符
-- SUBSTR(str,start,len) : 获取 str 中从 start 开始的 len 个字符
```

```sql

```











# 10.窗口函数的详细介绍

窗口函数（Window Function）是SQL语言中一种强大的数据分析工具，它可以对关系型数据库中的数据进行分组、排序、累计、排名等操作。窗口函数可以在SELECT语句中指定一个或多个窗口，用于计算每行与其它行之间的逻辑关系，从而实现一些高级的聚合和分析操作。

```sql
-- 窗口函数的语法形式：<窗口函数>([expression]) OVER ([PARTITION BY <partition_expression>] [ORDER BY <sort_expression> [ASC | DESC]] [<window_frame_clause>])
```

其中，`<窗口函数>`表示要执行的窗口函数名称，`[expression]`表示要计算的表达式或字段名，`OVER`关键字指定了窗口，`[PARTITION BY <partition_expression>]`表示分组条件，`[ORDER BY <sort_expression> [ASC | DESC]]`表示排序方式，`[<window_frame_clause>]`表示窗口范围。

常见的窗口函数包括：

- `ROW_NUMBER()`：为每行返回一个唯一的整数值。
- `RANK()`：计算行在结果集中的排名，如果有并列的行，则会产生相同的排名。
- `DENSE_RANK()`：计算行在结果集中的排名，如果有并列的行，则会跳过相同的排名。
- `NTILE(n)`：将结果集分成n份，并为每行分配一个桶号。
- `SUM()、AVG()、MIN()、MAX()`：用于计算每组数据的聚合值，可以在窗口函数中使用。

窗口函数的使用规范如下：

1. 分组条件：如果要对每个分组进行计算，需要使用`PARTITION BY`子句指定分组条件。如果不指定分组条件，则整个查询结果集将被视为一个分组。
2. 排序方式：如果需要按照某种顺序进行计算，可以使用`ORDER BY`子句指定排序方式。如果不指定排序方式，则默认按照源表中返回行的顺序计算。
3. 窗口范围：可以使用`ROW`或`RANGE`关键字定义窗口范围。其中，`ROW`表示基于行数的窗口，`RANGE`表示基于值域的窗口。可以使用`UNBOUNDED PRECEDING`、`CURRENT ROW`、`UNBOUNDED FOLLOWING`等关键字指定窗口的开始和结束位置。例如，`RANGE BETWEEN 1 PRECEDING AND 1 FOLLOWING`表示窗口包括当前行与前一行和后一行的数据。
4. 窗口函数的语法：窗口函数的语法是在SELECT语句中使用的，不能在WHERE、JOIN和GROUP BY子句中使用。此外，窗口函数也不能嵌套使用。

总之，窗口函数是SQL语言中非常强大的数据分析工具，可以用于各种数据累计、分组、排序和排名等操作。在使用窗口函数时，需要注意分组条件、排序方式和窗口范围的使用规范，以确保结果的正确性和有效性。

## 10.1详细介绍窗口范围

窗口范围是窗口函数中一个非常重要的概念，它用于定义每个窗口包含的数据行的范围。窗口范围分为两种类型：基于行数的窗口和基于值域的窗口。

1. 基于行数的窗口（rows）

基于行数的窗口是指窗口函数所涉及到的数据行的物理位置。在窗口函数中，使用`ROWS`关键字来指定窗口范围的类型。以下是`ROWS`关键字的一些常见用法：

- `ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW`：表示计算当前行及其之前的所有行。
- `ROWS BETWEEN CURRENT ROW AND UNBOUNDED FOLLOWING`：表示计算当前行及其之后的所有行。
- `ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING`：表示计算当前行及其相邻的前一行和后一行

​	2.基于值域的窗口（range）

基于值域的窗口是指窗口函数所涉及到的数据行的排序位置。在窗口函数中，使用`RANGE`关键字来指定窗口范围的类型。以下是`RANGE`关键字的一些常见用法：

- `RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW`：表示计算当前行及其之前的所有行，以当前行的值作为窗口的结束点。
- `RANGE BETWEEN CURRENT ROW AND UNBOUNDED FOLLOWING`：表示计算当前行及其之后的所有行，以当前行的值作为窗口的开始点。
- `RANGE BETWEEN 1 PRECEDING AND 1 FOLLOWING`：表示计算当前行及其相邻的前一行和后一行，以当前行的值作为窗口的中心点。

需要注意的是，在基于值域的窗口中，使用`RANGE`关键字时必须指定`ORDER BY`子句，以便对窗口内的数据进行排序。

在使用窗口范围时，有几个重要的概念需要理解：

- `UNBOUNDED PRECEDING`：表示窗口的起点是无限远，即从结果集的第一行开始计算。
- `CURRENT ROW`：表示窗口的起点是当前行。
- `UNBOUNDED FOLLOWING`：表示窗口的终点是无限远，即到结果集的最后一行结束计算。
- `PRECEDING`：表示相对当前行的前N行。例如，`1 PRECEDING`表示相对当前行的前一行。
- `FOLLOWING`：表示相对当前行的后N行。例如，`1 FOLLOWING`表示相对当前行的后一行。

例如，以下是一个窗口函数的示例：

```sql
SELECT 
	item_id,
    sale_date,
    sale_qty,
    SUM(sale_qty) OVER(PARTITION BY item_id ORDER BY sale_date ROWS BETWEEN 2 PRECEDING AND CURRENT ROW) AS sum_qty
FROM
	sales;
```

在这个示例中，窗口函数`SUM()`用于计算每个商品的连续三天销售量总和。使用`PARTITION BY`对商品进行分组，使用`ORDER BY`按照日期排序，使用`ROWS BETWEEN 2 PRECEDING AND CURRENT ROW`指定了窗口范围为当前行及其前两行。

总之，窗口范围是窗口函数中非常重要的概念，它用于定义每个窗口包含的数据行的范围。在使用窗口函数时，需要根据具体情况选择合适的窗口范围类型，并使用合适的起点和终点来计算结果。



# 11.正则表达式

在 MySQL 中，正则表达式是一种强大的工具，用于匹配和操作文本数据。MySQL 提供了多个内置函数来支持正则表达式的使用，包括 REGEXP、REGEXP_LIKE、REGEXP_REPLACE 等函数。

以下是一些常用的 MySQL 正则表达式函数及其简单使用：

1. REGEXP：用于检查一个字符串是否与指定的正则表达式匹配。

   ```sql
   SELECT 
   	column 
   FROM 
   	table 
   WHERE 
   	column REGEXP 'pattern';
   ```

2. REGEXP_LIKE：用于检查一个字符串是否与指定的正则表达式匹配，返回布尔值。

   ```sql
   SELECT 
   	column 
   FROM 
   	table 
   WHERE 
   	REGEXP_LIKE(column, 'pattern');
   ```

3. REGEXP_REPLACE：用于在字符串中使用正则表达式进行替换操作。

   ```sql
   SELECT 
   	REGEXP_REPLACE(column, 'pattern', 'replacement') 
   FROM 
   	table;
   ```

4. REGEXP_INSTR：用于返回一个字符串在另一个字符串中第一次出现的位置。

   ```sql
   SELECT 
   	REGEXP_INSTR(column, 'pattern') 
   FROM 
   	table;
   ```

5. REGEXP_SUBSTR：用于从字符串中提取满足正则表达式的子字符串。

   ```sql
   SELECT 
   	REGEXP_SUBSTR(column, 'pattern') 
   FROM
   	table;
   ```

在上述函数中，'pattern' 是要匹配的正则表达式。正则表达式可以使用各种元字符和模式匹配符来定义规则，如 `.`（匹配任意字符）、`*`（匹配零个或多个前面的元素）、`+`（匹配一个或多个前面的元素）等。

以下是一个简单示例，展示如何使用 REGEXP 函数来查询以 'A' 开头的字符串：

```sql
SELECT 
	column 
FROM 
	table 
WHERE 
	column REGEXP '^A';
```



在正则表达式中，可以使用一些特殊的元字符来进行模糊匹配。下面是一些常用的元字符用于模糊匹配的示例：

1. `.`：匹配任意单个字符（除了换行符）。
   - 示例：`a.b` 可以匹配 "aab"、"acb"、"axb" 等。
2. `*`：匹配前一个元素零次或多次。
   - 示例：`ab*c` 可以匹配 "ac"、"abc"、"abbc"、"abbbc" 等。
3. `+`：匹配前一个元素一次或多次。
   - 示例：`ab+c` 可以匹配 "abc"、"abbc"、"abbbc" 等，但不能匹配 "ac"。
4. `?`：匹配前一个元素零次或一次。
   - 示例：`ab?c` 可以匹配 "ac"、"abc"，但不能匹配 "abbc"。
5. `[]`：用于指定一个字符集合，匹配其中的任意一个字符。
   - 示例：`[aeiou]` 可以匹配任意一个元音字母。
   - 示例：`[0-9]` 可以匹配任意一个数字字符。
6. `[^]`：用于指定一个排除的字符集合，匹配不在集合中的任意一个字符。
   - 示例：`[^aeiou]` 可以匹配任意一个非元音字母。
7. `()`：用于分组多个元素，可以对分组应用其他限定符。
   - 示例：`(ab)+` 可以匹配 "ab"、"abab"、"ababab" 等。

这些元字符可以结合使用，以构建更复杂的模糊匹配规则。需要注意的是，正则表达式是区分大小写的，如果需要进行不区分大小写的匹配，可以在表达式前面加上 `(?i)` 或使用 `REGEXP` 函数的参数指定 `i` 标志。



在 MySQL 中，你可以使用 REGEXP 运算符来检查一个字符串是否包含另一个字符串。下面是一个示例查询，用于在字符串中查找是否包含指定的子字符串：

```sql
SELECT 
	column 
FROM 
	table
WHERE 
	column REGEXP 'pattern';
```

在上述查询中，`column` 是要搜索的列名，`table` 是要搜索的表名，`pattern` 是要匹配的正则表达式模式。

例如，如果你想在 `content` 列中查找是否包含字符串 "example"，可以使用以下查询：

```sql
SELECT 
	content 
FROM 
	table 
WHERE 
	content REGEXP 'example';
```

这将返回所有包含 "example" 字符串的记录。

需要注意的是，REGEXP 运算符默认情况下是大小写敏感的，如果你希望进行不区分大小写的匹配，可以在查询中添加 `COLLATE` 子句，并选择适当的字符集和排序规则。例如：

```sql
SELECT 
	content 
FROM 
	table 
WHERE 
	content COLLATE utf8_general_ci REGEXP 'example';
```

在上述查询中，`utf8_general_ci` 表示使用 UTF-8 字符集和不区分大小写的排序规则进行匹配。

















