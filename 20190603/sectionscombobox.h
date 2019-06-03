#ifndef SECTIONSCOMBOBOX_H
#define SECTIONSCOMBOBOX_H

#include <QWidget>

namespace Ui {
class SectionsComboBox;
}

class SectionsComboBox : public QWidget {
    Q_OBJECT

    friend class SectionsComboBoxDelegate;

public:
    explicit SectionsComboBox( QWidget *parent = nullptr );
    ~SectionsComboBox();

private slots:

    void on_startBox_currentIndexChanged( int index );

private:
    Ui::SectionsComboBox *ui;
};

#endif   // SECTIONSCOMBOBOX_H
