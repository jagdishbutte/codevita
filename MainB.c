#include <stdio.h>
#include <string.h>
#include <limits.h>

void computeLPSArray(const char *pattern, int m, int *lps) {
    int len = 0;
    lps[0] = 0;

    for (int i = 1; i < m;) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPsearch(const char *text, const char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int lps[m];
    computeLPSArray(pattern, m, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            return 1; // Found the pattern
        } else if (i < n && pattern[j] != text[i]) {
            if (j) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return 0; // Pattern not found
}

int min_string_factor(const char *X, const char *Y, int S, int R) {
    int len_x = strlen(X);
    int len_y = strlen(Y);
    int dp[len_x + 1];

    for (int i = 0; i <= len_x; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    char reversed_Y[len_y + 1];
    for (int i = 0; i < len_y; i++) {
        reversed_Y[i] = Y[len_y - 1 - i];
    }
    reversed_Y[len_y] = '\0';

    for (int i = 0; i < len_x; i++) {
        for (int j = i + 1; j <= len_x; j++) {
            char x_sub[j - i + 1];
            strncpy(x_sub, X + i, j - i);
            x_sub[j - i] = '\0';

            if (KMPsearch(Y, x_sub)) {
                dp[j] = dp[j] < dp[i] + S ? dp[j] : dp[i] + S;
            }
            if (KMPsearch(reversed_Y, x_sub)) {
                dp[j] = dp[j] < dp[i] + R ? dp[j] : dp[i] + R;
            }
        }
    }

    return dp[len_x] == INT_MAX ? -1 : dp[len_x];
}

int main() {
    char X[10001], Y[10001];
    int S, R;

    fgets(X, sizeof(X), stdin);
    fgets(Y, sizeof(Y), stdin);
    scanf("%d %d", &S, &R);
    
    X[strcspn(X, "\n")] = 0;
    Y[strcspn(Y, "\n")] = 0;

    int result = min_string_factor(X, Y, S, R);
    if (result == -1) {
        printf("Impossible");
    } else {
        printf("%d", result);
    }

    return 0;
}
