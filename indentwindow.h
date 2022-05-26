#ifndef INDENTWINDOW_H
#define INDENTWINDOW_H

#include <QDialog>


namespace Ui {
class indentwindow;
}

class indentwindow : public QDialog
{
    Q_OBJECT

public:
    explicit indentwindow(QWidget *parent = nullptr);
    ~indentwindow();

   short Get_Indent_left();
   short Get_Indent_right();
   short Get_Indent_before();
   short Get_Indent_after();
   short Get_Line_Space();

private:
    Ui::indentwindow *ui;
    short ind1 = 40, ind2 = 40, ind_before = 40, ind_after=40, line_space = 100, indent;
};

#endif // INDENTWINDOW_H
