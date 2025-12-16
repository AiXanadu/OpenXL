#ifndef			_XL_WINDOW_HEADER_H_
#define			_XL_WINDOW_HEADER_H_

// C++
#include <set>
#include <map>

// QtCore
#include <QtCore/qglobal.h>
#include <QtCore>
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QCryptographicHash>
#include <QUuid>
#include <QDateTime>
#include <QVariant>
#include <QSettings>
#include <QStandardPaths>
#include <QProcess>
#include <QTextCodec>
#include <QList>
#include <QMargins>
#include <QTextCharFormat>
#include <QTextBlock>
#include <QEvent>
#include <QEasingCurve>
#include <QClipboard>
#include <QShortcut>

// QtGui
#include <QApplication>
#include <QStyleFactory>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QPixmap>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QtWidgets/QWidget>
#include <qsystemdetection.h>
#include <QRect>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QMovie>
#include <QScrollBar>
#include <QMenu>
#include <QProxyStyle>
#include <QStyleOption>
#include <QStyleOptionMenuItem>
#include <QPainter>
#include <QComboBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QTreeView>
#include <QFileIconProvider>
#include <QTemporaryFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextEdit>
#include <QGraphicsDropShadowEffect>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLayout>
#include <QFontDatabase>
#include <QLineEdit>
#include <QScreen>
#include <QStyledItemDelegate>
#include <QPainterPath>
#include <QStylePainter>
#include <QToolTip>
#include <QRadioButton>
#include <QSpinBox>

#include <QMap>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QContextMenuEvent>
#include <QWheelEvent>

#include <QMovie>
#include <QMimeData>
#include <QFileIconProvider>
#include <QTemporaryFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <QPainterPath>
#include <QtSvg/QSvgRenderer>
#include <QScreen>

#include <QStyleFactory>
#include <QProxyStyle>
#include <QStyleOption>
#include <QStyleOptionMenuItem>
#include <QStyledItemDelegate>
#include <QStylePainter>
#include <QStandardItemModel>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>
#include <QTableWidget>
#include <QListWidget>
#include <QTreeView>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <qsystemdetection.h>
#include <QMenu>
#include <QFontComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QDrag>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include <QHeaderView>
#include <QRadioButton>
#include <QToolTip>
#include <QGuiApplication>
#include <QApplication>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

// Arch
#if defined(Q_OS_WIN32)
#include <Windows.h>
#endif



// 页面枚举 - 1级
typedef enum XL_WINDOW_L1
{
	// 下载中
	kXL_WL1_PROGRESS				= 0,

	// 已完成
	kXL_WL1_SUCCESS					= 1,

	// 已删除
	kXL_WL1_DELETE					= 2
}XL_WINDOW_L1;



#endif
