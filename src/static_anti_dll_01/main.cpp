#include <Windows.h>
#include <stdio.h>

static const char *g_defult_msg = "guest";

extern "C" __declspec(dllexport) void say_hello(const char *msg) {
  if (msg) {
    fprintf(stdout, "hello %s\n", msg);
  } else {
    fprintf(stdout, "hello %s\n", g_defult_msg);
  }
}

extern "C" __declspec(dllexport) bool GetSystemVersion(int &major, int &minor) {
  OSVERSIONINFO osvi;
  BOOL bIsWindowsXPorLater;

  ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  if (!GetVersionEx(&osvi)) {
    fprintf(stderr, "get system version failed\n");
    return false;
  }
  major = osvi.dwMajorVersion;
  minor = osvi.dwMinorVersion;
  return true;
}
