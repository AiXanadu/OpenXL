#include <source/Message/XLMessageFrame.h>


// constructor
XLMessageFrame::XLMessageFrame(QWidget* _Parent, const XL_TASK_SHARED& _TaskS, bool _Release) noexcept : QFrame(_Parent), XLMessageCore(_TaskS)
{
	this->setAttribute(Qt::WA_DeleteOnClose, _Release);
	QObject::connect(this, &XLMessageFrame::signalObserverMessage, this, &XLMessageFrame::receiveObserverMessage, Qt::QueuedConnection);
}

// destructor
XLMessageFrame::~XLMessageFrame() noexcept
{
	QObject::disconnect(this, &XLMessageFrame::signalObserverMessage, this, &XLMessageFrame::receiveObserverMessage);
}



// [event] 大小
void XLMessageFrame::resizeEvent(QResizeEvent* _Event)
{
	this->coreWindowSkinUpdate();
	QFrame::resizeEvent(_Event);
}

// [event] 显示
void XLMessageFrame::showEvent(QShowEvent* _Event)
{
	this->coreWindowInitialize();
	setAttribute(Qt::WA_Mapped);
	QFrame::showEvent(_Event);
	emit signalWindowShow();
}

// [event] 隐藏
void XLMessageFrame::hideEvent(QHideEvent* _Event)
{
	QFrame::hideEvent(_Event);
	emit signalWindowHide();
}

// [event] 关闭
void XLMessageFrame::closeEvent(QCloseEvent* _Event)
{
	QFrame::closeEvent(_Event);
	emit signalWindowDestroy();
}



// 观察者接收消息
void XLMessageFrame::Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	emit signalObserverMessage(_Message, _Param1, _Param2);
}

// [receive] 观察者消息
void XLMessageFrame::receiveObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	observerMessageHandle(_Message, _Param1, _Param2);
}
