pandas中的主要数据结构被实现为以下两类:
* DataFrame 关系型数据表格 包含多个行和已命名的列
* Series 单一列 DataFrame中包含一个或多个series,每个series均有一个名称

创建Series的一种方法是构建Series对象:
```
pd.Series(['Beijing','ShangHai','Xi'An'])
```
可以将映射string列名称的dict传递到它们各自的Series,从而创建DataFrame对象.如果Series在长度上不一致,系统会用特殊的 `NA/NaN`值填充缺失的值:

```
city_names = pd.Series(['Beijing','ShangHai','Xi'An'])
population = pd.Series([852469,1015782,325485])
pd.DataFrame({'city name':city_names,'Population':population})

```
大多数情况下,需要将真个文件加载到DataFrame中,
```
california_housing_dataframe = pd.read_csv("xxxx")
california_housing_dataframe.describe()
```

使用DataFrame.describe来显示关于DataFrame的有趣统计信息
使用DataFrame.head来显示DataFrame的前几个记录

使用DataFrame.hist 快速了解一个列中值的分布


可以向Series应用Python的基本运算指令

`population / 1000`

Series.apply用以参数形式接收`lambda函数`

population.apply(lambda val:val > 10000)


Series和DataFrame对象也定义了index属性,该属性会向每个Series项或DataFrame行赋一个标识符值
