
#include <iostream>
#include <Windows.h>

class UI {
	private:
		void initUI(std::string title, int winWidth, int winHeight) {
			WNDCLASSEX uiclass;

			std::memset(&uiclass, 0, sizeof(uiclass));
			// purging memory and zeroing
			uiclass.cbSize = sizeof(uiclass);
			// setting size of the structure - versioning or variable length?? need to check
			uiclass.style = 0x0040;
			// setting style to CS_CLASSDC
			uiclass.lpfnWindProc = WndProc;
			// setting WndProc
			uiclass.hInstance = GetModuleHandle(NULL);
			// getting exe handle of current program (hence NULL)
			uiclass.hIcon = NULL;
			// setting to default icon
			uiclass.hCursor = LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
			// setting to default cursor using loadimage
			uiclass.hbrBackground =(HBRUSH)GetStockObject(DKGRAY_BRUSH);
			//  setting window to dark gray
			uiclass.lpszClassName = L"MainWindowClass";
			// defining name for reference
			RegisterClass(&uiclass);

			auto flag = WS_OVERLAPPEDWINDOW;
			// ?? need to ask

			std::wstring str(title.begin(), title.end());
			// conversion from string to wstring


			HWND hwnd = CreateWindowExW(NULL, uiclass.lpszClassName, str.c_str(), flag, 0, 0, winWidth, winHeight, 0, 0, uiclass,hInstance, 0);

			ShowWindow(hwnd, SW_SHOWDEFAULT);
			UpdateWindow(hwnd);
		}
	public:
		void runUI(std::string a,int b,int c) {
			initUI(a,b,c);
		}
		// running the function that is in the private scope here - 
		//means all vars and classes within cannot be accessed by outside
};



void main() {
	UI box("Main Window", 1600, 900);

	bool done = false;
    while (!done) {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

    }
}

LRESULT WINAPI WndProc (HWND hWnd, UINT data, WPARAM wParam, LPARAM lParam) {
	switch(data) {
		case WM_SIZE:
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) {
				return 0;
			}
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
	}
	return ::DefWindowProcW(hWnd, data, wParam, lParam);
}