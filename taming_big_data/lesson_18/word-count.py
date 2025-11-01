from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("WordCount")
sc = SparkContext(conf = conf)

input = sc.textFile("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/Book")
words = input.flatMap(lambda x: x.split())
wordCounts = words.countByValue()


'''
这两步操作的目的是为了清理和过滤文本数据：
第11行 encode('ascii', 'ignore')：
将字符串编码为 ASCII 字节串
'ignore' 参数的作用是忽略所有非 ASCII 字符
这样可以过滤掉所有特殊字符、表情符号、非英文字符等
例如："café" 会变成 b"caf"（é 被忽略了）
第13行 decode()：
将字节串重新解码回普通字符串
这样才能正常打印输出
例如：b"caf" 解码回 "caf"
第12行的 if cleanWord 检查：
如果一个词完全由非 ASCII 字符组成（比如中文、特殊符号），encode 后会得到空字节串
这个检查可以过滤掉这些完全为空的结果
简单来说：这是一个数据清洗过程，用来去除文本中的非标准 ASCII 字符，确保输出的都是干净的英文字符和数字。这在处理可能包含各种编码问题的文本文件时特别有用。
例如，如果 Book 文件中有些词包含了特殊的引号、破折号或其他 Unicode 字符，这个操作就能把它们清理掉。
'''

for word, count in wordCounts.items():
    cleanWord = word.encode('ascii', 'ignore')
    if cleanWord:
        print(cleanWord.decode() + " " + str(count))


