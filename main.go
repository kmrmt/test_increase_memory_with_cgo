package main

// #cgo LDFLAGS: -L. -ltest -lstdc++
// #include "c.h"
import "C"

func main() {
	const (
		dim  int = 128
		size int = 1000000
	)

	C.header()

	vectors := make([]float32, dim*size)
	for i := 0; i < size; i++ {
		vectors[i*dim] = float32(i)
	}

	o := C.or_init()
	for n := 0; n < 100; n++ {
		ids := make([]C.size_t, size)
		C.stat(C.CString("init"))
		for i := 0; i < size; i++ {
			ids[i] = C.or_insert(o, (*C.float)(&vectors[i*dim]), C.size_t(dim))
		}
		C.stat(C.CString("insert"))

		for i := 0; i < size; i++ {
			C.or_remove(o, ids[i])
		}
		C.stat(C.CString("remove"))
	}

	C.stat(C.CString("finish"))
}
