#include <source/Task/XLTaskManager.h>
#include <source/Task/XLTaskConfigure.h>
#include <source/Task/XLTaskHandle.h>



// 任务 - 管理器
struct PKTaskManager
{
	// 任务列表
	std::map<XL_TASK_ID, XL_TASK_HANDLE>		taskArray;

	// 任务互斥量
	std::mutex					taskMutex;
};



// constructor
XLTaskManager::XLTaskManager() noexcept
{
	d_ptr = new(std::nothrow) PKTaskManager();
}

// destructor
XLTaskManager::~XLTaskManager() noexcept
{
	delete d_ptr;
}



// [opt] 实例
const XL_TASK_MANAGER& XLTaskManager::example() noexcept
{
	static auto	static_object_example = std::make_shared<XLTaskManager>();
	return static_object_example;
}



// [opt] 任务删除
static void XLTaskManagerRemove(const XL_TASK_HANDLE& _TaskHandle) noexcept
{
	Q_UNUSED(_TaskHandle);
}

// [opt] 任务创建
XL_TASK_ID XLTaskManager::create(const QString& _FileUri, const QString& _FileDir, const QString& _FileName) noexcept
{
	// 创建任务对象
	auto		vTaskHandle = std::make_shared<XLTaskHandle>();
	if(nullptr == vTaskHandle)
	{
		return XL_INVALID_ID;
	}
	auto		vTaskID = XLTaskConfigure::example()->findUsableId();
	if(XL_INVALID_ID == vTaskID)
	{
		return XL_INVALID_ID;
	}
	vTaskHandle->taskShared->taskId = vTaskID;
	vTaskHandle->taskShared->fileUri = _FileUri;
	vTaskHandle->taskShared->fileDir = _FileDir;
	vTaskHandle->taskShared->fileName = _FileName;

	// 插入到列表中
	XL_MUTEX_LOCKER(d_ptr->taskMutex);
	auto		vIterator = d_ptr->taskArray.find(vTaskID);
	if(vIterator != d_ptr->taskArray.end())
	{
		return XL_INVALID_ID;
	}
	d_ptr->taskArray[vTaskID] = vTaskHandle;
	return vTaskID;
}

// [opt] 任务删除
bool XLTaskManager::remove(XL_TASK_ID _TaskId) noexcept
{
	if(XL_INVALID_ID == _TaskId)
	{
		return false;
	}

	XL_MUTEX_LOCKER(d_ptr->taskMutex);

	auto		vIterator = d_ptr->taskArray.find(_TaskId);
	if(vIterator == d_ptr->taskArray.end())
	{
		return false;
	}
	std::thread(XLTaskManagerRemove, vIterator->second).detach();
	d_ptr->taskArray.erase(vIterator);
	return true;
}

// [opt] 任务是否存在
bool XLTaskManager::exist(XL_TASK_ID _TaskId) noexcept
{
	XL_MUTEX_LOCKER(d_ptr->taskMutex);

	auto		vIterator = d_ptr->taskArray.find(_TaskId);
	return vIterator != d_ptr->taskArray.end();
}

// [opt] 任务是否存在
bool XLTaskManager::exist(const QString& _FileUri) noexcept
{
	XL_MUTEX_LOCKER(d_ptr->taskMutex);

	for(const auto & vIterator : d_ptr->taskArray)
	{
		if(vIterator.second->taskShared->fileUri == _FileUri)
		{
			return true;
		}
	}
	return false;
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
