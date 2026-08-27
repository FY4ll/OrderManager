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
    
    //Set the main windows layout information
    QWidget *central = new QWidget(this); //Set a widget zone to page
    setCentralWidget(central);//Making it the main content
    QHBoxLayout *mainLayout = new QHBoxLayout(central);//Adding a QHBox layout to central

    //Creating the sidebar
    QWidget *sidebar = new QWidget();
    sidebar->setObjectName("sidebar");
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);

    QPushButton *productsButton = new QPushButton("Products");
    productsButton->setObjectName("sidebarButton");

    QPushButton *ordersButton = new QPushButton("Orders");
    ordersButton->setObjectName("sidebarButton");

    QPushButton *settingsButton = new QPushButton("Settings");
    settingsButton->setObjectName("sidebarButton");

    sidebarLayout->addWidget(productsButton);
    sidebarLayout->addWidget(ordersButton);
    sidebarLayout->addWidget(settingsButton);

    mainLayout->addWidget(sidebar);

    //Creating the main content area
    QWidget *content = new QWidget();
    content->setObjectName("content");
    QVBoxLayout *contentLayout = new QVBoxLayout(content);

    //creating a first label
    QLabel *title = new QLabel("Products");
    contentLayout->addWidget(title);

    //creating a list widget to display products
    productList = new QListWidget;
    contentLayout->addWidget(productList);
    refreshProductList();

    //Creating the product action buttons
    QHBoxLayout *actionsLayout = new QHBoxLayout();

    //Button to let the user put his own product
    QPushButton *newProductButton = new QPushButton("New Product");
    actionsLayout->addWidget(newProductButton);

    //CONNECT THE BUTTON TO THE METHODS ONNEWPRODUCT CLICK
    connect(newProductButton, &QPushButton::clicked, this, &MainWindow::onNewProductClicked);

    //Button to delete the selected elements in the list above
    QPushButton *deleteButton = new QPushButton("Remove Product");
    actionsLayout->addWidget(deleteButton);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteProductClicked);

    //Button to update product information like price and other stuffs
    QPushButton *updateButton = new QPushButton("Update Product");
    actionsLayout->addWidget(updateButton);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateProductClicked);
    contentLayout->addLayout(actionsLayout);
    mainLayout->addWidget(content);
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
        int productID = selectedItem->data(Qt::UserRole).toInt();
        productManager.removeProduct(productID);
        refreshProductList();
    }
};
void MainWindow::onUpdateProductClicked()
{
    QListWidgetItem *selectedItem = productList->currentItem();
    if (selectedItem != nullptr)
    {
        int productID = selectedItem->data(Qt::UserRole).toInt();
        Product *product = productManager.getProductById(productID);
        if (product != nullptr)
        {
            ProductDialog dialog(productManager, product);
            dialog.exec();
            refreshProductList();
        }
    }
}