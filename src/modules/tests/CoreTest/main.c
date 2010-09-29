#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"

#define LOGNONE  0
#define LOGERROR 1
#define LOGWARN  2
#define LOGINFO  3
#define LOGDEBUG 4
#define LOGLEVEL LOGDEBUG

#if LOGLEVEL >= LOGERROR
#   define LOGE(msg) printf("%s\n", (msg))
#else
#   define LOGE(msg)
#endif // LOGERROR
#if LOGLEVEL >= LOGWARN
#   define LOGW(msg) printf("%s\n", (msg))
#else
#   define LOGW(msg)
#endif // LOGWARN
#if LOGLEVEL >= LOGINFO
#   define LOGI(msg) printf("%s\n", (msg))
#else
#   define LOGI(msg)
#endif // LOGINFO
#if LOGLEVEL >= LOGDEBUG
#   define LOGD(msg) printf("%s\n", (msg))
#else
#   define LOGD(msg)
#endif // LOGDEBUG

#define LOGA(test)  \
    if(!(test))     \
        LOGE("Assert error: "#test)

void cbOpen(void* window)
{
LOGI("cbOpen");
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}
void cbClose(void* window)
{
LOGI("cbClose");
    done = 1;
}
void cbResize(void* window, SGuint width, SGuint height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

SGCoreWindowCallbacks callbacks;
SGModuleInfo* minfo;
void* window;
SGuint ret;
SGuint width;
SGuint height;
SGbool opened;
int main()
{
#if LOGLEVEL >= LOGINFO
    printf("SIEGE Core Module Test\n");
#ifdef __DATE__
    printf("Date: %s\n", __DATE__);
#endif //__DATE__
#ifdef __TIME__
    printf("Time: %s\n", __TIME__);
#endif //__TIME__
    printf("Loglevel: %d\n", LOGLEVEL);
    printf("----------------------------------------\n");
#endif // LOGLEVEL

LOGD("loadCore");
    loadCore("SDLGL");

    callbacks.open = cbOpen;
    callbacks.close = cbClose;
    callbacks.resize = cbResize;

    atexit(quit);

LOGI("sgModuleInit");
    ret = sgModuleInit(NULL, &minfo);
    LOGA(ret == SG_OK);
    LOGA(minfo != NULL);
LOGI("sgCoreWindowCreate");
    ret = sgCoreWindowCreate(&window);
    LOGA(ret == SG_OK);
    LOGA(window != NULL);
LOGI("sgCoreWindowSetCallbacks");
    ret = sgCoreWindowSetCallbacks(window, &callbacks);
    LOGA(ret == SG_OK);
LOGI("!sgCoreWindowIsOpened");
    ret = sgCoreWindowIsOpened(window, &opened);
    LOGA(ret == SG_OK);
    LOGA(opened == SG_FALSE);
LOGI("sgCoreWindowOpen");
    ret = sgCoreWindowOpen(window, 640, 480, 32, 0);
    LOGA(ret == SG_OK);
LOGI("sgCoreWindowSetTitle");
    ret = sgCoreWindowSetTitle(window, "SIEGE Test - Core");

LOGI("sgCoreWindowIsOpened");
    ret = sgCoreWindowIsOpened(window, &opened);
    LOGA(ret == SG_OK);
    LOGA(opened == SG_TRUE);

    done = 0;
    while(!done)
    {
        draw(640, 480);
    }

LOGI("sgCoreWindowSetSize");
    ret = sgCoreWindowSetSize(window, 800, 600);
    LOGA(ret == SG_OK);

LOGI("sgCoreWindowGetSize");
    ret = sgCoreWindowGetSize(window, &width, &height);
    LOGA(ret == SG_OK);
    LOGA(width == 800);
    LOGA(height == 600);

    done = 0;
    while(!done)
    {
        draw(640, 480);
    }

LOGI("sgCoreWindowClose");
    ret = sgCoreWindowClose(window);
    LOGA(ret == SG_OK);

LOGI("!sgCoreWindowIsOpened");
    ret = sgCoreWindowIsOpened(window, &opened);
    LOGA(ret == SG_OK);
    LOGA(opened == SG_FALSE);

    return 0;
}

void quit(void)
{
LOGI("quit");
LOGI("sgCoreWindowDestroy");
    ret = sgCoreWindowDestroy(window);
    LOGA(ret == SG_OK);
LOGI("sgModuleExit");
    ret = sgModuleExit(minfo);
    LOGA(ret == SG_OK);
LOGD("freeCore");
    freeCore();
}

void draw(SGuint width, SGuint height)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0);
        glVertex2i(64, 64);
        glColor3ub(0, 255, 0);
        glVertex2i(width - 64, 64);
        glColor3ub(0, 0, 255);
        glVertex2i(width / 2, height - 64);
    glEnd();

    printf("%s", "");
    //LOGI("sgCoreWindowSwapBuffers");
    ret = sgCoreWindowSwapBuffers(window);
    LOGA(ret == SG_OK);
}
