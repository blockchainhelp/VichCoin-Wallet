#ifndef RPCCONSOLE_H
#define RPCCONSOLE_H

#include "guiutil.h"
#include "peertablemodel.h"
#include "net.h"

#include <QWidget>
#include <QDialog>
#include <QCompleter>

namespace Ui {
    class RPCConsole;
}
class ClientModel;

/** Local pwrcoin RPC console. */
class RPCConsole: public QWidget
{
    Q_OBJECT

public:
    explicit RPCConsole(QWidget *parent = 0);
    ~RPCConsole();

    void setClientModel(ClientModel *model);

    enum MessageClass {
        MC_ERROR,
        MC_DEBUG,
        CMD_REQUEST,
        CMD_REPLY,
        CMD_ERROR
    };

protected:
    virtual bool eventFilter(QObject* obj, QEvent *event);
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_lineEdit_returnPressed();
    void on_tabWidget_currentChanged(int index);
    /** open the debug.log from the current datadir */
    void on_openDebugLogfileButton_clicked();
    /** display messagebox with program parameters (same as pwrcoin-qt --help) */
    void on_showCLOptionsButton_clicked();
     /** change the time range of the network traffic graph */
    void on_sldGraphRange_valueChanged(int value);
    /** update traffic statistics */
    void updateTrafficStats(quint64 totalBytesIn, quint64 totalBytesOut);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

public slots:
    void clear();
    void message(int category, const QString &message, bool html = false);
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count, int countOfPeers);
    /** Go forward or back in history */
    void browseHistory(int offset);
    /** Scroll console view to end */
    void scrollToEnd();
    /** Switch to info tab and show */
    void showInfo();
    /** Switch to console tab and show */
    void showConsole();
    /** Switch to network tab and show */
    void showNetwork();
    /** Switch to peers tab and show */
    void showPeers();
    /** Open external (default) editor with npw.conf */
    void showConfEditor();
    /** Handle selection of peer in peers list */
    void peerSelected(const QItemSelection &selected, const QItemSelection &deselected);
    /** Handle updated peer information */
    void peerLayoutChanged();
signals:
    // For RPC command executor
    void stopExecutor();
    void cmdRequest(const QString &command);

private:
    static QString FormatBytes(quint64 bytes);
    void setTrafficGraphRange(int mins);
    /** show detailed information on ui about selected node */
    void updateNodeDetail(const CNodeCombinedStats *stats);

    enum ColumnWidths
    {
        ADDRESS_COLUMN_WIDTH = 200,
        SUBVERSION_COLUMN_WIDTH = 100,
    };

    Ui::RPCConsole *ui;
    ClientModel *clientModel;
    QStringList history;
    int historyPtr;
    QCompleter *autoCompleter;
    NodeId cachedNodeid;

    void startExecutor();
};

#endif // RPCCONSOLE_H
