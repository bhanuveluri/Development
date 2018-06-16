#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <QTreeWidgetItem>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QToolButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCheckBox>

#define PHYSICAL_PROPERTIES "Physical Properties"
#define MATERIAL_PROPERTIES "Material Properties"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddRoot(int column, QString name);

    void AddChild(QTreeWidgetItem* item , int column, QString name);

private:
    Ui::MainWindow *ui;
    QTreeWidget* tree_widget_;
    bool is_hide_;
};

#endif // MAINWINDOW_H
