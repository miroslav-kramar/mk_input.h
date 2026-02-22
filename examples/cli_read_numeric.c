#include <stdio.h>
#include "../mk_input.h"

int main() {
    MkScanner sc = mk_scanner_create_default();
    
    while (true) {
        // We have functions for every native type
        const int n = mk_scanner_get_int(&sc);
        mk_scanner_clear_input(&sc);
        const MkStatus status = mk_scanner_get_status(&sc);
        
        printf("Status: %s\n", mk_status_get_string(status));
        printf("Number: %d\n", n);
        printf("\n");
        
        if (status != MK_STATUS_OK) {
            mk_scanner_clear_status(&sc);
            continue;
        }
        if (n == 0) {
            break;
        }
    }
    
    return 0;
}