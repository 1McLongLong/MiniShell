#include "header.h"

static int count_words(const char *str, char c)
{
  int count = 0, i, len;
  char lastC;
  int insideQuotes = 0; // Flag to track if inside quotes
  len = ft_strlen(str);
  if (len > 0) {
    lastC = str[0];
  }
  for (i = 0; i <= len; i++) {
    if (str[i] == '\"')  // Toggle inside quotes
      insideQuotes = !insideQuotes;
    if (!insideQuotes && (str[i] == c || str[i] == '\0') && lastC != c)
      count++;
    lastC = str[i];
  }
  return count;
}

static void    free_string(char **str, int word_count)
{
  int    i;

  i = word_count;
  while (i)
  {
    i--;
    free(str[i]);
  }
  free(str);
}

static char    *my_ft_strdup(const char *str, int len)
{
  int        i;
  char    *copy;

  copy = (char *)malloc(len + 1);
  if (!copy)
    return (NULL);
  i = 0;
  while (i < len)
  {
    copy[i] = str[i];
    i++;
  }
  copy[i] = '\0';
  return (copy);
}

static void	fill_result(char **result, char const *s, char c, int word_count)
{
  int		i;
  int		len;
  int		in_quotes;

  i = 0;
  in_quotes = 0;
  while (i < word_count)
  {
    while (*s == c)
      s++;
    len = 0;
    while (s[len] && (in_quotes || s[len] != c))
    {
      if (s[len] == '\"')
        in_quotes = !in_quotes;
      len++;
    }
    result[i] = my_ft_strdup(s, len);
    s += len;
    i++;
  }
}

char    **token_split(char const *s, char c)
{
  int        i;
  int        words_count;
  char    **full_str;


  if (s == NULL) 
    return (NULL);
  words_count = count_words(s, c);
  full_str = malloc(sizeof(char *) * (words_count + 1));
  if (full_str == NULL)
    return (NULL);
  fill_result(full_str, s, c, words_count);
  full_str[words_count] = NULL;
  i = 0;
  while (i < words_count)
  {
    if (!full_str[i])
    {
      free_string(full_str, words_count);
      return (NULL);
    }
    i++;
  }
  return (full_str);
}
