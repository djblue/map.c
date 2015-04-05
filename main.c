#include "test.h"
#include "map.h"

#include <stdio.h>

int main (int argc, char **argv) {

  begin("map#create()");
    map *m = map_create();
    assert(m->size == 0, "map initializes to size 0");
    assert(m->n == MAP_NUM_BUCKET, "correct # of buckets");
    map_free(m);
  end();

  begin("map#create_n()");
    map *m = map_create_n(1024);
    assert(m->size == 0, "map initializes to size 0");
    assert(m->n == 1024, "correct # of buckets");
    map_free(m);
  end();

  begin("map#set()");
    int i = 1024, j = 2046;
    map *m = map_create();

    map_set(m, 0, &i);
    assert(m->size == 1, "map maintains size correctly");
    assert(m->b[0]->value == &i, "map stores value correctly");

    map_set(m, MAP_NUM_BUCKET, &j);
    assert(m->b[0]->value == &j,
      "map collides but stores value correctly");
    assert(m->b[0]->next->value == &i,
      "map collides but stores value correctly");

    map_free(m);
  end();

  begin("map#unset()");
    int i = 1024, j = 2046;

    map *m = map_create();

    map_set(m, 0, &i);
    map_unset(m, 0);
    assert(m->size == 0, "map maintains size correctly");
    assert(m->b[0] == NULL, "map stores value correctly");

    map_set(m, 0, &i);
    map_set(m, MAP_NUM_BUCKET, &j);
    assert(m->size == 2, "map maintains size correctly");
    map_unset(m, 0);
    assert(m->size == 1, "map maintains size correctly");
    assert(m->b[0] != NULL, "map stores value correctly");
    assert(m->b[0]->value == &j, "map stores value correctly");
    map_unset(m, MAP_NUM_BUCKET);

    map_unset(m, -1);
    map_unset(m, 0);
    map_unset(m, 1);
    assert(m->size == 0, "unset is nop if key doesn't exist");

    map_free(m);
  end();

  begin("map#get()");
    int i = 2046;
    char *str = "2046";
    map *m = map_create();

    map_set(m, 0, &i);
    assert(map_get(m, 0) == &i, "map gets value correctly");

    map_set(m, MAP_NUM_BUCKET, str);
    assert(map_get(m, 0) == &i, "map doesn't clobber keys");
    assert(map_get(m, MAP_NUM_BUCKET) == str, "map gets value after collision");

    map_set(m, 2*MAP_NUM_BUCKET, str+1);
    assert(map_get(m, 2*MAP_NUM_BUCKET) == str + 1, "map doesn't clobber keys");

    map_free(m);
  end();

  begin("map#has()");
    int i = 2046;
    map *m = map_create();

    map_set(m, i, &i);
    assert(map_has(m, i) == 1, "map finds key when in map");
    assert(map_has(m, i+1) == 0, "map doesn't find key when not in map");
    assert(map_has(m, i-1) == 0, "map doesn't find key when not in map");

    map_set(m, i+1, &i);
    assert(map_has(m, i) == 1, "map finds key when in map");
    assert(map_has(m, i+1) == 1, "map finds key when in map");
    assert(map_has(m, i-1) == 0, "map doesn't find key when not in map");

    map_free(m);
  end();

  begin("performance");
    int value = 1234;
    map *m = map_create();
    for (int i = 0; i < 100000; i++) {
      map_set(m, i, &value);
      map_unset(m, i-1);
    }
  end();

  return 0;
}
