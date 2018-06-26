#include <jni.h>
#include <iostream>
#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

using namespace std;

int main() {
	JavaVM *jvm;                    // Pointer to the JVM (Java Virtual Machine)
	JNIEnv *env;                      // Pointer to native interface
	//================== prepare loading of Java VM ============================
	JavaVMInitArgs vm_args;                        // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	char optionStr[] = "-Djava.class.path=./target/classes";
	options[0].optionString = optionStr; // where to find java .class
	vm_args.version = JNI_VERSION_1_6;             // minimum Java version
	vm_args.nOptions = 1;                          // number of options
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false; // invalid options make the JVM init fail
	//=============== load and initialize Java VM and JNI interface =============
	jint rc = JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);  // YES !!
	delete options;    // we then no longer need the initialisation options.
	if (rc != JNI_OK) {
		// TO DO: error processing...
		cin.get();
		exit(EXIT_FAILURE);
	}
	//=============== Display JVM version =======================================
	cout << "JVM load succeeded: Version ";
	jint ver = env->GetVersion();
	cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

	// TO DO: add the code that will use JVM <============  (see next steps)
	jclass cls = env->FindClass("com/yen/jni/HelloWorld");
	if (cls == nullptr) {
		cerr << "ERROR: class not found !";
	} else {                                  // if class found, continue
		cout << "Class HelloWorld found" << endl;
		jmethodID mid = env->GetStaticMethodID(cls, "main",
				"()V"); // find method
		if (mid == nullptr)
			cerr << "ERROR: method void main() not found !" << endl;
		else {
			env->CallStaticVoidMethod(cls, mid);                 // call method
			cout << endl;
		}
	}

//	if (env->ExceptionOccurred()) {
//	env->ExceptionDescribe();
//	}

	jvm->DestroyJavaVM();
	cin.get();
}
