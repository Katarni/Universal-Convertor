//
// Created by Тимур Ахметзянов on 03.12.2023.
//

#pragma once
#include "Convertor.h"

class App : public QMainWindow {
 Q_OBJECT

 public:
  App(int width, int height);
  ~App() override;

  void render() {
    window_->show();
  }

 private slots:
  void convertNumber();

 private:
  QWidget* window_;
  QLineEdit* num_edit_;
  QLineEdit* base_edit_;
  QLineEdit* target_base_edit_;
  QPushButton* convert_;
  QLineEdit* converted_num_;
};