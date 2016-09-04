/*
 * Writing by German Bernhardt <german.bernhardt@gmail.com>
 * if you make any improvements please let me know thanks!
 */
#include "stdafx.h"

#include <windows.h>
#include "sendkeys.h"
#include "sendkeys.cpp"
#include "serial.h"
#include "serial.cpp"
#include <commdlg.h>
#include <tchar.h>

// JPEG CONVERSION
#include <unknwn.h>
#include <gdiplus.h>
#include <memory>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
using namespace std;

 // ZNTS = NON THREAD SAFE
//#pragma comment(lib,"php7.lib")
//#define ZNTS 1

// ZTS = THREAD SAFE
//#pragma comment(lib,"php5ts.lib")
#pragma comment(lib,"php7ts.lib")
#define ZTS 1

#define PHP_COMPILER_ID "VC14"
#define ZEND_WIN32 1
#define PHP_WIN32 1

#include <php.h>
#ifdef HAVE_CONFIG_H
 #include "config.h"
#endif
#define ZEND_DEBUG 1
#include "php_wapi.h"

static zend_function_entry wapi_functions[]={
	PHP_FE(wapi_screenshot,NULL)
	PHP_FE(wapi_get_window,NULL)
	PHP_FE(wapi_set_window,NULL)
	PHP_FE(wapi_get_window_process_id,NULL)
	PHP_FE(wapi_open_process,NULL)
	PHP_FE(wapi_read_process_memory,NULL)
	PHP_FE(wapi_write_process_memory,NULL)

	PHP_FE(wapi_get_window_text,NULL)
	PHP_FE(wapi_set_window_text,NULL)

	PHP_FE(wapi_get_clipboard,NULL)
	PHP_FE(wapi_set_clipboard,NULL)

	PHP_FE(wapi_mouse_event,NULL)
	PHP_FE(wapi_set_cursor_pos,NULL)
	PHP_FE(wapi_sendkeys,NULL)
	PHP_FE(wapi_get_cursor_pos,NULL)
	PHP_FE(wapi_get_key_state,NULL)

	PHP_FE(wapi_dialog,NULL)

	PHP_FE(wapi_serial_connect,NULL)
	PHP_FE(wapi_serial_write,NULL)
	PHP_FE(wapi_serial_read,NULL)
	PHP_FE(wapi_serial_is_connected,NULL)
	{NULL, NULL, NULL}
};

zend_module_entry wapi_module_entry = {
 #if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
 #endif
 PHP_WAPI_EXTNAME,
 wapi_functions,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 #if ZEND_MODULE_API_NO >= 20010901
  PHP_WAPI_VERSION,
 #endif
 STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(wapi)

class CScreenShot {
public:
	/*
	 * philipgoh/screen_grab.cpp
	 * https://gist.github.com/philipgoh/3865787
	 */
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
		UINT num = 0;          // number of image encoders
		UINT size = 0;         // size of the image encoder array in bytes
		ImageCodecInfo* pImageCodecInfo = NULL;
		
		GetImageEncodersSize(&num, &size);
		if (size == 0) return -1;  // Failure
		
		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL) return -1;  // Failure
		
		GetImageEncoders(num, size, pImageCodecInfo);
		for (UINT j = 0; j < num; ++j) {
			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;  // Success
			}
		}
		free(pImageCodecInfo);
		return -1;  // Failure
	}

	void screenshot(HWND WindowHwnd, char *name, DWORD left, DWORD top, DWORD width, DWORD height) {
		RECT WindowParams;
		GetClientRect(WindowHwnd, &WindowParams);
		if (width == 0) width = WindowParams.right - WindowParams.left;
		if (height == 0) height = WindowParams.bottom - WindowParams.top;

		//CREATE
		HDC DevC = GetDC(NULL);
		HDC CaptureDC = CreateCompatibleDC(DevC);
		HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC, WindowParams.right - WindowParams.left, WindowParams.bottom - WindowParams.top);
		SelectObject(CaptureDC, CaptureBitmap);
		
		char ext[4];
		memcpy(ext, &name[(strlen(name) - 3)], 3);
		ext[3] = '\0';
		if (strcmp(ext, "jpg") == 0) {
			// Initialize GDI+.
			GdiplusStartupInput gdiplusStartupInput;
			ULONG_PTR gdiplusToken;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			// JPEG
			BitBlt(CaptureDC, 0, 0, width, height, DevC, left, top, SRCCOPY | CAPTUREBLT);
			Bitmap *p_bmp = Bitmap::FromHBITMAP(CaptureBitmap, NULL);
			CLSID pngClsid;
			int result = GetEncoderClsid(L"image/jpeg", &pngClsid);
			
			WCHAR wname[255];
			int len = strlen(name);
			for (int i = 0; i < len; i++) {
				wname[i] = name[i];
				if (i == len - 1) wname[i + 1] = '\0';
			}
			p_bmp->Save(wname, &pngClsid, NULL);
			delete p_bmp;

			//Shutdown GDI+
			GdiplusShutdown(gdiplusToken);

		} else {
			// BMP
			DWORD FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * (width*height * 4));
			char *BmpFileData = (char*)GlobalAlloc(0x0040, FileSize);
			PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
			PBITMAPINFOHEADER  BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];
			BFileHeader->bfType = 0x4D42; // BM
			BFileHeader->bfSize = sizeof(BITMAPFILEHEADER);
			BFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
			BInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
			BInfoHeader->biPlanes = 1;
			BInfoHeader->biBitCount = 24;
			BInfoHeader->biCompression = BI_RGB;
			BInfoHeader->biHeight = height;
			BInfoHeader->biWidth = width;
			RGBTRIPLE *image = (RGBTRIPLE*)&BmpFileData[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];
			RGBTRIPLE color;

			BitBlt(CaptureDC, 0, 0, width, height, DevC, left, top, SRCCOPY | CAPTUREBLT);
			GetDIBits(CaptureDC, CaptureBitmap, 0, height, image, (LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

			DWORD Junk;
			HANDLE FH = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
			WriteFile(FH, BmpFileData, FileSize, &Junk, 0);
			CloseHandle(FH);
			GlobalFree(BmpFileData);
		}

		// clean up
		DeleteObject(CaptureBitmap);// fuck glitch 9994
		DeleteDC(CaptureDC);
		ReleaseDC(NULL, DevC);// fuck glitch 9994
		DeleteDC(DevC);
		// END
	};
};
CScreenShot m_ss; // ScreenShot Object
PHP_FUNCTION(wapi_screenshot) {
	char *str;zend_long len,handle,left,top,width,height;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lsllll", &handle, &str, &len, &left, &top, &width, &height) == FAILURE) RETURN_NULL();
	if (handle == 0) handle = (zend_long)GetDesktopWindow();
	m_ss.screenshot((HWND)handle, str, (DWORD)left, (DWORD)top, (DWORD)width, (DWORD)height);
	RETURN_NULL();
}

PHP_FUNCTION(wapi_get_window) {
	char *str; zend_long len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) == FAILURE) RETURN_NULL();
	if (strcmp(str, "active") == 0) {
		RETURN_LONG((long)GetActiveWindow());
	} else if (strcmp(str, "console") == 0) {
		RETURN_LONG((long)GetConsoleWindow());
	} else if (strcmp(str, "desktop") == 0) {
		RETURN_LONG((long)GetDesktopWindow());
	} else if (strcmp(str, "foreground") == 0) {
		RETURN_LONG((long)GetForegroundWindow());
	} else {
		RETURN_LONG((long)FindWindow(NULL, str));
	}
	RETURN_NULL();
}

PHP_FUNCTION(wapi_set_window) {
	char *str; zend_long len, handle;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &str, &len, &handle) == FAILURE) RETURN_NULL();
	if (strcmp(str, "active") == 0) {
		RETURN_BOOL(SetActiveWindow((HWND)handle));
	} else if (strcmp(str, "foreground") == 0) {
		RETURN_BOOL(SetForegroundWindow((HWND)handle));
	} else if (strcmp(str, "focus") == 0) {
		RETURN_BOOL(SetFocus((HWND)handle));
	} else if (strcmp(str, "enable") == 0) {
		RETURN_BOOL(EnableWindow((HWND)handle, true));
	} else if (strcmp(str, "disable") == 0) {
		RETURN_BOOL(EnableWindow((HWND)handle, false));
	}
	RETURN_BOOL(false);
}

PHP_FUNCTION(wapi_get_window_process_id) {
	zend_long handle; DWORD id;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &handle) == FAILURE) RETURN_NULL();
	GetWindowThreadProcessId((HWND)handle, &id);
	RETURN_LONG((long)id);
}

PHP_FUNCTION(wapi_open_process) {
	zend_long pid;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &pid) == FAILURE) RETURN_NULL();
	 RETURN_LONG((long)OpenProcess(PROCESS_ALL_ACCESS, false, (DWORD)pid));
}

PHP_FUNCTION(wapi_read_process_memory) {
	zend_long handle, address; DWORD buffer = 22; SIZE_T bytes;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &handle, &address) == FAILURE) RETURN_NULL();
	ReadProcessMemory((HANDLE)handle, (LPCVOID)address, &buffer, sizeof(buffer), &bytes);
	RETURN_LONG((long)buffer);
}

PHP_FUNCTION(wapi_write_process_memory) {
	zend_long handle, address, value; SIZE_T bytes;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &handle, &address, &value) == FAILURE) RETURN_NULL();
	RETURN_BOOL(WriteProcessMemory((HANDLE)handle, (LPVOID)address, &value, sizeof(value), &bytes));
}

PHP_FUNCTION(wapi_get_window_text) {
	char str[1000]; zend_long handle;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &handle) == FAILURE) RETURN_NULL();
	GetWindowText((HWND)handle, str, sizeof(str));
	RETURN_STRING(str);
}

PHP_FUNCTION(wapi_set_window_text) {
	char *str; zend_long len, handle;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &str, &len, &handle) == FAILURE)  RETURN_BOOL(false);
	RETURN_BOOL(SetWindowText((HWND)handle, (LPCSTR)str));
}

PHP_FUNCTION(wapi_get_clipboard) {
	HANDLE h;
	if (!OpenClipboard(NULL)) RETURN_NULL();
	h = GetClipboardData(CF_TEXT);
	CloseClipboard();
	if ((char*)h == NULL) {
		RETURN_NULL();
	} else {
		RETURN_STRING((char*)h);
	}
}

PHP_FUNCTION(wapi_set_clipboard) {
	char *str; zend_long len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) == FAILURE)  RETURN_BOOL(false);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len+1);
	memcpy(GlobalLock(hMem), str, len+1);
	GlobalUnlock(hMem);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

PHP_FUNCTION(wapi_mouse_event) {
	zend_long event,x,y,data,info;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllll", &event, &x, &y, &data, &info) == FAILURE) RETURN_NULL();
	mouse_event((int)event, (int)x, (int)y, (int)data, (int)info);
}

PHP_FUNCTION(wapi_set_cursor_pos) {
	zend_long l, t;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &l, &t) == FAILURE) RETURN_NULL();
	SetCursorPos((int)l, (int)t);
}

CSendKeys m_sk;// SendKeys Object
PHP_FUNCTION(wapi_sendkeys) {
	char *str; zend_long len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) == FAILURE) RETURN_NULL();
	m_sk.SendKeys(_T(str));
}

PHP_FUNCTION(wapi_get_cursor_pos) {
	POINT point;
	char buffer[11];
	if(GetCursorPos(&point)) {
		snprintf(buffer, sizeof(buffer), "%d%s%d", point.x, ";", point.y);
	}
	RETURN_STRING(buffer);
}

PHP_FUNCTION(wapi_get_key_state) {
	zend_long key;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) RETURN_NULL();
	if (GetKeyState((int)key) & 0x80) {
		RETURN_BOOL(true);
	} else {
		RETURN_BOOL(false);
	}
}

PHP_FUNCTION(wapi_dialog) {
	char *str, *filter; zend_long lstr, lfilter;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &str, &lstr, &filter, &lfilter) == FAILURE) RETURN_NULL();
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = 0;
	ofn.lpstrDefExt = 0;
	ofn.lpstrFile = new TCHAR[MAX_PATH];
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = _T(filter);
	ofn.nFilterIndex = 0;
	ofn.lpstrInitialDir = 0;
	ofn.lpstrTitle = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (strcmp(str, "open") == 0) {
		GetOpenFileName(&ofn);
	} else {
		GetSaveFileName(&ofn);
	}
	RETURN_STRING(ofn.lpstrFile);
}

Serial m_serial; // Serial object
PHP_FUNCTION(wapi_serial_connect) {
	char *str; zend_long len, baudRate;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &str, &len,&baudRate) == FAILURE) RETURN_NULL();
	if(m_serial.Connect(str,baudRate)){
	 RETURN_BOOL(true);
	} else {
	 RETURN_BOOL(false);
	}
}

PHP_FUNCTION(wapi_serial_write) {
	char *str; zend_long len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) == FAILURE) RETURN_NULL();
	m_serial.WriteData(str,len);
}

PHP_FUNCTION(wapi_serial_read) {
	zend_long num;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &num) == FAILURE) RETURN_NULL();
	char str[256] = "";
	m_serial.ReadData(str, (int)num);
	RETURN_STRING(str);
}

PHP_FUNCTION(wapi_serial_is_connected) {
	if (m_serial.IsConnected()) {
		RETURN_BOOL(true);
	} else {
		RETURN_BOOL(false);
	}
}