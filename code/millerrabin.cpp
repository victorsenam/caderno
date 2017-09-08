llu llrand() { llu a = rand(); a<<= 32; a+= rand(); return a;}
int is_probably_prime(llu n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    llu s = 0, d = n - 1;
    while (d % 2 == 0) {
        d/= 2; s++;
    }
    for (int k = 0; k < 64; k++) {
        llu a = (llrand() % (n - 3)) + 2;
        llu x = exp_mod(a, d, n);
        if (x != 1 && x != n-1) {
            for (int r = 1; r < s; r++) {
                x = mul_mod(x, x, n);
                if (x == 1)
                    return 0;
                if (x == n-1)
                    break;
            }
            if (x != n-1)
                return 0;
        }
    }
    return 1;
}
