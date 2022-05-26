#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QCheckBox>
#include <QComboBox>
#include <QStringList>
#include <QFontDatabase>
#include <QToolBar>
#include <QBrush>
#include <QWidget>
#include <QAbstractItemView>
#include <QSpinBox>
#include <QTextEdit>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QTextList>
#include <QTextListFormat>
#include <indentwindow.h>
#include <QImage>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QTextDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    window.setModal(true);

    ui->textEdit->createStandardContextMenu();

    ui->toolBar->setIconSize(QSize(18,18));
    ui->toolBar_2->setIconSize(QSize(19,19));

    QComboBox* fontsComboBox = new QComboBox(this);
    ui->toolBar->addWidget(fontsComboBox);
    fontsComboBox->setMaximumWidth(100);
    fontsComboBox->view()->setMinimumWidth(300);
    fontsComboBox->addItem("Часто используемые");
    fontsComboBox->setItemData(0, QBrush(Qt::gray), Qt::BackgroundRole);
    fontsComboBox->addItem("Times New Roman");
    fontsComboBox->addItem("Arial");
    fontsComboBox->addItem("Calibri");
    fontsComboBox->addItem("Все шрифты");
    fontsComboBox->setItemData(4, QBrush(Qt::gray), Qt::BackgroundRole);
    fontsComboBox->setCurrentIndex(1);
    QStringList fonts_list = QFontDatabase().families();
    fontsComboBox->addItems(fonts_list);
    connect(fontsComboBox, &QComboBox::currentTextChanged, this, &MainWindow::Change_Font);

    QSpinBox *sizesSpinBox = new QSpinBox;
    ui->toolBar->addWidget(sizesSpinBox);
    sizesSpinBox->setSingleStep(2);
    sizesSpinBox->setMinimum(2);
    sizesSpinBox->setMaximum(600);
    sizesSpinBox->setValue(12);
    connect(sizesSpinBox, &QSpinBox::valueChanged, this, &MainWindow::Change_Size);


     textColor = new QComboBox(this);
    ui->toolBar_2->addWidget(textColor);
    textColor->setMaximumWidth(40);
    textColor->view()->setMinimumWidth(150);
    textColor->addItem("Цвет текста");
    textColor->addItem("Красный");
    textColor->addItem("Желтый");
    textColor->addItem("Синий");
    textColor->addItem("Зеленый");
    textColor->addItem("Черный");
    textColor->addItem("Больше цветов...");
    textColor->setItemIcon(0, QIcon(":/img/textcolor.png"));
    textColor->setItemIcon(1, QIcon(":/img/red.png"));
    textColor->setItemIcon(2, QIcon(":/img/yellow.png"));
    textColor->setItemIcon(3, QIcon(":/img/blue.png"));
    textColor->setItemIcon(4, QIcon(":/img/green.png"));
    textColor->setItemIcon(5, QIcon(":/img/black (2).png"));
    textColor->setItemIcon(6, QIcon(":/img/rainbow.png"));
    connect(textColor, &QComboBox::currentIndexChanged, this, &MainWindow::Text_Color);

    backgroundColor = new QComboBox(this);
     ui->toolBar_2->addWidget(backgroundColor);
     backgroundColor->setMaximumWidth(40);
     backgroundColor->view()->setMinimumWidth(150);
     backgroundColor->addItem("Цвет фона текста");
     backgroundColor->addItem("Красный");
     backgroundColor->addItem("Желтый");
     backgroundColor->addItem("Синий");
     backgroundColor->addItem("Зеленый");
     backgroundColor->addItem("Без фона");
     backgroundColor->addItem("Больше цветов...");
     backgroundColor->setItemIcon(0, QIcon(":/img/backgroundcolor.png"));
     backgroundColor->setItemIcon(1, QIcon(":/img/red.png"));
     backgroundColor->setItemIcon(2, QIcon(":/img/yellow.png"));
     backgroundColor->setItemIcon(3, QIcon(":/img/blue.png"));
     backgroundColor->setItemIcon(4, QIcon(":/img/green.png"));
     backgroundColor->setItemIcon(5, QIcon(":/img/white.png"));
     backgroundColor->setItemIcon(6, QIcon(":/img/rainbow.png"));
     connect(backgroundColor, &QComboBox::currentIndexChanged, this, &MainWindow::Background_Color);

     ui->toolBar_2->addSeparator();
    ui->toolBar_2->addAction(ui->normal_baseline);
     ui->toolBar_2->addAction(ui->toUpper);
     ui->toolBar_2->addAction(ui->toLower);
     ui->toolBar->addAction(ui->UpperCase);

     ui->toolBar->addAction(ui->LowerCase);


     ui->toolBar->addSeparator();
      ui->toolBar_2->addSeparator();
     markers = new QComboBox(this);
     ui->toolBar->addWidget(markers);
     markers->setMaximumWidth(40);
     markers->view()->setMinimumWidth(200);

     markers->addItem("Маркеры");
     markers->addItem("Квадрат");
     markers->addItem("Пустой круг");
     markers->addItem("Заполненный круг");


     markers->setItemIcon(0, QIcon(":/img/markers.png"));
     markers->setItemIcon(1, QIcon(":/img/square.png"));
     markers->setItemIcon(2, QIcon(":/img/marker2.png"));
     markers->setItemIcon(3, QIcon(":/img/marker3.png"));


     lists = new QComboBox(this);
     ui->toolBar->addWidget(lists);
     lists->setMaximumWidth(40);
     lists->view()->setIconSize(QSize(70,70));
     lists->view()->setMinimumWidth(75);
     lists->addItem("Нумерация");
     lists->addItem("");
     lists->addItem("");
     lists->addItem("");
     lists->addItem("");
     lists->addItem("");
     lists->setItemIcon(0, QIcon(":/img/list.png"));
     lists->setItemIcon(1, QIcon(":/img/list123.jpg"));
     lists->setItemIcon(2, QIcon(":/img/list_abc.png"));
     lists->setItemIcon(3, QIcon(":/img/list_i.png"));
     lists->setItemIcon(4, QIcon(":/img/list_ABC).png"));
     lists->setItemIcon(5, QIcon(":/img/list_I_II_III.png"));

     connect(markers, &QComboBox::currentIndexChanged, this, &MainWindow::Markers);
     connect(lists, &QComboBox::currentIndexChanged, this, &MainWindow::Markers);

     ui->toolBar_2->addAction(ui->increase_indent);
     ui->toolBar_2->addAction(ui->decrease_indent);
     ui->toolBar_2->addAction(ui->indent_edit);

     lineSpacing = new QComboBox(this);
     ui->toolBar->addWidget(lineSpacing);
     lineSpacing->setMaximumWidth(40);
     lineSpacing->view()->setMinimumWidth(300);
     lineSpacing->addItem("Межстрочный интервал");
     lineSpacing->addItem("1,0");
     lineSpacing->addItem("1,15");
     lineSpacing->addItem("1,5");
     lineSpacing->addItem("2,0");
     lineSpacing->addItem("Настроить межстрочный интервал...");
     lineSpacing->setItemIcon(0, QIcon(":/myres/img/lineSpacing (2).png"));
     connect(lineSpacing, &QComboBox::currentIndexChanged, this, &MainWindow::Line_Spacing);


     verticalIndents = new QComboBox(this);
     ui->toolBar_2->addWidget(verticalIndents);
     verticalIndents->setMaximumWidth(43);
     verticalIndents->view()->setMinimumWidth(300);
     verticalIndents->addItem("Интервалы перед и после абзацев");
     verticalIndents->addItem("Добавить интервал перед абзацем");
     verticalIndents->addItem("Добавить интервал после абзаца..");
     verticalIndents->addItem("Убрать отступы");
     verticalIndents->addItem("Настроить интервалы абзацев..");
     verticalIndents->setItemIcon(0, QIcon(":/myres/img/verticalIndents.png"));
     connect(verticalIndents, &QComboBox::currentIndexChanged, this, &MainWindow::Indent_Up_Down);

     ui->toolBar->addSeparator();
     ui->toolBar->addSeparator();

     ui->toolBar_2->addSeparator();
     ui->toolBar_2->addSeparator();

      ui->toolBar->addAction(ui->insert_image);






}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mouse_Press_Event(QMouseEvent *event)
{
    QRect p = this->geometry();
    if(event->button() == Qt::LeftButton)
    {
        last_coords = event->pos();
        move_bool = true;
    }
}

void MainWindow::mouse_Move_Event(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && move_bool)
        move(event->globalX()-last_coords.x(),
             event->globalY()-last_coords.y());
}

void MainWindow::mouse_Release_Event(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && move_bool) {
            move_bool = false;
        }
}





void MainWindow::Markers(const int &index)
{
    QTextListFormat listFormat;
    unsigned int pos1, pos2;
     QTextCursor cursor = ui->textEdit->textCursor();;
    pos1 = cursor.position();
    pos2 = cursor.anchor();
    if (markers->currentIndex() != 0)//сработал combobox маркеров
    {
        switch(index)
        {
        case 1:
            listFormat.setStyle(QTextListFormat::ListSquare);
            break;
        case 2:
            listFormat.setStyle(QTextListFormat::ListCircle);
            break;
        case 3:
            listFormat.setStyle(QTextListFormat::ListDisc);
            break;
        default:
            break;
        }
    }
    else//сработал combobox нумерации
    {
       switch(index)
       {

       case 1:
           listFormat.setStyle(QTextListFormat::ListDecimal);
           break;
        case 2:
           listFormat.setStyle(QTextListFormat::ListLowerAlpha);
           break;
       case 3:
          listFormat.setStyle(QTextListFormat::ListLowerRoman);
          break;
       case 4:
          listFormat.setStyle(QTextListFormat::ListUpperAlpha);
          break;
       case 5:
          listFormat.setStyle(QTextListFormat::ListUpperRoman);
          break;
       default:
           break;
       }
    }


    lists->setCurrentIndex(0);
    markers->setCurrentIndex(0);
   if (pos1 != pos2)
   {
       cursor.createList(listFormat);
   }



}

void MainWindow::Change_Size(const int &size)
{
    QFont currentFont = ui->textEdit->currentFont();
    currentFont.setPointSize(size);
    ui->textEdit->setCurrentFont(currentFont);
}

void MainWindow::Change_Font(const QFont &f)
{
    QFont currentFont = ui->textEdit->currentFont();
    ui->textEdit->setCurrentFont(f);
}


void MainWindow::on_open_file_triggered()
{

    QString path = QFileDialog::getOpenFileName(this, "Выбрать файл", "C:\\",  "Все файлы (*.*);; txt (*.txt);; docx (*.docx);" );
  QFile fread = path;
  if (!fread.open(QFile::ReadOnly | QFile::Text))
  {
      QMessageBox::information(this, "Ошибка", "Ошибка открытия файла: " + fread.errorString());
    return;
  }

  setWindowTitle(path);
  QTextStream stream(&fread);
  stream.setEncoding(QStringConverter::System);//чтоб работал русский язык
  QString buffer = stream.readAll();
  ui->textEdit->setText(buffer);
  fread.flush(); //данные считываются непосредственно с жесткого диска без буфера обмена
  fread.close();
}

void MainWindow::on_new_file_triggered()
{
  current_file.clear();
  ui->textEdit->setText(QString());
}


void MainWindow::on_save_as_triggered()
{
QString path = QFileDialog::getSaveFileName(this, "Сохранить как");
QFile file(path);
if (!file.open(QFile::WriteOnly|QFile::Text))
{
    QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл: " + file.errorString());
    return;
}
current_file = path;
setWindowTitle(path);
QTextStream out(&file);
QString text = ui->textEdit->toPlainText();
out<<text;
file.close();
}


void MainWindow::on_Bold_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();

     QTextCharFormat charFormat = cursor.charFormat();
     if (charFormat.fontWeight() == QFont::Bold )
     {
         ui->textEdit->setFontWeight(QFont::Normal);
     }
     else
     {
      ui->textEdit->setFontWeight(QFont::Bold);
     }


}




void MainWindow::on_save_file_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, "Сохранить");
    QFile file(path);
    if (!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.close();
}


void MainWindow::on_Undo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_Redo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_italic_triggered()
{
    if (ui->textEdit->textCursor().charFormat().fontItalic() == QFont::StyleItalic)
    {
       ui->textEdit->setFontItalic(QFont::StyleNormal);
    }
    else
    {
     ui->textEdit->setFontItalic(QFont::StyleItalic);
    }

}



void MainWindow::on_underlined_triggered()
{
    if (ui->textEdit->textCursor().charFormat().fontUnderline())
    {
       ui->textEdit->setFontUnderline(QFont::StyleNormal);
    }
    else
    {
     ui->textEdit->setFontUnderline(QFont::UnderlineResolved);
    }
}


void MainWindow::on_AlignLeft_triggered()

{

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat text = cursor.blockFormat();
    text.setAlignment(Qt::AlignLeft|Qt::AlignAbsolute);
    cursor.mergeBlockFormat(text);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_AlignRight_triggered()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat text = cursor.blockFormat();
    text.setAlignment(Qt::AlignRight|Qt::AlignAbsolute);
    cursor.mergeBlockFormat(text);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_AlignCenter_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat text = cursor.blockFormat();
    text.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(text);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_AlignWidth_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat text = cursor.blockFormat();
    text.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(text);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::Text_Color(const int &index)
{


   QColor color = Qt::black;

   switch(index)
   {
   case 1:
       color = Qt::red;
       break;
   case 2:
       color = Qt::yellow;
       break;
   case 3:
       color = Qt::blue;
       break;
   case 4:
       color = Qt::green;
       break;
   case 5:
       color = Qt::black;
       break;
   case 6:
       color = QColorDialog::getColor(QColorDialog::ShowAlphaChannel);
       break;
    default:
       break;

   }
textColor->setCurrentIndex(0);
ui->textEdit->setTextColor(color);


}
void MainWindow::Background_Color(const int &index)
{


   QColor color = Qt::black;

   switch(index)
   {
   case 1:
       color = Qt::red;
       break;
   case 2:
       color = Qt::yellow;
       break;
   case 3:
       color = Qt::blue;
       break;
   case 4:
       color = Qt::green;
       break;
   case 5:
       color = Qt::white;
       break;
   case 6:
       color = QColorDialog::getColor(QColorDialog::ShowAlphaChannel);
       break;
    default:
       break;

   }
backgroundColor->setCurrentIndex(0);
ui->textEdit->setTextBackgroundColor(color);


}

void MainWindow::on_toUpper_triggered()
{
    QString str = ui->textEdit->textCursor().selectedText();
    str = "<sup>"+str+"</sup>";
    ui->textEdit->textCursor().insertHtml(str);

}


void MainWindow::on_UpperCase_triggered()
{
    QString str = ui->textEdit->textCursor().selectedText();
    str = str.toUpper();
     ui->textEdit->textCursor().insertText(str);
}


void MainWindow::on_LowerCase_triggered()
{
    QString str = ui->textEdit->textCursor().selectedText();
    str = str.toLower();
     ui->textEdit->textCursor().insertText(str);
}


void MainWindow::on_toLower_triggered()
{

     QTextCursor cursor = ui->textEdit->textCursor();;

    QString str = ui->textEdit->textCursor().selectedText();

    str = "<sub>"+str+"</sub>";
    ui->textEdit->textCursor().insertHtml(str);
}


void MainWindow::on_increase_indent_triggered()
{
    QTextBlockFormat indentFormat;
    short text_edit_width = 800, cur_indent;

    cur_indent = ui->textEdit->textCursor().blockFormat().leftMargin();
    if (cur_indent < (text_edit_width - indent_left))//чтобы текст не уходил за правую границу
    {
        indentFormat.setLeftMargin(cur_indent + indent_left);
        ui->textEdit->textCursor().setBlockFormat(indentFormat);
    }
}


void MainWindow::on_decrease_indent_triggered()
{

    QTextBlockFormat indentFormat;
    short cur_indent;
    cur_indent = ui->textEdit->textCursor().blockFormat().leftMargin();
    if(cur_indent < indent_right)//чтобы текст не уходил за левую границу
    {
        cur_indent = indent_right;
    }
    indentFormat.setLeftMargin(cur_indent - indent_right );
    ui->textEdit->textCursor().setBlockFormat(indentFormat);
}

 void MainWindow:: on_indent_edit_triggered()
 {

     window.exec();
     indent_left = window.Get_Indent_left();
     indent_right = window.Get_Indent_right();

 }

 void MainWindow::Indent_Up_Down(const int &index)
 {

     QTextCursor cursor = ui->textEdit->textCursor();
     QTextBlockFormat text = cursor.blockFormat();
     switch(index)
     {
     case 1://интервал перед абзацем
       text.setTopMargin(indent_before);
         break;
     case 2: //интервал после абзаца
       text.setBottomMargin(indent_after);
         break;
     case 3:
        text.setTopMargin(0);
        text.setBottomMargin(0);
         break;
     case 4: //вспомогательное окно
          window.exec();
          indent_before = window.Get_Indent_before();
          indent_after = window.Get_Indent_after();
         break;
     default:
         break;


     }

     verticalIndents->setCurrentIndex(0);
     cursor.mergeBlockFormat(text);
     ui->textEdit->setTextCursor(cursor);
 }

 void MainWindow::Line_Spacing(const int &index)
 {

     QTextCursor cursor = ui->textEdit->textCursor();
     QTextBlockFormat text = cursor.blockFormat();

     switch(index)
     {
     case 1:
         line_space = 100;
         break;
     case 2:
         line_space = 115;
         break;
     case 3:
         line_space = 150;
         break;
     case 4:
         line_space = 200;
         break;
     case 5:
       window.exec();
       line_space = (window.Get_Line_Space())*100;
         break;
     default:
         break;


     }
     lineSpacing->setCurrentIndex(0);
     text.setLineHeight(line_space, QTextBlockFormat::ProportionalHeight);
     cursor.mergeBlockFormat(text);
     ui->textEdit->setTextCursor(cursor);
 }


void MainWindow::on_insert_image_triggered()
{

    QString path = QFileDialog::getOpenFileName(this, "Выбрать файл", "C:\\",  "Все файлы (*.*);" );
    QFile fread = path;
    QImage image = QImage(path);
    QRect p;
    p = image.rect();

    ui->textEdit->textCursor().insertImage(path);



  fread.close();
}



void MainWindow::on_normal_baseline_triggered()
{

    QTextCursor cursor = ui->textEdit->textCursor();;

   QString str = ui->textEdit->textCursor().selectedText();
   ui->textEdit->setStyleSheet("vertical-align:baseline");
   //str = "<pre>" + str + "</pre>";
   ui->textEdit->textCursor().insertHtml(str);
}

