1，如果是在xml布局文件中的layout动态添加view ，需要给layout在xml中先添加id，
然后通过id将layout转为groupview，然后addview
2，如果是自己动态创建的layout，则可直接转为groupview 然后addview
```c++
//这个是activity_main.xml文件：
<?xml version="1.0" encoding="utf-8"?>
<android.support.constraint.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity"
    android:id="@+id/activity_s" //在此处增加id
    >

    <TextView
        android:id="@+id/sample_text"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Hello World!"
        app:layout_constraintBottom_toBottomOf="parent"
        app:layout_constraintLeft_toLeftOf="parent"
        app:layout_constraintRight_toRightOf="parent"
        app:layout_constraintTop_toTopOf="parent" />

</android.support.constraint.ConstraintLayout>
```

```java
//这个是mainactivity.java
super.onCreate(savedInstanceState);
 setContentView(R.layout.activity_main);
 ViewGroup mains = findViewById(R.id.activity_s); //此处将id做转换。
 mains.addView(bt1);   //此处将view进行添加
```
