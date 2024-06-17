#ifndef PARAMS_H
#define PARAMS_H

#define NTRU_HPS
#define NTRU_N 821
#define NTRU_LOGQ 12

/* Do not modify below this line */

#define NTRU_Q (1 << NTRU_LOGQ)
#define MODQ(X) ((X) & (NTRU_Q - 1))


#endif
