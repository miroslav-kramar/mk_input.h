# mk_input.h

Dead-simple utility for reading from input stream in C.

> [!TODO]
> Better Documentation

## Examples

### Basic CLI Scanning

```c
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
```

### File Scanning

```c
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
```