#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "hash.h"

int main(void) {
    HashTable *t = ht_create();
    int found;
    size_t expected = 0;

    assert(t != NULL);
    assert(ht_size(t) == 0);

    assert(ht_get(t, 4177, &found) == 0 && found == 0);
    assert(ht_contains(t, 4177) == 0);
    assert(ht_remove(t, 4177) == 0);

    ht_put(t, 4177, 8123);   expected++;
    ht_put(t, 4209, 90311);  expected++;
    ht_put(t, 4193, -4402);  expected++;
    assert(ht_size(t) == expected);
    assert(ht_get(t, 4177, &found) == 8123 && found == 1);
    assert(ht_get(t, 4209, &found) == 90311 && found == 1);
    assert(ht_get(t, 4193, &found) == -4402 && found == 1);

    assert(ht_remove(t, 4209) == 1);  expected--;
    assert(ht_remove(t, 4209) == 0);
    assert(ht_contains(t, 4209) == 0);
    assert(ht_get(t, 4177, &found) == 8123 && found == 1);
    assert(ht_get(t, 4193, &found) == -4402 && found == 1);

    assert(ht_remove(t, 4193) == 1);  expected--;
    assert(ht_remove(t, 4177) == 1);  expected--;
    assert(ht_size(t) == 0);
    assert(expected == 0);

    ht_put(t, 4177, 555);  expected++;
    assert(ht_get(t, 4177, &found) == 555 && found == 1);

    ht_put(t, 731, 12);     expected++;
    ht_put(t, 2906, 400);   expected++;
    ht_put(t, 58, -73);     expected++;
    assert(ht_size(t) == expected);
    assert(ht_remove(t, 2906) == 1);  expected--;
    assert(ht_get(t, 58, &found) == -73 && found == 1);
    assert(ht_get(t, 731, &found) == 12 && found == 1);
    assert(ht_contains(t, 2906) == 0);

    ht_put(t, 6613, 0);  expected++;
    assert(ht_get(t, 6613, &found) == 0 && found == 1);
    assert(ht_contains(t, 6613) == 1);

    ht_put(t, 6613, -29);
    assert(ht_get(t, 6613, &found) == -29 && found == 1);
    assert(ht_size(t) == expected);

    ht_put(t, INT_MAX, 19);    expected++;
    ht_put(t, INT_MIN, -23);   expected++;
    ht_put(t, 0, 7);           expected++;
    ht_put(t, -8841, 5150);    expected++;
    assert(ht_size(t) == expected);
    assert(ht_get(t, INT_MAX, &found) == 19 && found == 1);
    assert(ht_get(t, INT_MIN, &found) == -23 && found == 1);
    assert(ht_get(t, 0, &found) == 7 && found == 1);
    assert(ht_get(t, -8841, &found) == 5150 && found == 1);

    for (int i = 0; i < 617; i++) {
        ht_put(t, 9000 + 13 * i, i * 31 - 4000);
        expected++;
    }
    assert(ht_size(t) == expected);
    for (int i = 0; i < 617; i++) {
        assert(ht_get(t, 9000 + 13 * i, &found) == i * 31 - 4000);
        assert(found == 1);
    }
    for (int i = 0; i < 617; i += 3) {
        assert(ht_remove(t, 9000 + 13 * i) == 1);
        expected--;
    }
    assert(ht_size(t) == expected);
    for (int i = 0; i < 617; i++) {
        if (i % 3 == 0) {
            assert(ht_contains(t, 9000 + 13 * i) == 0);
        } else {
            assert(ht_get(t, 9000 + 13 * i, &found) == i * 31 - 4000);
            assert(found == 1);
        }
    }

    assert(ht_get(t, 4177, &found) == 555 && found == 1);
    assert(ht_get(t, INT_MIN, &found) == -23 && found == 1);

    ht_destroy(t);
    ht_destroy(NULL);
    printf("test2: all checks passed\n");
    return 0;
}
