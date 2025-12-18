#ifndef			_XL_MESSAGE_DEFINE_H_
#define			_XL_MESSAGE_DEFINE_H_

#include <source/XLWindowHeader.h>



// 参数
#define	XLM_PARAM(_Value)						((x_uint64_t)(_Value))
#define	XLM_NULL							0x00000000UL



// [msg] 应用程序
#define	XLM_SOFTWARE_SKIN						0x01010000UL		// 主题更新
#define	XLM_SOFTWARE_LANGUAGE						0x01020000UL		// 语言切换
#define XLM_SOFTWARE_SHOW						0x01030000UL		// 窗口显示
#define XLM_SOFTWARE_HIDE						0x01040000UL		// 窗口隐藏
#define XLM_SOFTWARE_MINIMIZE						0x01050000UL		// 窗口最小化
#define XLM_SOFTWARE_RESTORE						0x01060000UL		// 窗口还原
#define XLM_SOFTWARE_MAXIMIZE						0x01070000UL		// 窗口最大化
#define XLM_SOFTWARE_DESTROY						0x01080000UL		// 窗口销毁



// [msg] 窗口消息
#define XLM_WINDOW_SWITCH_LEVEL_1					0x02010000UL		// 窗口切换:级别1



// [msg] 帐号消息
#define XLM_USER_LOGIN							0x03010000UL		// 帐号登录
#define XLM_USER_SWITCH							0x03030000UL		// 帐号切换
#define XLM_USER_EXIT							0x03040000UL		// 帐号退出



// [msg] 任务消息
#define XLM_TASK_UPDATE							0x04010000UL		// 任务更新



#endif
