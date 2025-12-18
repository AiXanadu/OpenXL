#include <source/Task/XLTaskManager.h>



// [opt] 任务是否存在
bool XLTaskManager::exist(XL_TASK_ID _TaskId) noexcept
{
	return 0 != _TaskId;
}

// [opt] 任务是否存在
bool XLTaskManager::exist(const XL_TASK_SHARED& _TaskS) noexcept
{
	if(nullptr == _TaskS)
	{
		return false;
	}
	return XLTaskManager::exist(_TaskS->taskId);
}
