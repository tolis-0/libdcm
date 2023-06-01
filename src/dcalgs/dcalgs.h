#ifndef _DCALGS_H
#define _DCALGS_H


/* 	Binary Search. Finds the value X in [START, END] such that
	if VAR >= X then CONDITION is true, otherwise it's false.
	In the end VAR = X and all the variables are set correctly.
	WARNING: The statements inside have to be deterministic for
	some value of VAR otherwise the behaviour is undefined       */

#define ftbs(VAR, START, END, CONDITION) \
	VAR = ((START) + (END))/2; \
	for (int64_t VAR##_r = (START), VAR##_l = (END), VAR##_cond = 0; \
		(VAR##_r < VAR##_l && (VAR = (VAR##_r + VAR##_l)/2, 1)) \
		|| ((VAR == VAR##_r) ? 0 : (VAR = VAR##_r, 1)); \
		(CONDITION) ? (VAR##_l = VAR) : (VAR##_r = VAR + 1))

/*	
 *	Example Usage:
 *
 *	ftbs (j, 1, LIMIT, root >= CONSTANT) {
 *		fval= f(j);
 *		gval = g(j);
 *		root = sqrt(fval) + sqrt(gval);
 *	} 
*/


#endif // _DCALGS_H
