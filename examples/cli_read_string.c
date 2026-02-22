#include <stdio.h>
#include "../mk_input.h"

int main() {
    // Create scanner struct
    // Reads from stdin, delimiter is all whitespace
    MkScanner sc = mk_scanner_create_default();
    char buffer[128];
    
    // Scan for string
    const size_t length = mk_scanner_get_string(&sc, buffer, sizeof(buffer));
    
    // Get only the first token, discard the rest
    mk_scanner_clear_input(&sc);
    
    // Get Status Of Last Operation
    MkStatus status = mk_scanner_get_status(&sc);
    
    // Get textual representation of status
    printf("Status: %s\n", mk_status_get_string(status));
    if (status != MK_STATUS_OK) {
        return 1;
    }
    printf("Length: %zu\n", length);
    printf("String: [%s]\n", buffer);
    return 0;
}