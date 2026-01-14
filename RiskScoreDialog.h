#pragma once

#ifndef RISKSCOREDIALOG_H
#define RISKCOREDIALOG_H

#include <QDialog>


namespace Ui {
	class RiskScoreDialog;
}

class RiskScoreDialog : public QDialog
{
	Q_OBJECT

public:
	explicit RiskScoreDialog(QWidget* parent = nullptr);
	~RiskScoreDialog();

	void loadRiskScore(); 


private:
	Ui::RiskScoreDialog* ui;
	void showSortMenu(int column);
};


#endif // !RISKSCOREDIALOG_H


