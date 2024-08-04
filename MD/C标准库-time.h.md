
<!-- TOC -->
  * [标准库 `<time.h>`](#标准库-timeh)
    * [1. 变量类型](#1-变量类型)
    * [2. 宏](#2-宏)
    * [3. 函数](#3-函数)
* [time()函数](#time函数)
* [localtime()函数](#localtime函数)
* [gmtime()函数](#gmtime函数)
* [strftime()函数](#strftime函数)
* [asctime()函数](#asctime函数)
* [ctime()函数](#ctime函数)
* [mktime()函数](#mktime函数)
* [nanosleep()函数](#nanosleep函数)
* [clock_getres()函数](#clock_getres函数)
* [clock_gettime()函数](#clock_gettime函数)
* [clock_settime()函数](#clock_settime函数-)
* [timespec_get()函数](#timespec_get函数)
<!-- TOC -->
## 标准库 `<time.h>`


time.h 头文件定义了四个变量类型、两个宏和各种操作日期和时间的函数。

<time.h> 是 C 标准库中的一个头文件，提供了处理和操作日期和时间的函数和类型。这个头文件中的函数用于获取当前时间、设置时间、格式化时间和计算时间差等。

### 1. 变量类型

time.h 头文件定义了以下变量类型 ：
> size_t：它是一个无符号整数类型，用来表示字符串的长度。
> time_t：它是一个整数类型，用来表示时间的秒数。
> clock_t：它是一个整数类型，用来表示 CPU 时间。
> tm：它是一个结构类型，用来表示日期和时间。

tm 结构类型定义如下：

```c
struct tm {
    int tm_sec;         /* 秒 范围从 0 到 59 */
    int tm_min;         /* 分 范围从 0 到 59 */
    int tm_hour;        /* 时 范围从 0 到 23 */
    int tm_mday;        /* 月中的第几天 范围从 1 到 31 */
    int tm_mon;         /* 月份（从 0 到 11） */
    int tm_year;        /* 年份（从 1900 开始） */
    int tm_wday;        /* 星期几（从 0 到 6，0 是星期日） */
    int tm_yday;        /* 年中的第几天 范围从 0 到 365*/
    int tm_isdst;       /* 夏令时 */
  
```
### 2. 宏

time.h 头文件定义了以下宏：

- `NULL`：它是一个值为 0 的指针常量。
- `CLOCKS_PER_SEC`：它是一个常量，它的值等于每秒的时钟周期数。
- `TIME_UTC`：它是一个常量，它的值等于 1，表示以 Coordinated Universal Time (UTC) 作为时间基准。

### 3. 函数

time.h 头文件定义了以下函数：

- `clock_t clock()`：它返回程序运行的 CPU 时间。
- 
- `time_t time(time_t *t)`：它返回从 1970 年 1 月 1 日 00:00:00 UTC 到现在的秒数。如果 t 非空指针，则它将存储当前时间。
- 
- `double difftime(time_t time1, time_t time2)`：它返回 time1 和 time2 之间的秒数差值。
- 
- `struct tm *localtime(const time_t *timep)`：它将时间戳转换为 tm 结构。
- 
- `struct tm *gmtime(const time_t *timep)`：它将时间戳转换为 tm 结构，并以 Coordinated Universal Time (UTC) 作为时间基准。
- 
- `size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *tm)`：它根据 tm 结构和 format 字符串，将时间格式化为字符串。
- 
- `char *asctime(const struct tm *tm)`：它将 tm 结构转换为字符串。
- 
- `char *ctime(const time_t *timep)`：它将时间戳转换为字符串。
- 
- `time_t mktime(struct tm *tm)`：它将 tm 结构转换为时间戳。
- 
- `int nanosleep(const struct timespec *req, struct timespec *rem)`：它使程序暂停一段时间。
- 
- `int clock_getres(clockid_t clk_id, struct timespec *res)`：它获取 clk_id 对应的时钟的最小精度。
- 
- `int clock_gettime(clockid_t clk_id, struct timespec *tp)`：它获取 clk_id 对应的时钟的时间。
- 
- `int clock_settime(clockid_t clk_id, const struct timespec *tp)`：它设置 clk_id 对应的时钟的时间。
- 
- `int timespec_get(struct timespec *ts, int base)`：它将时间戳转换为 timespec 结构。


# time()函数

time()函数用来获取当前时间，返回值是从 1970 年 1 月 1 日 00:00:00 UTC 到现在的秒数。如果 t 非空指针，则它将存储当前时间。

```c
#include <time.h>

int main() {
    time_t now;
    time(&now);
    printf("The current time is: %ld\n", now);
    return 0;
}
```

# localtime()函数

localtime()函数用来将时间戳转换为 tm 结构，并以本地时间作为时间基准。

```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t now;
    struct tm *local_time;
    time(&now);
    local_time = localtime(&now);
    printf("The current local time is: %s\n", asctime(local_time));
    return 0;
}
```

# gmtime()函数

gmtime()函数用来将时间戳转换为 tm 结构，并以 Coordinated Universal Time (UTC) 作为时间基准。

```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t now;
    struct tm *utc_time;
    time(&now);
    utc_time = gmtime(&now);
    printf("The current UTC time is: %s\n", asctime(utc_time));
    return 0;
}
```

# strftime()函数

strftime()函数用来根据 tm 结构和 format 字符串，将时间格式化为字符串。

```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t now;
    struct tm *local_time;
    char time_str[100];
    time(&now);
    local_time = localtime(&now);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    printf("The current local time is: %s\n", time_str);
    return 0;
}
```


# asctime()函数

asctime()函数用来将 tm 结构转换为字符串。

```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t now;
    struct tm *local_time;
    char time_str[100];
    time(&now);
    local_time = localtime(&now);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    printf("The current local time is: %s\n", time_str);
    return 0;
}
```

# ctime()函数

ctime()函数用来将时间戳转换为字符串。

```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t now;
    char time_str[100];
    time(&now);
    ctime_r(&now, time_str);
    printf("The current local time is: %s\n", time_str);
    return 0;
}
```


# mktime()函数

mktime()函数用来将 tm 结构转换为时间戳。

```c
#include <time.h>
#include <stdio.h>

int main() {
    time_t now;
    struct tm local_time;
    time(&now);
    local_time = *localtime(&now);
    local_time.tm_hour = 10;
    local_time.tm_min = 30;
    local_time.tm_sec = 0;
    time_t new_time = mktime(&local_time);
    printf("The new time is: %ld\n", new_time);
    return 0;
}
```


# nanosleep()函数

nanosleep()函数用来使程序暂停一段时间。

```c
#include <time.h>
#include <stdio.h>
#include <unistd.h>


int main() {
    struct timespec req, rem;
    req.tv_sec = 1;
    req.tv_nsec = 0;
    nanosleep(&req, &rem);
    printf("The program has slept for 1 second.\n");
    return 0;
}
```


# clock_getres()函数


clock_getres()函数用来获取 clk_id 对应的时钟的最小精度。

```c
#include <time.h>
#include <stdio.h>

int main() {
    struct timespec res;
    clock_getres(CLOCK_REALTIME, &res);
    printf("The minimum resolution of CLOCK_REALTIME is %ld nanoseconds.\n", res.tv_nsec);
    return 0;
}
```


# clock_gettime()函数


clock_gettime()函数用来获取 clk_id 对应的时钟的时间。

```c
#include <time.h>
#include <stdio.h>

int main() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    printf("The current time is: %ld.%09ld\n", tp.tv_sec, tp.tv_nsec);
    return 0;
}
```


# clock_settime()函数 


clock_settime()函数用来设置 clk_id 对应的时钟的时间。

```c
#include <time.h>
#include <stdio.h>

int main() {
    struct timespec tp;
    tp.tv_sec = 1580000000; // 2020-02-01 00:00:00 UTC
    tp.tv_nsec = 0;
    clock_settime(CLOCK_REALTIME, &tp);
    printf("The time has been set to 2020-02-01 00:00:00 UTC.\n");
    return 0;
}
```


# timespec_get()函数


timespec_get()函数用来将时间戳转换为 timespec 结构。

```c
#include <time.h>
#include <stdio.h>


int main() {
    struct timespec ts;
    time_t now;
    time(&now);
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("The current time is: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
    return 0;
}
```

