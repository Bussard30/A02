#include <stdio.h>
#include <stdbool.h>

int n;
int m;
int k;

bool debug = true;

int next(FILE *f) {
    int i;
    fscanf(f, "%d", &i);
    return i;
}

void skipLine(FILE *filebuf) {
    fscanf(filebuf, "%*[^\n]\n");
    if(debug) printf("-");
}

void skipNumbers(FILE *filebuf, int _n) {
    if(debug)printf("|%d", _n);
    for (int i = 0; i < _n; i++) {
        next(filebuf);
    }
    if(debug)printf("|");
}

FILE *goToA(int _n, bool print_debug) {
    if (print_debug && debug) { printf("A(%d", _n); }
    FILE *filebuf = fopen("..\\\\input.txt", "r+");
    //skips initial n k m
    skipLine(filebuf);
    // skips all lines before a_n
    for (int i = 0; i < _n; i++) {
        skipLine(filebuf);
    }
    if (print_debug && debug) { printf(")"); }
    return filebuf;
}

FILE *goToB0(int _n) {
    _n += 1;
    if(debug)printf("B(%d", _n);
    FILE *filebuf = fopen("..\\\\input.txt", "r+");
    goToA(n - 1, false);
    //skips last a_n
    skipLine(filebuf);
    //skips empty line
    skipLine(filebuf);
    for (int i = 0; i < _n; i++) {
        skipLine(filebuf);
    }
    if(debug)printf(")");
    return filebuf;
}


void calculateMatrixProduct() {
    //initialize file
    FILE *fp = fopen("..\\\\input.txt", "r+");
    n = next(fp);
    k = next(fp);
    m = next(fp);
    if(debug)printf("%d,", n);
    if(debug)printf("%d,", m);
    if(debug)printf("%d\n", k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(debug)printf("C{{");
            int sum = 0;
            FILE *fa = goToA(i, true);
            for (int _k = 0; _k < k; _k++) {
                int na = next(fa);
                FILE *fb = goToB0(_k);
                skipNumbers(fb, j);
                int ba = next(fb);
                if(debug)printf("%d * %d", na, ba);
                sum += na * ba;
            }
            if(debug)printf("}}");
            printf("%d ", sum);
        }
        printf("\n");
    }

    //close file
    fclose(fp);
}

int main() {
    calculateMatrixProduct();
    return 0;
}


