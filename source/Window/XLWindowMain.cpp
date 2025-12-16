#include <source/Window/XLWindowMain.h>
#include "ui_XLWindowMain.h"
#include <source/Window/Progress/XLWindowProgress.h>
#include <source/Window/Success/XLWindowSuccess.h>
#include <source/Window/Delete/XLWindowDelete.h>



// 主界面
struct PKWindowMain
{
	// 界面 - 下载中
	XLWindowProgress*				viewProgress = nullptr;

	// 界面 - 已完成
	XLWindowSuccess*				viewSuccess = nullptr;

	// 界面 - 已删除
	XLWindowDelete*					viewDelete = nullptr;
};



// constructor
XLWindowMain::XLWindowMain(QWidget* _Parent) noexcept : QWidget(_Parent), ui(new Ui::XLWindowMain)
{
	d_ptr = new(std::nothrow) PKWindowMain();
	ui->setupUi(this);
	d_ptr->viewProgress = new(std::nothrow) XLWindowProgress(ui->Widget_View);
	d_ptr->viewSuccess = new(std::nothrow) XLWindowSuccess(ui->Widget_View);
	d_ptr->viewDelete = new(std::nothrow) XLWindowDelete(ui->Widget_View);
	ui->Layout_View->addWidget(d_ptr->viewProgress);
	ui->Layout_View->addWidget(d_ptr->viewSuccess);
	ui->Layout_View->addWidget(d_ptr->viewDelete);

	QObject::connect(ui->Button_Progress, &QPushButton::clicked, this, &XLWindowMain::receiveButtonProgress, Qt::QueuedConnection);
	QObject::connect(ui->Button_Success, &QPushButton::clicked, this, &XLWindowMain::receiveButtonSuccess, Qt::QueuedConnection);
	QObject::connect(ui->Button_Delete, &QPushButton::clicked, this, &XLWindowMain::receiveButtonDelete, Qt::QueuedConnection);
}

// destructor
XLWindowMain::~XLWindowMain() noexcept
{
	delete ui;
	delete d_ptr;
}



// [event] 大小
void XLWindowMain::resizeEvent(QResizeEvent* _Event) noexcept
{
	QWidget::resizeEvent(_Event);
}

// [event] 绘图
void XLWindowMain::paintEvent(QPaintEvent* _Event) noexcept
{
	QWidget::paintEvent(_Event);
}



// [handle] 处理 - 窗口切换
void XLWindowMain::handleWindowSwitch(XL_WINDOW_L1 _WL1) noexcept
{
	switch (_WL1)
	{
		case kXL_WL1_PROGRESS:
			d_ptr->viewProgress->show();
			d_ptr->viewSuccess->hide();
			d_ptr->viewDelete->hide();
			break;
		case kXL_WL1_SUCCESS:
			d_ptr->viewProgress->hide();
			d_ptr->viewSuccess->show();
			d_ptr->viewDelete->hide();
			break;
		case kXL_WL1_DELETE:
			d_ptr->viewProgress->hide();
			d_ptr->viewSuccess->hide();
			d_ptr->viewDelete->show();
			break;
		default:
			break;
	}
}



// [receive] 按钮点击 - 下载中
void XLWindowMain::receiveButtonProgress() noexcept
{
	handleWindowSwitch(kXL_WL1_PROGRESS);
}

// [receive] 按钮点击 - 已完成
void XLWindowMain::receiveButtonSuccess() noexcept
{
	handleWindowSwitch(kXL_WL1_SUCCESS);
}

// [receive] 按钮点击 - 已删除
void XLWindowMain::receiveButtonDelete() noexcept
{
	handleWindowSwitch(kXL_WL1_DELETE);
}
