#ifndef			_XL_WINDOW_DELETE_H_
#define			_XL_WINDOW_DELETE_H_

#include <source/XLWindowHeader.h>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XLWindowDelete;
}
QT_END_NAMESPACE

// 界面 - 已删除
class XLWindowDelete : public QWidget
{
Q_OBJECT

private:
	// UI
	Ui::XLWindowDelete*			ui;

public:
	// constructor
	explicit XLWindowDelete(QWidget* _Parent) noexcept;

	// destructor
	~XLWindowDelete() noexcept override;
};

#endif
