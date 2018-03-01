#pragma once
#include <atlstr.h>
namespace Nsis7zLog
{
	ATL::CString GetMyDocPath();
	BOOL WriteNsis7zLog(LPCTSTR pchKeyword, LPCTSTR pchFmt, ...);
}

