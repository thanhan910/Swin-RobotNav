//#include <windows.h>
//#include <string>
//#include "Location.h"
//
//enum Color32
//{
//	White,
//	Black,
//	Red,
//	Green,
//	Blue,
//	Yellow,
//	Orange,
//	Cyan,
//	Purple,
//	Pink,
//	Brown,
//	Grey,
//};
//const int COLOR_COUNT = 12;
//
//COLORREF colorRGB[COLOR_COUNT];
//
//HBRUSH colorbrush[COLOR_COUNT];
//
//void initialize_colors_and_brushes()
//{
//	// Initialize the colorrefs
//	colorRGB[Color32::White] = RGB(255, 255, 255);
//	colorRGB[Color32::Black] = RGB(0, 0, 0);
//	colorRGB[Color32::Red] = RGB(255, 0, 0);
//	colorRGB[Color32::Green] = RGB(0, 128, 0);
//	colorRGB[Color32::Blue] = RGB(0, 0, 255);
//	colorRGB[Color32::Yellow] = RGB(255, 255, 0);
//	colorRGB[Color32::Orange] = RGB(255, 165, 0);
//	colorRGB[Color32::Cyan] = RGB(128, 0, 128);
//	colorRGB[Color32::Purple] = RGB(255, 192, 203);
//	colorRGB[Color32::Pink] = RGB(255, 192, 203);
//	colorRGB[Color32::Brown] = RGB(165, 42, 42);
//	colorRGB[Color32::Grey] = RGB(128, 128, 128);
//
//	for (int i = 0; i < COLOR_COUNT; i++)
//	{
//		colorbrush[i] = CreateSolidBrush(colorRGB[i]);
//	}
//}
//
//enum Menu
//{
//	Initial, Goal, Wall,
//	DFS, BFS, GBFS, AS, CUS1, CUS2
//};
//
//Menu currentMode = Menu::Initial;
//
//// Global variables
//const int CELL_SIZE = 30;
//const int GRID_SIZE = 30;
//const int GRID_ORIGIN_X = 200;
//const int GRID_ORIGIN_Y = 100;
//int grid[GRID_SIZE][GRID_SIZE] = { Color32::White };
//
//
//int currentColor = Color32::Red;
//
//// Function declarations
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//void DrawGrid(HDC hdc);
//void ToggleCell(int x, int y);
//
//void DrawGrid(HDC hdc)
//{
//	for (int x = 0; x < GRID_SIZE; x++)
//	{
//		for (int y = 0; y < GRID_SIZE; y++)
//		{
//			RECT rect = {
//				GRID_ORIGIN_X + x * CELL_SIZE, // top left x position
//				GRID_ORIGIN_Y + y * CELL_SIZE, // top left y position
//				GRID_ORIGIN_X + (x + 1) * CELL_SIZE, // bottom right x position
//				GRID_ORIGIN_Y + (y + 1) * CELL_SIZE // bottom right y position
//			};
//			// Draw cell
//			FillRect(hdc, &rect, colorbrush[grid[x][y]]); // Draw cell
//			DrawEdge(hdc, &rect, EDGE_SUNKEN, BF_RECT); // Draw edge
//
//			std::string s = "N";
//
//			// COnvert string to wide char
//			int bufferSize = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
//			wchar_t* buffer = new wchar_t[bufferSize];
//			MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, bufferSize);
//
//			// Draw text
//			SetTextColor(hdc, colorRGB[Color32::Black]);
//			SetBkMode(hdc, TRANSPARENT);
//			DrawText(hdc, buffer, -1, &rect, DT_LEFT | DT_TOP | DT_SINGLELINE);
//		}
//	}
//}
//
//void ToggleCell(int x, int y)
//{
//	if (grid[x][y] == currentColor) grid[x][y] = 0;
//	else grid[x][y] = currentColor;
//}
//
//void create_window()
//{
//	// initialize variables
//	initialize_colors_and_brushes();
//
//	// Register the window class
//	const wchar_t CLASS_NAME[] = L"Grid Window Class";
//	HINSTANCE hInstance = GetModuleHandle(NULL);
//	WNDCLASS wc = { };
//	wc.lpfnWndProc = WindowProc;
//	wc.hInstance = hInstance;
//	wc.lpszClassName = CLASS_NAME;
//
//	RegisterClass(&wc);
//
//	// Create the window
//	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Grid",
//		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
//		GRID_ORIGIN_X + GRID_SIZE * CELL_SIZE + CELL_SIZE, // width
//		GRID_ORIGIN_Y + GRID_SIZE * CELL_SIZE + CELL_SIZE, // height
//		NULL, NULL, hInstance, NULL);
//
//	if (hwnd == NULL) return;
//
//	// Show the window
//	ShowWindow(hwnd, SW_SHOWDEFAULT);
//
//	// Run the message loop
//	MSG msg = { };
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//}
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;
//	int x, y;
//
//	switch (uMsg)
//	{
//	case WM_CREATE:
//		// Create the radio buttons
//		CreateWindow(L"BUTTON", L"Initial", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
//			10, 10, 80, 30, hwnd, (HMENU)Menu::Initial, GetModuleHandle(NULL), NULL);
//		CreateWindow(L"BUTTON", L"Goal", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
//			10, 50, 80, 30, hwnd, (HMENU)Menu::Goal, GetModuleHandle(NULL), NULL);
//		CreateWindow(L"BUTTON", L"Wall", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
//			10, 90, 80, 30, hwnd, (HMENU)Menu::Wall, GetModuleHandle(NULL), NULL);
//
//		// Set the first radio button to checked
//		SendMessage(GetDlgItem(hwnd, currentMode), BM_SETCHECK, BST_CHECKED, 0);
//
//		break;
//	case WM_COMMAND:
//		//currentMode = LOWORD(wParam);
//		// Handle the radio button clicks
//		switch (LOWORD(wParam))
//		{
//		case Menu::Initial:
//			currentColor = Color32::Red;
//			break;
//		case Menu::Goal:
//			currentColor = Color32::Green;
//			break;
//		case Menu::Wall:
//			currentColor = Color32::Grey;
//			break;
//		}
//		break;
//	case WM_PAINT:
//		// Draw the grid
//		PAINTSTRUCT ps;
//		hdc = BeginPaint(hwnd, &ps);
//		DrawGrid(hdc);
//		EndPaint(hwnd, &ps);
//		break;
//	case WM_LBUTTONDOWN:
//		// Toggle the cell that was clicked
//		x = (LOWORD(lParam) - GRID_ORIGIN_X) / CELL_SIZE;
//		y = (HIWORD(lParam) - GRID_ORIGIN_Y) / CELL_SIZE;
//		if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE)
//		{
//			// Update the selected cell
//			ToggleCell(x, y);
//			// Redraw the window
//			InvalidateRect(hwnd, NULL, TRUE);
//		}
//		break;
//	case WM_DESTROY:
//		// Cleanup
//		DeleteObject(colorRGB);
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hwnd, uMsg, wParam, lParam);
//	}
//	return 0;
//}
//
