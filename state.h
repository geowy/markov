#ifndef MARKOV_STATE_H
#define MARKOV_STATE_H

typedef struct State State;

State* state_create(char value);

void state_destroy(State *state);

char state_has_value(State *state, char value);

void state_add_next(State *state, char next);

char state_pick_next(State *state);

#endif
