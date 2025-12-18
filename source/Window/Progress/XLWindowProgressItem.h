#ifndef			_XL_WINDOW_PROGRESS_ITEM_H_
#define			_XL_WINDOW_PROGRESS_ITEM_H_

#include <source/XLWindowHeader.h>
#include <source/Message/XLMessageWidget.h>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XLWindowProgressItem;
}
QT_END_NAMESPACE

// 界面 - 下载中 - 子项
class XLWindowProgressItem : public XLMessageWidget
{
Q_OBJECT

private:
	// UI
	Ui::XLWindowProgressItem*		ui;

public:
	// constructor
	XLWindowProgressItem(QWidget* _Parent, const XL_TASK_SHARED& _TaskS, bool _Release) noexcept;

	// destructor
	~XLWindowProgressItem() noexcept override;

public:
	// [msg] 任务更新
	void messageTaskUpdate() noexcept override;

public slots:
	// [receive] 按钮 - 开始
	virtual void receiveButtonStart() noexcept final;

	// [receive] 按钮 - 停止
	virtual void receiveButtonStop() noexcept final;
};

#endif
