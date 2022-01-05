/*
Copyright (c) 1984, 1985, 1986, 1987, 1988 AT&T
	All Rights Reserved

Note: This software was created by the Bell Laboratories unit of AT&T.
Bell Laboratories was subsequently part of Lucent Technologies, later part of
Alcatel-Lucent, and now part of Nokia; some copyrights may have been assigned
by AT&T to its successors. This license is granted by Nokia solely to the
extent of its right to do so.
*/

#include <stdio.h>
#include "ear.h"
	
extern void	ToStr();
double atof();

docompN(v1, num, op, rev)
register VARP	v1;
double	num;
register int	op;
register int	rev;
{
	char	numstr[CONVSIZ];
	double	ans;

	if (MUSTSTR(v1->cur))
		goto STRCMP;
	if (!DIDCHECK(v1->cur))
		v1->cur|=isitanum(S(v1));
	if (ISNUM(v1->cur)) {
		if (!NUMAVAIL(v1->cur)) {
			v1->num=atof(S(v1));
			v1->cur|=NUMFLD;
		}
		ans=v1->num-num;
		goto DONE;
	}
	if (!STRAVAIL(v1->cur))
		ToStr(v1);
	STRCMP:;
	sprintf(numstr, "%.6g", num);
	ans=strcmp(S(v1), numstr);
	DONE:;
	switch(op) {
	case LT:	return(rev?ans>0:ans<0);
	case LTE:	return(rev?ans>=0:ans<=0);
	case GT:	return(rev?ans<0:ans>0);
	case GTE:	return(rev?ans<=0:ans>=0);
	case EQ:	return(ans==0);
	case NEQ:	return(ans!=0);
	default: awkerr("unimplemented comparison op");
	}
	return(-1);
}
