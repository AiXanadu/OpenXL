#include <source/Task/XLTaskStream.h>



// 任务 - 共享流
struct PKTaskStream
{
	// 文件对象
	QFile						file;

	// 文件锁
	std::mutex					mutex;
};



// constructor
XLTaskStream::XLTaskStream() noexcept
{
	d_ptr = new(std::nothrow) PKTaskStream();
}

// destructor
XLTaskStream::~XLTaskStream() noexcept
{
	close();
	delete d_ptr;
}



// [opt] 打开文件
bool XLTaskStream::open(const QString& _FilePath, x_uint64_t _FileSize) noexcept
{
	XL_MUTEX_LOCKER(d_ptr->mutex);

	d_ptr->file.setFileName(_FilePath);
	if(!d_ptr->file.open(QIODevice::ReadWrite))
	{
		return false;
	}

	if (!d_ptr->file.resize((qint64)_FileSize))
	{
		d_ptr->file.close();
		return false;
	}
	return true;
}

// [opt] 关闭文件
bool XLTaskStream::close() noexcept
{
	XL_MUTEX_LOCKER(d_ptr->mutex);

	if(d_ptr->file.isOpen())
	{
		d_ptr->file.flush();
		d_ptr->file.close();
		return true;
	}
	return false;
}

// [opt] 刷新数据
bool XLTaskStream::flush() noexcept
{
	XL_MUTEX_LOCKER(d_ptr->mutex);

	return d_ptr->file.flush();
}



// [opt] 写入
bool XLTaskStream::write(x_uint64_t _Pos, const void* _Data, x_uint64_t _Size) noexcept
{
	if(nullptr == _Data || 0 == _Size)
	{

	}

	XL_MUTEX_LOCKER(d_ptr->mutex);

	if(!d_ptr->file.seek((qint64)_Pos))
	{
		return false;
	}

	auto		vSyncI = d_ptr->file.write((const char*)_Data, _Size);
	if(vSyncI <= 0)
	{
		return false;
	}
	return (x_uint64_t)vSyncI == _Size;
}

// [opt] 写入
bool XLTaskStream::write(x_uint64_t _Pos, const QByteArray& _Data) noexcept
{
	return XLTaskStream::write(_Pos, _Data.data(), _Data.size());
}
