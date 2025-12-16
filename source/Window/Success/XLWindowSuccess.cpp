#include <source/Window/Success/XLWindowSuccess.h>
#include "ui_XLWindowSuccess.h"



// constructor
XLWindowSuccess::XLWindowSuccess(QWidget* _Parent) noexcept : QWidget(_Parent), ui(new Ui::XLWindowSuccess)
{
	ui->setupUi(this);
}

// destructor
XLWindowSuccess::~XLWindowSuccess() noexcept
{
	delete ui;
}
