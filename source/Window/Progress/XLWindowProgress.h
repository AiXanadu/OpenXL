#ifndef			_XL_WINDOW_PROGRESS_H_
#define			_XL_WINDOW_PROGRESS_H_

#include <source/XLWindowHeader.h>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XLWindowProgress;
}
QT_END_NAMESPACE

// 界面 - 下载中
class XLWindowProgress : public QWidget
{
Q_OBJECT

private:
	// UI
	Ui::XLWindowProgress*			ui;

public:
	// constructor
	explicit XLWindowProgress(QWidget* _Parent) noexcept;

	// destructor
	~XLWindowProgress() noexcept override;
};

#endif
