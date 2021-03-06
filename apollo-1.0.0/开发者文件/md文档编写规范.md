大标题
======
中标提
------
如果你只输入了等于号=，但其上方无文字，那么就只会显示一条直线。如果上方有了文字，但你又只想显示一条横线，而不想把上方的文字转义成大标题的话，那么你就要在等于号=和文字直接补一个空行。  

补空行：是很常用的用法，当你不想上下两个不同的布局方式交错到一起的时候，就要在两种布局之间补一个空行。  

如果你只输入了短横线（减号）-，其上方无文字，那么要显示直线，必须要写三个减号以上。不过与等于号的显示效果不同，它显示出来时虚线而不是实线。同减号作用相同的还有星号*和下划线_，同样的这两者符号也要写三个以上才能显示一条虚横线。  

# 一级标题  
## 二级标题  
### 三级标题  
#### 四级标题  
##### 五级标题  
###### 六级标题  

直接输入的文字就是普通文本。需要注意的是要换行的时候不能直接通过回车来换行，需要使用<br>(或者<br/>)。也就是html里面的标签。事实上，markdown支持一些html标签，你可以试试。当然如果你完全使用html来写的话，就丧失意义了，毕竟markdown并非专门做前端的，然而仅实现一般效果的话，它会比html写起来要简洁得多得多啦。  

这是一段普通的文本，  
直接回车不能换行，<br>  
要使用\<br>  
换行也可在段尾加两个空格  
# 多行文本

多行文本和单行文本异曲同工，只要在每行行首加两个Tab  

如果你想使一段话中部分文字高亮显示，来起到突出强调的作用，那么可以把它用 `  ` 包围起来。注意这不是单引号，而是Tab上方，数字1左边的按键（注意使用英文输入法）。  

# 文字超链接
给一段文字加入超链接的格式是这样的 [ 要显示的文字 ]( 链接的地址 )。比如：  
[我的博客](http://blog.csdn.net/guodongxiaren)  
#插入圆点符号
* 昵称：果冻虾仁  
* 别名：隔壁老王  
* 英文名：Jelly  
此外还有二级圆点和三级圆点。就是多加一个Tab。  
#缩进

缩进的含义是很容易理解的。。
>数据结构  
>>树  
>>>二叉树  
>>>>平衡二叉树  
>>>>>满二叉树  
# 来源于网络的图片
可以使用的最简单，最基本的语法是：  
![](http://www.baidu.com/img/bdlogo.gif)  
即 叹号! + 方括号[ ] + 括号( ) 其中叹号里是图片的URL。  
如果不加叹号! ,就会变成普通文本baidu了。  
在方括号里可以加入一些标识性的信息，比如  
![baidu](http://www.baidu.com/img/bdlogo.gif)  
如果你想达到鼠标悬停显示提示信息  
![baidu](http://www.baidu.com/img/bdlogo.gif "百度logo")  
# GitHub仓库里的图片
https://github.com/ 你的用户名 / 你的项目名 / raw / 分支名 / 存放图片的文件夹 / 该文件夹下的图片  
![](https://github.com/guodongxiaren/ImageCache/raw/master/Logo/foryou.gif)  

# 给图片加上超链接
如果你想使图片带有超链接的功能，即点击一个图片进入一个指定的网页。那么可以这样写：  
[![baidu]](http://baidu.com)  
[baidu]:http://www.baidu.com/img/bdlogo.gif "百度Logo" 
# 插入代码片段
我们需要在代码的上一行和下一行用` `` 标记。``` 不是三个单引号，而是数字1左边，Tab键上面的键。要实现语法高亮那么只要在 ``` 之后加上你的编程语言即可（忽略大小写）。c++语言可以写成c++也可以是cpp。   
