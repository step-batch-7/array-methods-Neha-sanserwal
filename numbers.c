#include <stdio.h>
#include <stdlib.h>
#include "array_void.h"
typedef void (*DisplayData)(ArrayVoid_ptr);
Bool is_even(int number);
int add_one(int number);
void display(Array *arr);
int product(int num1, int num2);

int add_one(int number)
{
  return number + 1;
}
void *add_one_void(Object num)
{
  *(int *)&num += 1;
  return num;
}

Bool is_even(int number)
{
  return number % 2 == 0;
}

Bool is_even_void(Object number)
{
  return is_even(*(int *)&number);
}

int product(int num1, int num2)
{
  return num1 * num2;
}

Object product_int_void(Object num1, Object num2)
{

  *(int *)&num2 = (*(int *)&num1 * *(int *)&num2);
  return num2;
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
  void *inti_ptr;
  *(int *)&inti_ptr = 1;

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

  ArrayVoid_ptr filtered_void = filter_void(src_void, &is_even_void);
  printf("output of filter void: \n");
  display_void(filtered_void, &display_numbers);

  Array *filtered_values = filter(src, &is_even);
  printf("Even numbers are :\n");
  display(filtered_values);

  Object reduced_void = reduce_void(src_void, inti_ptr, &product_int_void);
  printf("product of mapped numbers is : %d\n", *(int *)&reduced_void);

  int reduced_value = reduce(src, 1, &product);
  printf("product of mapped numbers is : %d\n", reduced_value);
  return 0;
}