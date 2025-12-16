#include <source/Window/XLWindowMain.h>



// [main] 启用HDPI支持
static void XL_Main_Enable_HDPI_Support() noexcept
{
#if defined(Q_OS_WIN32)
	SetProcessDPIAware();

	auto		vDesktopDC = ::GetDC(nullptr);
	auto		vDPI_W = ::GetDeviceCaps(vDesktopDC, LOGPIXELSX);
	::ReleaseDC(nullptr, vDesktopDC);

	auto		vScanRatio = (double)vDPI_W / 96.0f;
	if(vScanRatio <= 0.4f)
	{
		qputenv("QT_SCALE_FACTOR", "0.25");
	}
	else if(vScanRatio <= 0.6f)
	{
		qputenv("QT_SCALE_FACTOR", "0.5");
	}
	else if(vScanRatio <= 0.9f)
	{
		qputenv("QT_SCALE_FACTOR", "0.75");
	}
	else if(vScanRatio <= 1.1f)
	{
		qputenv("QT_SCALE_FACTOR", "1.0");
	}
	else if(vScanRatio <= 1.4f)
	{
		qputenv("QT_SCALE_FACTOR", "1.25");
	}
	else if(vScanRatio <= 1.6f)
	{
		qputenv("QT_SCALE_FACTOR", "1.5");
	}
	else if(vScanRatio <= 1.9f)
	{
		qputenv("QT_SCALE_FACTOR", "1.75");
	}
	else if(vScanRatio <= 2.1f)
	{
		qputenv("QT_SCALE_FACTOR", "2.0");
	}
	else if(vScanRatio <= 2.4f)
	{
		qputenv("QT_SCALE_FACTOR", "2.25");
	}
	else if(vScanRatio <= 2.6f)
	{
		qputenv("QT_SCALE_FACTOR", "2.5");
	}
	else
	{
		qputenv("QT_SCALE_FACTOR", "3.0");
	}
#else
	// 启用高DPI缩放
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
	qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
#endif
	// OpenGL渲染级别		(不启用时可能：在某些旧显卡机器上启动程序时，浏览器页面显示花屏)
	// QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL, true);
	QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, true);

	// 高质量图片
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
}



// 入口点
int main(int _Argc, char* _Argv[])
{
	XL_Main_Enable_HDPI_Support();
	QApplication	app(_Argc, _Argv);

	XLWindowMain	w(nullptr);
	w.resize(2000, 1500);
	w.show();

	return QApplication::exec();
}
