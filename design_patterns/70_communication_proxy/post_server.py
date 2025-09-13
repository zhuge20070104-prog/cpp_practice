# coding: utf-8
from flask import Flask
from flask import request
import json


app = Flask(__name__)


@app.route('/',methods=['GET'])
def hello_world():
    return 'Hello World!'

# 设置访问URL：'/plus'，methods：允许哪种方式访问
@app.route('/plus',methods=['POST'])
def plus():
    data = json.loads(request.data.decode())
    x = data['x']
    y = data['y']
    return json.dumps({"sum": x+y})


if __name__ == '__main__':
    # 设置host，端口8080。threaded=True 代表开启多线程
    app.run(host='0.0.0.0', port=8080, threaded=True)
