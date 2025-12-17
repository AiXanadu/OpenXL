#ifndef			_XL_MESSAGE_THREAD_H_
#define			_XL_MESSAGE_THREAD_H_

#include <source/Message/XLMessageCore.h>


// 消息 - 线程
class XLMessageThread : public QThread, public XLMessageCore
{
Q_OBJECT

public:
	// constructor
	XLMessageThread(QObject* _Parent, XL_TASK_ID _TaskId, bool _Release) noexcept;

	// destructor
	~XLMessageThread() noexcept override;

public:
	// 观察者接收消息
	void Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept override;

signals:
	// [signal] 观察者消息
	void signalObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2);

public slots:
	// [receive] 观察者消息
	virtual void receiveObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept final;
};

#endif
