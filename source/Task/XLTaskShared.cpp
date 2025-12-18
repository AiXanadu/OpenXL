#include <source/Task/XLTaskShared.h>



// constructor
XLTaskShared::XLTaskShared(XL_TASK_ID _TaskId) noexcept
{
	this->taskId = _TaskId;
}

// destructor
XLTaskShared::~XLTaskShared() noexcept = default;
