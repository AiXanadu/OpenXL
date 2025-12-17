#include <source/Window/Progress/XLWindowProgressItem.h>
#include "ui_XLWindowProgressItem.h"



// constructor
XLWindowProgressItem::XLWindowProgressItem(QWidget* _Parent, XL_TASK_ID _TaskId, bool _Release) noexcept : XLMessageWidget(_Parent, _TaskId, _Release), ui(new Ui::XLWindowProgressItem)
{
	ui->setupUi(this);
}

// destructor
XLWindowProgressItem::~XLWindowProgressItem() noexcept
{
	delete ui;
}
