#ifndef			_XL_WINDOW_SUCCESS_H_
#define			_XL_WINDOW_SUCCESS_H_

#include <source/XLWindowHeader.h>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XLWindowSuccess;
}
QT_END_NAMESPACE

// 界面 - 已完成
class XLWindowSuccess : public QWidget
{
Q_OBJECT

private:
	// UI
	Ui::XLWindowSuccess*			ui;

public:
	// constructor
	explicit XLWindowSuccess(QWidget* _Parent) noexcept;

	// destructor
	~XLWindowSuccess() noexcept override;
};

#endif
