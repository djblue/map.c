# map.c

[![Build Status](https://travis-ci.org/djblue/map.c.svg)](https://travis-ci.org/djblue/map.c)

Basic map written in c. There currently is no hash function because keys
are expected to be integers, although adding a hashing function would be
super simple; it just happened for my use case, I didn't need a hash
function.

NOTE: All values are expected to be pointers.

# building

To build the project, do:

    make

# test

All of the tests are in the `main.c` file.

To run all the test, do:

    make test

# methods

Below are all the supported methods of the hash map.

## map_create()

Will create and return a hash map with `MAP_NUM_BUCKET` buckets.

Example:

```c
map *m = map_create();
// use m
```

## map_create_n(n)

Will create and return a hash map with `1024` buckets.

```c
map *m = map_create_n(1024);
// use m
```

## map_free(m)

Will free a previously created map.

```c
map *m = map_create();
map_free(m);
```

## map_set(m, key, value)

Will set a key to the supplied value.

```c
int i = 1234;
// will store reference to i with key = 0.
map_set(m, 0, &i);
```

## map_unset(m, key)

Will remove key 0 from map.

```c
map_set(m, 0);
```

## map_get(m, key)

Get value for a given key from map m.

```c
map_get(m, 0);
```

## map_has(m, key)

Check if the map has a given key.

```c
map_has(m, 0);
```
