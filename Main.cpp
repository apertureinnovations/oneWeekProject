
#include <iostream>
#include <Windows.h>

class UI {
	private:
		
		void initUI(std::string title, int winHeight, int winWidth) {
			WNDCLASSEX uiclass;

			std::memset(&uiclass, 0, sizeof(uiclass));
			uiclass.cbSize = sizeof(uiclass);
			uiclass.style = 0x0040;
			uiclass.lpfnWindProc = WndProc;
			uiclass.hInstance = GetModuleHandle(NULL);
			uiclass.hIcon = NULL;
			uiclass.hCursor = LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
			uiclass.hbrBackground =(HBRUSH)(COLOR_WINDOW + 1);
			uiclass.lpszClassName = L"MainWindowClass";
			RegisterClass(&uiclass);

			auto flag = WS_OVERLAPPEDWINDOW;
		}
	public:
		void runUI(std::string a,int b,int c) {
			initUI(a,b,c);
		}

};



void main() {
	
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