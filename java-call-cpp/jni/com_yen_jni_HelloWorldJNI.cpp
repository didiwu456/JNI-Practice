/*
 * HelloWorldJNI.cpp
 *
 *  Created on: Jun 23, 2018
 *      Author: ywu
 */
#include "com_yen_jni_HelloWorldJNI.h"

#include <jni.h>
//#include <stdio.h>
#include <iostream>

JNIEXPORT void JNICALL Java_com_yen_jni_HelloWorldJNI_sayHello
(JNIEnv* env, jobject thisObject) {
	std::cout << "Hello from C++ !!" << std::endl;
}
