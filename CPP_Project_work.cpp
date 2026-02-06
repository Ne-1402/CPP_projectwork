#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

string digits[10][5] = {
    {" ### ", "#   #", "#   #", "#   #", " ### "},  // 0
    {"  #  ", " ##  ", "  #  ", "  #  ", "#####"},  // 1
    {" ### ", "#   #", "   # ", "  #  ", "#####"},  // 2
    {" ### ", "#   #", "  ## ", "#   #", " ### "},  // 3
    {"#   #", "#   #", "#####", "    #", "    #"},  // 4
    {"#####", "#    ", "#### ", "    #", "#### "},  // 5
    {" ### ", "#    ", "#### ", "#   #", " ### "},  // 6
    {"#####", "    #", "   # ", "  #  ", " #   "},  // 7
    {" ### ", "#   #", " ### ", "#   #", " ### "},  // 8
    {" ### ", "#   #", " ####", "    #", " ### "}   // 9
};

string colon[5] = {"  ", " #", "  ", " #", "  "};

void displayDigitalClock(int h, int m, int s) {
    cout << "\033[2J\033[1;1H";
    
    int d1 = h / 10;
    int d2 = h % 10;
    int d3 = m / 10;
    int d4 = m % 10;
    int d5 = s / 10;
    int d6 = s % 10;
    
    cout << "\n\n";
    for (int i = 0; i < 5; i++) {
        cout << "    " << digits[d1][i] << " " << digits[d2][i] << "  " << colon[i] 
             << "  " << digits[d3][i] << " " << digits[d4][i] << "  " << colon[i]
             << "  " << digits[d5][i] << " " << digits[d6][i] << endl;
    }
    cout << "\n\n";
}

void showAlarm() {
    for (int i = 0; i < 5; i++) {
        cout << "\033[2J\033[1;1H";
        cout << "\n\n\n";
        cout << "    #####  #####  #   #  #####       #   #  ####   #  \n";
        cout << "      #      #    ## ##  #           #   #  #   #  #  \n";
        cout << "      #      #    # # #  #####       #   #  ####   #  \n";
        cout << "      #      #    #   #  #           #   #  #      #  \n";
        cout << "      #    #####  #   #  #####        ###   #      #  \n";
        cout << "\n\n";
        cout << "           **** ALARM! ALARM! ALARM! ****\n\n";
        sleep(1);
        
        cout << "\033[2J\033[1;1H";
        cout << "\n\n\n";
        cout << "    ##### ##### #   # #####       #   # ####  # \n";
        cout << "      #     #   ## ## #           #   # #   # # \n";
        cout << "      #     #   # # # #####       #   # ####  # \n";
        cout << "      #     #   #   # #           #   # #     # \n";
        cout << "      #   ##### #   # #####        ###  #     # \n";
        cout << "\n\n";
        cout << "           ****                    ****\n\n";
        sleep(1);
    }
}

int main() {
    int choice;
    int h, m, s;
    
    cout << "Digital Clock\n";
    cout << "=============\n";
    cout << "1. System Time\n";
    cout << "2. Start from 00:00:00\n";
    cout << "3. Custom Time\n";
    cout << "4. Timer (Countdown)\n";
    cout << "Enter choice: ";
    cin >> choice;
    
    if (choice == 1) {
        while (true) {
            time_t now = time(0);
            tm *t = localtime(&now);
            h = t->tm_hour;
            m = t->tm_min;
            s = t->tm_sec;
            
            displayDigitalClock(h, m, s);
            sleep(1);
        }
    }
    else if (choice == 2) {
        h = 0;
        m = 0;
        s = 0;
    }
    else if (choice == 3) {
        cout << "Enter hours (0-23): ";
        cin >> h;
        cout << "Enter minutes (0-59): ";
        cin >> m;
        cout << "Enter seconds (0-59): ";
        cin >> s;
    }
    else if (choice == 4) {
        cout << "Enter timer hours: ";
        cin >> h;
        cout << "Enter timer minutes: ";
        cin >> m;
        cout << "Enter timer seconds: ";
        cin >> s;
        
        while (true) {
            displayDigitalClock(h, m, s);
            
            if (h == 0 && m == 0 && s == 0) {
                showAlarm();
                break;
            }
            
            sleep(1);
            
            s--;
            if (s < 0) {
                s = 59;
                m--;
                if (m < 0) {
                    m = 59;
                    h--;
                    if (h < 0) {
                        h = 0;
                        m = 0;
                        s = 0;
                    }
                }
            }
        }
        return 0;
    }
    else {
        cout << "Invalid choice!\n";
        return 1;
    }
    
    if (choice == 2 || choice == 3) {
        while (true) {
            displayDigitalClock(h, m, s);
            sleep(1);
            
            s++;
            if (s == 60) {
                s = 0;
                m++;
                if (m == 60) {
                    m = 0;
                    h++;
                    if (h == 24) {
                        h = 0;
                    }
                }
            }
        }
    }
    
    return 0;
}