#ifndef _SECRET_H
#define _SECRET_H

struct secret_keeper {
	unsigned int count;
	void *ptr;
};

union secret {
	unsigned int secret;
	void *ptr;
};

/* Below functions are implemented in secret_obj.o */

/* Get the secret keeper */
struct secret_keeper *get_keeper();

/* Verify a secret. Returns 1 if secret is correct  */
int verify_secret(unsigned int secret);

#endif
