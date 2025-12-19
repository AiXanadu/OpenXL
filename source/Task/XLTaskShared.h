#ifndef			_XL_TASK_SHARED_H_
#define			_XL_TASK_SHARED_H_

#include <source/XLWindowHeader.h>


// 任务对象 - 下载状态
typedef enum XL_DOWNLOAD_STATUS
{
	// 无对象
	kXL_DS_NONE				= 0,

	// 错误
	kXL_DS_ERROR				= 1,

	// 已暂停
	kXL_DS_PAUSE				= 2,

	// 下载中
	kXL_DS_DOWNLOAD				= 3,

	// 已完成
	kXL_DS_COMPLETE				= 4,

	// 等待开始
	kXL_DS_WAIT_START			= 5,

	// 等待停止
	kXL_DS_WAIT_STOP			= 6,

	// 已删除
	kXL_DS_DELETE				= 7,
}XL_DOWNLOAD_STATUS;

// 任务对象 - 共享对象
class XLTaskShared;
typedef std::shared_ptr<XLTaskShared>		XL_TASK_SHARED;
class XLTaskShared
{
public:
	// 任务ID
	XL_TASK_ID				taskId = 0;

	// 任务状态
	XL_DOWNLOAD_STATUS			taskStatus = kXL_DS_NONE;

	// 下载进度
	double 					downloadProgress = 0.0f;

	// 文件URL
	QString					fileUri;

	// 文件目录
	QString					fileDir;

	// 文件名称
	QString					fileName;

	// 文件大小
	quint64 				fileSize = 0;

public:
	// constructor
	explicit XLTaskShared(XL_TASK_ID _TaskId) noexcept;

	// destructor
	virtual ~XLTaskShared() noexcept;
};

#endif
