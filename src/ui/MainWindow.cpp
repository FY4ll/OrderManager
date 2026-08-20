#include "ui/MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

MainWindow::MainWindow(ProductManager& productManager)//Mainwindows.h method that sets the title and size of the window
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
    QListWidget *productList = new QListWidget();
    layout->addWidget(productList);
    //Giving accèss to product informations
    const std::vector<Product>& products = productManager.getProducts();
    //loop to get every products in the vector
    for(std::size_t i = 0; i < products.size(); i++){
        productList->addItem(
            QString::number(products[i].getId()) + " | " +
            QString::fromStdString(products[i].getName()) + " | " +
            QString::number(products[i].getPrice()));
    }

}