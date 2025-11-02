from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("TotalSpendByCustomers")
sc = SparkContext(conf = conf)

def extractCustomerPricePairs(line):
    fields = line.split(',')
    return (int(fields[0]), float(fields[2]))

input = sc.textFile("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/customer-orders.csv")
mappedInput = input.map(extractCustomerPricePairs)
totalByCustomer = mappedInput.reduceByKey(lambda x, y: x + y)
results = totalByCustomer.collect()

for result in results:
    print(result)