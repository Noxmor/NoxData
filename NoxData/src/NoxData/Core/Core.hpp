#pragma once

namespace NoxData {

#define ND_NODISCARD [[nodiscard]]

#define ND_DEBUGBREAK() __debugbreak()

#ifdef ND_DEBUG
#define ND_ENABLE_ASSERTS
#endif

#ifdef ND_ENABLE_ASSERTS
#define ND_ASSERT(x) { if(!(x)) { ND_DEBUGBREAK(); } }
#else
#define ND_ASSERT(x, ...)
#endif
}