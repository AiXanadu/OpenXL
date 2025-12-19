#ifndef			_XL_TASK_CONFIGURE_H_
#define			_XL_TASK_CONFIGURE_H_

#include <source/XLWindowHeader.h>


// 下载任务 - 配置
struct PKTaskConfigure;
typedef struct PKTaskConfigure			PKTaskConfigure;
class XLTaskConfigure;
typedef std::shared_ptr<XLTaskConfigure>	XL_TASK_CFG;
class XLTaskConfigure
{
public:
	// constructor
	XLTaskConfigure() noexcept;

	// destructor
	virtual ~XLTaskConfigure() noexcept;

public:
	// [opt] 实例
	static const XL_TASK_CFG& example() noexcept;

public:
	// [get] 获取一个可用ID
	virtual XL_TASK_ID findUsableId() const noexcept final;
};

#endif
