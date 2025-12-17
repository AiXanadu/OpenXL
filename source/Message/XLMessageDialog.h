#ifndef			_XL_MESSAGE_DIALOG_H_
#define			_XL_MESSAGE_DIALOG_H_

#include <source/Message/XLMessageCore.h>


// 消息框架: 对话框
class XLMessageDialog : public QDialog, public XLMessageCore
{
	Q_OBJECT

public:
	// constructor
	XLMessageDialog(QWidget* _Parent, XL_TASK_ID _TaskId, bool _Release) noexcept;

	// destructor
	~XLMessageDialog() noexcept override;

protected:
	// [event] 大小
	void resizeEvent(QResizeEvent* _Event) override;

	// [event] 显示
	void showEvent(QShowEvent* _Event) override;

	// [event] 隐藏
	void hideEvent(QHideEvent* _Event) override;

	// [event] 关闭
	void closeEvent(QCloseEvent* _Event) override;

public:
	// 观察者接收消息
	void Notify_ObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept override;

signals:
	// [signal] 观察者消息
	void signalObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2);

public slots:
	// [receive] 观察者消息
	virtual void receiveObserverMessage(x_uint64_t _Message, x_uint64_t _Param1, x_uint64_t _Param2) noexcept final;

signals:
	// [signal] 窗口显示
	void signalWindowShow();

	// [signal] 窗口隐藏
	void signalWindowHide();

	// [signal] 窗口关闭
	void signalWindowDestroy();
};

#endif
