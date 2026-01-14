//#include "TimeLine.h"
//#include "ui_TimeLine.h"
//
//#include <QSqlQuery>
//#include <QSqlError>
//#include <QDebug>
//
//#include <QDate>
//#include <QDateTime>
//#include <QPainter>
//#include <QLayout>
//
//#include <QtCharts/QChart>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
//
//#include <QtCharts/QDateTimeAxis>
//#include <QtCharts/QValueAxis>
//#include <QVBoxLayout>
//#include <QTimer>
//
//#include <QGuiApplication>
//#include <QDebug>
//
//
//TimeLine::TimeLine(QWidget* parent)
//    : QDialog(parent), ui(new Ui::TimeLine)
//{
//    ui->setupUi(this);
//    resize(700, 400);
//    QTimer::singleShot(0, this, &TimeLine::loadTrend);
//
//}
//
//TimeLine::~TimeLine()
//{
//    delete ui;
//}
//
//void TimeLine::loadTrend()
//{
//    qDebug() << "QGuiApplication instance:"
//        << QGuiApplication::instance();
//    if (!QGuiApplication::instance()) {
//        qDebug() << "NO GUI APPLICATION - ABORT CHART";
//        return;
//    }
//    
//
//    QSqlQuery query;
//
//    QString sql =
//        "SELECT substr(timestamp, 1, 10) AS day, COUNT(*) AS events "
//        "FROM logs "
//        "GROUP BY day "
//        "ORDER BY day ASC;";
//
//    if (!query.exec(sql)) {
//        qDebug() << "Trend SQL error:" << query.lastError().text();
//        return;
//    }
//
//    QLineSeries* series = new QLineSeries;
//    series->setName("Log Activity");
//
//    while (query.next()) {
//        QDate date = QDate::fromString(query.value("day").toString(), "yyyy-MM-dd");
//        series->append(date.startOfDay().toMSecsSinceEpoch(),
//            query.value("events").toInt());
//    }
//
//    QChart* chart = new QChart; 
//    chart->setTheme(QChart::ChartThemeLight);
//    chart->addSeries(series);
//    chart->setTitle("Log Activity Trend");
//    chart->legend()->hide();
//
//    QDateTimeAxis* axisX = new QDateTimeAxis;
//    axisX->setFormat("yyyy-MM-dd");
//
//    QValueAxis* axisY = new QValueAxis;
//    axisY->setTitleText("Events");
//
//    chart->addAxis(axisX, Qt::AlignBottom);
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisX);
//    series->attachAxis(axisY);
//
//    QChartView* view = new QChartView(chart);
//    view->setRenderHint(QPainter::Antialiasing);
//
//    QLayout* lay = ui->charWidget->layout();
//    if (!lay) {
//        lay = new QVBoxLayout(ui->charWidget);
//        lay->setContentsMargins(0, 0, 0, 0);
//    }
//    lay->addWidget(view);
//}
//
//
//
//
