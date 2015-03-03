// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package runtime

const (
	thechar           = '7'
	_BigEndian        = 0
	_CacheLineSize    = 32
	_RuntimeGogoBytes = 60
	_PhysPageSize     = 65536*goos_nacl + 4096*(1-goos_nacl)
	_PCQuantum        = 4
	_Int64Align       = 8
)
