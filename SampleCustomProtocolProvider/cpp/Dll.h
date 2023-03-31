
#pragma once

//
// global dll hinstance
extern HINSTANCE g_hinst;
#define HINST_THISDLL g_hinst

//#define _ATL_FREE_THREADED

//#define _ATL_NO_AUTOMATIC_NAMESPACE
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


//#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

void DllAddRef();
void DllRelease();
