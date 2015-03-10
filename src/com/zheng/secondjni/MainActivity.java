package com.zheng.secondjni;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends Activity {

	private TextView tv_1;
	private NativeClass nativeClass;

	public void helloFromJava() {
		// Toast.makeText(MainActivity.this, "我来自MainActivity",
		// Toast.LENGTH_LONG)
		// .show();
		// tv_1.setText("C调用JAVA的MainActivity类helloFromJava()方法");
		System.out.println("C调用JAVA的MainActivity类helloFromJava()方法");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		tv_1 = (TextView) findViewById(R.id.tv_1);
		nativeClass = new NativeClass(this);
	}

	public void btOnClick1(View v) {
		tv_1.setText("12+23=" + nativeClass.setIntAdd(12, 23));
	}

	public void btOnClick2(View v) {
		tv_1.setText("字符串12342343拼接adfsdfdsf->\n"
				+ nativeClass.setStringAdd("12342343", "adfsdfdsf"));
	}

	public void btOnClick3(View v) {

		int[] arr = new int[] { 1, 2, 3, 4, 5 };
		String Str = "";
		nativeClass.intMethod(arr);
		for (int i : arr) {
			System.out.println(i);
			Str = Str + i + ",";
		}
		tv_1.setText("数组{ 1, 2, 3, 4, 5 }+5操作：\n" + "{ " + Str + " }");
	}

	public void btOnClick4(View v) {
		nativeClass.callMethod1();
	}

	public void btOnClick5(View v) {
		nativeClass.callMethod2();
	}

	public void btOnClick6(View v) {
		nativeClass.callMethod3();
	}

	public void btOnClick7(View v) {
		nativeClass.callMethod4();
	}

	public void btOnClick8(View v) {
		nativeClass.callMethod5();
	}

}
