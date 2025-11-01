import re
from pyspark import SparkConf, SparkContext


'''
这行代码做了以下几件事：
1. text.lower()
首先将输入的文本转换为小写，这样 "Hello" 和 "hello" 会被认为是同一个单词。
2. re.compile(r'\W+', re.UNICODE)
创建一个正则表达式模式对象：
r'\W+：这是正则表达式模式
\W 表示匹配非单词字符（也就是除了字母、数字、下划线之外的所有字符）
+ 表示匹配一个或多个这样的字符
所以 \W+ 匹配一个或多个非单词字符，比如空格、标点符号、特殊符号等
re.UNICODE：标志位，表示按照 Unicode 标准来处理字符，这样可以正确处理各种语言的字符
3. .split(text.lower())
使用上面创建的正则表达式模式来分割文本：
在所有匹配 \W+ 的位置进行分割
本质上就是在所有非单词字符的地方把文本切开
举个例子：
输入文本: "Hello, world! How are you?"
执行过程：
text.lower() → "hello, world! how are you?"
在 , , ! , 等非单词字符处分割
结果：["hello", "world", "how", "are", "you", ""]
为什么这样做？
这个函数的目的是规范化单词，用于单词计数：
去除标点符号
统一大小写
将文本分割成干净的单词列表
这样在后续的 countByValue() 操作中，就能准确统计每个单词出现的次数，而不会因为大小写或标点符号的差异导致同一个单词被重复计数。
'''

def normalizeWords(text):
    return re.compile(r'\W+', re.UNICODE).split(text.lower())

conf = SparkConf().setMaster("local").setAppName("WordCount")
sc = SparkContext(conf = conf)

input = sc.textFile("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/Book")
words = input.flatMap(normalizeWords)
wordCounts = words.countByValue()

for word, count in wordCounts.items():
    cleanWord = word.encode('ascii', 'ignore')
    if cleanWord:
        print(cleanWord.decode() + " " + str(count))