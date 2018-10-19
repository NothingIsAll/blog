jni接口，静态注册就是签名包名类名一大串的那种，在此只介绍接口动态注册方法

jni接口文件中标准代码块：
```c++
        #define JAVA_CLASS_NAME "com/audiocn/libs/CamShowGlRender"
        extern "C"{
        	 jstring stringFromJNI(JNIEnv *env, jclass type){
        		return  env->NewStringUTF("hello mrfan iam come back!!");
        	}
        	 void onSurfaceCreated(JNIEnv *env, jclass type){
        		glrender.onSurfaceCreated();
        	}
        	 void onSurfaceChanged(JNIEnv *env, jclass type,jint width,jint heigh){
        		glrender.onSurfaceChanged(width,heigh);
        	}
        	 void onDrawFrame(JNIEnv *env, jclass type){
        		glrender.onDrawFrame();
        	}
        	 jint PutYuvData(JNIEnv *env, jclass type,jbyteArray data,jint size,jint width,jint heigh){
        		char *buf = (char*) env->GetByteArrayElements(data, JNI_FALSE);
        		int res = glrender.setYUV420N21(width,heigh,buf,size);
        		env->ReleaseByteArrayElements(data, (jbyte*)buf, JNI_FALSE);
        		return res;
        	}
        	static JNINativeMethod getMethods[] = {
        	        {"stringFromJNI","()Ljava/lang/String;",(void*)stringFromJNI},
        			{"onSurfaceCreated","()V",(void*)onSurfaceCreated},
        			{"onSurfaceChanged","(II)V",(void*)onSurfaceChanged},
        			{"onDrawFrame","()V",(void*)onDrawFrame},
        			{"PutYuvData","([BIII)I",(void*)PutYuvData}
        	};
        	//此函数通过调用JNI中 RegisterNatives 方法来注册我们的函数
        	static int registerNativeMethods(JNIEnv* env, const char* className,JNINativeMethod* getMethods,int methodsNum){
        	    jclass clazz;
        	    //找到声明native方法的类
        	    clazz = env->FindClass(className);
        	    if(clazz == NULL){
        	        return JNI_FALSE;
        	    }
        	   //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
        	    if(env->RegisterNatives(clazz,getMethods,methodsNum) < 0){
        	        return JNI_FALSE;
        	    }
        	    return JNI_TRUE;
        	}
        	static int registerNatives(JNIEnv* env){
        	    //指定类的路径，通过FindClass 方法来找到对应的类
        	    const char* className  = JAVA_CLASS_NAME;
        	    return registerNativeMethods(env,className,getMethods, sizeof(getMethods)/ sizeof(getMethods[0]));
        	}
        	//回调函数 在这里面注册函数
        	JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
        	    JNIEnv* env = NULL;
        	   //判断虚拟机状态是否有问题
        	    if(vm->GetEnv((void**)&env,JNI_VERSION_1_6)!= JNI_OK){
        	        return -1;
        	    }
        	    //开始注册函数 registerNatives -》registerNativeMethods -》env->RegisterNatives
        	    if(!registerNatives(env)){
        	        return -1;
        	    }
        	    //返回jni 的版本
        	    return JNI_VERSION_1_6;
        	}
        }
```
每个jni接口类如果需要动态注册接口都要 在所有接口方法后面添加上这段代码，然后稍作修改
对`static JNINativeMethod getMethods[] = {`介绍：

  ```
  typedef struct {
const char* name;       //接口函数名称
const char* signature;  //接口函数签名
void* fnPtr;            //接口函数指针（记得前置转换成void*）
} JNINativeMethod;
  ```

  每个jni接口类只需要把类成员函数按照`struct JNINativeMethod[]`的格式添加，就成功的动态注册了jni方法。

  下面再说一下最重要的`接口函数签名`：
  接口函数签名可以依照类型签名对照表来自己组装，估计这么做的始作俑者很少吧，干货来了，
  同过`javap`工具转换每个java类的class二级制文件，而得到类中每个`native`方法的签名，
  然后把签名拷贝过来，

  ```
  cd 到java类编译后的class所在路径下，我的在AS中路径为       （E:\AndroidStudioProjects\Opengltest\app\build\intermediates\classes\debug\entry\com\audiocn\tlkg\opengltest）

  javap -s -private 类名
  ```
  `-s`：显示函数签名
  `-private`：显示函数的最低权限为private，默认只显示public

  可以得到结果：
  ```
  public class entry.com.audiocn.tlkg.opengltest.demoglRender implements android.opengl.GLSurfaceView$Renderer {
  public entry.com.audiocn.tlkg.opengltest.demoglRender();
    descriptor: ()V

  public void onSurfaceCreated(javax.microedition.khronos.opengles.GL10, javax.microedition.khronos.egl.EGLConfig);
    descriptor: (Ljavax/microedition/khronos/opengles/GL10;Ljavax/microedition/khronos/egl/EGLConfig;)V

  public void onSurfaceChanged(javax.microedition.khronos.opengles.GL10, int, int);
    descriptor: (Ljavax/microedition/khronos/opengles/GL10;II)V

  public void onDrawFrame(javax.microedition.khronos.opengles.GL10);
    descriptor: (Ljavax/microedition/khronos/opengles/GL10;)V

  private native java.lang.String stringFromJNI();
    descriptor: ()Ljava/lang/String;

  public native void onSurfaceCreated();
    descriptor: ()V

  public native void onSurfaceChanged(int, int);
    descriptor: (II)V

  public native void onDrawFrame();
    descriptor: ()V

  public static native int PutYuvData(byte[], int, int, int);
    descriptor: ([BIII)I

  static {};
    descriptor: ()V
}
  ```
####ps:注意在复制签名(descriptor)时，对象类型可能后面有 `;` 如` ()Ljava/lang/String;`  +
使用时千万不要删掉`;`！！！
