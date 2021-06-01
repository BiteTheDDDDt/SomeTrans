# Project SomeTrans
### Todolist
- [x] shell入口 
- [ ] 数据库声明读入
  - [X] 表结构
  - [ ] 索引
  - [X] 主键
- [ ] 行数据读入整合
- [ ] UK/PK去重
- [ ] 非法数据清洗
- [ ] 数据写入目标文件
### Notes
* 去重
    * 初赛中对于source_file_dir中不同源文件可能存在相同主键的值，这里保证主键相同的话数据也是相同的，即主键相同视为重复数据，选手对结果需要进行去重。
* 排序
	* 部分表会出现复合主键的情况，排序的次序与schema.info里主键列出现的顺序相同，并且按照ASC出现。
* 非法数据
    * 非法整数数值。如定义为int的列值出现了非法字符，我们统一将其处理为"0"值；
    * 超长浮点数精度。如定义为decimal(3, 2)的列值中出现了小数点后3位，我们对其进行4舍5入；
    * 非法时间数据。如定义为datetime的列值中出现了非法的日期，我们将其统一成"2020-04-01 00:00:00.0"；
    * 超长字符长度。如定义为varchar(16)的列值出现了17个字符，此时我们按照此列的最大长度对列值截断（注意不考虑"\0"因素)。


