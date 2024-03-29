/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   vi:ai:tabstop=8:shiftwidth=4:softtabstop=4:expandtab
*/

/*
 * Author: Gabriel Burca <gburca dash binder at ebixio dot com>
 *
 * Sample code for using binders in Android from C++
 *
 * The Demo service provides 3 operations: push(), alert(), add(). See
 * the IDemo class documentation to see what they do.
 *
 * Both the server and client code are included below.
 *
 * To view the log output:
 *      adb logcat -v time binder_demo:* *:S
 *
 * To run, create 2 adb shell sessions. In the first one run "binder" with no
 * arguments to start the service. In the second one run "binder N" where N is
 * an integer, to start a client that connects to the service and calls push(N),
 * alert(), and add(N, 5).
 */

#define LOG_TAG "client_demo"

/* For relevant code see:
    frameworks/native/{include,libs}/binder/{IInterface,Parcel}.{h,cpp}
    system/core/include/utils/{Errors,RefBase}.h
 */

#include <stdlib.h>

#include <utils/RefBase.h>
#include <utils/Log.h>
#include <binder/TextOutput.h>

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

// Ajouter
#include "com/android/sampservice/ISampService.h"
#include "com/android/sampservice/BpSampService.h"

using namespace android;


#define INFO(...) \
    do { \
        printf(__VA_ARGS__); \
        printf("\n"); \
        ALOGD(__VA_ARGS__); \
    } while(0)

void assert_fail(const char *file, int line, const char *func, const char *expr) {
    INFO("assertion failed at file %s, line %d, function %s:",
            file, line, func);
    INFO("%s", expr);
    abort();
}

#define ASSERT(e) \
    do { \
        if (!(e)) \
            assert_fail(__FILE__, __LINE__, __func__, #e); \
    } while(0)


// Where to print the parcel contents: aout, alog, aerr. alog doesn't seem to work.
#define PLOG aout

// Helper function to get a hold of the service.
sp<com::android::sampservice::ISampService> getDemoServ() {
    sp<IServiceManager> sm = defaultServiceManager();
    ASSERT(sm != 0);
    sp<IBinder> binder = sm->getService
	    (String16("com.android.sampservice.ISampService")); 
    // Remplacer le nom par service list et le nom affiché
    // TODO: If the service is not running, getService times out and binder == 0.
    ASSERT(binder != 0);
    sp<com::android::sampservice::ISampService> demo = 
         interface_cast<com::android::sampservice::ISampService>(binder);
    ASSERT(demo != 0);
    return demo;
}


int main() {

        INFO("We're the client: ");


        sp<com::android::sampservice::ISampService> demo = getDemoServ();
        
        const int32_t a = 10;
        const int32_t b = 15;
        int32_t sum;
	int32_t diff;

        demo->add(a, b, &sum);
        ALOGD("Addition result: %i + %i = %i", a, b, sum);

	demo->sub(b, a, &diff);
        ALOGD("Substraction result: %i + %i = %i", b, a, diff);

        return 0;
}
