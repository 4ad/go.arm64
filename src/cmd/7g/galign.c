// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <u.h>
#include <libc.h>
#include "gg.h"

int	thechar	= '7';
char*	thestring = "arm64";
LinkArch*	thelinkarch = &linkarm64;

void
linkarchinit(void)
{
}

vlong MAXWIDTH = 1LL<<50;

/*
 * go declares several platform-specific type aliases:
 * int, uint, float, and uintptr
 */
Typedef	typedefs[] =
{
	{"int",		TINT,		TINT64},
	{"uint",		TUINT,		TUINT64},
	{"uintptr",	TUINTPTR,	TUINT64},
	{0}
};

void
betypeinit(void)
{
	widthptr = 8;
	widthint = 8;
	widthreg = 8;

	zprog.as = AGOK;

	listinit7();
}
