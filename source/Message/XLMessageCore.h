#ifndef			_XL_MESSAGE_CORE_H_
#define			_XL_MESSAGE_CORE_H_

#include <source/XLWindowHeader.h>
#include <source/Task/XLTaskManager.h>
#include <source/Message/XLMessageDefine.h>
#include <source/Message/XLMessageObserver.h>


// 消息分发器 - 核心
struct PKMessageCore;
typedef struct PKMessageCore			PKMessageCore;
class XLMessageCore : public XLMessageObserverInterface
{
private:
	// 私有数据
	PKMessageCore*				d_ptr;

public:
	// constructor
	explicit XLMessageCore(const XL_TASK_SHARED& _TaskS) noexcept;

	// destructor
	virtual ~XLMessageCore() noexcept;

public:
	// [get] 任务ID
	virtual XL_TASK_ID taskId() const noexcept final;

	// [set] 任务对象
	virtual void taskShared(const XL_TASK_SHARED& _TaskS) noexcept final;

	// [get] 任务对象
	virtual const XL_TASK_SHARED& taskShared() const noexcept final;

protected:
	// [get] 判断窗口是否初始化
	virtual bool isWindowInitialize() const noexcept final;

	// [opt] 单次窗口初始化
	virtual void coreWindowInitialize() noexcept final;

	// [opt] 单次主题更新
	virtual void coreWindowSkinUpdate() noexcept final;

public:
	// [opt] 观察者界面模型句柄
	static XLMessageObserverHandle* observerMainHandle() noexcept;

	// [opt] 通知添加
	virtual void observerListenAppend(x_uint64_t _Message) noexcept final;

	// [opt] 通知移除
	virtual void observerListenRemove(x_uint64_t _Message) noexcept final;

	// [opt] 消息发送
	static void observerMessageSend(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept;

	// [opt] 消息处理
	virtual void observerMessageHandle(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept final;

public:
	// [opt] 更新窗口
	virtual void windowUpdate() noexcept;

	// [opt] 窗口初始化
	virtual void windowInitialize() noexcept;

public:
	// [msg] 主题更新
	virtual void messageSoftwareSkin() noexcept;

	// [msg] 语言切换
	virtual void messageSoftwareLanguage() noexcept;

	// [msg] 窗口显示
	virtual void messageSoftwareShow() noexcept;

	// [msg] 窗口隐藏
	virtual void messageSoftwareHide() noexcept;

	// [msg] 窗口最小化
	virtual void messageSoftwareMinimize() noexcept;

	// [msg] 窗口还原
	virtual void messageSoftwareRestore() noexcept;

	// [msg] 窗口最大化
	virtual void messageSoftwareMaximize() noexcept;

	// [msg] 窗口销毁
	virtual void messageSoftwareDestroy() noexcept;

public:
	// [msg] 页面切换
	virtual void messageWindowSwitch_1(x_uint64_t _Level_1) noexcept;

public:
	// [msg] 帐号登录
	virtual void messageUserLogin() noexcept;

	// [msg] 帐号切换
	virtual void messageUserSwitch() noexcept;

	// [msg] 帐号退出
	virtual void messageUserExit() noexcept;

public:
	// [msg] 任务更新
	virtual void messageTaskUpdate() noexcept;
};

#endif
