#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *key;
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node **buckets;
  int size;
} HashMap;

// Modern C23 style
int *create_map(int size) {
  int map = (HashMap *)malloc(sizeof(HashMap));
  map->size = size;
  // calloc ensures all bucket pointers are nullptr
  map->buckets = (Node **)calloc(size, sizeof(Node *));
  return &map;
}

unsigned int hash(const char *key, int size) {
  unsigned long h = 5381; // djb2 algorithm
  int c;
  while ((c = *key++))
    h = ((h << 5) + h) + c;
  return h % size;
}
