//
// Created by Тимур Ахметзянов on 03.12.2023.
//

#include "App.h"

App::App(int width, int height) {
  window_ = new QMainWindow();
  window_->setFixedSize(width, height);
  window_->setWindowTitle("Universal Convertor");
  window_->setStyleSheet("QMainWindow { background: #fff; }");

  num_edit_ = new QLineEdit(window_);
  num_edit_->resize(550, 30);
  num_edit_->move(25, 70);
  num_edit_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                          "color: #000;"
                          "padding-left: 5px;"
                          "border-radius: 8px; }");
  num_edit_->setPlaceholderText("Число");

  base_edit_ = new QLineEdit(window_);
  base_edit_->resize(150, 30);
  base_edit_->move(25, 120);
  base_edit_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                          "color: #000;"
                          "padding-left: 5px;"
                          "border-radius: 8px; }");
  base_edit_->setPlaceholderText("Исходная система");

  target_base_edit_ = new QLineEdit(window_);
  target_base_edit_->resize(150, 30);
  target_base_edit_->move(200, 120);
  target_base_edit_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                                  "color: #000;"
                                  "padding-left: 5px;"
                                  "border-radius: 8px; }");
  target_base_edit_->setPlaceholderText("Целевая система");

  converted_num_ = new QLineEdit(window_);
  converted_num_->resize(550, 30);
  converted_num_->move(25, 170);
  converted_num_->setReadOnly(true);
  converted_num_->setStyleSheet("QLineEdit { background: #dfd1e6;"
                           "color: #000;"
                           "padding-left: 5px;"
                           "border-radius: 8px; }");
  converted_num_->setPlaceholderText("Конвертированное число");

  convert_ = new QPushButton(window_);
  convert_->resize(150, 40);
  convert_->move(225, 220);
  convert_->setStyleSheet("QPushButton { background: #dfd1e6;"
                          "color: #000;"
                          "border-radius: 8px; }");
  convert_->setText("Конвертировать");
  connect(convert_, SIGNAL (released()), this, SLOT (convertNumber()));
}

App::~App() {
  delete base_edit_;
  delete target_base_edit_;
  delete num_edit_;
  delete convert_;
  delete window_;
}

void App::convertNumber() {
  std::string number = num_edit_->text().toStdString();
  int base = base_edit_->text().toInt();
  int target = target_base_edit_->text().toInt();

  num_edit_->clear();
  base_edit_->clear();
  target_base_edit_->clear();

  std::string converted = Convertor::convert(number, base, target);
  converted_num_->setText(QString::fromStdString(converted));
}
