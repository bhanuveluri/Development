#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedWidth(1000);

    is_hide_ = true;

    tree_widget_ = new QTreeWidget(this);
    tree_widget_->setColumnCount(2);
    tree_widget_->setHeaderHidden(false);
    //tree_widget_->header()->setStretchLastSection(true);
    tree_widget_->header()->setSectionResizeMode(QHeaderView::Stretch);
    tree_widget_->setAlternatingRowColors(true);

    QStringList header_labels;
    header_labels.push_back(tr("Property"));
    header_labels.push_back(tr("Value"));

    tree_widget_->setColumnCount(header_labels.count());
    tree_widget_->setHeaderLabels(header_labels);

    this->AddRoot(0,"Inputs");
    this->AddRoot(0,"Style Settings");
    this->AddRoot(0,"Sensor Parameters");
    this->AddRoot(0,"Area Parameters");
    this->AddRoot(0,"Combination Inputs");
    this->AddRoot(0,"Scout Parameter");
    this->AddRoot(0,"Outputs");


    this->setCentralWidget(tree_widget_);

    QMenuBar* m = new QMenuBar();


    QMenu* mm = new QMenu();
    mm->setTitle("File");
    mm->addAction(new QAction("New"));
    mm->addAction(new QAction("Open"));
    m->addMenu(mm);

    this->setMenuBar(m);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddRoot(int column, QString name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(column, name);
    tree_widget_->addTopLevelItem(item);
    //tree_widget_->setItemWidget(item, 0, new QLabel("Material Type"));
    //tree_widget_->setItemWidget(item, 1, new QLineEdit("0"));


    //tree_widget_->setItemWidget(item, column, new QLabel(name));
    //tree_widget_->setItemWidget(item, 1, new QLabel(""));

    if(name == "Inputs")
    {
        //item->setExpanded(!is_hide_);
        this->AddChild(item,0, "Desination");
        this->AddChild(item,0, "Plan type");
        this->AddChild(item,0, "Hide Style setting");
        //this->AddChild(item,0, "Style setting");
    }
    else if(name == "Sensor Parameters")
    {
        //item->setHidden(is_hide_);
        this->AddChild(item,0, "Sensor Type");
        this->AddChild(item,0, "Detection Distance");
        this->AddChild(item,0, "Spacing Factor");

    }
    else if(name == "Style Settings")
    {
        item->setExpanded(true);
        item->setHidden(is_hide_);
        this->AddChild(item,0, "Line Style");
        this->AddChild(item,0, "Line Width");
        this->AddChild(item,0, "Symbol Size");
        this->AddChild(item,0, "Line Colour");

    }
    else if(name == "Area Parameters")
    {
        QTableWidget* wdg = new QTableWidget();
        wdg->setColumnCount(2);
        wdg->setHorizontalHeaderLabels(QStringList() << "Latitude" << "Longitude");

        wdg->setRowCount(1);
        QLineEdit* edit1 = new QLineEdit("0");
        wdg->setCellWidget(0, 0, edit1);
        QLineEdit* edit2 = new QLineEdit("0");
        wdg->setCellWidget(0, 1, edit2);

        wdg->setRowCount(2);
        QLineEdit* edit3 = new QLineEdit("0");
        wdg->setCellWidget(1, 0, edit3);
        QLineEdit* edit4 = new QLineEdit("0");
        wdg->setCellWidget(1, 1, edit4);

        wdg->setRowCount(3);
        QLineEdit* edit5 = new QLineEdit("0");
        wdg->setCellWidget(2, 0, edit5);
        QLineEdit* edit6 = new QLineEdit("0");
        wdg->setCellWidget(2, 1, edit6);

        wdg->setRowCount(4);
        QLineEdit* edit7 = new QLineEdit("0");
        wdg->setCellWidget(3, 0, edit7);
        QLineEdit* edit8 = new QLineEdit("0");
        wdg->setCellWidget(3, 1, edit8);
        wdg->setContentsMargins(0, 0, 0, 0);


        QGridLayout* h_layout = new QGridLayout();

        h_layout->addWidget(wdg, 0,  1);

        h_layout->setMargin(0);
        h_layout->setSpacing(0);
        h_layout->setContentsMargins(0, 0, 0, 0);

        QCheckBox* check_box = new QCheckBox();
        //check_box->setText("Select With Mouse Clicked");

        QLabel* label = new QLabel("Select With Mouse Clicked");
        h_layout->addWidget(check_box, 1, 0);
        h_layout->addWidget(label, 1, 1);

        QWidget* widget = new QWidget();
        widget->setLayout(h_layout);

        tree_widget_->setItemWidget(item, 0, widget);

        //this->AddChild(item,0, "Select With Mouse Clicked");
    }
    else if(name == "Combination Inputs"){
        this->AddChild(item,0, "No of Sonobuoys");
        this->AddChild(item,0, "Length");
        this->AddChild(item,0, "Breadth");
        this->AddChild(item,0, "Area Corner");
        this->AddChild(item,0, "Orientation");
        this->AddChild(item,0, "Breadth left");
        this->AddChild(item,0, "Breadth Right");
    }
    else if(name == "Scout Parameter"){
        this->AddChild(item,0, "Scout Position");
        this->AddChild(item,0, "Remarks");

    }
    else if(name == "Outputs"){

        this->AddChild(item,0, "Length");
        this->AddChild(item,0, "Breadth");
        this->AddChild(item,0, "Area");
        this->AddChild(item,0, "Sonobuoys along Length");
        this->AddChild(item,0, "Sonobuoys along Breadth");
        this->AddChild(item,0, "No of Sonobuoys along length");
        this->AddChild(item,0, "No of Sonobuoys along Breath");
        this->AddChild(item,0, "No of Sonobuoys Required");
        this->AddChild(item,0, "No of Sonobuoys Left");
    }





}

void MainWindow::AddChild(QTreeWidgetItem *item, int column, QString name)
{
    QTreeWidgetItem* chld_item = new QTreeWidgetItem();
    chld_item->setText(column, name);
    item->addChild(chld_item);
    if(name == "Desination")
    {
        QLineEdit* line_edit = new QLineEdit("0");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);

    }

    if(name == "Hide Style setting")
    {
        chld_item->setCheckState(0, Qt::Checked);
        QPushButton *push_button = new QPushButton("set");
        tree_widget_->setItemWidget(chld_item,1,push_button);
        connect(push_button, &QPushButton::clicked, [this, name, item]()
        {
            qDebug() << "in Push button";
            for(int i = 0; i < tree_widget_->topLevelItemCount(); i++)
            {
                //for(int j = 0; j < tree_widget_->topLevelItem(i)->childCount(); j++)
                {
                    qDebug() << tree_widget_->topLevelItem(i)->text(0);
                    if(tree_widget_->topLevelItem(i)->text(0) == "Style Settings")
                    {
                        tree_widget_->topLevelItem(i)->setExpanded(true);
                        tree_widget_->topLevelItem(i)->setHidden(is_hide_);
                        is_hide_ = !is_hide_;
                    }
                }
            }
        });
    }
    if(name == "No of Sonobuoys")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "Length")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "Length")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "Breadth")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "Scout Position")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
        qDebug() << "in scout";
    }
    if(name == "Remarks")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
        qDebug() << "in scout";
    }
    if(name == "Area")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
        qDebug() << "in scout";
    }
    if(name == "Sonobuoys along Length")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
        // qDebug() << "in scout";
    }
    if(name == "Sonobuoys along Breadth")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
        //qDebug() << "in scout";
    }

    if(name == "No of Sonobuoys along length")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "No.of Sonobuoys along Length")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "No.of Sonobuoys along Breadth")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "No of Sonobuoys Required")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "No of Sonobuoys Left")
    {
        QLineEdit* line_edit = new QLineEdit("");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);
    }
    if(name == "Sensor Type")
    {
        QComboBox* combo_box = new QComboBox(this);
        combo_box->addItems(QStringList() <<"RGB1A");
        tree_widget_->setItemWidget(chld_item, 1, combo_box);
    }
    if(name == "Plan type")
    {
        QComboBox* combo_box = new QComboBox(this);
        combo_box->addItems(QStringList() <<"Air Plan 1"<<"Air Plan 2"<<"Air Plan 3"<<"Air Plan 5");
        tree_widget_->setItemWidget(chld_item, 1, combo_box);
    }

    if(name == "Detection Distance")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);

    }
    if(name == "Spacing Factor")
    {
        QLineEdit* line_edit = new QLineEdit("40");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);

    }
    if(name == "Area Corner")
    {
        QLineEdit* line_edit = new QLineEdit("00");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);

    }
    if(name == "Orientation")
    {
        QLineEdit* line_edit = new QLineEdit("45");
        tree_widget_->setItemWidget(chld_item, 1, line_edit);

    }
    if(name == "Style setting")
    {
        QPushButton* push_button = new QPushButton();
        push_button->setIcon(QIcon("E:\vinod\Photos"));
        push_button->setText("set");
        push_button->setFixedWidth(1);
        tree_widget_->setItemWidget(chld_item, 1, push_button);


    }


    else
    {
        QLineEdit* line_edit = new QLineEdit("0");

        if(name == "Style setting")
        {
            QPushButton* push_button = new QPushButton();
            push_button->setIcon(QIcon("E:\vinod\Photos"));
            push_button->setText("set");
            push_button->setFixedWidth(1);
            tree_widget_->setItemWidget(chld_item, 1, push_button);

            connect(push_button, &QPushButton::clicked, [this, name, item]()
            {
                for(int i = 0; i < tree_widget_->topLevelItemCount(); i++)
                {
                    for(int j = 0; j < tree_widget_->topLevelItem(i)->childCount(); j++)
                    {
                        if(tree_widget_->topLevelItem(i)->child(j)->text(0) == "Style setting")
                        {
                            tree_widget_->topLevelItem(i)->setHidden(is_hide_);
                            is_hide_ = !is_hide_;
                        }
                    }
                }
            });

            //            QHBoxLayout *hLayout = new QHBoxLayout();
            //            hLayout->addWidget(line_edit);
            //            hLayout->addWidget(buttn);

            //            hLayout->setSpacing(0);
            //            hLayout->setMargin(0);
            //            hLayout->setContentsMargins(0,0,0,0);

            //            QWidget *dual_push_buttons = new QWidget();
            //            dual_push_buttons->setFixedHeight(50);
            //            dual_push_buttons->setLayout(hLayout);
            //            dual_push_buttons->setContentsMargins(0, 0, 0, 0);


            //            tree_widget_->setItemWidget(chld_item, 1, dual_push_buttons);
            //            return;
            //        }
            //        if(name == "Velocity")
            //        {
            //            QLineEdit* line_edit2 = new QLineEdit("0");
            //            QLineEdit* line_edit3 = new QLineEdit("0");

            //            QHBoxLayout *hLayout = new QHBoxLayout();
            //            hLayout->addWidget(line_edit);
            //            hLayout->addWidget(line_edit2);
            //            hLayout->addWidget(line_edit3);

            //            hLayout->setSpacing(0);
            //            hLayout->setMargin(0);
            //            hLayout->setContentsMargins(0,0,0,0);

            //            QWidget *dual_push_buttons = new QWidget();
            //            dual_push_buttons->setFixedHeight(50);
            //            //dual_push_buttons->setS
            //            dual_push_buttons->setLayout(hLayout);
            //            tree_widget_->setItemWidget(chld_item, 1, dual_push_buttons);
            //            return;
            //        }
            //        else
            //        {
            //            tree_widget_->setItemWidget(chld_item, 1, line_edit);
            //        }
            //    }
        }}

}
























