#include <stdlib.h>
#include "array.h"

Array *create_array(int length)
{
  Array *array = malloc(sizeof(Array));
  array->length = length;
  array->array = malloc(sizeof(int) * length);
  return array;
}

void copy_values(int *from, Array *to)
{
  for (int i = 0; i < to->length; i++)
  {
    to->array[i] = from[i];
  }
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