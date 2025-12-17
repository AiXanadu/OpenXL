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
	XLWindowProgressItem(QWidget* _Parent, XL_TASK_ID _TaskId, bool _Release) noexcept;

	// destructor
	~XLWindowProgressItem() noexcept override;
};

#endif
