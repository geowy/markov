#ifndef MARKOV_WORDS_H
#define MARKOV_WORDS_H

typedef struct Words Words;

Words* words_create(char *path);

void words_destroy(Words *words);

char* words_get_next(Words *words, char *word, int max_word_length);

#endif
