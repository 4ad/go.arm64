// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Hashing algorithm inspired by ?

// +build amd64 amd64p32 arm64 ppc64 ppc64le

package runtime

import "unsafe"

func memhash(p unsafe.Pointer, seed, s uintptr) uintptr {
	return 0
}

func nilinterhash(p unsafe.Pointer, h uintptr) uintptr {
	return 0
}
