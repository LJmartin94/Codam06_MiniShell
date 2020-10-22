#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "libft/libft.h"


void vector_init(t_vector *v)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->len = 0;
    v->data = malloc(sizeof(void *) * v->capacity);
}

int vector_total(t_vector *v)
{
    return v->len;
}

static void vector_resize(t_vector *v, int capacity)
{
    // #ifdef DEBUG_ON
    // printf("vector_resize: %d to %d\n", v->capacity, capacity);
    // #endif

    void **data = ft_realloc(v->data, sizeof(void *) * capacity);
    if (data) {
        v->data = data;
        v->capacity = capacity;
    }
}

void vector_add(t_vector *v, void *item)
{
    if (v->capacity == v->len)
        vector_resize(v, v->capacity * 2);
    v->data[v->len++] = item;
}

void vector_set(t_vector *v, int index, void *item)
{
    if (index >= 0 && index < v->len)
        v->data[index] = item;
}

void *vector_get(t_vector *v, int index)
{
    if (index >= 0 && index < v->len)
        return v->data[index];
    return NULL;
}

void vector_delete(t_vector *v, int index)
{
    if (index < 0 || index >= v->len)
        return;

    v->data[index] = NULL;

    for (int i = index; i < v->len - 1; i++) {
        v->data[i] = v->data[i + 1];
        v->data[i + 1] = NULL;
    }

    v->len--;

    if (v->len > 0 && v->len == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

void vector_free(t_vector *v)
{
    free(v->data);
}