#include "common.h"
#include "user.h"
int prime(int n, int d) {
    if (n <= 1) {
        return 0; 
    }
    if (d == 1) {
        return 1; 
    }
    if (mod(n,d) == 0) {
        return 0; 
    }
    return prime(n, d - 1); 
}

void list(int n) {
    if (n > 1) {
        list(n - 1);
        if (prime(n, n - 1)) {
            putint(n);
            puts("\n");
        }
    }
}

int main() {
    list(100);
    exit();
}