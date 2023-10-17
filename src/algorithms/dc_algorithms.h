#ifndef _DC_ALGORITHMS_H
#define _DC_ALGORITHMS_H


/* 	Binary Search. Finds the value x in [start, end] such that
	if var >= x then condition is true, otherwise it's false.
	In the end var = x and all the variables are set correctly.
	WARNING: The statements inside have to be deterministic for
	some value of var otherwise the behaviour is undefined       */

#define dc_fbs(var, start, end, condition) \
	dc_comp_binary_search(0, 1, var, start, end, condition)

/* 	Same but if var <= x then condition is true, otherwise it's false */

#define dc_lbs(var, start, end, condition) \
	dc_comp_binary_search(1, 0, var, start, end, !(condition))

#define dc_comp_binary_search(is_lt, is_ft, var, start, end, condition) \
	for (typeof(var) var##_r = ( \
		var = ((start) < 0 && (end) > 0) ? 0 : (start) + ((end) - (start))/2, \
		(start)), var##_l = (end); \
		(var##_r < var##_l && (var = var##_r + (var##_l - var##_r)/2 + is_lt, 1)) \
		|| ((var == var##_r) ? 0 : (var = var##_r, 1)); \
		(condition) ? (var##_l = var - is_lt) : (var##_r = var + is_ft))

/*	
 *	Example Usage:
 *
 *	dc_fbs (j, 1, LIMIT, roots >= CONSTANT) {
 *		fval= f(j);
 *		gval = g(j);
 *		roots = sqrt(fval) + sqrt(gval);
 *	}
*/


#endif // _DC_ALGORITHMS_H
