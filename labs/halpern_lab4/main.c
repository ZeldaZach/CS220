#include <stdio.h>
#include <stdlib.h>
#include "secret.h"

unsigned int extract_secret(struct secret_keeper *);

int main()
{
	struct secret_keeper *k;
	unsigned int secret;
	k = get_keeper();
	secret = extract_secret(k);
	printf("Secret is %s\n", verify_secret(secret) == 1 ?  "correct" : "wrong");
	return 0;
}

unsigned int extract_secret(struct secret_keeper *k)
{
	int i;
	union secret *s = k->ptr; /* The secret is hidden in layers of pointers. Start at the K's pointer */

	/* Now, we will keep going down in the pointer levels until we hit the secret */
	for (i = 1; i < k->count; i++)
		s = s->ptr;
	
	/* Secret is in this layer, just return it now */
	return 	s->secret;
}

