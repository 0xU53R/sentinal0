#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -----------------------------
// STRUCT: Event model
// -----------------------------
typedef struct {
    char ip[20];
    int port;
    int connections;
} Event;

// -----------------------------
// LOG FUNCTION
// -----------------------------
void log_event(Event e, FILE *logFile) {
    fprintf(logFile, "%s | PORT:%d | CONN:%d\n",
            e.ip, e.port, e.connections);
    fflush(logFile);
}

// -----------------------------
// DETECTION ENGINE
// -----------------------------
int analyze_event(Event e) {
    int risk = 0;

    // Rule 1: Too many connections
    if (e.connections > 20) {
        risk += 60;
    }

    // Rule 2: SSH brute force hint
    if (e.port == 22 && e.connections > 10) {
        risk += 30;
    }

    // Rule 3: High ports slightly suspicious
    if (e.port > 10000) {
        risk += 10;
    }

    return risk;
}

// -----------------------------
// SIMULATE EVENT GENERATION
// -----------------------------
Event generate_event() {
    Event e;

    // Fake IP pool
    char *ips[] = {
        "192.168.1.10",
        "192.168.1.15",
        "10.0.0.5",
        "8.8.8.8"
    };

    strcpy(e.ip, ips[rand() % 4]);
    e.port = (rand() % 65535) + 1;
    e.connections = rand() % 50;

    return e;
}

// -----------------------------
// MAIN LOOP
// -----------------------------
int main() {
    srand(time(NULL));

    FILE *logFile = fopen("sentinel.log", "a");

    if (!logFile) {
        printf("Error opening log file\n");
        return 1;
    }

    printf("🛡️ Sentinel C Engine Started...\n\n");

    for (int i = 0; i < 20; i++) {
        Event e = generate_event();

        int risk = analyze_event(e);

        log_event(e, logFile);

        printf("IP: %s | Port: %d | Conn: %d | Risk: %d\n",
               e.ip, e.port, e.connections, risk);

        if (risk >= 70) {
            printf("⚠️ ALERT: High-risk activity detected!\n\n");
        }

        // small delay simulation
        for (volatile long j = 0; j < 100000000; j++);
    }

    fclose(logFile);

    printf("\n✔ Sentinel finished execution.\n");

    return 0;
}
