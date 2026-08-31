#include "ui/MainWindow.h"
#include "ui/ProductDialog.h"
#include "ui/ProductItemWidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QFrame>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(ProductManager& productManager): QMainWindow(nullptr), productManager(productManager), pageStack(nullptr), searchInput(nullptr), pageTitle(nullptr), pageSubtitle(nullptr), productCountLabel(nullptr), productList(nullptr), activeIndicator(nullptr), currentPageIndex(0){
    setWindowTitle("OrderManager");
    resize(1280, 800);
    setMinimumSize(1050, 680);
    setupUi();
}
void MainWindow::setupUi(){
    QWidget* central = new QWidget(this);
    central->setObjectName("centralWidget");
    setCentralWidget(central);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setupSidebar();
    setupHeader();
    setupPages();
    QWidget* sidebar = findChild<QWidget*>("sidebar");
    if(sidebar != nullptr){
        mainLayout->addWidget(sidebar);
    }
    QWidget* content = new QWidget();
    content->setObjectName("mainContent");
    QVBoxLayout* contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(34, 30, 34, 30);
    contentLayout->setSpacing(24);
    QWidget* header = new QWidget();
    header->setObjectName("header");
    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(20);
    QWidget* titleContainer = new QWidget();
    QVBoxLayout* titleLayout = new QVBoxLayout(titleContainer);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(4);
    pageTitle = new QLabel("Dashboard");
    pageTitle->setObjectName("pageTitle");
    pageSubtitle = new QLabel("Overview of your warehouse activity");
    pageSubtitle->setObjectName("pageSubtitle");
    titleLayout->addWidget(pageTitle);
    titleLayout->addWidget(pageSubtitle);
    headerLayout->addWidget(titleContainer);
    headerLayout->addStretch();
    searchInput = new QLineEdit();
    searchInput->setObjectName("globalSearch");
    searchInput->setPlaceholderText("Search products...");
    searchInput->setFixedWidth(290);
    searchInput->setClearButtonEnabled(true);
    headerLayout->addWidget(searchInput);
    contentLayout->addWidget(header);
    contentLayout->addWidget(pageStack, 1);
    mainLayout->addWidget(content, 1);
    connect(searchInput, &QLineEdit::textChanged, this, &MainWindow::filterProducts);
    searchInput->hide();
}
void MainWindow::setupSidebar(){
    QWidget* sidebar = new QWidget();
    sidebar->setObjectName("sidebar");
    sidebar->setMinimumWidth(245);
    sidebar->setMaximumWidth(245);
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(20, 24, 20, 20);
    sidebarLayout->setSpacing(7);
    QWidget* logoContainer = new QWidget();
    QVBoxLayout* logoLayout = new QVBoxLayout(logoContainer);
    logoLayout->setContentsMargins(8, 0, 8, 25);
    logoLayout->setSpacing(1);
    QLabel* logo = new QLabel("ORDER");
    logo->setObjectName("logo");
    QLabel* logoSubtitle = new QLabel("MANAGER");
    logoSubtitle->setObjectName("logoSubtitle");
    QLabel* version = new QLabel("INVENTORY & LOGISTICS");
    version->setObjectName("logoVersion");
    logoLayout->addWidget(logo);
    logoLayout->addWidget(logoSubtitle);
    logoLayout->addSpacing(9);
    logoLayout->addWidget(version);
    sidebarLayout->addWidget(logoContainer);
    QLabel* workspaceLabel = new QLabel("WORKSPACE");
    workspaceLabel->setObjectName("navigationLabel");
    sidebarLayout->addWidget(workspaceLabel);
    sidebarLayout->addSpacing(5);
    sidebarLayout->addWidget(createSidebarButton("Dashboard", 0));
    sidebarLayout->addWidget(createSidebarButton("Products", 1));
    sidebarLayout->addWidget(createSidebarButton("Orders", 2));
    sidebarLayout->addWidget(createSidebarButton("Reception", 3));
    sidebarLayout->addWidget(createSidebarButton("Stock", 4));
    sidebarLayout->addSpacing(20);
    QLabel* systemLabel = new QLabel("SYSTEM");
    systemLabel->setObjectName("navigationLabel");
    sidebarLayout->addWidget(systemLabel);
    sidebarLayout->addSpacing(5);
    sidebarLayout->addWidget(createSidebarButton("Settings", 5));
    sidebarLayout->addStretch();
    QFrame* statusContainer = new QFrame();
    statusContainer->setObjectName("statusContainer");
    QHBoxLayout* statusLayout = new QHBoxLayout(statusContainer);
    statusLayout->setContentsMargins(10, 9, 10, 9);
    statusLayout->setSpacing(7);
    QLabel* statusDot = new QLabel("●");
    statusDot->setObjectName("statusDot");
    QLabel* statusLabel = new QLabel("System ready");
    statusLabel->setObjectName("systemStatus");
    statusLayout->addWidget(statusDot);
    statusLayout->addWidget(statusLabel);
    statusLayout->addStretch();
    sidebarLayout->addWidget(statusContainer);
    activeIndicator = new QFrame(sidebar);
    activeIndicator->setObjectName("activeIndicator");
    activeIndicator->setFixedSize(3, 26);
    activeIndicator->show();
    sidebar->setParent(this);
    QTimer::singleShot(0, this, [this, sidebar](){
        QPushButton* button = sidebar->findChildren<QPushButton*>("sidebarButton").value(0);
        if(button != nullptr){
            activeIndicator->move(0, button->y() + (button->height() - activeIndicator->height()) / 2);
        }
    });
}
QPushButton* MainWindow::createSidebarButton(const QString& text, int pageIndex){
    QPushButton* button = new QPushButton(text);
    button->setObjectName("sidebarButton");
    button->setCursor(Qt::PointingHandCursor);
    button->setCheckable(true);
    button->setProperty("pageIndex", pageIndex);
    if(pageIndex == 0){
        button->setChecked(true);
    }
    connect(button, &QPushButton::clicked, this, [this, pageIndex, button](){
        if(pageIndex == currentPageIndex){
            return;
        }
        updateSidebarSelection(pageIndex);
        animateSidebarIndicator(button);
        setCurrentPage(pageIndex);
    });
    return button;
}
void MainWindow::updateSidebarSelection(int pageIndex){
    QWidget* sidebar = findChild<QWidget*>("sidebar");
    if(sidebar == nullptr){
        return;
    }
    const QList<QPushButton*> buttons = sidebar->findChildren<QPushButton*>("sidebarButton");
    for(QPushButton* button : buttons){
        int buttonPageIndex = button->property("pageIndex").toInt();
        button->setChecked(buttonPageIndex == pageIndex);
    }
}
void MainWindow::setupHeader(){
}
void MainWindow::setupPages(){
    pageStack = new QStackedWidget();
    pageStack->setObjectName("pageStack");
    pageStack->addWidget(createDashboardPage());
    pageStack->addWidget(createProductsPage());
    pageStack->addWidget(createWipPage("Orders", "Order management is currently under development."));
    pageStack->addWidget(createWipPage("Reception", "Reception management is currently under development."));
    pageStack->addWidget(createWipPage("Stock", "Stock management is currently under development."));
    pageStack->addWidget(createWipPage("Settings", "Application settings are currently under development."));
}
QWidget* MainWindow::createDashboardPage(){
    QWidget* page = new QWidget();
    page->setObjectName("dashboardPage");
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);
    QWidget* welcomeContainer = new QWidget();
    welcomeContainer->setObjectName("welcomeContainer");
    QVBoxLayout* welcomeLayout = new QVBoxLayout(welcomeContainer);
    welcomeLayout->setContentsMargins(2, 2, 2, 2);
    welcomeLayout->setSpacing(4);
    QLabel* welcome = new QLabel("Welcome back.");
    welcome->setObjectName("dashboardWelcome");
    QLabel* description = new QLabel("Everything you need to manage your warehouse in one place.");
    description->setObjectName("dashboardDescription");
    welcomeLayout->addWidget(welcome);
    welcomeLayout->addWidget(description);
    layout->addWidget(welcomeContainer);
    QGridLayout* statsLayout = new QGridLayout();
    statsLayout->setContentsMargins(0, 6, 0, 0);
    statsLayout->setHorizontalSpacing(14);
    statsLayout->setVerticalSpacing(14);
    QFrame* productsCard = new QFrame();
    productsCard->setObjectName("statCard");
    productsCard->setProperty("animationIndex", 0);
    QVBoxLayout* productsLayout = new QVBoxLayout(productsCard);
    productsLayout->setContentsMargins(22, 20, 22, 20);
    productsLayout->setSpacing(6);
    QLabel* productsTitle = new QLabel("PRODUCTS");
    productsTitle->setObjectName("statTitle");
    QLabel* productsValue = new QLabel(QString::number(productManager.getProducts().size()));
    productsValue->setObjectName("statValue");
    QLabel* productsSubtitle = new QLabel("Items in catalog");
    productsSubtitle->setObjectName("statSubtitle");
    productsLayout->addWidget(productsTitle);
    productsLayout->addWidget(productsValue);
    productsLayout->addWidget(productsSubtitle);
    QFrame* ordersCard = new QFrame();
    ordersCard->setObjectName("statCard");
    ordersCard->setProperty("animationIndex", 1);
    QVBoxLayout* ordersLayout = new QVBoxLayout(ordersCard);
    ordersLayout->setContentsMargins(22, 20, 22, 20);
    ordersLayout->setSpacing(6);
    QLabel* ordersTitle = new QLabel("ORDERS");
    ordersTitle->setObjectName("statTitle");
    QLabel* ordersValue = new QLabel("—");
    ordersValue->setObjectName("statValue");
    QLabel* ordersSubtitle = new QLabel("Coming soon");
    ordersSubtitle->setObjectName("statSubtitle");
    ordersLayout->addWidget(ordersTitle);
    ordersLayout->addWidget(ordersValue);
    ordersLayout->addWidget(ordersSubtitle);
    QFrame* stockCard = new QFrame();
    stockCard->setObjectName("statCard");
    stockCard->setProperty("animationIndex", 2);
    QVBoxLayout* stockLayout = new QVBoxLayout(stockCard);
    stockLayout->setContentsMargins(22, 20, 22, 20);
    stockLayout->setSpacing(6);
    QLabel* stockTitle = new QLabel("STOCK");
    stockTitle->setObjectName("statTitle");
    QLabel* stockValue = new QLabel("—");
    stockValue->setObjectName("statValue");
    QLabel* stockSubtitle = new QLabel("Coming soon");
    stockSubtitle->setObjectName("statSubtitle");
    stockLayout->addWidget(stockTitle);
    stockLayout->addWidget(stockValue);
    stockLayout->addWidget(stockSubtitle);
    statsLayout->addWidget(productsCard, 0, 0);
    statsLayout->addWidget(ordersCard, 0, 1);
    statsLayout->addWidget(stockCard, 0, 2);
    layout->addLayout(statsLayout);
    QFrame* activityCard = new QFrame();
    activityCard->setObjectName("activityCard");
    activityCard->setProperty("animationIndex", 3);
    QVBoxLayout* activityLayout = new QVBoxLayout(activityCard);
    activityLayout->setContentsMargins(22, 20, 22, 20);
    activityLayout->setSpacing(14);
    QHBoxLayout* activityHeader = new QHBoxLayout();
    QLabel* activityTitle = new QLabel("Recent activity");
    activityTitle->setObjectName("sectionTitle");
    QLabel* activityStatus = new QLabel("LIVE");
    activityStatus->setObjectName("liveBadge");
    activityHeader->addWidget(activityTitle);
    activityHeader->addStretch();
    activityHeader->addWidget(activityStatus);
    activityLayout->addLayout(activityHeader);
    QLabel* activityDescription = new QLabel("Your latest warehouse events will appear here.");
    activityDescription->setObjectName("sectionDescription");
    activityLayout->addWidget(activityDescription);
    QFrame* separator = new QFrame();
    separator->setObjectName("separator");
    separator->setFrameShape(QFrame::HLine);
    activityLayout->addWidget(separator);
    QLabel* emptyActivity = new QLabel("No recent activity yet");
    emptyActivity->setObjectName("emptyState");
    emptyActivity->setAlignment(Qt::AlignCenter);
    activityLayout->addWidget(emptyActivity);
    activityLayout->addStretch();
    layout->addWidget(activityCard, 1);
    return page;
}
QWidget* MainWindow::createProductsPage(){
    QWidget* page = new QWidget();
    page->setObjectName("productsPage");
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(18);
    QWidget* toolbar = new QWidget();
    toolbar->setObjectName("productsToolbar");
    QHBoxLayout* toolbarLayout = new QHBoxLayout(toolbar);
    toolbarLayout->setContentsMargins(0, 0, 0, 0);
    toolbarLayout->setSpacing(9);
    QWidget* countContainer = new QWidget();
    QVBoxLayout* countLayout = new QVBoxLayout(countContainer);
    countLayout->setContentsMargins(0, 0, 0, 0);
    countLayout->setSpacing(2);
    productCountLabel = new QLabel();
    productCountLabel->setObjectName("productCount");
    QLabel* countSubtitle = new QLabel("Product catalog");
    countSubtitle->setObjectName("productCountSubtitle");
    countLayout->addWidget(productCountLabel);
    countLayout->addWidget(countSubtitle);
    toolbarLayout->addWidget(countContainer);
    toolbarLayout->addStretch();
    QPushButton* updateButton = new QPushButton("Edit");
    updateButton->setObjectName("secondaryButton");
    updateButton->setCursor(Qt::PointingHandCursor);
    QPushButton* deleteButton = new QPushButton("Delete");
    deleteButton->setObjectName("dangerButton");
    deleteButton->setCursor(Qt::PointingHandCursor);
    QPushButton* newProductButton = new QPushButton("+  New Product");
    newProductButton->setObjectName("primaryButton");
    newProductButton->setCursor(Qt::PointingHandCursor);
    toolbarLayout->addWidget(updateButton);
    toolbarLayout->addWidget(deleteButton);
    toolbarLayout->addSpacing(7);
    toolbarLayout->addWidget(newProductButton);
    layout->addWidget(toolbar);
    QFrame* listContainer = new QFrame();
    listContainer->setObjectName("productListContainer");
    QVBoxLayout* listLayout = new QVBoxLayout(listContainer);
    listLayout->setContentsMargins(7, 7, 7, 7);
    listLayout->setSpacing(0);
    QWidget* tableHeader = new QWidget();
    tableHeader->setObjectName("productTableHeader");
    tableHeader->setFixedHeight(40);
    QHBoxLayout* headerLayout = new QHBoxLayout(tableHeader);
    headerLayout->setContentsMargins(18, 0, 18, 0);
    QLabel* idHeader = new QLabel("ID");
    idHeader->setObjectName("tableHeaderLabel");
    idHeader->setFixedWidth(80);
    QLabel* nameHeader = new QLabel("PRODUCT");
    nameHeader->setObjectName("tableHeaderLabel");
    QLabel* priceHeader = new QLabel("PRICE");
    priceHeader->setObjectName("tableHeaderLabel");
    priceHeader->setFixedWidth(125);
    priceHeader->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerLayout->addWidget(idHeader);
    headerLayout->addWidget(nameHeader);
    headerLayout->addStretch();
    headerLayout->addWidget(priceHeader);
    listLayout->addWidget(tableHeader);
    productList = new QListWidget();
    productList->setObjectName("productList");
    productList->setSelectionMode(QAbstractItemView::SingleSelection);
    productList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    productList->setSpacing(2);
    productList->viewport()->installEventFilter(this);
    listLayout->addWidget(productList);
    layout->addWidget(listContainer, 1);
    connect(productList, &QListWidget::itemSelectionChanged, this, &MainWindow::updateProductSelection);
    connect(newProductButton, &QPushButton::clicked, this, &MainWindow::onNewProductClicked);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateProductClicked);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteProductClicked);
    refreshProductList();
    return page;
}
QWidget* MainWindow::createWipPage(const QString& title, const QString& description){
    QWidget* page = new QWidget();
    page->setObjectName("wipPage");
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(10);
    QLabel* icon = new QLabel("WIP");
    icon->setObjectName("wipIcon");
    icon->setAlignment(Qt::AlignCenter);
    QLabel* titleLabel = new QLabel(title);
    titleLabel->setObjectName("wipTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel* statusLabel = new QLabel("WORK IN PROGRESS");
    statusLabel->setObjectName("wipStatus");
    statusLabel->setAlignment(Qt::AlignCenter);
    QLabel* descriptionLabel = new QLabel(description);
    descriptionLabel->setObjectName("wipDescription");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setMaximumWidth(500);
    layout->addWidget(icon);
    layout->addSpacing(8);
    layout->addWidget(titleLabel);
    layout->addWidget(statusLabel);
    layout->addSpacing(5);
    layout->addWidget(descriptionLabel);
    return page;
}
void MainWindow::setCurrentPage(int index){
    if(pageStack == nullptr){
        return;
    }
    if(index < 0 || index >= pageStack->count()){
        return;
    }
    if(index == currentPageIndex){
        return;
    }
    currentPageIndex = index;
    const QStringList titles = {"Dashboard", "Products", "Orders", "Reception", "Stock", "Settings"};
    const QStringList subtitles = {"Overview of your warehouse activity", "Manage your product catalog", "Manage and track your orders", "Manage incoming stock", "Monitor your inventory", "Configure your application"};
    updatePageHeader(titles[index], subtitles[index]);
    searchInput->setVisible(index == 1);
    if(index != 1){
        searchInput->clear();
    }
    animatePageTransition(index);
}
void MainWindow::updatePageHeader(const QString& title, const QString& subtitle){
    if(pageTitle != nullptr){
        pageTitle->setText(title);
    }
    if(pageSubtitle != nullptr){
        pageSubtitle->setText(subtitle);
    }
}
void MainWindow::animatePageTransition(int index){
    QWidget* newPage = pageStack->widget(index);
    if(newPage == nullptr){
        return;
    }
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(newPage);
    newPage->setGraphicsEffect(effect);
    QPropertyAnimation* opacityAnimation = new QPropertyAnimation(effect, "opacity");
    opacityAnimation->setDuration(220);
    opacityAnimation->setStartValue(0.0);
    opacityAnimation->setEndValue(1.0);
    opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    pageStack->setCurrentWidget(newPage);
    opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(opacityAnimation, &QPropertyAnimation::finished, newPage, [newPage](){
        newPage->setGraphicsEffect(nullptr);
    });
}
void MainWindow::animateSidebarIndicator(QPushButton* button){
    if(activeIndicator == nullptr || button == nullptr){
        return;
    }
    QPropertyAnimation* animation = new QPropertyAnimation(activeIndicator, "geometry");
    animation->setDuration(180);
    animation->setStartValue(activeIndicator->geometry());
    animation->setEndValue(QRect(0, button->y() + (button->height() - activeIndicator->height()) / 2, 3, 26));
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void MainWindow::animateDashboardCards(){
    if(pageStack == nullptr){
        return;
    }
    QWidget* dashboard = pageStack->widget(0);
    if(dashboard == nullptr){
        return;
    }
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(dashboard);
    dashboard->setGraphicsEffect(effect);
    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(300);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, &QPropertyAnimation::finished, dashboard, [dashboard](){
        dashboard->setGraphicsEffect(nullptr);
    });
}
void MainWindow::refreshProductList(){
    if(productList == nullptr){
        return;
    }
    productList->clear();
    const std::vector<Product>& products = productManager.getProducts();
    for(std::size_t i = 0; i < products.size(); i++){
        QListWidgetItem* item = new QListWidgetItem();
        item->setData(Qt::UserRole, products[i].getId());
        ProductItemWidget* productWidget = new ProductItemWidget(products[i]);
        item->setSizeHint(QSize(0, 64));
        productList->addItem(item);
        productList->setItemWidget(item, productWidget);
    }
    if(productCountLabel != nullptr){
        QString countText = QString::number(products.size());
        productCountLabel->setText(countText + (products.size() == 1 ? " product" : " products"));
    }
}
void MainWindow::filterProducts(const QString& text){
    if(productList == nullptr){
        return;
    }
    QString searchText = text.trimmed();
    for(int i = 0; i < productList->count(); i++){
        QListWidgetItem* item = productList->item(i);
        if(item == nullptr){
            continue;
        }
        int productId = item->data(Qt::UserRole).toInt();
        Product* product = productManager.getProductById(productId);
        if(product == nullptr){
            item->setHidden(true);
            continue;
        }
        QString name = QString::fromStdString(product->getName());
        QString id = QString::number(product->getId());
        bool matches = searchText.isEmpty() || name.contains(searchText, Qt::CaseInsensitive) || id.contains(searchText, Qt::CaseInsensitive);
        item->setHidden(!matches);
    }
}
void MainWindow::onNewProductClicked(){
    ProductDialog dialog(productManager);
    if(dialog.exec() == QDialog::Accepted){
        refreshProductList();
    }
}
void MainWindow::onDeleteProductClicked(){
    if(productList == nullptr){
        return;
    }
    QListWidgetItem* selectedItem = productList->currentItem();
    if(selectedItem == nullptr){
        return;
    }
    int productID = selectedItem->data(Qt::UserRole).toInt();
    Product* product = productManager.getProductById(productID);
    if(product == nullptr){
        return;
    }
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Delete product");
    messageBox.setText("Delete \"" + QString::fromStdString(product->getName()) + "\"?");
    messageBox.setInformativeText("This action cannot be undone.");
    messageBox.setIcon(QMessageBox::Warning);
    QPushButton* deleteButton = messageBox.addButton("Delete", QMessageBox::AcceptRole);
    messageBox.addButton("Cancel", QMessageBox::RejectRole);
    messageBox.exec();
    if(messageBox.clickedButton() != deleteButton){
        return;
    }
    productManager.removeProduct(productID);
    refreshProductList();
}
void MainWindow::onUpdateProductClicked(){
    if(productList == nullptr){
        return;
    }
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
        refreshProductList();
    }
}
void MainWindow::updateProductSelection(){
    if(productList == nullptr){
        return;
    }
    for(int i = 0; i < productList->count(); i++){
        QListWidgetItem* item = productList->item(i);
        ProductItemWidget* productWidget = static_cast<ProductItemWidget*>(productList->itemWidget(item));
        if(productWidget != nullptr){
            productWidget->setSelected(item->isSelected());
        }
    }
}
bool MainWindow::eventFilter(QObject* object, QEvent* event){
    if(productList != nullptr && object == productList->viewport() && event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if(productList->itemAt(mouseEvent->position().toPoint()) == nullptr){
            productList->clearSelection();
        }
    }
    return QMainWindow::eventFilter(object, event);
}