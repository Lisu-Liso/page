from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload():
    print('*')

    # 获取请求体的 JSON 数据
    data = request.get_json()

    # 打印接收到的信息
    print("Received data:", data)
    information = json.dumps(data)

    # 处理 POST 请求的逻辑
    # ...

    return jsonify({'message': 'JSON data uploaded successfully!'})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=7070)
