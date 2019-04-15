# 用ESP8266打造一个自动床帘   

## 初衷
床帘不可谓是宿舍神器之一，在一个公共空间内打造一个私人空间。但是也不可避免的带来了一些问题，比如早上睁开双眼，感觉是凌晨四点钟，其实已经早上八点了。所以我才设计这一个装置用于解决这个问题。

## 功能
+ 通过开关来改变床帘状态
+ 在指定时间打开
+ 在指定时间打开后，一定时间内不会被关上

## 机械结构设计
在原有的蚊帐的结构上经行改造，中间使用皮带轮传动，两端放置主动和从动部分。

![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/_2019-Apr-11_11-00-56AM-000_CustomizedView2541721419_jpg.jpg)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/IMG_20190410_193629.jpg)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/IMG_20190410_194153.jpg)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/IMG_20190410_200548.jpg)

## 电路结构设计
之前的作品中，ESP8266都是作为WIFI接入点来使用的，但是在这一次的设计中，8266作为了主控来使用。电路整体使用12V供电，通过LM2596-3.3v将12V转为3.3V电压给8266供电；通过LM2596-ADJ给电机供电。其余电路设计部分略。
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/IMG_20190313_122031.jpg)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/IMG_20190313_131816.jpg)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/IMG_20190313_131918.jpg)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/Schematic__Sheet-1_20190411191325.png)
![](https://raw.githubusercontent.com/h1997l1997/Automatic-bed-curtain/blob/master/pic_video/PCB_NEW-PCB_20190411191436.png)

## 程序结构设计
因为学校有每日熄灯，所以对于床帘状态的获取（开或关）是一个难点。后来查阅8266的DATASHEET得知，8266编程中有一片EEPROM可供使用，只要在每次完成一次操作之后，记录下当时的状态，写入EEPORM中即可。其二的困难是时间的获取，这就是选择8266做主控的最大原因，连接互联网的便利，可以很好地解决获取时间这个问题。在程序设计上，可以通过NTP服务器来获得准确时间。综上程序结构大体设计为：连接WIFI→NTP获得时间→是否到达指定时间，如果是则打开→检测开关状态→根据状态决定操作
