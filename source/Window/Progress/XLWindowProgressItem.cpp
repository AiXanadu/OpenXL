#include <source/Window/Progress/XLWindowProgressItem.h>
#include "ui_XLWindowProgressItem.h"



// constructor
XLWindowProgressItem::XLWindowProgressItem(QWidget* _Parent, const XL_TASK_SHARED& _TaskS, bool _Release) noexcept : XLMessageWidget(_Parent, _TaskS, _Release), ui(new Ui::XLWindowProgressItem)
{
	ui->setupUi(this);

	ui->Bar_Task_Progress->setRange(0, 10000);

	QObject::connect(ui->Button_Start, &QPushButton::clicked, this, &XLWindowProgressItem::receiveButtonStart, Qt::QueuedConnection);
	QObject::connect(ui->Button_Stop, &QPushButton::clicked, this, &XLWindowProgressItem::receiveButtonStop, Qt::QueuedConnection);

	observerListenAppend(XLM_TASK_UPDATE);
}

// destructor
XLWindowProgressItem::~XLWindowProgressItem() noexcept
{
	delete ui;
}



// [msg] 任务更新
void XLWindowProgressItem::messageTaskUpdate() noexcept
{
	// 更新状态
	switch(taskShared()->taskStatus)
	{
		case kXL_DS_ERROR:
			ui->Label_Task_Status->setText(tr("下载失败"));
			ui->Button_Start->show();
			ui->Button_Stop->hide();
			break;
		case kXL_DS_PAUSE:
			ui->Label_Task_Status->setText(tr("已暂停"));
			ui->Button_Start->show();
			ui->Button_Stop->hide();
			break;
		case kXL_DS_DOWNLOAD:
			ui->Label_Task_Status->setText(tr("下载中"));
			ui->Button_Start->hide();
			ui->Button_Stop->show();
			break;
		case kXL_DS_COMPLETE:
			ui->Label_Task_Status->setText(tr("已完成"));
			ui->Button_Start->hide();
			ui->Button_Stop->hide();
			break;
		case kXL_DS_WAIT_START:
			ui->Label_Task_Status->setText(tr("等待开始"));
			ui->Button_Start->hide();
			ui->Button_Stop->show();
			break;
		case kXL_DS_WAIT_STOP:
			ui->Label_Task_Status->setText(tr("等待完成"));
			ui->Button_Start->hide();
			ui->Button_Stop->show();
			break;
		default:
			ui->Label_Task_Status->setText(tr("未知状态"));
			ui->Button_Start->hide();
			ui->Button_Stop->hide();
			break;
	}

	// 更新进度
	ui->Bar_Task_Progress->setValue((int)(taskShared()->downloadProgress * 100));
}



// [receive] 按钮 - 开始
void XLWindowProgressItem::receiveButtonStart() noexcept
{
}

// [receive] 按钮 - 停止
void XLWindowProgressItem::receiveButtonStop() noexcept
{
}
