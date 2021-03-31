#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn Up(D10);
DigitalIn Down(D11);
DigitalIn Select(D12);
uLCD_4DGL uLCD(D1, D0, D2);
AnalogOut wave_out(D7);
AnalogIn sample_wave(A5);
Thread thread;
float ADCdata[500];

void sample(void)
{
    for(int i = 0; i < 500; i++) {
        ADCdata[i] = sample_wave;
        ThisThread::sleep_for(2ms);
    }
    for (int i = 0; i < 500; i++) {
        printf("%f\r\n", ADCdata[i]);
    }
}

int main()
{
    int freq = 826;
    int i, j;
    double T, up_time, down_time, amp;      // T means the period of triangular wave.
                                            // up_time means the time of the upward region of one period. 

    wave_out = 0;

    i = ((SIZE_X / 5) - 6) / 2 - 1;
    j = ((SIZE_Y / 7) - 1) / 2 - 1;

    uLCD.background_color(WHITE);
    uLCD.cls();
    uLCD.textbackground_color(WHITE);
    uLCD.color(BLACK);
    uLCD.set_font(FONT_5X7);
    uLCD.locate(i, j);
    uLCD.printf("%d Hz", freq);

    while(1) {
        if (Up == 1) {
            if (freq > 900)
                freq = 126;
            else
                freq += 100;
            uLCD.cls();
            uLCD.locate(i, j);
            uLCD.printf("%d Hz", freq);
            ThisThread::sleep_for(500ms);
        }
        else if (Down == 1) {
            if (freq < 200)
                freq = 826;
            else
                freq -= 100;
            uLCD.cls();
            uLCD.locate(i, j);
            uLCD.printf("%d Hz", freq);
            ThisThread::sleep_for(500ms);
        }
        if (Select == 1)
            break;
    }

    T = 1 / (double)freq;
    up_time = T / 5;
    down_time = (T / 5) * 4;
    amp = 3 / 3.3;

    thread.start(sample);

    while(1) {
        for(float a = 0.0; a < amp; a += amp / (up_time / 0.0000241)) {     // we try and error and find out that 0.0000237 is the best value.
            wave_out = a;
        }
        for(float b = amp; b > 0; b -= amp / (down_time / 0.0000241)) {
            wave_out = b;
        }
    }
}