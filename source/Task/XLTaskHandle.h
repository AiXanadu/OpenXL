#ifndef			_XL_TASK_HANDLE_H_
#define			_XL_TASK_HANDLE_H_

#include <source/XLWindowHeader.h>
#include <source/Task/XLTaskShared.h>


// 下载任务 - 处理
struct PKTaskHandle;
typedef struct PKTaskHandle			PKTaskHandle;
class XLTaskHandle;
typedef std::shared_ptr<XLTaskHandle>		XL_TASK_HANDLE;
class XLTaskHandle
{
public:
	// 任务信息
	XL_TASK_SHARED				taskShared;

public:
	// constructor
	XLTaskHandle() noexcept;

	// destructor
	virtual ~XLTaskHandle() noexcept;
};

#endif
