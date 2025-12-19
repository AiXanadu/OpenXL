#ifndef			_XL_TASK_MANAGER_H_
#define			_XL_TASK_MANAGER_H_

#include <source/Task/XLTaskShared.h>


// 任务 - 管理器
struct PKTaskManager;
typedef struct PKTaskManager			PKTaskManager;
class XLTaskManager;
typedef std::shared_ptr<XLTaskManager>		XL_TASK_MANAGER;
class XLTaskManager
{
private:
	// 私有数据
	PKTaskManager*				d_ptr;

public:
	// constructor
	XLTaskManager() noexcept;

	// destructor
	virtual ~XLTaskManager() noexcept;

public:
	// [opt] 实例
	static const XL_TASK_MANAGER& example() noexcept;

public:
	// [opt] 任务创建
	virtual XL_TASK_ID create(const QString& _FileUri, const QString& _FileDir, const QString& _FileName) noexcept final;

	// [opt] 任务删除
	virtual bool remove(XL_TASK_ID _TaskId) noexcept final;

	// [opt] 任务是否存在
	virtual bool exist(XL_TASK_ID _TaskId) noexcept final;

	// [opt] 任务是否存在
	virtual bool exist(const QString& _FileUri) noexcept final;

	// [opt] 任务是否存在
	virtual bool exist(const XL_TASK_SHARED& _TaskS) noexcept final;
};

#endif
