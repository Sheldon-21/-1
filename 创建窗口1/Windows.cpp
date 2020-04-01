#include <windows.h>

//窗口过程函数
LRESULT CALLBACK DealMessage(HWND hWnd,//窗口句柄，消息所属的窗口
	UINT uMsg,//消息标志
	WPARAM wParam,//附加信息
	LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, TEXT("ABC"), TEXT("鼠标左键按下"), MB_OK);
		break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;  //绘图结构体
		HDC dc = BeginPaint(hWnd, &ps);//开始
		wchar_t  p[] = L"可以了吗？";//转化宽字节
		TextOutW(dc, 30, 30, p,wcslen (p) );
		EndPaint(hWnd, &ps);//
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(2);//WM_QUIT,给主函数 return msg.wParam
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//WINAPI:修饰函数，规定了函数参数入栈从右往左，函数调用完毕，自动清理堆栈
//CALLBACK：（和上面的含义一样）
int WINAPI WinMain(HINSTANCE hInstance,//应用程序实例
	HINSTANCE hPrevInstance,//上一个应用程序实例，不用
	LPSTR lpCmdLine,//命令行参数
	int nCmdShow//窗口显示的样式，最大化，最小化
	)
{
	/*
	1，定义入口函数 WinMain( )
	2，创建一个窗口
	  A）设计窗口类 WNDCLASS（给成员变量赋值）
	  B）注册窗口类
	  C）显示和更新窗口
	3，消息循环
	4，窗口过程函数
	*/


	//设计窗口类 WNDCLASS（给成员赋值）
	WNDCLASS wc;
	wc.cbClsExtra = 0;//类的附加信息
	wc.cbWndExtra = 0;//窗口附加信息
						//获取系统默认的白色画板
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景色，必须写
	//wc.hCursor = NULL;//光标,使用默认
	wc.hCursor = LoadCursor(NULL, IDC_HELP);//加载系统默认光标
	//wc.hIcon = NULL;//默认图标
	wc.hIcon = LoadIcon(NULL, IDI_WARNING);//加载系统默认图标

	wc.hInstance = hInstance;//应用程序实例
	wc.lpfnWndProc = DealMessage;//窗口过程函数名字，消息处理函数

	wc.lpszClassName = TEXT("abc");//类的名字
	wc.lpszMenuName = NULL;//菜单名字
	wc.style = nCmdShow; //显示风格

	//B)注册窗口类，告诉系统窗口过程函数的入口地址
	RegisterClass(&wc);

	//C)创建窗口类
	HWND hWnd = CreateWindow(TEXT("abc"), TEXT("第一个窗口"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	//D)显示和更新窗口
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	//消息循环
	MSG msg;
	//如果接受到WM_QUIT，返回0，退出
	//如果出错，返回-1，不退出
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//翻译工作
		//虚拟按键转为标准字符WM_CHAR
		TranslateMessage(&msg);

		//给操作系统分发消息
		DispatchMessage(&msg);

	}
	return msg.wParam;
}