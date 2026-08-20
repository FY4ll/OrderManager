#include "ui/ProductDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

ProductDialog::ProductDialog()
{
    //window size
    setWindowTitle("Add New Product");
    resize(400, 300);
    //window layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("Add a new product to the list");
    layout->addWidget(title);
    // Name input for new product
    QLineEdit *nameInput = new QLineEdit();
    layout->addWidget(nameInput);

    //Price input only for double value no string
    QDoubleSpinBox *priceInput = new QDoubleSpinBox;
    layout->addWidget(priceInput);

    QPushButton *addButton = new QPushButton("Add Product to the list");
    layout->addWidget(addButton);    
}