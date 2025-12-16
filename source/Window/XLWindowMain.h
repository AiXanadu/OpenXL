#ifndef			_XL_WINDOW_MAIN_H_
#define			_XL_WINDOW_MAIN_H_

#include <source/XLWindowHeader.h>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XLWindowMain;
}
QT_END_NAMESPACE

// 主界面
struct PKWindowMain;
typedef struct PKWindowMain			PKWindowMain;
class XLWindowMain : public QWidget
{
Q_OBJECT

private:
	// 私有数据
	PKWindowMain*				d_ptr;

	// UI
	Ui::XLWindowMain*			ui;

public:
	// constructor
	explicit XLWindowMain(QWidget* _Parent) noexcept;

	// destructor
	~XLWindowMain() noexcept override;

protected:
	// [event] 大小
	void resizeEvent(QResizeEvent* _Event) noexcept override;

	// [event] 绘图
	void paintEvent(QPaintEvent* _Event) noexcept override;

public:
	// [handle] 处理 - 窗口切换
	virtual void handleWindowSwitch(XL_WINDOW_L1 _WL1) noexcept final;

public slots:
	// [receive] 按钮点击 - 下载中
	virtual void receiveButtonProgress() noexcept final;

	// [receive] 按钮点击 - 已完成
	virtual void receiveButtonSuccess() noexcept final;

	// [receive] 按钮点击 - 已删除
	virtual void receiveButtonDelete() noexcept final;
};


#endif
