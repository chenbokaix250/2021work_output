### python常用方法整理
#### python capitalize()方法
将字符串的第一个字母变成大写,其他字母变小写,对于8位字节编码需要根据本地环境.
```
s = 'a, BCD'
s.capitalize()
'A, bcd'
```

#### python center()方法
返回一个原字符串居中,并使用空格填充至长度width的新字符串.默认填充字符为空格
```
str = 'runoob'
str.center(20, '*')
'*******runoob*******'
```

#### python count方法
用于统计字符串里某个字符出现的次数.可选参数为在字符串搜索的开始与结束位置.
str.count(sub, start= 0,end=len(string))
```
str = "this is string example....wow!!!";
 
sub = "i";
print "str.count(sub, 4, 40) : ", str.count(sub, 4, 40)
```

#### python decode方法
以encoding制定的编码格式解码字符串,默认编码为字符串编码

str.decode(encoding='UTF-8',errors='strict')

encoding -- 要使用的编码，如"UTF-8"。

errors -- 设置不同错误的处理方案。默认为 'strict',意为编码错误引起一个UnicodeError。 其他可能得值有 'ignore', 'replace', 'xmlcharrefreplace', 'backslashreplace' 以及通过 codecs.register_error() 注册的任何值。

```
str = "this is string example....wow!!!";
str = str.encode('base64','strict');
 
print "Encoded String: " + str;
print "Decoded String: " + str.decode('base64','strict')
```

