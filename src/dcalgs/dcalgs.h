#ifndef _DCALGS_H
#define _DCALGS_H


/* 	Binary Search. Finds the value x in [start, end] such that
	if var >= x then condition is true, otherwise it's false.
	In the end var = x and all the variables are set correctly.
	WARNING: The statements inside have to be deterministic for
	some value of var otherwise the behaviour is undefined       */

#define ftbs(var, start, end, condition) \
	FT_AND_LT_BS(0, 1, var, start, end, condition)

/* 	Same but if var <= x then condition is true, otherwise it's false */

#define ltbs(var, start, end, condition) \
	FT_AND_LT_BS(1, 0, var, start, end, condition)

#define FT_AND_LT_BS(is_lt, is_ft, var, start, end, condition) \
	var = ((start) + (end))/2; \
	for (int64_t var##_r = (start), var##_l = (end); \
		(var##_r < var##_l && (var = (var##_r + var##_l)/2, 1)) \
		|| ((var == var##_r) ? 0 : (var = var##_r, 1)); \
		(condition) ? (var##_l = var + is_lt) : (var##_r = var + is_ft))

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
