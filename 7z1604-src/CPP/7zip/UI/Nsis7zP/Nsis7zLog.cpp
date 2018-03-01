#include "stdafx.h"
#include "Nsis7zLog.h"
#include <ShlObj.h>
#include <ShellAPI.h>

namespace Nsis7zLog
{
//获取我的文档目录
ATL::CString GetMyDocPath()
{
	HKEY	hKey = NULL;
	DWORD	dwType = REG_SZ;
	TCHAR	szPath[MAX_PATH * 2] = { 0 };
	DWORD	dwData = _countof(szPath) - 1;
	TCHAR	szDocuments[MAX_PATH * 2] = { 0 };

	::SHGetSpecialFolderPath(NULL, szDocuments, CSIDL_PERSONAL, FALSE);
	if (_tcsstr(szDocuments, _T("systemprofile")) == NULL)
		return szDocuments;

	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"), 0, KEY_READ, &hKey))
		return szDocuments;

	if (ERROR_SUCCESS == RegQueryValueEx(hKey, _T("Personal"), NULL, &dwType, (LPBYTE)szPath, &dwData))
		_tcscpy_s(szDocuments, dwData, szPath);

	RegCloseKey(hKey);
	return szDocuments;
}

BOOL WriteNsis7zLog(LPCTSTR pchKeyword, LPCTSTR pchFmt, ...)
{
	va_list va = (va_list)(&pchFmt + 1);
	CString strText;
	strText.FormatV(pchFmt, va);
	SYSTEMTIME t;
	::GetLocalTime(&t);
	CString strLogInfo;
	strLogInfo.Format(_T("\n%04d-%02d-%02d %02d:%02d:%02d.%03d [%s] %s"),
		t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, pchKeyword, strText);

	CString strDoc = GetMyDocPath();
	strDoc += _T("\\EC 10.0\\Log");

	if (!::PathFileExists(strDoc))
		::SHCreateDirectoryEx(NULL, strDoc, NULL);
	strDoc += _T("\\Nsis7zLog.log");
	HANDLE hFile = CreateFile(strDoc, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::SetFilePointer(hFile, 0, NULL, FILE_END);
	}

	DWORD dwWritted = 0;
	if (INVALID_HANDLE_VALUE != hFile)
		::WriteFile(hFile, strLogInfo.GetString(), strLogInfo.GetLength() * sizeof(TCHAR), &dwWritted, NULL);
	CloseHandle(hFile);
	return TRUE;
}

}
