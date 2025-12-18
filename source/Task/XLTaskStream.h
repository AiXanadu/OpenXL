#ifndef			_XL_TASK_STREAM_H_
#define			_XL_TASK_STREAM_H_

#include <source/XLWindowHeader.h>


// 任务 - 共享流
struct PKTaskStream;
typedef struct PKTaskStream			PKTaskStream;
class XLTaskStream;
typedef std::shared_ptr<XLTaskStream>		XL_TASK_STREAM;
class XLTaskStream
{
private:
	// UI
	PKTaskStream*				d_ptr;

public:
	// constructor
	XLTaskStream() noexcept;

	// destructor
	virtual ~XLTaskStream() noexcept;

public:
	// [opt] 打开文件
	virtual bool open(const QString& _FilePath, x_uint64_t _FileSize) noexcept final;

	// [opt] 关闭文件
	virtual bool close() noexcept final;

	// [opt] 刷新数据
	virtual bool flush() noexcept final;

public:
	// [opt] 写入
	virtual bool write(x_uint64_t _Pos, const void* _Data, x_uint64_t _Size) noexcept final;

	// [opt] 写入
	virtual bool write(x_uint64_t _Pos, const QByteArray& _Data) noexcept final;
};

#endif
