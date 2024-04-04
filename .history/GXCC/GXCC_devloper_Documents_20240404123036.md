# GXCC开发者文档 - 中文

## 关于GXCC

GXCC是一个集中控制器，用于协调各个扩展之间的工作。作为第三方开发者，您可以为GXCC开发扩展。

## 扩展包

这是您发行扩展的其中一种方式，也是我们最推荐的一种方式。
扩展包由两部分组成，包括JSON格式的自述文件和扩展安装程序。JSON自述文件的内容包括`name`
```json
{
    "name": "ExtensionInstaller",
    "id": "00000001",
    "version": "v0.2.0",
    "type": "5"
}
```

## Extend Extension

用于处理各类扩展的耗时操作，节省GXCC监听和运行的时间。
Extend Extension可以与扩展以各种方式连接。但是不建议使用网络连接，因为网络连接具有不确定性和延迟。并且在无网络环境下会出现超时现象。

## Listener扩展

Listener扩展是GXCC的监听器扩展。
Listener扩展的开发准则为

## GXCC v1.0

这是GXCC的最基础的版本，支持Listener和Runner扩展。