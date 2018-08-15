#include <iostream>

#define N 999

void shuffle(int *s, int n);
void output(int *s, int n);
int score(int *s, int *d, int *a, int n);
void swap(int *s, int a, int b);
void display(int *s, int n);

using namespace std;

int main(void) {
    int s[N], d[2*N-1], a[2*N-1], r, p;

    srand(time(NULL));

    for (int i = 0; i < N; i++)
        s[i] = i;

    shuffle(s, N);

    p = score(s, d, a, N);

    for (r = 0; p > 0; r++) {
        int u, v, z, b, q[N], w[N];

        u = rand() % N;

        p -= (d[u+s[u]] > 1) + (a[u-s[u]+N-1] > 1);
        d[u+s[u]]--;
        a[u-s[u]+N-1]--;

        for (int i = 0; i < N; i++) {
            q[i] = p - (d[i+s[i]] > 1) - (a[i-s[i]+N-1] > 1);
            d[i+s[i]]--;
            a[i-s[i]+N-1]--;

            q[i] += (d[u+s[i]] > 0) + (a[u-s[i]+N-1] > 0);
            d[u+s[i]]++;
            a[u-s[i]+N-1]++;

            q[i] += (d[i+s[u]] > 0) + (a[i-s[u]+N-1] > 0);
            d[i+s[u]]++;
            a[i-s[u]+N-1]++;

            d[u+s[i]]--;
            a[u-s[i]+N-1]--;

            d[i+s[u]]--;
            a[i-s[u]+N-1]--;

            d[i+s[i]]++;
            a[i-s[i]+N-1]++;
        }

        b = N;
        for (int i = 0; i < N; i++)
            b = q[i] < b ? q[i] : b;

        z = 0;
        for (int i = 0; i < N; i++)
            if (q[i] == b) {
                w[z++] = i;
            }

        v = w[rand() % z];

        d[v+s[v]]--;
        a[v-s[v]+N-1]--;

        swap(s, u, v);

        d[u+s[u]]++;
        a[u-s[u]+N-1]++;

        d[v+s[v]]++;
        a[v-s[v]+N-1]++;

        p = q[v];
    }

    cout << r << endl;
    output(s, N);

    if (N < 70)
        display(s, N);

    p = score(s, d, a, N);

    cout << (p == 0 ? "Valid" : "Invalid") << endl;

    return 0;
}

void shuffle(int *s, int n) {
    for (int i = n-1; i > 0; i--)
        swap(s, i, rand() % (i+1));
}

int score(int *s, int *d, int *a, int n) {
    int p = 0;

    for (int i = 0; i < 2*n-1; i++) {
        d[i] = 0;
        a[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        d[i+s[i]]++;
        a[i-s[i]+n-1]++;
    }

    for (int i = 0; i < 2*n-1; i++)
        p += (d[i] > 0 ? d[i]-1 : 0) + (a[i] > 0 ? a[i]-1 : 0);

    return p; 
}

void output(int *s, int n) {
    for (int i = 0; i < n; i++)
        cout << s[i] << ' ';
    cout << endl;
}

void swap(int *s, int a, int b) {
    int t = s[a];
    s[a] = s[b];
    s[b] = t;
}

void display(int *s, int n) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << (s[i] == j ? 'Q' : '.');
        cout << endl;
    }
}
