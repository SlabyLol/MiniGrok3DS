#pragma once
// CTRPluginFramework expects "types.h".
// Provide the standard 3DS types from libctru.
#include <3ds/types.h>

// CTRPF uses NORETURN in some headers
#ifndef NORETURN
#define NORETURN __attribute__((noreturn))
#endif
