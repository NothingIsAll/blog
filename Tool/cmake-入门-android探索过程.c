cmake 在windows上编译安卓平台可执行文件的探索

cmake是基于各平台各自的编译makefile工具之上做的统一构建型工具
是对makefile的统一构建，然后在用对应平台的编译工具执行make操作

需要准备的环境是：

1，cmake.exe工具，在android studio的sdk里面可以搜索到（由于as已对cmake做支持，并且已经下载了cmake工具）
添加到win系统环境变量（D:\Green_Soft\SDK\cmake\3.6.3155560\bin）
2，make.exe工具，在android studio sdk中同样能搜索到，添加到win环境变量
（D:\Green_Soft\SDK\ndk-bundle\prebuilt\windows-x86_64\bin）
3，ndk工具，同样在as中能下载到，添加到win环境变量
（D:\Green_Soft\SDK\ndk-bundle\）
4，android.toolchain.cmake ，cmake针对每个交叉编译，都有一个交叉编译的配置文件，以便提供交叉编译的平台信息（cpu类型，系统平台，编译工具依赖等）这个文件可以在交叉编译的cmake里面找到，也可以在网上去下载其他如opencv项目使用的文件，

以上准备完成后可以建立一个test文件目录进行交叉编译测试，命令如下

cmake -DCMAKE_TOOLCHAIN_FILE=C:\Users\mrfan\cmakedirtest\android.toolchain.cmake -DANDROID_NDK=D:\Green_Soft\SDK\ndk-bundle -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DCMAKE_GENERATOR="Ninja"

cmake --build .

备注：在win平台下cmake会默认用ms的编译工具，为了避免这个错误，google人员添加了ninja工具，以便能顺利编译。
所以-DCMAKE_GENERATOR="Ninja"这个选项一定要加上。

示例：https://github.com/NothingIsAll/Toolcode/tree/master/yuvshow
