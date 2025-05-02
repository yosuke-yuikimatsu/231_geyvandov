#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regex> <text> <replacement>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *text = argv[2];
    const char *replacement = argv[3];

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char errbuf[100];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        regfree(&regex);
        return 1;
    }

    size_t result_size = 1024;
    char *result = malloc(result_size);
    if (!result) {
        perror("malloc");
        regfree(&regex);
        return 1;
    }
    result[0] = '\0';
    size_t result_len = 0;

    const char *current = text;
    regmatch_t match;

    while ((ret = regexec(&regex, current, 1, &match, 0)) == 0) {
        size_t pre_len = match.rm_so;
        size_t match_len = match.rm_eo - match.rm_so;

        if (result_len + pre_len + 1 > result_size) {
            result_size = result_len + pre_len + 100;
            char *new_result = realloc(result, result_size);
            if (!new_result) {
                perror("realloc");
                regfree(&regex);
                free(result);
                return 1;
            }
            result = new_result;
        }
        strncat(result, current, pre_len);
        result_len += pre_len;
        current += match.rm_so + match_len;

        size_t repl_len = strlen(replacement);
        if (result_len + repl_len + 1 > result_size) {
            result_size = result_len + repl_len + 100;
            char *new_result = realloc(result, result_size);
            if (!new_result) {
                perror("realloc");
                regfree(&regex);
                free(result);
                return 1;
            }
            result = new_result;
        }
        strcat(result, replacement);
        result_len += repl_len;
    }

    size_t remaining_len = strlen(current);
    if (result_len + remaining_len + 1 > result_size) {
        result = realloc(result, result_len + remaining_len + 1);
        if (!result) {
            perror("realloc");
            regfree(&regex);
            return 1;
        }
    }
    strcat(result, current);

    printf("%s\n", result);

    free(result);
    regfree(&regex);
    return 0;
}