#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

typedef struct Chain Chain;

Chain* chain_create(void);

void chain_destroy(Chain *chain);

void chain_feed_word(Chain *chain, char *word);

void chain_generate_word(Chain *chain, char *word, int max_word_length);

#endif
