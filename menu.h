/*
 * File: menu.h
 * Author: NIKDOG
 * Created on 01.12.2011 19:55
 */

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

using namespace std;

class UMenu {
    char **title;
    int count;
public:
    UMenu();

    UMenu(int);

    void InitElements(int);

    void AddElementTitle(int, char *);

    int ShowMenu();

    ~UMenu();
};

#endif // MENU_H_INCLUDED

