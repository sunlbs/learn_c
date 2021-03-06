/*
    dmp…檔案的排出
*/

#include  <ctype.h>
#include  <stdio.h>

/*--- 將串流src的內容排出到dst�v ---*/
void dump(FILE* src, FILE* dst) {
    int            n;
    unsigned long  count = 0;
    unsigned char  buf[16];

    while ((n = fread(buf, 1, 16, src)) > 0) {
        int  i;

        fprintf(dst, "%08lX ", count);                      /* 位址 */

        for (i = 0; i < n; i++) {                           /* 16進位數 */
            fprintf(dst, "%02X ", (unsigned)buf[i]);
        }

        if (n < 16)
            for (i = n; i < 16; i++) {
                fputs("   ", dst);
            }

        for (i = 0; i < n; i++) {                           /* 字元 */
            fputc(isprint(buf[i]) ? buf[i] : '.', dst);
        }

        fputc('\n', dst);

        count += 16;
    }

    fputc('\n', dst);
}

int main(int argc, char* argv[]) {
    FILE*  fp;

    if (argc < 2) {
        fputs("請指定檔案。\n", stderr);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "rb")) == NULL) {
                fprintf(stderr, "檔案%s無法開啟。\n", *argv);
                return (1);
            } else {
                dump(fp, stdout);    /* 串流fp→標準輸出 */
                fclose(fp);
            }
        }
    }

    return (0);
}
