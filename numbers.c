#include <stdio.h>
#include <stdlib.h>
#include "array_void.h"
typedef void (*DisplayData)(ArrayVoid_ptr);
Bool is_even(int number);
void display(Array *arr);
int product(int num1, int num2);
int add_one(int number)
{

  return number + 1;
}
void *add_one_void(void *num)
{
  *(int *)&num += 1;
  return num;
}

Bool is_even(int number)
{
  return number % 2 == 0;
}

int product(int num1, int num2)
{
  return num1 * num2;
}

void display(Array *src)
{
  for (int i = 0; i < src->length; i++)
  {
    printf("%d ", src->array[i]);
  }
  printf("\n");
}

void display_numbers(ArrayVoid_ptr src)
{
  for (int i = 0; i < src->length; i++)
  {
    printf("%d ", *(int *)&src->array[i]);
  }
  printf("\n");
}

void display_void(ArrayVoid_ptr array_void, DisplayData display_function)
{

  display_function(array_void);
}

int main()
{
  int length = 5;
  int sample[] = {1, 2, 3, 4, 5};
  Array *src = create_array(5);
  copy_values(sample, src);

  ArrayVoid_ptr src_void = create_void_array(length);
  for (int i = 0; i < length; i++)
  {
    *(int *)&src_void->array[i] = sample[i];
  }
  ArrayVoid_ptr mapped_void = map_void(src_void, &add_one_void);

  printf("output of mapped void: \n");
  display_void(mapped_void, &display_numbers);

  Array *mapped_values = map(src, &add_one);
  printf("Numbers after adding one are :\n");
  display(mapped_values);

  Array *filtered_values = filter(src, &is_even);
  printf("Even numbers are :\n");
  display(filtered_values);

  int reduced_value = reduce(mapped_values, 1, &product);
  printf("product of mapped numbers is : %d", reduced_value);
  return 0;
}