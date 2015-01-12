// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package runtime

import "unsafe"

const (
	_AT_NULL     = 0
	_AT_PLATFORM = 15 //  introduced in at least 2.6.11
	_AT_HWCAP    = 16 // introduced in at least 2.6.11
	_AT_RANDOM   = 25 // introduced in 2.6.29

	_HWCAP_VFP   = 1 << 6  // introduced in at least 2.6.11
	_HWCAP_VFPv3 = 1 << 13 // introduced in 2.6.30
)

var randomNumber uint32

//go:nosplit
func setup_auxv(argc int32, argv **byte) {
	// skip over argv, envv to get to auxv
	n := argc + 1
	for argv_index(argv, n) != nil {
		n++
	}
	n++
	// TODO(dfc) vdso_linux_amd64 has a much better way of doing this parsing
	auxv := (*[1 << 28]uint64)(add(unsafe.Pointer(argv), uintptr(n)*ptrSize))

	for i := 0; auxv[i] != _AT_NULL; i += 2 {
		switch auxv[i] {
		case _AT_RANDOM: // kernel provides a pointer to 16-bytes worth of random data
			if auxv[i+1] != 0 {
				// the pointer provided may not be word alined, so we must to treat it
				// as a byte array.
				rnd := (*[16]byte)(unsafe.Pointer(uintptr(auxv[i+1])))
				randomNumber = uint32(rnd[0]) | uint32(rnd[1])<<8 | uint32(rnd[2])<<16 | uint32(rnd[3])<<24
			}
		}
	}
}

func cputicks() int64 {
	// Currently cputicks() is used in blocking profiler and to seed fastrand1().
	// nanotime() is a poor approximation of CPU ticks that is enough for the profiler.
	// randomNumber provides better seeding of fastrand1.
	return nanotime() + int64(randomNumber)
}
