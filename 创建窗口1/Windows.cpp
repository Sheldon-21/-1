#include <windows.h>

//���ڹ��̺���
LRESULT CALLBACK DealMessage(HWND hWnd,//���ھ������Ϣ�����Ĵ���
	UINT uMsg,//��Ϣ��־
	WPARAM wParam,//������Ϣ
	LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, TEXT("ABC"), TEXT("����������"), MB_OK);
		break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;  //��ͼ�ṹ��
		HDC dc = BeginPaint(hWnd, &ps);//��ʼ
		wchar_t  p[] = L"��������";//ת�����ֽ�
		TextOutW(dc, 30, 30, p,wcslen (p) );
		EndPaint(hWnd, &ps);//
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(2);//WM_QUIT,�������� return msg.wParam
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//WINAPI:���κ������涨�˺���������ջ�������󣬺���������ϣ��Զ������ջ
//CALLBACK����������ĺ���һ����
int WINAPI WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ��
	HINSTANCE hPrevInstance,//��һ��Ӧ�ó���ʵ��������
	LPSTR lpCmdLine,//�����в���
	int nCmdShow//������ʾ����ʽ����󻯣���С��
	)
{
	/*
	1��������ں��� WinMain( )
	2������һ������
	  A����ƴ����� WNDCLASS������Ա������ֵ��
	  B��ע�ᴰ����
	  C����ʾ�͸��´���
	3����Ϣѭ��
	4�����ڹ��̺���
	*/


	//��ƴ����� WNDCLASS������Ա��ֵ��
	WNDCLASS wc;
	wc.cbClsExtra = 0;//��ĸ�����Ϣ
	wc.cbWndExtra = 0;//���ڸ�����Ϣ
						//��ȡϵͳĬ�ϵİ�ɫ����
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����ɫ������д
	//wc.hCursor = NULL;//���,ʹ��Ĭ��
	wc.hCursor = LoadCursor(NULL, IDC_HELP);//����ϵͳĬ�Ϲ��
	//wc.hIcon = NULL;//Ĭ��ͼ��
	wc.hIcon = LoadIcon(NULL, IDI_WARNING);//����ϵͳĬ��ͼ��

	wc.hInstance = hInstance;//Ӧ�ó���ʵ��
	wc.lpfnWndProc = DealMessage;//���ڹ��̺������֣���Ϣ������

	wc.lpszClassName = TEXT("abc");//�������
	wc.lpszMenuName = NULL;//�˵�����
	wc.style = nCmdShow; //��ʾ���

	//B)ע�ᴰ���࣬����ϵͳ���ڹ��̺�������ڵ�ַ
	RegisterClass(&wc);

	//C)����������
	HWND hWnd = CreateWindow(TEXT("abc"), TEXT("��һ������"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	//D)��ʾ�͸��´���
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	//��Ϣѭ��
	MSG msg;
	//������ܵ�WM_QUIT������0���˳�
	//�����������-1�����˳�
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//���빤��
		//���ⰴ��תΪ��׼�ַ�WM_CHAR
		TranslateMessage(&msg);

		//������ϵͳ�ַ���Ϣ
		DispatchMessage(&msg);

	}
	return msg.wParam;
}