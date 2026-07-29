#ifndef MENU_H
#define MENU_H
#include <mysqlx/xdevapi.h>

class Menu{
private:
    void showAdminMenu(mysqlx::Session* session);

public:
    void showMainMenu();
};

#endif