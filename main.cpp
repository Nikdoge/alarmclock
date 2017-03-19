/*
 * File: main.c
 * Author: NIKDOG
 * Created on 17.12.2010 01:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "menu.h"

#define LANGUAGE 0 //0 - English, 1 - Russian (doesn't work currently(worked before(will be revived)))
#define VERSION "5.2"

using namespace std;

HWND GetConsoleHwnd();

char **setLanguage(boolean);

void log(char[]);

void log(char[], char[]);

void fnExit (void)
{
    log("Program ended work");
}

int main(void) {
    atexit(fnExit);
    cout << "Getting handler to current window to enable flashing";
    HWND handlerToWindow = GetConsoleHwnd();
    cout << " [OK]" << endl;
    //setlocale(LC_ALL, "Russian");
    cout << "Initializing language data";
    char **data = setLanguage(0);
    cout << " [OK]" << endl;
    cout << "Setting console name and background";
    system(data[0]);
    cout << " [OK]" << endl;
    cout << "Initializing time data";
    time_t timeT = time(NULL);
    cout << " [OK]" << endl;
    log("Program started work");

    do {
        int position = 0;
        char currentTime[7] = {0, 0, 0, 0, 0, 0, '\0'}; //%H%M%S
        char alarmTime[5] = {0, 0, 0, 0, '\0'}; //%H%M
        ifstream alarmSoundFile;

        char buffer; //key input
        do {
            system(data[1]);
            cout << data[3] << endl; //"In specified time Alarmclock starts"
            cout << data[4] << '\n' << endl; //"file 'alarm.mp3' from folder, where Alarmclock.exe is located"
            cout << data[5] << endl; //"Enter alarm time:"
            switch (position) {
                case 0:
                    cout << "_-:--";
                    break;
                case 1:
                    cout << alarmTime[0] << "_:--";
                    break;
                case 2:
                    cout << alarmTime[0] << alarmTime[1] << ":_-";
                    break;
                case 3:
                    cout << alarmTime[0] << alarmTime[1] << ':' << alarmTime[2] << "_";
                    break;
                case 4:
                    cout << alarmTime[0] << alarmTime[1] << ':' << alarmTime[2] << alarmTime[3];
                    break;
            }
            cout << "\n\n" << data[6] << '\n' << data[11] << endl;

            buffer = (char) getch();
            switch(buffer) {
                case 27: //Esc
                    delete[]data;
                    return 0;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if(position < 4) {
                        if ((position == 0 && buffer <= '2') ||
                            (position == 1 && (alarmTime[0] <= '1' || (alarmTime[0] == '2' && buffer <= '3'))) ||
                            (position == 2 && buffer <= '5') ||
                            (position > 2)) {
                            alarmTime[position] = buffer;
                            position++;
                        }
                    }
                    break;
                case 8:
                    if(position > 0) position--;
                    break;
                case 13:
                    if(position == 4) {
                        alarmSoundFile.open(data[2]); //try to open alarm.mp3 and what to do if can't
                        if (alarmSoundFile.is_open() == false) {
                            alarmSoundFile.close();
                            cout << '\n' << data[7] << endl; //"Error: can't find file 'alarm.mp3'!"
                            Sleep(1000);
                        } else position = -1; //if file is successfully opened, escape from cycle
                    }
                    break;
                case 'L':
                case 'l':
                case 132: //Д
                case 164: //д
                    system("start Alarmclock.log");
                    break;
                default:
                    break;
            }
            Sleep(40);
        } while (position >= 0);

        position = 0;
        timeT = time(&timeT);
        strftime(currentTime, 7, "%H%M%S", localtime(&timeT));

        log("Alarm set at ", alarmTime);

        do {
            if (kbhit()) {
                switch (getch()) {
                    case 32: //32 is Space
                        position = -1;
                        continue; //shifting to verification of cycle conditions
                    case 27: { //27 is Esc
                        delete[]data;
                        return 0;
                    }
                    default:
                        break;
                }
            }

            system(data[1]); //"cls"
            cout << data[8] << endl; //"System time:"

            timeT = time(&timeT);
            strftime(currentTime, 20, "%H%M%S", localtime(&timeT));

            cout << currentTime[0] << currentTime[1] << ':' << currentTime[2] << currentTime[3] << ':' <<
            currentTime[4] << currentTime[5] << '\n' << endl;
            cout << data[9] << endl; //"Alarm:"
            cout << alarmTime[0] << alarmTime[1] << ':' << alarmTime[2] << alarmTime[3] << '\n' << endl;

            if (currentTime[0] == alarmTime[0] && currentTime[1] == alarmTime[1] &&
                currentTime[2] == alarmTime[2] && currentTime[3] == alarmTime[3]) {
                cout << data[12] << endl; //"Activation..."

                alarmSoundFile.close();
                if(handlerToWindow != GetForegroundWindow())FlashWindow(handlerToWindow,true); //Window flashes

                log("Alarm rings"); //Logging
                system(data[2]); //"alarm.mp3"

                if(handlerToWindow != GetForegroundWindow())FlashWindow(handlerToWindow,false);
                break;
            }
            cout << data[10] << '\n' << data[11] << endl; //"Change alarm time \tSpace" "Exit program with \tEsc"
            Sleep(1000);
        } while (position >= 0);
    } while (true);
}

char **setLanguage(boolean showInterface) {
    int i;
    int dataSize = 13;
    char **data = new char *[dataSize];
    for (i = 0; i < dataSize; i++)
        data[i] = new char[80];

    if (LANGUAGE == 0) {
        //English
        data[3] = "In specified time Alarmclock starts";
        data[4] = "file 'alarm.mp3' from folder, where Alarmclock.exe is located";
        data[5] = "Enter alarm time:";
        data[6] = "After input press \tEnter";
        data[7] = "Error: can't find file 'alarm.mp3'!";
        data[8] = "System time: ";
        data[9] = "Alarm: ";
        data[10] = "Change alarm time \tSpace";
        data[11] = "Exit program with \tEsc";
        data[12] = "Activation...";
    } else {
        //Russian
        char **nativeData = new char *[dataSize];
        for (i = 3; i < dataSize; i++)
            nativeData[i - 3] = new char[80];

        nativeData[3] = "В заданное время Alarmclock запускает воспроизведение";
        nativeData[4] = "файла 'alarm.mp3' из папки, где расположен Alarmclock.exe";
        nativeData[5] = "Введите время будильника:";
        nativeData[6] = "После ввода нажмите \tEnter";
        nativeData[7] = "Ошибка: Невозможно найти файл 'alarm.mp3'!";
        nativeData[8] = "Системное время: ";
        nativeData[9] = "Будильник: ";
        nativeData[10] = "Задать новые данные \tПробел";
        nativeData[11] = "Выйти из программы \tEsc";
        nativeData[12] = "Активация...";
        for (i = 3; i < dataSize; i++)CharToOem(nativeData[i], data[i]);
        for(i=0;i<dataSize;i++)delete[]nativeData[i];
    }
    data[0] = "title Alarmclock 5.2 by Nikdoge&color f0";
    data[1] = "cls";
    data[2] = "alarm.mp3";

    return data;
}

void log(char message[], char alarmTime[]) {
    int currentTimeLength = 25;
    char currentTime[currentTimeLength];
    time_t timeT = time(NULL);
    strftime(currentTime, (size_t) currentTimeLength, "%Y-%m-%d %H:%M:%S", localtime(&timeT)); //%H:%M:%S

    ofstream file;
    file.open("Alarmclock.log", ios_base::app);
    if(file.is_open()) {
        file << '[';
        file << currentTime;
        file << ']' << ' ';
        file << message;
        file << alarmTime[0] << alarmTime[1] << ':' << alarmTime[2] << alarmTime[3];
        file << '\n';
    }
    file.close();
}

void log(char message[]) {
    int currentTimeLength = 25;
    char currentTime[currentTimeLength];
    time_t timeT = time(NULL);
    strftime(currentTime, (size_t) currentTimeLength, "%Y-%m-%d %H:%M:%S", localtime(&timeT)); //%H:%M:%S

    ofstream file;
    file.open("Alarmclock.log", ios_base::app);
    if(file.is_open()) {
        file << '[';
        file << currentTime;
        file << ']' << ' ';
        file << message;
        file << '\n';
    }
    file.close();
}

//Source: https://support.microsoft.com/en-us/kb/124103
HWND GetConsoleHwnd(void)
{
    int MY_BUFSIZE = 1024; // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
    // WindowTitle.
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
    // WindowTitle.

    // Fetch current window title.
    GetConsoleTitle(pszOldWindowTitle, (DWORD)MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.
    wsprintf(pszNewWindowTitle,"%d/%d",
             GetTickCount(),
             GetCurrentProcessId());

    // Change current window title.
    SetConsoleTitle(pszNewWindowTitle);

    // Ensure window title has been updated.
    Sleep(40);

    // Look for NewWindowTitle.
    hwndFound = FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.
    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
}

