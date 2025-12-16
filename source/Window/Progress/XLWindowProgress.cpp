#include <source/Window/Progress/XLWindowProgress.h>
#include "ui_XLWindowProgress.h"



// constructor
XLWindowProgress::XLWindowProgress(QWidget* _Parent) noexcept : QWidget(_Parent), ui(new Ui::XLWindowProgress)
{
	ui->setupUi(this);
}

// destructor
XLWindowProgress::~XLWindowProgress() noexcept
{
	delete ui;
}
