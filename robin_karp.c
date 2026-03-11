#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BASE 256
#define MOD 1000000007ULL

// Compute (base^exp) % MOD
static uint64_t mod_pow(uint64_t base, size_t exp) {
  uint64_t result = 1;
  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

void rabin_karp(const char *text, const char *pattern) {
  size_t n = strlen(text);
  size_t m = strlen(pattern);

  if (m > n)
    return;

  uint64_t pattern_hash = 0;
  uint64_t window_hash = 0;

  uint64_t highest_power = mod_pow(BASE, m - 1);

  for (size_t i = 0; i < m; i++) {
    pattern_hash = (pattern_hash * BASE + pattern[i]) % MOD;
    window_hash = (window_hash * BASE + text[i]) % MOD;
  }

  for (size_t i = 0; i <= n - m; i++) {
    if (pattern_hash == window_hash) {
      if (strncmp(text + i, pattern, m) == 0) {
        printf("Pattern found at index %zu\n", i);
      }
    }
    if (i < n - m) {
      window_hash = (window_hash + MOD - (text[i] * highest_power) % MOD) % MOD;

      window_hash = (window_hash * BASE + text[i + m]) % MOD;
    }
  }
}

int main(void) {
  const char *text = "ababcabcabababd";
  const char *pattern = "ababd";

  rabin_karp(text, pattern);

  return 0;
}
