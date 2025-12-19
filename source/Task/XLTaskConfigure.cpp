#include <source/Task/XLTaskConfigure.h>



// constructor
XLTaskConfigure::XLTaskConfigure() noexcept = default;

// destructor
XLTaskConfigure::~XLTaskConfigure() noexcept = default;



// [opt] 实例
const XL_TASK_CFG& XLTaskConfigure::example() noexcept
{
	static auto	static_object_example = std::make_shared<XLTaskConfigure>();
	return static_object_example;
}



// [get] 获取一个可用ID
XL_TASK_ID XLTaskConfigure::findUsableId() const noexcept
{
	return XL_INVALID_ID;
}
