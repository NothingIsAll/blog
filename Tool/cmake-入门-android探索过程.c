cmake ��windows�ϱ��밲׿ƽ̨��ִ���ļ���̽��

cmake�ǻ��ڸ�ƽ̨���Եı���makefile����֮������ͳһ�����͹���
�Ƕ�makefile��ͳһ������Ȼ�����ö�Ӧƽ̨�ı��빤��ִ��make����

��Ҫ׼���Ļ����ǣ�

1��cmake.exe���ߣ���android studio��sdk�������������������as�Ѷ�cmake��֧�֣������Ѿ�������cmake���ߣ�
��ӵ�winϵͳ����������D:\Green_Soft\SDK\cmake\3.6.3155560\bin��
2��make.exe���ߣ���android studio sdk��ͬ��������������ӵ�win��������
��D:\Green_Soft\SDK\ndk-bundle\prebuilt\windows-x86_64\bin��
3��ndk���ߣ�ͬ����as�������ص�����ӵ�win��������
��D:\Green_Soft\SDK\ndk-bundle\��
4��android.toolchain.cmake ��cmake���ÿ��������룬����һ���������������ļ����Ա��ṩ��������ƽ̨��Ϣ��cpu���ͣ�ϵͳƽ̨�����빤�������ȣ�����ļ������ڽ�������cmake�����ҵ���Ҳ����������ȥ����������opencv��Ŀʹ�õ��ļ���

����׼����ɺ���Խ���һ��test�ļ�Ŀ¼���н��������ԣ���������

cmake -DCMAKE_TOOLCHAIN_FILE=C:\Users\mrfan\cmakedirtest\android.toolchain.cmake -DANDROID_NDK=D:\Green_Soft\SDK\ndk-bundle -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DCMAKE_GENERATOR="Ninja"

cmake --build .

��ע����winƽ̨��cmake��Ĭ����ms�ı��빤�ߣ�Ϊ�˱����������google��Ա�����ninja���ߣ��Ա���˳�����롣
����-DCMAKE_GENERATOR="Ninja"���ѡ��һ��Ҫ���ϡ�

ʾ����https://github.com/NothingIsAll/Toolcode/tree/master/yuvshow
