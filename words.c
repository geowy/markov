#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "words.h"

struct Words {
  FILE* file;
};

Words* words_create(char *path) {
  FILE* file = fopen(path, "r");
  if (!file) return NULL;
  Words *words = malloc(sizeof(Words));
  words->file = file;
  return words;
}

void words_destroy(Words* words) {
  fclose(words->file);
  free(words);
  words = NULL;
}

char* words_get_next(Words *words, char *word, int max_word_length) {
  char *result = fgets(word, max_word_length, words->file);
  if (!result) return NULL;
  for (int i = 0; i < max_word_length; i++) {
    if (isgraph(word[i])) continue;
    word[i] = '\0';
    break;
  }
  return word;
}
