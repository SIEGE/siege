#ifndef _GC_log_h
#define _GC_log_h

#include <fstream>

// to be removed and replaced!
#ifdef _DEBUG
#define use_logs
#endif

using namespace std;
ofstream fhandle;

namespace GC
{
    int LogOpen(char* fname = "gamelog.log")
    {
        #ifdef use_logs
        fhandle.open(fname);
        return 1;
        #else
        return -1;
        #endif
    }

    void LogClose()
    {
        #ifdef use_logs
        fhandle.close();
        #endif
    }

    void LogWrite(char* text,int space = 0)
    {
        #ifdef use_logs
        for(int i=0; i<space; i++)
        {
            fhandle << " ";
        }
        fhandle << text << "\n";
        #endif
    }
}

#endif
