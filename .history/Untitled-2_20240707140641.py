import ollama
response = ollama.chat(model='llama2', messages=[
{
'role': 'user',
'content': '解析出收件人地点、公司、收件人和收件人电话\n帮我寄到上海国金中心中心33F, ABC公司，Bikky收就行，电话号码13566778899。我的电话是18988998899，上海杨浦区。',
},
])
print(response['message']['content'])