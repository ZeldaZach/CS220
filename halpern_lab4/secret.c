/*
 * NOTE: This file is only for your reference. It is not meant to compile.
 */

struct secret_keeper* get_keeper() {
	struct secret_keeper *keeper;
	union secret *s, *temp;

	keeper = (struct secret_keeper *) malloc (sizeof(struct secret_keeper));
	s = (union secret *) malloc (sizeof(union secret));
	keeper->ptr = (void *) s;
	keeper->count = /* random number > 1 */
	
	for(i = 1; i < keeper->count; i++) {
		temp = (union secret *) malloc (sizeof(union secret));
		s->ptr = temp;
		s = temp;
	}

	s->secret = /* Secret */
	return keeper;
} 

