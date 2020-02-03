`1.gcc -E source_file.c`
-E ,只执行到预编译.直接输出预编译结果

`2.gcc -S source_file.c`
-S ,只执行到源代码到汇编代码的转换,输出汇编代码

`3.gcc -c suorce_file.c`
-c ,只执行到编译,输出目标文件

`4 gcc(-E/S/c/) source_file.c -o output_filename`
-o,指定输出文件名,可以配合以上三种标签使用
-o,参数可以被省略.这种请看下编译器将使用以下默认名称输出:
1. -E:预编译结果将被输出到标准输出端口(通常是显示器)
2. -S:生成名为source_file.s的汇编代码
3. -c:生成名为source_file.o的目标文件
无标签情况:生成名为a.out的可执行文件

`5.gcc -g source_file.c`
-g,生成供调试用的可执行文件,可以在gdb中运行.由于文件中包含类调试信息因此运行效率很低

`6.gcc -s source_file.c`
-s ,直接生成与运用strip同样效果的可执行文件(删除类所有符号信息)

`7.gcc -O source_file.c`
-O(大写),编译器对代码进行自动优化编译,输出效率更高的可执行文件.