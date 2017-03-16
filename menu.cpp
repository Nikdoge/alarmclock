#include "menu.h"

UMenu::UMenu() {

}

UMenu::UMenu(int inCount) {
    count = inCount;
    title = new char *[count];
    for (int i = 0; i < count; i++)
        title[i] = new char[255];
    for (int i = 0; i < count; i++)
        title[i] = "none";
}

void UMenu::InitElements(int inCount) {
    count = inCount;
    title = new char *[count];
    for (int i = 0; i < count; i++)
        title[i] = new char[255];
    for (int i = 0; i < count; i++)
        title[i] = "none";
}

void UMenu::AddElementTitle(int number, char *inTitle) {
    title[number] = inTitle;
}

int UMenu::ShowMenu() {
    system("cls");
    int position = 0;
    while (1) {
        system("cls");
        for (int i = 0; i < count; i++) {
            if (position == i)cout << ' ' << (char) 26 << ' ' << i + 1 << ". " << title[i] << endl; //26 is ->
            else cout << "   " << i + 1 << ". " << title[i] << endl;
        }
        switch (getch()) {
            case 224: { //224 is first part of complex key codes
                if (kbhit()) {
                    switch (getch()) {
                        case 72: //72 is arrow up
                            position--;
                            break;
                        case 80: //80 is arrow down
                            position++;
                            break;
                    }
                }
            }
                break;
            case 13: //13 is Enter
                system("cls");
                return position;
        }
        if (position > count - 1)position = 0;
        if (position < 0)position = count - 1;
    }
}

UMenu::~UMenu() {
    free(title);
}

