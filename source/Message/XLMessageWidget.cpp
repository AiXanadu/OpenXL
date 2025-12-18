#include <source/Message/XLMessageWidget.h>


// constructor
XLMessageWidget::XLMessageWidget(QWidget* _Parent, const XL_TASK_SHARED& _TaskS, bool _Release) noexcept : QWidget(_Parent), XLMessageCore(_TaskS)
{
	this->setAttribute(Qt::WA_DeleteOnClose, _Release);
	this->setMouseTracking(true);
	QObject::connect(this, &XLMessageWidget::signalObserverMessage, this, &XLMessageWidget::receiveObserverMessage, Qt::QueuedConnection);
}

// destructor
XLMessageWidget::~XLMessageWidget() noexcept
{
	QObject::disconnect(this, &XLMessageWidget::signalObserverMessage, this, &XLMessageWidget::receiveObserverMessage);
}



// [event] 大小
void XLMessageWidget::resizeEvent(QResizeEvent* _Event)
{
	this->coreWindowSkinUpdate();
	QWidget::resizeEvent(_Event);
}

// [event] 显示
void XLMessageWidget::showEvent(QShowEvent* _Event)
{
	this->coreWindowInitialize();
	setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(_Event);
	emit signalWindowShow();
}

// [event] 隐藏
void XLMessageWidget::hideEvent(QHideEvent* _Event)
{
	QWidget::hideEvent(_Event);
	emit signalWindowHide();
}

// [event] 关闭
void XLMessageWidget::closeEvent(QCloseEvent* _Event)
{
	QWidget::closeEvent(_Event);
	emit signalWindowDestroy();
}



// 观察者接收消息
void XLMessageWidget::Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	emit signalObserverMessage(_Message, _Param1, _Param2);
}

// [receive] 观察者消息
void XLMessageWidget::receiveObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	observerMessageHandle(_Message, _Param1, _Param2);
}
