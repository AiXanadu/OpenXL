#include <source/Message/XLMessageDialog.h>


// constructor
XLMessageDialog::XLMessageDialog(QWidget* _Parent, XL_TASK_ID _TaskId, bool _Release) noexcept : QDialog(_Parent), XLMessageCore(_TaskId)
{
	this->setAttribute(Qt::WA_DeleteOnClose, _Release);
	QObject::connect(this, &XLMessageDialog::signalObserverMessage, this, &XLMessageDialog::receiveObserverMessage, Qt::QueuedConnection);
}

// destructor
XLMessageDialog::~XLMessageDialog() noexcept
{
	QObject::disconnect(this, &XLMessageDialog::signalObserverMessage, this, &XLMessageDialog::receiveObserverMessage);
}



// [event] 大小
void XLMessageDialog::resizeEvent(QResizeEvent* _Event)
{
	this->coreWindowSkinUpdate();
	QDialog::resizeEvent(_Event);
}

// [event] 显示
void XLMessageDialog::showEvent(QShowEvent* _Event)
{
	this->coreWindowInitialize();
	setAttribute(Qt::WA_Mapped);
	QDialog::showEvent(_Event);
	emit signalWindowShow();
}

// [event] 隐藏
void XLMessageDialog::hideEvent(QHideEvent* _Event)
{
	QDialog::hideEvent(_Event);
	emit signalWindowHide();
}

// [event] 关闭
void XLMessageDialog::closeEvent(QCloseEvent* _Event)
{
	QDialog::closeEvent(_Event);
	emit signalWindowDestroy();
}



// 观察者接收消息
void XLMessageDialog::Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	emit signalObserverMessage(_Message, _Param1, _Param2);
}

// [receive] 观察者消息
void XLMessageDialog::receiveObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	observerMessageHandle(_Message, _Param1, _Param2);
}
