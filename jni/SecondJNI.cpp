#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include "com_zheng_secondjni_NativeClass.h"

#define LOG_TAG "clog"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**********************************************************
 * 在C语言中不能直接操作java中的字符串
 * 要把java中的字符串转换成c语言中 char数组
 * *********************************************************/
char* jstringTostring(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes",
			"(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

/**********************************************************
 * 返回   两个int 类型数据相加   的结果
 * *********************************************************/
JNIEXPORT jint JNICALL Java_com_zheng_secondjni_NativeClass_setIntAdd(
		JNIEnv * env, jobject obj, jint x, jint y) {
	// 想在logcat控制台上 打印日志
	LOGD("x=%d", x);
	LOGI("y=%d", y);
	return x + y;
}

/**********************************************************
 * 返回固定字符串
 * *********************************************************/
JNIEXPORT jstring JNICALL Java_com_zheng_secondjni_NativeClass_getString(
		JNIEnv * env, jobject obj) {
	return env->NewStringUTF("zhengyuhui");
}

/**********************************************************
 * 返回拼接字符串 （传入字符串 + 固定字符串）
 * *********************************************************/
JNIEXPORT jstring JNICALL Java_com_zheng_secondjni_NativeClass_setNewString(
		JNIEnv * env, jobject obj, jstring str) {
	//定义char类型变量
	char* c = "hello";
	char* cstr = jstringTostring(env, str);
	//打印char类型变量的数值
	LOGD("%s", c);
	LOGD("%s", cstr);
	//合并两个char类型变量cstr、c到cstr中，并打印
	strcat(cstr, c);
	LOGD("%s", cstr);
	//返回合并结果cstr
	return env->NewStringUTF(cstr);
}

/**********************************************************
 * 返回拼接字符串（传入字符串 + 传入字符串）
 * *********************************************************/
JNIEXPORT jstring JNICALL Java_com_zheng_secondjni_NativeClass_setStringAdd(
		JNIEnv * env, jobject obj, jstring str1, jstring str2) {

	char* cstr1 = jstringTostring(env, str1);
	char* cstr2 = jstringTostring(env, str2);
	strcat(cstr1, cstr2);
	return env->NewStringUTF(cstr1);
}

/**********************************************************
 * 数组操作
 * *********************************************************/
JNIEXPORT jintArray JNICALL Java_com_zheng_secondjni_NativeClass_intMethod(
		JNIEnv * env, jobject jobject, jintArray jarray) {
	// jArray  遍历数组   jint* (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
	// 数组的长度    jsize (*GetArrayLength)(JNIEnv*, jarray);
	// 对数组中每个元素 +5
	int length = env->GetArrayLength(jarray);
	int* array = env->GetIntArrayElements(jarray, 0);
	int i = 0;
	for (; i < length; i++) {
		*(array + i) += 5;
	}
	return jarray;
}

/**********************************************************
 * C调用JAVA的NativeClass类helloFromJava()方法
 * *********************************************************/
JNIEXPORT void JNICALL Java_com_zheng_secondjni_NativeClass_callMethod1(
		JNIEnv * env, jobject jobject) {

	/*************************************************************************
	 * java中的反射：
	 * Class<?> forName = Class.forName("com.example.ndkcallback.DataProvider");
	 * Method declaredMethod = forName.getDeclaredMethod("helloFromJava", new Class[]{});
	 * declaredMethod.invoke(forName.newInstance(), new Object[]{});
	 ******************************************************************	 */
	// 得到要调用方法所在的类
	jclass clazz = env->FindClass("com/zheng/secondjni/NativeClass");//jclass  (*FindClass)(JNIEnv*, const char*);
	// 得到方法的ID （参数：所在类，方法名，方法签名）
	jmethodID methodId = env->GetMethodID(clazz, "helloFromJava", "()V");//  jmethodID (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	// 调用方法
	env->CallVoidMethod(jobject, methodId);	// void  (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
}

/**********************************************************
 * C调用JAVA的NativeClass类Add(int x, int y)方法
 * *********************************************************/
JNIEXPORT void JNICALL Java_com_zheng_secondjni_NativeClass_callMethod2(
		JNIEnv * env, jobject jobject) {
	jclass clazz = env->FindClass("com/zheng/secondjni/NativeClass");
	jmethodID methodId = env->GetMethodID(clazz, "Add", "(II)I");
	env->CallIntMethod(jobject, methodId, 3, 5);// jint (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
}

/**********************************************************
 * C调用JAVA的NativeClass类printString(String s)方法
 * *********************************************************/
JNIEXPORT void JNICALL Java_com_zheng_secondjni_NativeClass_callMethod3(
		JNIEnv * env, jobject jobject) {   // 参数 object  就是native方法所在的类
	jclass clazz = env->FindClass("com/zheng/secondjni/NativeClass");
	jmethodID methodId = env->GetMethodID(clazz, "printString",
			"(Ljava/lang/String;)V");
	jstring str = env->NewStringUTF("我是来自.cpp的输出");
	env->CallVoidMethod(jobject, methodId, str);
}

/**********************************************************
 * C调用JAVA的MainActivity类helloFromJava()方法
 * *********************************************************/
JNIEXPORT void JNICALL Java_com_zheng_secondjni_NativeClass_callMethod4(
		JNIEnv * env, jobject j) {
	jclass clazz = env->FindClass("com/zheng/secondjni/MainActivity");
	jmethodID methodId = env->GetMethodID(clazz, "helloFromJava", "()V");
	// 需要创建DataProvider的 对象
	jobject obj = env->AllocObject(clazz);  // new MainActivity();
	env->CallVoidMethod(obj, methodId);
}

/**********************************************************
 * C调用JAVA的NativeClass类静态方法
 * *********************************************************/
JNIEXPORT void JNICALL Java_com_zheng_secondjni_NativeClass_callMethod5(
		JNIEnv * env, jobject j) {
	jclass clazz = env->FindClass("com/zheng/secondjni/NativeClass");
	jmethodID methodid = env->GetStaticMethodID(clazz, "demo", "()V");
	env->CallStaticVoidMethod(clazz, methodid);
}

