#include "indentwindow.h"
#include "ui_indentwindow.h"
#include <mainwindow.h>


indentwindow::indentwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::indentwindow)
{
    ui->setupUi(this);
    ui->indent_left->setValue(ind1);
    ui->indent_right->setValue(ind2);
    ui->indent_left->setMaximum(700);
    ui->indent_right->setMaximum(700);
    ui->indent_before->setValue(ind_before);
    ui->indent_before->setValue(ind_after);
    ui->line_spacing->setValue(line_space);
    connect(ui->indent_left, &QSpinBox::valueChanged, this, &indentwindow::Get_Indent_left);
    connect(ui->indent_right, &QSpinBox::valueChanged, this, &indentwindow::Get_Indent_right);

}

indentwindow::~indentwindow()
{
    delete ui;
}

short indentwindow::Get_Indent_left()
{
    indent = ui->indent_left->value();
    ui->indent_left->setValue(indent);
    ind1 = indent;
return indent;
}

short indentwindow::Get_Indent_right()
{
    indent = ui->indent_right->value();
    ui->indent_right->setValue(indent);
    ind2 = indent;
return indent;
}

short indentwindow::Get_Indent_before()
{
    indent = ui->indent_before->value();
    ui->indent_before->setValue(indent);
    return indent;
}

short indentwindow::Get_Indent_after()
{
    indent = ui->indent_after->value();
    ui->indent_after->setValue(indent);
    return indent;
}

short indentwindow::Get_Line_Space()
{
    indent = ui->line_spacing->value();
    ui->line_spacing->setValue(indent);
    return indent;
}
