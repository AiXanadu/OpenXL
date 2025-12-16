#include <source/Window/Delete/XLWindowDelete.h>
#include "ui_XLWindowDelete.h"



// constructor
XLWindowDelete::XLWindowDelete(QWidget* _Parent) noexcept : QWidget(_Parent), ui(new Ui::XLWindowDelete)
{
	ui->setupUi(this);
}

// destructor
XLWindowDelete::~XLWindowDelete() noexcept
{
	delete ui;
}
