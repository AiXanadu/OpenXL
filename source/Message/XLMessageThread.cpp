#include <source/Message/XLMessageThread.h>


// constructor
XLMessageThread::XLMessageThread(QObject* _Parent, const XL_TASK_SHARED& _TaskS, bool _Release) noexcept : QThread(_Parent), XLMessageCore(_TaskS)
{
	if (_Release)
	{
		QObject::connect(this, &QThread::finished, this, &QThread::deleteLater);
	}

	QObject::connect(this, &XLMessageThread::signalObserverMessage, this, &XLMessageThread::receiveObserverMessage, Qt::QueuedConnection);
}

// destructor
XLMessageThread::~XLMessageThread() noexcept
{
	QObject::disconnect(this, &XLMessageThread::signalObserverMessage, this, &XLMessageThread::receiveObserverMessage);
}



// 观察者接收消息
void XLMessageThread::Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	emit signalObserverMessage(_Message, _Param1, _Param2);
}

// [receive] 观察者消息
void XLMessageThread::receiveObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	observerMessageHandle(_Message, _Param1, _Param2);
}
