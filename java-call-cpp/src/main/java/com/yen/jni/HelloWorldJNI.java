package com.yen.jni;

/**
 * Hello world!
 *
 */
public class HelloWorldJNI 
{
	private native void sayHello();
    public static void main( String[] args )
    {
        new HelloWorldJNI().sayHello();
    }
    static {
    	System.loadLibrary("native");
    }
}
