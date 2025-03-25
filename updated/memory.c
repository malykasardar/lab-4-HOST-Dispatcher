#include "types.h"

// Define available_resources globally
Resources available_resources = {2, 1, 1, 2};

void init_resources() {
    available_resources.printers = 2;
    available_resources.scanners = 1;
    available_resources.modems = 1;
    available_resources.cds = 2;
}

int allocate_resources(Process *p) {
    if (available_resources.printers >= p->printers &&
        available_resources.scanners >= p->scanners &&
        available_resources.modems >= p->modems &&
        available_resources.cds >= p->cds) {
        available_resources.printers -= p->printers;
        available_resources.scanners -= p->scanners;
        available_resources.modems -= p->modems;
        available_resources.cds -= p->cds;
        return 1;
    }
    return 0;
}

void release_resources(Process *p) {
    available_resources.printers += p->printers;
    available_resources.scanners += p->scanners;
    available_resources.modems += p->modems;
    available_resources.cds += p->cds;
}
