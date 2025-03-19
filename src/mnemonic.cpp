#include "mnemonic.hpp"
#include "hash.hpp"

char word_buffer[LONGEST_WORD + 1];

void loadWordFromPROGMEM(int index, char* buffer)
{
  int word_counter = 0;
  int k = 0;
  while (k < MNEMONIC_WORDS_SIZE)
  {
    if (pgm_read_byte_near(mnemonic_words + k) == '\0')
    {
      word_counter++;
      if (word_counter == index)
      {
        k++;
        int x = 0;
        while (pgm_read_byte_near(mnemonic_words + k) != '\0')
        {
          buffer[x] = pgm_read_byte_near(mnemonic_words + k);
          x++;
          k++;
        }
        buffer[x] = '\0';
        break;
      }
    }
    k++;
  }
}

void getPhrase(const uint8_t* raw, char* mnemonic) {
  char hex[65];
  memset(hex, 0, sizeof(hex));
  
  for (int i = 0; i < 32; i++) {
    sprintf(hex + (i * 2), "%02x", raw[i]);
  }
  
  for (int j = 0; j < 64; j += 8) {
    char temp[9];
    memcpy(temp, hex + j, 8);
    temp[8] = '\0';
    
    memcpy(hex + j + 0, temp + 6, 2);
    memcpy(hex + j + 2, temp + 4, 2);
    memcpy(hex + j + 4, temp + 2, 2);
    memcpy(hex + j + 6, temp + 0, 2);
  }
  
  const int n = WORD_COUNT;
  int mnemonic_index = 0;
  
  for (int i = 0; i < 64; i += 8) {
    char chunk[9];
    memcpy(chunk, hex + i, 8);
    chunk[8] = '\0';
    uint32_t x = strtoul(chunk, NULL, 16);
    
    uint16_t w1 = x % n;
    uint16_t w2 = ((x / n) + w1) % n;
    uint16_t w3 = ((x / n / n) + w2) % n;
    
    loadWordFromPROGMEM(w1, word_buffer);
    strcpy(mnemonic + mnemonic_index, word_buffer);
    mnemonic_index += strlen(word_buffer);
    mnemonic[mnemonic_index++] = ' ';
    
    loadWordFromPROGMEM(w2, word_buffer);
    strcpy(mnemonic + mnemonic_index, word_buffer);
    mnemonic_index += strlen(word_buffer);
    mnemonic[mnemonic_index++] = ' ';
    
    loadWordFromPROGMEM(w3, word_buffer);
    strcpy(mnemonic + mnemonic_index, word_buffer);
    mnemonic_index += strlen(word_buffer);
    mnemonic[mnemonic_index++] = ' ';
  }
  
  char trimmed_words[25 * 3 + 1];
  int trimmed_index = 0;
  int word_start = 0;
  
  for (int i = 0; i < 24; i++) {
    int count = 0;
    int j = word_start;
    
    while (count < 3 && mnemonic[j] != ' ' && mnemonic[j] != '\0') {
      trimmed_words[trimmed_index++] = mnemonic[j++];
      count++;
    }
    
    while (mnemonic[j] != ' ' && mnemonic[j] != '\0') {
      j++;
    }
    
    if (mnemonic[j] == ' ') {
      word_start = j + 1;
    }
  }
  trimmed_words[trimmed_index] = '\0';
  
  uint32_t checksum = crc32(trimmed_words, strlen(trimmed_words));
  
  uint16_t checksum_index = checksum % 24;
  
  word_start = 0;
  for (int i = 0; i < checksum_index; i++) {
    while (mnemonic[word_start] != ' ') {
      word_start++;
    }
    word_start++;
  }
  
  int j = word_start;
  while (mnemonic[j] != ' ' && mnemonic[j] != '\0') {
    j++;
  }
  
  char checksum_word[LONGEST_WORD + 1];
  memcpy(checksum_word, mnemonic + word_start, j - word_start);
  checksum_word[j - word_start] = '\0';
  
  strcpy(mnemonic + mnemonic_index, checksum_word);
  mnemonic_index += strlen(checksum_word);
  mnemonic[mnemonic_index] = '\0';
} 