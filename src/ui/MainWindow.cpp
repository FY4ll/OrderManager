#include "ui/MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "ui/ProductDialog.h"

//Mainwindows.h method that sets the title and size of the window
MainWindow::MainWindow(ProductManager& productManager) : productManager(productManager)
{
    //Set the main windows information: title and size 
    setWindowTitle("Order Manager"); //set the title of the window to "Order Manager"
    resize(800, 600); //set the size of the window to 800x600 pixels
    
    // Set the main window layout information
    QWidget *central = new QWidget(this); //Set a widget zone to page
    setCentralWidget(central);//Making it the main content
    QVBoxLayout *layout = new QVBoxLayout(central);//Adding a QVBox layout to central 

    //creating a first label
    QLabel *title = new QLabel("Products");
    //make title visible on the page
    layout->addWidget(title);
    //creating a list widget to display products
    productList = new QListWidget;
    layout->addWidget(productList);
    refreshProductList();
    // Button to let the user put his own product
    QPushButton *newProductButton = new QPushButton("New Product");
    layout->addWidget(newProductButton);
    //CONNECT THE BUTTON TO THE METHODS ONNEWPRODUCT CLICK
    connect(newProductButton, &QPushButton::clicked, this, &MainWindow::onNewProductClicked);
    //Button to delete the selected elements in the list above
    QPushButton *deleteButton = new QPushButton("Remove Product");
    layout->addWidget(deleteButton);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteProductClicked);

}
void MainWindow::onNewProductClicked()
{
    ProductDialog dialog(productManager);
    dialog.exec();
    refreshProductList();
}
void MainWindow::refreshProductList(){
    productList->clear();
   //Giving accèss to product informations
    const std::vector<Product>& products = productManager.getProducts();
       //loop to get every products in the vector
    for(std::size_t i = 0; i < products.size(); i++){
        QListWidgetItem *itemRowQTId = new QListWidgetItem();
        itemRowQTId->setData(Qt::UserRole, products[i].getId());
        itemRowQTId->setText(
            QString::number(products[i].getId()) + " | " +
            QString::fromStdString(products[i].getName()) + " | " +
            QString::number(products[i].getPrice()));
        productList->addItem(itemRowQTId);
    }
};
void MainWindow::onDeleteProductClicked(){
    QListWidgetItem *selectedItem = productList->currentItem();    
    if (selectedItem != nullptr){
        
    }else{

    }
};