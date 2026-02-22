#include <stdio.h>
#include "../mk_input.h"

int main() {
    FILE * file = fopen("lipsum.txt", "r");
    
    // Create scanner on file stream with custom delimiters
    MkScanner sc = mk_scanner_create(file, " ;,.:?!\n");
    char buffer[512];
    
    while (true) {
        mk_scanner_get_string(&sc, buffer, sizeof(buffer));
        MkStatus status = mk_scanner_get_status(&sc);
        
        // Check for EOF
        if (status == MK_STATUS_EOF) {
            printf("Scanned All File Contents.\n");
            break;
        }
        
        // Check for error / other status
        if (status != MK_STATUS_OK) {
            printf("Status: %s\n", mk_status_get_string(status));
            break;
        }
        
        mk_scanner_clear_status(&sc);
        printf("[%s]\n", buffer);
    }
    
    fclose(file);
    return 0;
}