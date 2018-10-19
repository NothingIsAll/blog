此类为yuv预览的render类，需要配合ANdroid GLSurfaceView类使用

java类名：
`#define JAVA_CLASS_NAME "com/audiocn/libs/CamShowGlRender"`

接口介绍如下：
1，测试接口，测试native环境是否ok
`public native String stringFromJNI();`
2，GLSurfaceView类使用Renderer的onSurfaceCreated(GL10 gl, EGLConfig config)调用
  `public native void onSurfaceCreated();`
3,GLSurfaceView类使用Renderer的 onSurfaceChanged(GL10 gl, int width, int height)调用
`public native void onSurfaceChanged(int width,int heigh);`
4,GLSurfaceView类使用Renderer的 onDrawFrame(GL10 gl)调用
`public native void onDrawFrame();`
5，放置yuv数据支持nv21的yuv420的格式，每次读取一帧数据。
其中参数size必须为：width*heigh*3/2
`public static native int PutYuvData(byte[] data,int size,int width,int heigh);`


示例：
1，Render子类回调调用
``` c++
@Override
public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    onSurfaceCreated();
}
@Override
public void onSurfaceChanged(GL10 gl, int width, int height) {
    onSurfaceChanged(width,height);
}
@Override
public void onDrawFrame(GL10 gl) {
    onDrawFrame();
}
2，放置yuv数据示例
class myThread extends Thread{
    private String path;
    myThread(String path){
        this.path = path;
    }
    @Override
    public void run() {
        super.run();
        String path = "/data/camera.yuv";
        int width = 1280;
        int height = 720;
        int readsize = 1280*720*3/2;
        int readres = 1;
        int putres = -1;
        try {
            FileInputStream inputStream = new FileInputStream(path);
            byte[] buffer = new byte[readsize];
            while(readres > 0){
                readres = inputStream.read(buffer,0,readsize);
                do {
                    putres = demoglRender.PutYuvData(buffer, readsize, width, height);
                    SystemClock.sleep(5);
                }while (putres < 0);
                SystemClock.sleep(5);
            }
            inputStream.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
```
