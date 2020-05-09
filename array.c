#include <stdlib.h>
#include <stdio.h>
#include "array_void.h"

Array *create_array(int length)
{
  Array *array = malloc(sizeof(Array));
  array->length = length;
  array->array = malloc(sizeof(int) * length);
  return array;
}

ArrayVoid_ptr create_void_array(int length)
{
  ArrayVoid_ptr array = malloc(sizeof(ArrayVoid));
  array->length = length;
  array->array = malloc(sizeof(Object) * length);
  return array;
}

void copy_values(int *from, Array *to)
{
  for (int i = 0; i < to->length; i++)
  {
    to->array[i] = from[i];
  }
}

void copy_void_values(void **from, ArrayVoid_ptr to)
{
  for (int i = 0; i < to->length; i++)
  {

    to->array[i] = from[i];
  }
}

ArrayVoid_ptr map_void(ArrayVoid_ptr src, MapperVoid mapper)
{
  ArrayVoid_ptr result = create_void_array(src->length);
  for (int i = 0; i < src->length; i++)
  {
    result->array[i] = mapper(src->array[i]);
  }
  return result;
}

Array *map(Array *src, Mapper mapper)
{
  Array *result = create_array(src->length);
  for (int i = 0; i < src->length; i++)
  {
    result->array[i] = mapper(src->array[i]);
  }
  return result;
}

ArrayVoid_ptr filter_void(ArrayVoid_ptr src, PredicateVoid predicator)
{
  void *result[src->length];
  int length_of_result = 0;
  for (int value_count = 0; value_count < src->length; value_count++)
  {
    if (predicator(src->array[value_count]))
    {
      result[length_of_result] = src->array[value_count];
      ++length_of_result;
    }
  }
  ArrayVoid_ptr filtered_values = create_void_array(length_of_result);
  copy_void_values(result, filtered_values);
  return filtered_values;
}

Array *filter(Array *src, Predicate predicator)
{
  int result[src->length];
  int length_of_result = 0;
  for (int value_count = 0; value_count < src->length; value_count++)
  {
    if (predicator(src->array[value_count]))
    {
      result[length_of_result] = src->array[value_count];
      ++length_of_result;
    }
  }
  Array *filtered_values = create_array(length_of_result);
  copy_values(result, filtered_values);
  return filtered_values;
}

int reduce(Array *src, int initial_value, Reducer reducer)
{
  int reduced_value = initial_value;
  for (int i = 0; i < src->length; i++)
  {
    reduced_value = reducer(src->array[i], reduced_value);
  }
  return reduced_value;
}