#ifndef SET_H
#define SET_H
#include "./doublelinkedlist.h"
#include <stdlib.h>

typedef DList Set;

// public
void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));

#define set_destroy dlist_destroy

int set_insert(Set *set, const void *data);
int set_remove(Set *set, void **data);
int set_union(Set *setu, const Set *set1, const Set *set2);
int set_intersection(Set *seti, const Set *set1, const Set *set2);
int set_difference(Set *setd, const Set *set1, const Set *set2);
int set_difference(Set *setd, const Set *set1, const Set *set2);
int set_is_member(const Set *set, const void *data);
int set_is_subset(const Set *set1, const Set *set2);
int set_is_equal(const Set *set1, const Set *set2);
void *set_get_member(Set *set, const void *data);

#define set_size(set) ((set)->size)

#endif // SET_H