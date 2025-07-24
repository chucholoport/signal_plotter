#include <stdio.h>

void setup() {
    printf("Setup executed.\n");
}

void loop() {
    printf("Loop running...\n");
}

int main(void) {
    setup();
    while (1) {
        loop();
        break; // evita bucle infinito por ahora
    }
    return 0;
}