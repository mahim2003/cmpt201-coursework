#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 100
#define MAX_LINES 100

typedef struct {
  int line_number;
  int value;
} Input;

typedef struct {
  int line_number;
  int value;
} IntermediateInput;

typedef struct {
  int doubled_value;
  int line_numbers[MAX_LINES];
  int line_count;
} Output;

void map(Input *input, IntermediateInput *intermediate_input) {
  intermediate_input->line_number = input->line_number;
  intermediate_input->value = input->value * 2;
}
void groupByKey(IntermediateInput *input, Output *output, int *result_count) {
  int i;
  for (i = 0; i < *result_count; i++) {
    if (output[i].doubled_value == input->value) {
      output[i].line_numbers[output[i].line_count] = input->line_number;
      output[i].line_count++;
      return;
    }
  }

  output[*result_count].doubled_value = input->value;
  output[*result_count].line_numbers[0] = input->line_number;
  output[*result_count].line_count = 1;
  (*result_count)++;
}

void reduce(Output output) {
  printf("(%d, [", output.doubled_value);
  for (int i = 0; i < output.line_count; i++) {
    printf("%d", output.line_numbers[i]);
    if (i < output.line_count - 1)
      printf(", ");
  }
  printf("])\n");
}

int main() {
  Input inputs[MAX_INPUT];
  IntermediateInput intermediate[MAX_INPUT];
  Output outputs[MAX_INPUT];
  int count = 0;
  printf("Enter values (one per line). Type 'end' to finish:\n");

  char buffer[50];
  while (fgets(buffer, sizeof(buffer), stdin)) {
    if (strncmp(buffer, "end", 3) == 0)
      break;

    inputs[count].line_number = count + 1;
    inputs[count].value = atoi(buffer);
    count++;
  }

  for (int i = 0; i < count; i++)
    map(&inputs[i], &intermediate[i]);

  int group_count = 0;
  for (int i = 0; i < count; i++)
    groupByKey(&intermediate[i], outputs, &group_count);

  for (int i = 0; i < group_count; i++)
    reduce(outputs[i]);

  return 0;
}
