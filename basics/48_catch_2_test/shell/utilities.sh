# 运行catch2 Test
# [config] 是 tag 过滤器, -r report格式是 xml，还可以是junit, console
# 但是我们不关注这个report, 我们搞的是数据驱动，后面会把report输出到 SQLite.db
# 然后使用ReactJs + Bulma + Flask来做联合展示
# 还需要集成一下SQLite到本工程就OK了
./main ./config/bifang_test.json   [config] -r xml