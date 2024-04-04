# GXCC开发者文档 - 中文

## 关于GXCC

GXCC是一个集中控制器，用于协调各个扩展之间的工作。作为第三方开发者，您可以为GXCC开发扩展。您可以使用任何编程语言编写扩展。

## 扩展包

这是您发行扩展的其中一种方式，也是我们最推荐的一种方式。
扩展包由两部分组成，包括JSON格式的自述文件和扩展安装程序，中间以`'~'`隔开。JSON自述文件的内容包括`name` `id` `version` `type`等。
这是一个自述文件的示例。（内容来自Spwaiter官方开发的ExtensionInstaller）
```json
{
    "name": "ExtensionInstaller",
    "id": "00000001",
    "version": "v0.2.0",
    "type": "5"
}
```

对于`name`字段，这是您开发扩展的名称，用于用户在扩展管理器中识别扩展的友好名称。这个字段内的内容您完全可以自定义。但是由于安装程序限制，您扩展名字的长度不可以超过`1024`字节。

对于`id`字段，这是您开发扩展后发行扩展的唯一标识码，用于存储和识别扩展。请注意，您开发的扩展的id需要从GXCC的官方指定位置获取，我们会为您生成独一无二的id。
目前获取途径尚未开发完成，会在等开发完成之后在此处放置获取链接。

对于`version`字段，这是您开发扩展的版本号。我们的扩展安装程序会判断您安装的版本。如果已经有了更高或当前版本，我们会询问用户是否继续安装。

对于`type`字段，我们规定，（来自ExtensionInstaller的部分源代码）
```cpp
switch(c){
    case '1':{
        temp2+="&Listener";
        break;
    }
    case '2':{
        temp2+="&Controller";
        break;
    }
    case '3':{
        temp2+="&Runner";
        break;
    }
    case '4':{
        temp2+="&Structure";
        break;
    }
    case '5':{
        temp2+="&MainControllerExtension";
        break;
    }
}
```

如果您要发行扩展，请注意在扩展包中的安装程序中包含卸载程序。您不需要处理关于GXCC的一切，卸载您需要的环境和扩展即可。

## Extend Extension

用于处理各类扩展的耗时操作，节省GXCC监听和运行的时间。
Extend Extension可以与扩展以各种方式连接。但是不建议使用网络连接，因为网络连接具有不确定性和延迟。并且在无网络环境下会出现超时现象。

## Listener扩展

Listener扩展是GXCC的监听器扩展。

Listener扩展的开发准则为“快”、“轻”，也就是说您开发的扩展需要具有较高的启动速度（这里指重载速度）。虽然您可以使用任何编程语言编写扩展程序，但是我们建议您使用可以生成可执行文件的语言。或者您可以单独编写启动您的扩展的可执行文件。这通常不需要很长时间。需要轻便的性质也是为了可以快速启动。

Listener扩展在GXCC后的首次启动需要启动Extend Extension时可以占用更多时间，是需要保持Extend Extension常加载，以便快速响应重载的Listener扩展。

Listener扩展呼叫GXCC进行下一步操作的方式为退出扩展。我们会在第一时间重新启动您的扩展，即使GXCC主程序未响应。因为我们使用新的进程来托管您的扩展程序。

Listener扩展与GXCC传输数据的方式是通过文件系统。在文件

## GXCC v1.0

这是GXCC的最基础的版本，支持Listener和Runner扩展。