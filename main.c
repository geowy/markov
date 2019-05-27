#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "chain.h"
#include "words.h"

// 250 should be good enough - https://en.wikipedia.org/wiki/Longest_words
#define MAX_WORD_LENGTH 250

typedef struct Options {
  char words_file_path[PATH_MAX];
  int word_count;
  unsigned seed;
} Options;

Options get_options(int argc, char *argv[]) {
  Options options = {
    .words_file_path = "/usr/share/dict/words",
    .word_count = 1,
    .seed = time(NULL)
  };
  int opt;
  while((opt = getopt(argc, argv, "d:w:s:")) != -1) {
    switch (opt) {
      case 'd':
        strcpy(options.words_file_path, optarg);
        break;
      case 'w':
        options.word_count = atoi(optarg);
        break;
      case 's':
        options.seed = atoi(optarg);
        break;
    }
  }
  return options;
}

int main(int argc, char *argv[]) {
  Options options = get_options(argc, argv);

  srand(options.seed);

  Words *words = words_create(options.words_file_path);
  if (!words) {
    printf("Error reading file: %s\n", options.words_file_path);
    exit(EXIT_FAILURE);
  }

  Chain *chain = chain_create();

  char word[MAX_WORD_LENGTH];
  while (words_get_next(words, word, MAX_WORD_LENGTH)) {
    chain_feed_word(chain, word);
  }

  for (int i = 0; i < options.word_count; i++) {
    chain_generate_word(chain, word, MAX_WORD_LENGTH);
    printf("%s\n", word);
  }

  chain_destroy(chain);
  words_destroy(words);
  return EXIT_SUCCESS;
}
