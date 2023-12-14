//
// Created by Тимур Ахметзянов on 03.12.2023.
//

#include "App.h"

App::App(int width, int height) {
  window_ = new QMainWindow();
  window_->setFixedSize(width, height);
  window_->setStyleSheet("QMainWindow { background: #fff; }");

  header_container_ = new QLabel(window_);
  header_container_->setFixedSize(305, 100);
  header_container_->move(147, 0);
  header_container_->setText("Universal Convertor");
  QFont header_font = header_container_->font();
  header_font.setPixelSize(32);
  header_font.setBold(true);
  header_container_->setFont(header_font);
  header_container_->setStyleSheet("QLabel { color: #000; }");

  num_edit_ = new QLineEdit(window_);
  num_edit_->resize(550, 30);
  num_edit_->move(25, 120);
  num_edit_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                          "color: #000;"
                          "padding-left: 5px;"
                          "border-radius: 8px; }");
  num_edit_->setPlaceholderText("Число");

  base_edit_ = new QLineEdit(window_);
  base_edit_->resize(150, 30);
  base_edit_->move(25, 170);
  base_edit_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                          "color: #000;"
                          "padding-left: 5px;"
                          "border-radius: 8px; }");
  base_edit_->setPlaceholderText("Исходная система");

  target_base_edit_ = new QLineEdit(window_);
  target_base_edit_->resize(150, 30);
  target_base_edit_->move(200, 170);
  target_base_edit_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                                  "color: #000;"
                                  "padding-left: 5px;"
                                  "border-radius: 8px; }");
  target_base_edit_->setPlaceholderText("Целевая система");

  converted_num_ = new QLabel(window_);
  converted_num_->resize(550, 30);
  converted_num_->move(25, 220);
  converted_num_->setStyleSheet("QLabel { background: #dfd1e6;"
                           "color: #000;"
                           "padding-left: 5px;"
                           "border-radius: 8px; }");
  converted_num_->setText("Конвертированное число");

  convert_ = new QPushButton(window_);
  convert_->resize(150, 40);
  convert_->move(225, 270);
  convert_->setStyleSheet("QPushButton { background: #dfd1e6;"
                          "color: #000;"
                          "border-radius: 8px; }");
  convert_->setText("Конвертировать");
  connect(convert_, SIGNAL (released()), this, SLOT (convertNumber()));

  number_ = "";

  save_button_ = new QPushButton(window_);
  save_button_->move(20, 330);
  save_button_->resize(100, 40);
  save_button_->setStyleSheet("QPushButton { background: #dfd1e6;"
                              "color: #000;"
                              "border-radius: 8px; }");
  save_button_->setText("Сохранить\nв файл");
  connect(save_button_, SIGNAL (released()), this, SLOT (saveToFile()));

  load_button_ = new QPushButton(window_);
  load_button_->move(140, 330);
  load_button_->resize(100, 40);
  load_button_->setStyleSheet("QPushButton { background: #dfd1e6;"
                              "color: #000;"
                              "border-radius: 8px; }");
  load_button_->setText("Загрузить\nиз файла");
  connect(load_button_, SIGNAL (released()), this, SLOT (loadFromFile()));
}

App::~App() {
  delete base_edit_;
  delete target_base_edit_;
  delete num_edit_;
  delete convert_;
  delete header_container_;
  delete load_button_;
  delete save_button_;
  delete window_;
}

void App::convertNumber() {
  std::string number = num_edit_->text().toStdString();
  int base = base_edit_->text().toInt();
  int target = target_base_edit_->text().toInt();

  number_ = Convertor::convert(number, base, target);
  converted_num_->setText(QString::fromStdString(number_));
}

void App::saveToFile() {
  QString file = QFileDialog::getSaveFileName(nullptr, "Сохранить в файл", "", "*.txt");
  QFile outFile(file);
  if (!outFile.open(QIODevice::WriteOnly)) return;
  QTextStream ostream(&outFile);

  ostream << QString::fromStdString(number_);

  outFile.close();
}

void App::loadFromFile() {
  num_edit_->clear();

  QString file = QFileDialog::getOpenFileName(nullptr, "Выбрать txt файл", "", "*.txt");
  QFile in(file);
  if (!in.open(QIODevice::ReadOnly)) return;
  QString data = in.readLine();
  in.close();

  if (data.isEmpty()) return;
  num_edit_->setText(data);
}
