#include <source/Message/XLMessageCore.h>



// 消息 - 核心
struct PKMessageCore
{
	// 任务ID
	XL_TASK_ID					taskId = 0;

	// 监听通知列表
	std::set<x_uint64_t>				listenArray;

	// 窗口初始化状态
	bool						widgetInitialize = false;

	// 单次主题更新标记
	bool						skinUpdate = false;
};



// constructor
XLMessageCore::XLMessageCore(XL_TASK_ID _TaskId) noexcept
{
	d_ptr = new(std::nothrow) PKMessageCore();
	d_ptr->taskId = _TaskId;
}

// destructor
XLMessageCore::~XLMessageCore() noexcept
{
	observerMainHandle()->remove(d_ptr->listenArray, this);
	d_ptr->listenArray.clear();
	delete d_ptr;
}



// [set] 任务ID
void XLMessageCore::taskId(XL_TASK_ID _TaskId) noexcept
{
	d_ptr->taskId = _TaskId;
}

// [set] 任务ID
XL_TASK_ID XLMessageCore::taskId() const noexcept
{
	return d_ptr->taskId;
}



// [get] 判断窗口是否初始化
bool XLMessageCore::isWindowInitialize() const noexcept
{
	return d_ptr->widgetInitialize;
}

// [opt] 单次窗口初始化
void XLMessageCore::coreWindowInitialize() noexcept
{
	if(!d_ptr->widgetInitialize)
	{
		this->windowInitialize();
	}
	d_ptr->widgetInitialize = true;
}

// [opt] 单次主题更新
void XLMessageCore::coreWindowSkinUpdate() noexcept
{
	if(!d_ptr->skinUpdate)
	{
		this->messageSoftwareSkin();
	}
	d_ptr->skinUpdate = true;
}



// [opt] 观察者界面模型句柄
XLMessageObserverHandle* XLMessageCore::observerMainHandle() noexcept
{
	static auto 	static_object_example = XLMessageObserverHandle::create(XLMessageObserverHandle::kFRAMEWORK_OBSERVER_SM_SYNC);
	return static_object_example;
}

// [opt] 通知添加
void XLMessageCore::observerListenAppend(x_uint64_t _Message) noexcept
{
	d_ptr->listenArray.insert(_Message);
	observerMainHandle()->append(_Message, this);
}

// [opt] 通知移除
void XLMessageCore::observerListenRemove(x_uint64_t _Message) noexcept
{
	auto		vIterator = d_ptr->listenArray.find(_Message);
	if(vIterator != d_ptr->listenArray.end())
	{
		observerMainHandle()->remove(*vIterator, this);
		d_ptr->listenArray.erase(vIterator);
	}
}

// [opt] 消息发送
void XLMessageCore::observerMessageSend(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	observerMainHandle()->send(_Message, _Param1, _Param2);
}

// [opt] 消息处理
void XLMessageCore::observerMessageHandle(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept
{
	Q_UNUSED(_Param1);
	Q_UNUSED(_Param2);
	switch(_Message)
	{
		case XLM_SOFTWARE_SKIN:				messageSoftwareSkin();						break;
		case XLM_SOFTWARE_LANGUAGE:			messageSoftwareLanguage();					break;
		case XLM_SOFTWARE_SHOW:				messageSoftwareShow();						break;
		case XLM_SOFTWARE_HIDE:				messageSoftwareHide();						break;
		case XLM_SOFTWARE_MINIMIZE:			messageSoftwareMinimize();					break;
		case XLM_SOFTWARE_RESTORE:			messageSoftwareRestore();					break;
		case XLM_SOFTWARE_MAXIMIZE:			messageSoftwareMaximize();					break;
		case XLM_SOFTWARE_DESTROY:			messageSoftwareDestroy();					break;

		case XLM_WINDOW_SWITCH_LEVEL_1:			messageWindowSwitch_1(_Param2);					break;

		case XLM_USER_LOGIN:				messageUserLogin();						break;
		case XLM_USER_SWITCH:				messageUserSwitch();						break;
		case XLM_USER_EXIT:				messageUserExit();						break;

		default:													break;
	}
}



// [opt] 更新窗口
void XLMessageCore::windowUpdate() noexcept
{
}

// [opt] 窗口初始化
void XLMessageCore::windowInitialize() noexcept
{
}



// [case] 主题更新
void XLMessageCore::messageSoftwareSkin() noexcept
{
}

// [case] 语言切换
void XLMessageCore::messageSoftwareLanguage() noexcept
{
}

// [case] 窗口显示
void XLMessageCore::messageSoftwareShow() noexcept
{
}

// [case] 窗口隐藏
void XLMessageCore::messageSoftwareHide() noexcept
{
}

// [case] 窗口最小化
void XLMessageCore::messageSoftwareMinimize() noexcept
{
}

// [case] 窗口还原
void XLMessageCore::messageSoftwareRestore() noexcept
{
}

// [case] 窗口最大化
void XLMessageCore::messageSoftwareMaximize() noexcept
{
}

// [case] 窗口销毁
void XLMessageCore::messageSoftwareDestroy() noexcept
{
}



// [case] 页面切换
void XLMessageCore::messageWindowSwitch_1(x_uint64_t _Level_1) noexcept
{
	Q_UNUSED(_Level_1);
}



// [case] 帐号登录
void XLMessageCore::messageUserLogin() noexcept
{
}

// [case] 帐号切换
void XLMessageCore::messageUserSwitch() noexcept
{
}

// [case] 帐号退出
void XLMessageCore::messageUserExit() noexcept
{
}
