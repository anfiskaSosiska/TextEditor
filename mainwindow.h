#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QComboBox>
#include <QItemDelegate>
#include <indentwindow.h>
#include <QPoint>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_open_file_triggered();


    void on_new_file_triggered();

    void on_save_as_triggered();

    void on_Bold_triggered();

    void on_save_file_triggered();

    void on_Undo_triggered();

    void on_Redo_triggered();

    void on_italic_triggered();

    void on_underlined_triggered();
    void Change_Font(const QFont &f);
    void Change_Size(const int &size);

    void on_AlignLeft_triggered();

    void on_AlignRight_triggered();

    void on_AlignCenter_triggered();

    void on_AlignWidth_triggered();

    void Text_Color(const int &index);
    void Background_Color(const int &index);

    void on_toUpper_triggered();

    void on_UpperCase_triggered();

    void on_LowerCase_triggered();
    void Markers(const int &index);

    void on_toLower_triggered();

    void on_increase_indent_triggered();

    void on_decrease_indent_triggered();

    void on_indent_edit_triggered();

    void Indent_Up_Down(const int &index);
    void Line_Spacing(const int &index);

    void on_insert_image_triggered();
    void mouse_Press_Event(QMouseEvent *event);
    void mouse_Move_Event(QMouseEvent *event);
    void mouse_Release_Event(QMouseEvent *event);

    void on_normal_baseline_triggered();

private:
    Ui::MainWindow *ui;
    QString current_file = "";
    QComboBox* textColor;
    QComboBox* backgroundColor;

    QComboBox* markers;
    QComboBox* lists;
    QComboBox* lineSpacing;
    QComboBox* verticalIndents;
    short indent_left = 40, indent_right = 40, indent_before = 40, indent_after = 40, line_space = 100;
    indentwindow window;
    QPoint last_coords;
    bool move_bool = false;

};

#endif // MAINWINDOW_H
