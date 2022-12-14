#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h> // для delay();
#include <windows.h>

void scroll(int direction, int lines, char l_row, char l_col, char r_row, char r_col, char attr)
{
    union REGS regs;
    if (direction)
    {
        regs.h.al = lines;  // Отступ вниз
        regs.h.ah = direction;  // Направление скроллинга [ 0 - очистка, 6 - вверх, 7 - вниз ]
    }
    else
    {
        regs.h.al = lines;
        regs.h.ah = 6;
    }
    regs.h.ch = l_row;  // Левый верхний угол y
    regs.h.cl = l_col;  // Левый верхний угол x
    regs.h.dh = r_row;  // Правый нижний угол y
    regs.h.dl = r_col;  // Правый нижний угол x
    regs.h.bh = attr;   // Цвет
    int86(0x10, &regs, &regs);
}

void getPrintColor(unsigned char colors)
{
    unsigned char bg = colors >> 4;   // Каждый раз получая число i сдвигаем побитово 4 [ там же 16 цветов ]
    unsigned char text = colors & 15; // Через побитовое И с 15, получаем число x которое всегда будет 0 <= x <= 15

    /*
        ************ Карта цветов **************

        BLACK Черный 0
        BLUE Синий 1
        GREEN Зеленый 2
        CYAN Сине-зеленый 3
        RED Красный 4
        MAGENTA Красно-синий 5
        BROWN Коричневый 6
        LIGHTGRAY Светло-серый 7
        DARKGRAY Темно-серый 8
        LIGHTBLUE Ярко-синий 9
        LIGHTGREEN Ярко-зеленый 10
        LIGHTCYAN Яркий сине-зеленый 11
        LIGHTRED Ярко-красный 12
        LIGHTMAGENTA Яркий красно-синий 13
        YELLOW Желтый 14
        WHITE Белый 15
    */

    /*
    // Просто каждый раз попадаем в один из case-ов и печатаем число цвет фон и текст
    switch (bg)     // Фон [ 8 цветов ]
    {
        case 0:
            cprintf("1 ");
            break;
        case 1:
            cprintf("2 ");
            break;
        case 2:
            cprintf("3 ");
            break;
        case 3:
            cprintf("4 ");
            break;
        case 4:
            cprintf("5 ");
            break;
        case 5:
            cprintf("6 ");
            break;
        case 6:
            cprintf("7 ");
            break;
        case 7:
            cprintf("8 ");
            break;
    }

    switch (text)   // Текст [ 16 цветов ]
    {
        case 0:
            cprintf("1 ");
            break;
        case 1:
            cprintf("2 ");
            break;
        case 2:
            cprintf("3 ");
            break;
        case 3:
            cprintf("4 ");
            break;
        case 4:
            cprintf("5 ");
            break;
        case 5:
            cprintf("6 ");
            break;
        case 6:
            cprintf("7 ");
            break;
        case 7:
            cprintf("8 ");
            break;
        case 8:
            cprintf("9 ");
            break;
        case 9:
            cprintf("10 ");
            break;
        case 10:
            cprintf("11 ");
            break;
        case 11:
            cprintf("12 ");
            break;
        case 12:
            cprintf("13 ");
            break;
        case 13:
            cprintf("14 ");
            break;
        case 14:
            cprintf("15 ");
            break;
        case 15:
            cprintf("16 ");
            break;
    }
    */

    cprintf("%i %i\r", bg + 1, text + 1);
}

int main()
{
    clrscr();                       // Чистка экрана
    window(25, 10, 55, 20);         // Установка окна вывода в консоле [ l_row, r_row, l_col, r_col ]
    textattr(112);                  // Устанавливает одновремено как цвет переднего плана, так и фона [ 112 (01110000) – инверсные цвета (черный на светлом) ]
    scroll(0, 0, 9, 24, 19, 54, 0); // Скроллиг сверху вниз
    for (int i = 0; i < 128; i++)   // т.к. 8 цветов фона + 16 цветов текста, всего 128 комбинациий, отсчет с 0 до 127
    {
        textattr(i);                    // Задаем цвет текста и фона
        cprintf("Well hello ");
        getPrintColor(i);               // Выводим значение цвета фона и текста
        delay(200);                     // Задержка в милисекудах 0.2 сек = 200 мсек итервал T сек
        scroll(7, 3, 9, 24, 19, 54, i); /* Cкроллиг
                                            [ 1st первое число - 6 (направлеие скроллига (7 обратно)),
                                            2nd второе число итервал S строк,
                                            все остальное одни меньше изначально заданного окна,
                                            по сути мы берем окно, строчку нижестоящую текущего окна,
                                            с теми же размерами и поднимаем место текущей ]
                                        */
    }
    clrscr();
    cprintf("\n\rThe program has been ends...\n\r");
    getch(); // Ожидаем нажатия любой клавиши
    return 0;
}
