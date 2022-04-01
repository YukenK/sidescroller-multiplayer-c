#include "vector.h"
#define LOOPLEN 100
typedef struct {
    int x;
    void* test;
} TestStruct;
int main() {
    Vector numbers;
    Vector structs;
    init_vector(&numbers, LOOPLEN, sizeof(int));
    init_vector(&structs, LOOPLEN, sizeof(TestStruct));
    return 0;
}