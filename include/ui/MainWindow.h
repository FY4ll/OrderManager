#pragma once
#include <QMainWindow>
#include "models/ProductsManager.h"
class QListWidget;
class QStackedWidget;
class QLineEdit;
class QLabel;
class QPushButton;
class QListWidgetItem;
class QEvent;
class QObject;
class QFrame;

class MainWindow : public QMainWindow{
    public:
        explicit MainWindow(ProductManager& productManager);
    private:
        ProductManager& productManager;
        QStackedWidget* pageStack;
        QLineEdit* searchInput;
        QLabel* pageTitle;
        QLabel* pageSubtitle;
        QLabel* productCountLabel;
        QListWidget* productList;
        QFrame* activeIndicator;
        int currentPageIndex;
        void setupUi();
        void setupSidebar();
        void setupHeader();
        void setupPages();
        QWidget* createDashboardPage();
        QWidget* createProductsPage();
        QWidget* createWipPage(const QString& title, const QString& description);
        QPushButton* createSidebarButton(const QString& text, int pageIndex);
        void setCurrentPage(int index);
        void updatePageHeader(const QString& title, const QString& subtitle);
        void updateSidebarSelection(int pageIndex);
        void animatePageTransition(int index);
        void animateSidebarIndicator(QPushButton* button);
        void animateDashboardCards();
        void refreshProductList();
        void filterProducts(const QString& text);
        void onNewProductClicked();
        void onDeleteProductClicked();
        void onUpdateProductClicked();
        void updateProductSelection();
    protected:
        bool eventFilter(QObject* object, QEvent* event) override;
};