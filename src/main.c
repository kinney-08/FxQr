
#include "fxlib.h"
// #include "stdio.h"
// #include "string.h"
// #include "math.h"

/*
 * Copyright (c) 2012-2014 Pavol Rusnak <stick@gk2.sk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int k, len = 0;
    int i;
    char str[300] = "", low = 0;
    char cap[] = {'A', 0, 'a', 0};

    while (1)
    {
        Bdisp_AllClr_VRAM();
        locate(1, 1);
        Print((unsigned char *)"FxQR");
        for (i = 0; i <= len / 21; i++)
        {
            locate(1, 2 + i);
            Print(str + i * 21);
        }
        locate(17, 8);
        Print((unsigned char *)(cap + low));
        GetKey(&k);
        if (k >= 0x20 && k <= 0xb9 && len < 120)
        {
            if (low && k >= 'A' && k <= 'Z')
            {
                k += 0x20;
            }
            if (k == 0x89)
                k = '+';
            if (k == 0x99)
                k = '-';
            if (k == 0xa8)
                k = '^';
            if (k == 0xa9)
                k = '*';
            if (k == 0xb9)
                k = '/';
            str[len++] = k;
            str[len] = 0;
        }
        if (k == KEY_CTRL_DEL && len > 0)
        {
            len--;
            str[len] = 0;
        }
        if (k == KEY_CTRL_AC)
        {
            for (i = 0; i < len; i++)
            {
                str[i] = 0;
            }
            len = 0;
        }
        if (k == KEY_CTRL_EXE)
        {
            Bdisp_AllClr_VRAM();
            parseMessage(str, 0);
            while (1)
            {
                GetKey(&k);
                if (k == KEY_CTRL_EXIT || k == KEY_CTRL_AC)
                    break;
            }
        }
        if (k == KEY_CTRL_F5)
        {
            low = 2 - low;
        }
        if (k == KEY_CTRL_F6)
        {
            Bdisp_AllClr_VRAM();
            locate(1, 1);
            Print((unsigned char *)"About");
            locate(1, 2);
            Print((unsigned char *)"Orig:github.com");
            locate(5, 3);
            Print((unsigned char *)"/bjguillot/qr");
            locate(1, 4);
            Print((unsigned char *)"ModifiedBy 1149761294");
            GetKey(&k);
        }
    }
    return 1;
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP

int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section
