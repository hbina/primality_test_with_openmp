//
// Created by hbina on 01/12/18.
//

#include "integer_primality_test.h"
#include <stdio.h>
#include <assert.h>

#define test_until_n 10

char serial_primality_test(long integer_n) {
    if (!(integer_n % 2l)) {
        return false;
    }
    long a = 3;
    while (integer_n % a && a < integer_n)a += 2l;
    return (char) (integer_n == a);
}

void verify_serial_primality_test() {
    for (long integer_n = 2; integer_n < test_until_n; integer_n += 2l) {
        assert(serial_primality_test(integer_n) == 0);
        serial_primality_test(integer_n);
    }
    assert(serial_primality_test(3) == true);
    assert(serial_primality_test(5) == true);
    assert(serial_primality_test(7) == true);
    assert(serial_primality_test(9) == false);
    assert(serial_primality_test(11) == true);
    assert(serial_primality_test(13) == true);
    assert(serial_primality_test(15) == false);
    assert(serial_primality_test(17) == true);
    assert(serial_primality_test(19) == true);
    assert(serial_primality_test(21) == false);
    printf("serial primality test verification tests passed\n");
}
