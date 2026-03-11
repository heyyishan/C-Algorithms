#include "stdbool.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// C23: constexpr for compile-time constants
uint64_t BASE = 256;    // Number of characters in input alphabet
uint64_t MOD = 1e9 + 7; // Large prime to minimize collisions

/**
 * Rabin-Karp Pattern Matching
 * Returns the index of the first occurrence of 'pat' in 'txt', or -1 if not
 * found.
 */
int rabin_karp_search(const char *txt, const char *pat) {
  auto n = strlen(txt); // C23: auto type inference
  auto m = strlen(pat);

  if (m > n)
    return -1;

  uint64_t pat_hash = 0; // Hash value for pattern
  uint64_t txt_hash = 0; // Hash value for current window in text
  uint64_t h = 1;        // The value of BASE^(m-1) % MOD

  // Precompute h = pow(BASE, m-1) % MOD
  for (size_t i = 0; i < m - 1; i++) {
    h = (h * BASE) % MOD;
  }

  // Calculate the initial hash value of pattern and first window of text
  for (size_t i = 0; i < m; i++) {
    pat_hash = (BASE * pat_hash + (uint8_t)pat[i]) % MOD;
    txt_hash = (BASE * txt_hash + (uint8_t)txt[i]) % MOD;
  }

  // Slide the pattern over text one by one
  for (size_t i = 0; i <= n - m; i++) {
    // If hashes match, check characters one by one (Hash Collision Check)
    if (pat_hash == txt_hash) {
      bool match = true;
      for (size_t j = 0; j < m; j++) {
        if (txt[i + j] != pat[j]) {
          match = false;
          break;
        }
      }
      if (match)
        return (int)i;
    }

    // Calculate hash value for next window:
    // Remove leading digit, add trailing digit
    if (i < n - m) {
      // Logic: txt_hash = (BASE * (txt_hash - old_char * h) + new_char) % MOD
      // We add MOD to handle negative results from subtraction
      txt_hash = (BASE * (txt_hash + MOD - (uint8_t)txt[i] * h) +
                  (uint8_t)txt[i + m]) %
                 MOD;
    }
  }

  return -1;
}

int main() {
  const char *text = "FAANG_INTERVIEW_PREP_WITH_C23";
  const char *pattern = "PREP";

  int result = rabin_karp_search(text, pattern);

  if (result != -1) {
    printf("Pattern found at index: %d\n", result);
  } else {
    printf("Pattern not found.\n");
  }

  return 0;
}
