#ifndef			_XL_TASK_MANAGER_H_
#define			_XL_TASK_MANAGER_H_

#include <source/Task/XLTaskShared.h>


// 任务 - 管理器
class XLTaskManager
{
public:
	// [opt] 任务是否存在
	static bool exist(XL_TASK_ID _TaskId) noexcept;

	// [opt] 任务是否存在
	static bool exist(const XL_TASK_SHARED& _TaskS) noexcept;
};

#endif
