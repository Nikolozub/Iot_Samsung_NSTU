#include "mbed.h"

#define RELAY_ON 0
#define RELAY_OFF 1

DigitalOut relay(D8);
DigitalOut led(LED1);
DigitalIn btns[] = { DigitalIn(D3), DigitalIn(D4), DigitalIn(D5), DigitalIn(D6) };


const char keybtn[] = { '1', '2', '3', '4' };
bool pushbtn[] = { false, false, false, false };

const char password[] = "1234";
const int psize = (sizeof(password) - 1) / sizeof(char);
int curr = 0;

void unlock();
void checkbtn(int i);

int main()
{
    for (int i = 0; i < 4; ++i)
        btns[i].mode(PullUp);

    while (true) {
        relay = RELAY_OFF;
        led = 1;
        for (int i = 0; i < 4; ++i) {
            if (btns[i] == 0 && !pushbtn[i]) {
                printf("%c\r\n", keybtn[i]);
                checkbtn(i);
                pushbtn[i] = true;
                wait_ms(50);
            }
            else if (btns[i] == 1 && pushbtn[i]) {
                pushbtn[i] = false;
                wait_ms(50);
            }
        }
    }
}

void unlock() {
    relay = RELAY_ON;
    printf("door is open!\r\n");
    for (int i = 0; i < 20; ++i) {
        led = !led;
        wait_ms(500);
    }
}

void checkbtn(int i) {
    if (keybtn[i] == password[curr]) {
        ++curr;
        if (curr >= psize) {
            unlock();
            curr = 0;
        }
    } else {
        curr = 0;
    }
}