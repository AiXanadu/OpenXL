#ifndef			_XL_MESSAGE_OBSERVER_H_
#define			_XL_MESSAGE_OBSERVER_H_

#include <source/XLWindowHeader.h>


// 消息分发器 - 观察者模式 - 接口
class XLMessageObserverInterface
{
public:
	// Notify Message(_Message:消息类型)(_Param1:消息参数1)(_Param2:消息参数2)
	virtual void Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept = 0;
};
typedef std::set<XLMessageObserverInterface*>				XLMessageObserverInterfaceList;
typedef std::map<x_uint64_t, XLMessageObserverInterfaceList>		XLMessageObserverInterfaceArray;



// 消息分发器 - 观察者模式 - 处理
struct PKMessageObserverHandle;
typedef struct PKMessageObserverHandle		PKMessageObserverHandle;
class XLMessageObserverHandle
{
private:
	// 私有数据
	PKMessageObserverHandle*		d_ptr;

public:
	// 同步模式
	typedef enum SyncMode
	{
		// 同步模式 - 所有观察者处理完成才返回
		kFRAMEWORK_OBSERVER_SM_SYNC	= 0,

		// 异步模式 - 发送消息时立即返回
		kFRAMEWORK_OBSERVER_SM_ASYNC	= 1
	}SyncMode;

public:
	// constructor
	XLMessageObserverHandle() noexcept;

	// destructor
	virtual ~XLMessageObserverHandle() noexcept;

private:
	// [thread] 异步线程
	static void asyncThreadHandle(XLMessageObserverHandle* _Context) noexcept;

	// [opt] 异步主循环
	virtual void asyncMainLoop() noexcept final;

	// [opt] 异步处理数据
	virtual void asyncHandleMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept final;

	// [opt] 同步处理数据
	virtual void syncHandleMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept final;

public:
	// [opt] 创建一个观察者对象
	static XLMessageObserverHandle* create(SyncMode _SyncMode) noexcept;

	// [opt] 释放一个观察者对象
	static void release(XLMessageObserverHandle* _Context) noexcept;

public:
	// [opt] 添加观察者
	virtual void append(x_uint64_t _Message, XLMessageObserverInterface* _Example) noexcept final;

	// [opt] 移除观察者
	virtual void remove(x_uint64_t _Message, XLMessageObserverInterface* _Example) noexcept final;

	// [opt] 移除观察者
	virtual void remove(const std::set<x_uint64_t>& _MessageArray, XLMessageObserverInterface* _Example) noexcept final;

	// [opt] 发送信息
	virtual void send(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept final;
};

#endif
