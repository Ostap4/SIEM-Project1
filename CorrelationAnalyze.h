#pragma once

#include <QDialog>
#ifndef CORRELATIONANALYZE_H
#define CORRELATIONANALYZE_H

QT_BEGIN_NAMESPACE
namespace Ui {
    class CorrelationAnalyzeDialog;
}
QT_END_NAMESPACE

class CorrelationAnalyzeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CorrelationAnalyzeDialog(QWidget* parent = nullptr);
    ~CorrelationAnalyzeDialog();

private:
    Ui::CorrelationAnalyzeDialog* ui;


    void setupComboBox();
    void configureTableForType(int index);

  
    void fillFailedSuccessTable();
    void fillIpEndpointTable();
    void onCorrelationTypeChanged(int index);
    void onAnalyzeClicked();
    void showSortMenu(int column);
}; 
#endif // CORRELATIONANALYZE_H
