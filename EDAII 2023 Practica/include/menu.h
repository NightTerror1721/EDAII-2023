#ifndef __MENUS_H__
#define __MENUS_H__

#include "user.h"
#include "user_list.h"


void show_main_menu(UsersList* users);

void show_user_menu(UsersList* users);

void show_fill_user_data_menu(User* user);

void show_unknown_friends_menu(User* current_user, const UsersList* users);


#endif //__MENUS_H__
