package com.zheng.secondjni;

import android.content.Context;
import android.widget.Toast;

public class NativeClass {

	private static Context context;

	public NativeClass(Context context) {
		this.context = context;
	}

	static {
		System.loadLibrary("SecondJNI");
	}

	public native String getString();

	public native String setNewString(String string);

	public native String setStringAdd(String string1, String string2);

	public native int setIntAdd(int x, int y);

	/************************************************************
	 * 给c代码传递int数组 让c代码给这个数组进行操作（图形 声音的处理）
	 ***********************************************************/
	public native int[] intMethod(int[] iNum);

	// C调用java空方法
	public void helloFromJava() {
		Toast.makeText(context, "我被调用了", Toast.LENGTH_LONG).show();
	}

	// C调用java中的带两个int参数的方法
	public int Add(int x, int y) {
		int result = x + y;
		Toast.makeText(context, "result:" + x + "+" + y + "=" + result,
				Toast.LENGTH_LONG).show();
		return result;
	}

	// C调用java中参数为string的方法
	public void printString(String s) {
		Toast.makeText(context, s, Toast.LENGTH_LONG).show();
	}

	// C调用java中静态的方法
	public static void demo() {
		Toast.makeText(context, "C调用java静态方法", Toast.LENGTH_LONG).show();
	}

	public native void callMethod1();

	public native void callMethod2();

	public native void callMethod3();

	public native void callMethod4();

	public native void callMethod5();
}
