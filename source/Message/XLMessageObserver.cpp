#include <source/Message/XLMessageObserver.h>



// 框架 - 观察者模式 - 参数
typedef struct XLMessageObserverArg
{
	x_uint64_t				type = 0;
	x_uint64_t				param1 = 0;
	x_uint64_t				param2 = 0;
}XLMessageObserverArg;

// 框架 - 观察者模式 - 私有数据
struct PKMessageObserverHandle
{
	// 同步模式
	XLMessageObserverHandle::SyncMode	syncMode = XLMessageObserverHandle::kFRAMEWORK_OBSERVER_SM_SYNC;

	// 是否允许运行
	bool					isAllow = false;

	// 是否运行中
	bool					isRunning = false;

	// 观察者 - 互斥锁
	std::mutex				observerMutex;

	// 观察者 - 列表
	XLMessageObserverInterfaceArray		observerArray;

	// 消息 - 锁
	std::mutex				messageMutex;

	// 消息 - 队列
	std::list<XLMessageObserverArg*>	messageArray;
};

// constructor
XLMessageObserverHandle::XLMessageObserverHandle() noexcept
{
	d_ptr = new(std::nothrow) PKMessageObserverHandle();
}

// destructor
XLMessageObserverHandle::~XLMessageObserverHandle() noexcept
{
	delete d_ptr;
}



// [thread] 异步线程
void XLMessageObserverHandle::asyncThreadHandle(XLMessageObserverHandle* _Context) noexcept
{
	_Context->asyncMainLoop();
}

// [opt] 异步主循环
void XLMessageObserverHandle::asyncMainLoop() noexcept
{
	d_ptr->isRunning = true;
	while(d_ptr->isAllow)
	{
		if(!d_ptr->messageArray.empty())
		{
			// 取出第一位消息参数
			d_ptr->messageMutex.lock();
			auto		vIteratorM = d_ptr->messageArray.begin();
			auto		vMessageArg = (*vIteratorM);
			d_ptr->messageArray.erase(vIteratorM);
			d_ptr->messageMutex.unlock();

			// 同步处理消息
			syncHandleMessage(vMessageArg->type, vMessageArg->param1, vMessageArg->param2);

			// 释放内存
			delete vMessageArg;
		}
		x_posix_msleep(1);
	}
	d_ptr->isRunning = false;
}

// [static] 异步处理数据
void XLMessageObserverHandle::asyncHandleMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	// 创建消息参数
	auto		vMessageArg = new(std::nothrow) XLMessageObserverArg();
	if(nullptr == vMessageArg)
	{
		return;
	}
	vMessageArg->type = _Message;
	vMessageArg->param1 = _Param1;
	vMessageArg->param2 = _Param2;

	// 加入到队列
	d_ptr->messageMutex.lock();
	d_ptr->messageArray.push_back(vMessageArg);
	d_ptr->messageMutex.unlock();
}

// [static] 同步处理数据
void XLMessageObserverHandle::syncHandleMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	XL_MUTEX_LOCKER(d_ptr->observerMutex);

	auto		vIteratorA = d_ptr->observerArray.find(_Message);
	if (vIteratorA == d_ptr->observerArray.end())
	{
		return;
	}
	for(auto & vIteratorI : vIteratorA->second)
	{
		vIteratorI->Notify_ObserverMessage(_Message, _Param1, _Param2);
	}
}



// [opt] 创建一个观察者对象
XLMessageObserverHandle* XLMessageObserverHandle::create(SyncMode _SyncMode) noexcept
{
	auto		vContext = new(std::nothrow) XLMessageObserverHandle();
	if(vContext)
	{
		vContext->d_ptr->syncMode = _SyncMode;
		if(kFRAMEWORK_OBSERVER_SM_ASYNC == _SyncMode)
		{
			vContext->d_ptr->isAllow = true;
			std::thread(XLMessageObserverHandle::asyncThreadHandle, vContext).detach();
		}
	}
	return vContext;
}

// [opt] 释放一个观察者对象
void XLMessageObserverHandle::release(XLMessageObserverHandle* _Context) noexcept
{
	_Context->d_ptr->isAllow = false;
	while(_Context->d_ptr->isRunning)
	{
		x_posix_msleep(1);
	}
	delete _Context;
}



// [opt] 添加观察者
void XLMessageObserverHandle::append(x_uint64_t _Message, XLMessageObserverInterface* _Example) noexcept
{
	XL_MUTEX_LOCKER(d_ptr->observerMutex);

	// 检查是否存在此消息的观察者列表
	auto		vIteratorA = d_ptr->observerArray.find(_Message);
	if(vIteratorA == d_ptr->observerArray.end())
	{
		d_ptr->observerArray.emplace(_Message, XLMessageObserverInterfaceList());
		vIteratorA = d_ptr->observerArray.find(_Message);
	}
	if(vIteratorA == d_ptr->observerArray.end())
	{
		return;
	}

	// 在观察者列表中插入一项
	auto		vIteratorI = vIteratorA->second.find(_Example);
	if(vIteratorI == vIteratorA->second.end())
	{
		vIteratorA->second.insert(_Example);
	}
}

// [opt] 移除观察者
void XLMessageObserverHandle::remove(x_uint64_t _Message, XLMessageObserverInterface* _Example) noexcept
{
	XL_MUTEX_LOCKER(d_ptr->observerMutex);

	// 检查是否存在此消息的观察者列表
	auto		vIteratorA = d_ptr->observerArray.find(_Message);
	if(vIteratorA == d_ptr->observerArray.end())
	{
		return;
	}

	// 在观察者列表中移除指定项
	auto		vIteratorI = vIteratorA->second.find(_Example);
	if(vIteratorI != vIteratorA->second.end())
	{
		vIteratorA->second.erase(vIteratorI);
	}
}

// [opt] 移除观察者
void XLMessageObserverHandle::remove(const std::set<x_uint64_t>& _MessageArray, XLMessageObserverInterface* _Example) noexcept
{
	if(_MessageArray.empty())
	{
		return;
	}

	XL_MUTEX_LOCKER(d_ptr->observerMutex);

	// 循环移除
	for(const auto & vIteratorM : _MessageArray)
	{
		// 检查是否存在此消息的观察者列表
		auto		vIteratorA = d_ptr->observerArray.find(vIteratorM);
		if(vIteratorA == d_ptr->observerArray.end())
		{
			continue;
		}

		// 在观察者列表中移除指定项
		auto		vIteratorI = vIteratorA->second.find(_Example);
		if(vIteratorI != vIteratorA->second.end())
		{
			vIteratorA->second.erase(vIteratorI);
		}
	}
}

// [opt] 发送信息
void XLMessageObserverHandle::send(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	switch(d_ptr->syncMode)
	{
		case kFRAMEWORK_OBSERVER_SM_SYNC:
			syncHandleMessage(_Message, _Param1, _Param2);
			break;
		case kFRAMEWORK_OBSERVER_SM_ASYNC:
			asyncHandleMessage(_Message, _Param1, _Param2);
			break;
		default:
			break;
	}
}
