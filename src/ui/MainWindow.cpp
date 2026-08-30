#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include "ui/ProductDialog.h"
#include "ui/MainWindow.h"
#include "ui/ProductItemWidget.h"

MainWindow::MainWindow(ProductManager& productManager): productManager(productManager){
    // Main window
    setWindowTitle("Order Manager");
    resize(800, 600);
    // Main layout
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    // Sidebar
    QWidget* sidebar = new QWidget();
    sidebar->setObjectName("sidebar");
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
    QPushButton* productsButton = new QPushButton("Products");
    productsButton->setObjectName("sidebarButton");
    QPushButton* ordersButton = new QPushButton("Orders");
    ordersButton->setObjectName("sidebarButton");
    QPushButton* settingsButton = new QPushButton("Settings");
    settingsButton->setObjectName("sidebarButton");
    sidebarLayout->addWidget(productsButton);
    sidebarLayout->addWidget(ordersButton);
    sidebarLayout->addWidget(settingsButton);
    mainLayout->addWidget(sidebar);
    // Main content
    QWidget* content = new QWidget();
    content->setObjectName("content");
    QVBoxLayout* contentLayout = new QVBoxLayout(content);
    QLabel* title = new QLabel("Products");
    contentLayout->addWidget(title);
    // Product list
    productList = new QListWidget;
    productList->setSelectionMode(QAbstractItemView::SingleSelection);
    productList->viewport()->installEventFilter(this);
    contentLayout->addWidget(productList);
    refreshProductList();
    connect(productList,&QListWidget::itemSelectionChanged,this,&MainWindow::updateProductSelection);
    // Product actions
    QHBoxLayout* actionsLayout = new QHBoxLayout();
    QPushButton* newProductButton = new QPushButton("New Product");
    actionsLayout->addWidget(newProductButton);
    connect(newProductButton,&QPushButton::clicked,this,&MainWindow::onNewProductClicked);
    QPushButton* deleteButton = new QPushButton("Remove Product");
    actionsLayout->addWidget(deleteButton);
    connect(deleteButton,&QPushButton::clicked,this,&MainWindow::onDeleteProductClicked);
    QPushButton* updateButton = new QPushButton("Update Product");
    actionsLayout->addWidget(updateButton);
    connect(updateButton,&QPushButton::clicked,this,&MainWindow::onUpdateProductClicked);
    contentLayout->addLayout(actionsLayout);
    mainLayout->addWidget(content);
}
void MainWindow::onNewProductClicked(){
    ProductDialog dialog(productManager);
    if(dialog.exec() == QDialog::Accepted){
        refreshProductList();
    }
}
void MainWindow::refreshProductList(){
productList->clear();
const std::vector<Product>& products = productManager.getProducts();
    for(std::size_t i = 0; i < products.size(); i++){
        QListWidgetItem* item = new QListWidgetItem();
        item->setData(Qt::UserRole, products[i].getId());
        ProductItemWidget* productWidget = new ProductItemWidget(products[i]);
        item->setSizeHint(QSize(0, 55));
        productList->addItem(item);
        productList->setItemWidget(item, productWidget);
    }
}

void MainWindow::onDeleteProductClicked(){
    QListWidgetItem* selectedItem = productList->currentItem();
    if(selectedItem == nullptr){
        return;
    }
    int productID = selectedItem->data(Qt::UserRole).toInt();
    productManager.removeProduct(productID);
    refreshProductList();
}
void MainWindow::onUpdateProductClicked(){
    QListWidgetItem* selectedItem = productList->currentItem();
    if(selectedItem == nullptr){
        return;
    }
    int productID = selectedItem->data(Qt::UserRole).toInt();
    Product* product = productManager.getProductById(productID);
    if(product == nullptr){
        return;
    }
    ProductDialog dialog(productManager, product);
    if(dialog.exec() == QDialog::Accepted){
        productManager.save();
        refreshProductList();
    }

}
void MainWindow::updateProductSelection(){
    for(int i = 0; i < productList->count(); i++){
        QListWidgetItem* item = productList->item(i);
        ProductItemWidget* productWidget = static_cast<ProductItemWidget*>(productList->itemWidget(item));
        if(productWidget != nullptr){
            productWidget->setSelected(item->isSelected());
        }
    }
}

bool MainWindow::eventFilter(QObject* object, QEvent* event){
    if(object == productList->viewport() &&event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if(productList->itemAt(mouseEvent->position().toPoint()) == nullptr){
            productList->clearSelection();
        }
    }
    return QMainWindow::eventFilter(object, event);
}
