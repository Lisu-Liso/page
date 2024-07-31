import requests
import json

# API地址
url = "https://api.binjie.fun/api/generateStream"

# 请求头（可选）
headers = {
    "Accept": "application/json, text/plain, */*",
    "Accept-Encoding": "gzip, deflate, br",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    "Content-Type": "application/json",
    "Origin": "https://chat18.aichatos.xyz",
    "Referer": "https://chat18.aichatos.xyz",
    "Sec-Ch-Ua": "\"Chromium\";v=\"116\", \"Not A;Brand\";v=\"24\", \"Microsoft Edge\";v=\"116\"",
    "Sec-Ch-Ua-Mobile": "?0",
    "Sec-Ch-Ua-Platform":"Windows",
    "Sec-Fetch-Dest": "empty",
    "Sec-Fetch-Mode": "cors",
    "Sec-Fetch-Site": "cross-site",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.0.0"
}
while 1:
    input_=input()
    print("-------------")
    payload = {
        "network": "true",
        "prompt": input_,
        "stream": "false",
        "system": "",
        "userId": "#/chat/1686975060957",
        "withoutContext": "false"
    }
    # 发送POST请求
    response = requests.post(url, json=payload, headers=headers)
    # 处理响应
    if response.status_code == 200:  # 请求成功
        data = response     # "" .json() """  # 获取响应体的JSON数据
        # 处理返回的数据
        print(data.text)
        print("-------------")
    else:
        print("请求失败:", response.text)
