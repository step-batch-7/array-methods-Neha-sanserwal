#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int add_one(int number);
Bool is_even(int number);
void display(Array *arr);
int product(int num1, int num2);
int add_one(int number)
{
  return number + 1;
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

int main()
{
  int length = 5;
  Array *src = create_array(5);
  for (int i = 0; i < src->length; i++)
  {
    src->array[i] = i;
  }
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