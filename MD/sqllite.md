# 数据库
## sqlite3的安装：
> sudo apt install sqlite3
> 
>验证是否安装成功：
> 
>sqlite3 --version
> 
>sqlite3 --help

## sqlite3的使用：
### 启动sqlite3

> sqlite3 xxx.db  

```c++

===>用sqlite3 来打开一个名称为test.db的本地数据库。

			出现如下提示符：表明数据库管理系统启动。
			sqlite> 

	  		退出数据库： 
	   		.q 命令
			
			注意：如果一直出现如下符号：
			...>   
			则写';'结束。
            
            以下所有命令必须在 sqlite> 后执行。
            
            创建一个数据库：
		1、touch  xxx.db
		2、sqlite3 xxx.db

	1、系统维护命令：===> .help
		出现所有相关的系统维护命令，都是以 "."开头。
		.database  列出当前系统中的所有数据库
		.tables    列出当期数据库中的所有表
		.schema xxx 列出当前指定的xxx表结构
        .databases 列出所有数据库的名称和路径
        .quit      退出sqlite3命令行
        .exit      退出sqlite3命令行
        .headers   显示表头
        .mode      显示模式
        .nullvalue 显示NULL值
        .output    输出到文件
        .dump      导出数据库
        .read      导入数据库
        .help      显示帮助信息
        .shell     进入shell命令行
        .dump      导出数据库
        .restore   导入数据库
        .clone     克隆数据库
        .load      加载扩展库
        .log       显示日志信息
        .trace     显示执行过程
        .expert    显示expert模式
        .dumpschema 导出数据库的结构
        .dump       导出数据库
        .restore    导入数据库
        .backup     备份数据库
        .restore    导入数据库
        .verify     校验数据库
        .pragma     设置编译选项
        .once       只执行一次的命令
        .restore_cmd 导入数据库的命令
        .backup_cmd 备份数据库的命令
        .init       初始化数据库
        .clone_cmd  克隆数据库的命令
        .dump_cmd   导出数据库的命令
        
		.dump  >xxx.sql  ===>导出数据库
		sqlite3 xxx.db < test.sql ===>导入数据库



	2、标准SQL语句：===》通用语法在其他平台可以直接使用。
		注意：所有的sql语句都以';'结尾。
		创建一个表：
		create table  表名(表字段1，表字段2，...);
		eg: create table user(id,name,age);
		注意：以上表的表字段，支持如下数据类型。int text real blob
			  默认是text类型。

		create table 表名 （表字段 类型，表字段 类型，。。。。);
		eg:
		create table user(id int ,name text,age int);
     
        
		删除一个表：
		drop table  表名；
		eg：drop table user;
	   数据库常规操作： 增加 删除 修改 查询
	   向表中增加数据：
	   insert into 表名 (字段名称 ) values (值名称);
	   eg:insert into user (id,name,age) values (1,"zhang",10);

	   insert into user values(3,"wang",11);
	   insert into user (name) values ( "li");

	   查询表中的数据：
	   select 列名 from 表名  条件；
	   eg：select * from user ;
	       select id from user;
		 select id,name from user where age = 11;

	   修改表中数据：
	   update 表名 set 表字段 = 值  满足条件：
	   eg： update user set id = 1 where name = 'li';
	   update user set id = 1 where name = "li" and passwd = "123";
	   update user set id = 2 where name = "li" or  name = "zhao";

	   修改表的字段：
	   alter table 表名 add  xxx;
	   alter tables 表明 drop column  xxx; ////sqlite3 不支持


	   eg:alter table user add age;


	   删除表中数据：
	   delete from 表名  满足条件：
	   eg：delete from user ;  ///删除表中所有数据
	   	   delete from user where id  = 1; ///删除id=1 的数据；
		   delete from user where id =1 and name = "zhang";
		   delete from user where id = 1 or id  = 2;
```



## 维护命令：

```c++
1、数据的导出：
sqlite3 xxx.db .dump > xxx.sql
//将数据库名称为xxx的数据库整体导出到脚本中。

		sqlite3> .output xxx.sql
			     .dump xxx ===>xxx是表名
	//将数据库中某个指定的xxx表导出到脚本中。
	

2、数据的导入：
sqlite3 xxx.db < xxx.sql
//将xxx.sql脚本导入到xxx.db数据库中。

		sqlite3> .read xxx.sql
			     .exit ===>退出数据库
                         
	//将xxx.sql脚本导入到当前打开的数据库中。
    
    
    
3、可视化工具安装：sqliteman-1.2.2.tar.gz
3.1  tar -zxvf sqliteman-1.2.2.tar.gz

		 yum install cmake
         
		 yum install qt-devel

    

	3.2  cmake .    
    
    
	cmake -DWANT_INTERNAL_QSCINTILLA=1

	3.3  make
	3.4  make install


```




# sqlite3 数据库编程接口：

## 1、需要的头文件
sqlite3.h

## 2、编译过程
-lsqlite3

## 3、编程框架：
打开数据库 ==》读写数据库(增，删，改，查) ==》关闭数据库
```c++

3.1 打开数据库： sqlite3_open
int sqlite3_open(char * path,sqlite3 ** db);
功能：打开指定path路径+文件名称的数据库，并将
打开的地址指向db变量的句柄。
参数：path 要打开的数据库路径+名称
db  要打开的数据库地址指针
返回值：成功  0
失败  -1；

	SQLITE_OK 宏（代表成功）


3.2 关闭数据库： sqlite3_close
int sqlite3_close(sqlite3 *db);
功能：关闭指定的数据库
参数：要关闭的数据库地址
返回值：成功  0
失败  -1；

3.3 数据库操作：
查询操作：sqlite3_get_table();  ////select

	int sqlite3_get_table(sqlite3 *db,char *sql,
					char *** rest,int *nrow,int *ncol,
					char ** errmsg);

	功能：在db数据库上执行sql查询语句，并将执行的
		  结果集返回到rest地址上，同时返回查询的行和列。
	参数：  db 要执行查询语句的数据库
	        sql  要执行的select查询语句
		  rest 查询的结果集是一个三级指针
		  nrow 查询的结果的行数
		  ncol 查询的结果的列数
		  errmsg 如果执行有错误，则存储错误。
	返回值：成功 0
			失败 非0；

	执行sql语句：sqlite3_exec();   ////insert delete update

	int sqlite3_exec(sqlite3 *db,char *sql,callback fun,
					void * arg,char ** errmsg);

	功能：在db数据库上执行sql 非查询语句。
		  并将结果返回。
	参数：  db 要执行sql的数据库
		  sql  要执行的非查询sql语句。
		  fun  如果该函数要执行查询语句，则该回调函数
		  	   用来回收查询的结果。
		  arg  回调函数的参数，如果没有回调函数则该参数为NULL；
		  errmsg  执行过程中的错误信息。
	返回值：执行成功  0
			失败  非0 ；

	int fun(void *arg ,int f_num,char ** f_value,char ** f_name)
	功能：该函数用于sqlite3_exec执行select语句的
		  结果集返回数据。
	参数：arg 由sqlite3_exec传入的参数
		  f_num 执行该命令所返回测结果集的字段个数。
		  f_value 查询结果集中的字段的值。
		  f_name  查询结果集中的字段的名称。
	返回值：成功 0
			失败 非0
	注意：该回调函数必须有返回值，否则可能导致查询异常。



```


	



# sqllite 事务处理：

```c++
事务处理：

事务是指一组数据库操作，要么全部成功，要么全部失败。

事务处理的特点：
1、原子性：事务是一个不可分割的工作单位，事务中包括的各个操作要么全部成功，要么全部失败。
2、一致性：事务必须是数据库从一个一致性状态变到另一个一致性状态。一致性与原子性是密切相关的。
3、隔离性：一个事务的执行不能被其他事务干扰。即一个事务内部的操作及使用的数据对并发的其他事务是隔离的，并发执行的各个事务之间不能互相干扰。
4、持久性：一个事务一旦提交，它对数据库中数据的改变就持久化了。接下来的其他操作或故障不应该对其有任何影响。

事务处理的原理：
事务处理的原理是通过日志来实现的。事务处理的日志记录了事务开始、结束的时间、操作的类型、操作的SQL语句等信息。

使用:
1、开始事务：sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
2、提交事务：sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &zErrMsg);
3、回滚事务：sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &zErrMsg);




```

## sqlite3_exec函数:


```c++
int sqlite3_exec(sqlite3 *db,const char *sql,
                 int (*callback)(void*,int,char**,char**),
                 void *arg,char **errmsg);

功能：在db数据库上执行sql 非查询语句。并将结果返回。
参数：  db 要执行sql的数据库
      sql  要执行的非查询sql语句。
      callback  如果该函数要执行查询语句，则该回调函数用来回收查询的结果。
      arg  回调函数的参数，如果没有回调函数则该参数为NULL；
      errmsg  执行过程中的错误信息。
返回值：执行成功  0
        失败  非0 ；


```

## 示例:

```c++
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>


int callback(void *arg, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)", NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "INSERT INTO test(name, age) VALUES('zhang', 10)", NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "INSERT INTO test(name, age) VALUES('wang', 11)", NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "SELECT * FROM test", callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "UPDATE test SET age = 12 WHERE name = 'wang'", NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "SELECT * FROM test", callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "DELETE FROM test WHERE age = 12", NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, "SELECT * FROM test", callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    return 0;
}


```