#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "state.h"

#define MAX_NEXT_VALUES CHAR_MAX

struct State {
  char value;
  char next_values[MAX_NEXT_VALUES];
  int next_value_count;
  int next_value_weights[MAX_NEXT_VALUES];
  int total_weight;
};

State* state_create(char value) {
  State *state = malloc(sizeof(State));
  state->value = value;
  state->total_weight = 0;
  return state;
}

void state_destroy(State *state) {
  free(state);
  state = NULL;
}

char state_has_value(State *state, char value) {
  return state->value == value;
}

void state_add_next(State *state, char next) {
  assert(state->next_value_count < MAX_NEXT_VALUES);
  int next_i = -1;
  for (int i = 0; i < state->next_value_count; i++) {
    if (state->next_values[i] != next) continue;
    next_i = i;
    break;
  }
  if (next_i != -1) {
    state->next_value_weights[next_i]++;
  } else {
    state->next_values[state->next_value_count] = next;
    state->next_value_weights[state->next_value_count] = 1;
    state->next_value_count++;
  }
  state->total_weight++;
}

char state_pick_next(State *state) {
  int target_weight = rand() % state->total_weight;
  int i = 0;
  int cumulative_weight = state->next_value_weights[0];
  while (cumulative_weight < target_weight) {
    i++;
    cumulative_weight += state->next_value_weights[i];
  }
  return state->next_values[i];
}
