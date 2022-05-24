/**
 * 使用GDI绘制 多边形 矩形 圆 椭圆等 并进行上色
 */
#include <windows.h>
#include <cmath>

// 用于注册的窗口类名
const char g_szClassName[] = "GDI_WINDOW";

void Paint(HWND hwnd)
{
    // paint struct 绘图结构体，存储目标窗口可以绘图的客户端区域(client area)
    PAINTSTRUCT ps;
    HDC hdc;   // DC(可画图的内存对象) 的句柄
    HPEN hpen; // 画笔

    // 通过窗口句柄获取该窗口的 DC
    hdc = BeginPaint(hwnd, &ps);

    // 创建普通画笔
    hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    // DC 选择画笔
    SelectObject(hdc, hpen);
    // 写文字
    SetTextColor(hdc, RGB(255, 0, 255));
    SetBkColor(hdc, RGB(0, 255, 0));
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 502, 502, "Here is a green point!", 22);
    // 一个红色的点
    SetPixel(hdc, 500, 500, RGB(0, 255, 0));
    SetPixel(hdc, 501, 500, RGB(0, 255, 0));
    SetPixel(hdc, 500, 501, RGB(0, 255, 0));
    SetPixel(hdc, 501, 501, RGB(0, 255, 0));

    // 画线
    TextOut(hdc, 20, 20, "Line", 4);
    MoveToEx(hdc, 50, 50, NULL);
    LineTo(hdc, 50, 10);

    // 画圆弧
    static const float PI= 3.141592653;    // PI
    int R = 30;                            // 半径
    int n = 50;                            // 点数
    int centerX = 400, centerY = 400;      // 圆心
    float startAngle = 0.f, endAngle = PI; // 起始角度和终止角度

    TextOut(hdc, centerX, centerY, "arc", 3);
    MoveToEx(hdc, centerX + int(R * cos(startAngle)), centerY + int(R * sin(startAngle)), NULL);
    float x, y;
    float step = (endAngle - startAngle) / n;
    for(int i = 1; i <= n; i++)
    {
        LineTo(hdc, centerX + int(R * cos(step * i + startAngle)), centerY + int(R * sin(step * i + startAngle)));
    }

    // 六边形顶点
    TextOut(hdc, 440, 10, "six-edge polygon", 16);
    POINT gPoint[6] = {{420, 10}, {540, 140}, {600, 100}, {550, 200}, {380, 180}, {420, 10}};
    Polygon(hdc, gPoint, 6);
    // 画填充矩形 边框仍是画笔颜色
    TextOut(hdc, 30, 200, "solid rect", 10);
    RECT rect;
    rect.left = 100;
    rect.top = 200;
    rect.right = 200;
    rect.bottom = 300;
    FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 255)));
    // 画线框矩形
    TextOut(hdc, 30, 310, "frame rect", 10);
    rect.left = 100;
    rect.top = 310;
    rect.right = 200;
    rect.bottom = 410;
    FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));

    // 换填充笔刷
    HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, bBrush);
    // 画填充椭圆
    TextOut(hdc, 100, 130, "solid ellipse", 13);
    Ellipse(hdc, 100, 150, 50, 120);
    // 画填充圆
    TextOut(hdc, 100, 80, "solid circle", 12);
    Ellipse(hdc, 100, 100, 50, 50);

    TextOut(hdc, 230, 90, "solid rect", 10);
    Rectangle(hdc, 200, 90, 230, 120);        // 普通矩形
    TextOut(hdc, 270, 10, "solid round rect", 16);
    RoundRect(hdc, 200, 10, 270, 80, 25, 25); // 圆角矩形

    EndPaint(hwnd, &ps);
}

/*
 * 第四步,窗口过程
 */
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    // 窗口绘制消息
    case WM_PAINT:
        /*
             * 只有这一个 case 是我们 GDI 入门中需要注意的
             *
             * 当程序执行到这个地方的时候，意味着系统像我们的程序发送了 WM_PAINT 消息
             * 也就是告诉我们的程序，可以开始绘制窗口的内容了。
             *
             */
        Paint(hwnd);
        break;
    // 窗口关闭消息
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    // 窗口销毁消息
    case WM_DESTROY:
        PostQuitMessage(0); // 发送离开消息给系统
        break;
    // 其他消息
    default:
        // pass 给系统，咱不管
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/*
 * 第一步,注册窗口类
 */
void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    // 1)配置窗口属性
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = MyWindowProc; // 设置第四步的窗口过程回调函数
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // 2)注册
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Failed to register window!"), TEXT("wrong"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // 进程退出
    }
}

/*
 * 第二步，创建窗口
 */
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd;
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        TEXT("GDI"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, // 出现坐标 x,y 默认分配 窗口宽 400 高 300
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, TEXT("Failed to create window!"), TEXT("wrong"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // 进程退出
    }

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}

/*
 * 主函数
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG Msg;

    // 第一步,注册窗口类
    RegisterMyWindow(hInstance);
    // 第二步:创建窗口
    hwnd = CreateMyWindow(hInstance, nCmdShow);
    // 第三步:消息循环
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}