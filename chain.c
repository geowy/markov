#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "chain.h"
#include "state.h"

#define MAX_STATES CHAR_MAX

struct Chain {
  State *states[MAX_STATES];
  int state_count;
};

Chain* chain_create() {
  Chain *chain = malloc(sizeof(Chain));
  chain->state_count = 0;
  return chain;
}

void chain_destroy(Chain *chain) {
  for (int i = 0; i < chain->state_count; i++) {
    state_destroy(chain->states[i]);
  }
  free(chain);
  chain = NULL;
}

static State* find_state(Chain *chain, char value) {
  for (int i = 0; i < chain->state_count; i++) {
    State *state = chain->states[i];
    if (state_has_value(state, value)) return state;
  }
  return NULL;
}

static State* create_state(Chain *chain, char value) {
  assert(chain->state_count < MAX_STATES);
  State *state = state_create(value);
  chain->states[chain->state_count] = state;
  chain->state_count++;
  return state;
}

static State* find_or_create_state(Chain *chain, char value) {
  State *state = find_state(chain, value);
  if (state != NULL) return state;
  return create_state(chain, value);
}

void chain_feed_word(Chain *chain, char *word) {
  char prev = '\0';
  int i = 0;
  do {
    State *state = find_or_create_state(chain, prev);
    state_add_next(state, word[i]);
    prev = word[i];
    i++;
  } while (prev != '\0');
}

void chain_generate_word(Chain *chain, char *word, int max_word_length) {
  State *state = find_state(chain, '\0');
  int i;
  for (i = 0; i < (max_word_length - 1); i++) {
    char next = state_pick_next(state);
    if (next == '\0') break;
    state = find_state(chain, next);
    word[i] = next;
  }
  word[i] = '\0';
}
