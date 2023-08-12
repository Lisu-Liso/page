#include <iostream>
#include <string>
#include <map>
#include <curl/curl.h>

// 回调函数，用于接收 HTTP 响应数据
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer)
{
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

int main()
{
    std::string url = "https://api.binjie.fun/api/generateStream";

    // 请求参数
    std::map<std::string, std::string> payload = {
        {"network", "true"},
        {"prompt", "Question"}, // 提问在这里，将 Question 改为你的实际问题
        {"stream", "false"},
        {"system", ""},
        {"userId", "#/chat/1686975060957"},
        {"withoutContext", "false"}
    };

    std::string responseBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    if (curl)
    {
        // 设置请求头
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json, text/plain, */*");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
        headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Origin: https://chat.jinshutuan.com");
        headers = curl_slist_append(headers, "Referer: https://chat.jinshutuan.com/");
        headers = curl_slist_append(headers, "Sec-Ch-Ua: \"Chromium\";v=\"116\", \"Not A;Brand\";v=\"24\", \"Microsoft Edge\";v=\"116\"");
        headers = curl_slist_append(headers, "Sec-Ch-Ua-Mobile: ?0");
        headers = curl_slist_append(headers, "Sec-Ch-Ua-Platform: Windows");
        headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
        headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
        headers = curl_slist_append(headers, "Sec-Fetch-Site: cross-site");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.0.0");

        // 构建 JSON 请求体
        std::string jsonPayload = "{";
        for (auto it = payload.begin(); it != payload.end(); ++it)
        {
            if (it != payload.begin())
                jsonPayload += ",";
            jsonPayload += "\"" + it->first + "\":\"" + it->second + "\"";
        }
        jsonPayload += "}";

        // 设置请求选项
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

        // 发送请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cout << "请求失败: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            if (httpCode == 200)
            {
                // 处理返回的数据
                std::cout << responseBuffer << std::endl;
            }
            else
            {
                std::cout << "请求失败，状态码：" << httpCode << std::endl;
            }
        }

        // 清理资源
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}
