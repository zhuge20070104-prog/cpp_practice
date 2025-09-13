# 并发 --parallel 
# 并发个数 --jobs， 默认是CPU count - 1
# https://developer.ibm.com/articles/parallel-tests-mocha-v8/

# 设置npm proxy
npm config set proxy http://10.224.0.110:3128

# 移除npm proxy
npm config rm proxy
npm config rm https-proxy

# 安装appium server 1.22.3
npm install appium@1.22.3

# 清除appium server 机器端缓存
adb uninstall io.appium.uiautomator2.server
adb uninstall io.appium.uiautomator2.server.test


