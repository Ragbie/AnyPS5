#ifndef CORE_LIBS_PRX_LIBKERNEL_FILE_SHAREDMEMORY_HPP
#define CORE_LIBS_PRX_LIBKERNEL_FILE_SHAREDMEMORY_HPP

#include <cstddef>
#include <cstdint>
#ifndef _WIN32
#include <sys/uio.h>
#endif

namespace File {

bool IsSharedMemoryDescriptor_nid_no_patch(int descriptor);
std::int64_t WriteSharedMemory_nid_no_patch(int descriptor, const void* buffer, std::size_t size);
std::int64_t PwriteSharedMemory_nid_no_patch(int descriptor, const void* buffer, std::size_t size, std::int64_t offset);
std::int64_t SeekSharedMemory_nid_no_patch(int descriptor, std::int64_t offset, int whence);
int TruncateSharedMemory_nid_no_patch(int descriptor, std::int64_t length);
#ifdef _WIN32
void* SharedMemorySection_nid_no_patch(int descriptor, std::uint64_t end);
std::int64_t ReadSharedMemory_nid_no_patch(int descriptor, void* buffer, std::size_t size);
std::int64_t PreadSharedMemory_nid_no_patch(int descriptor, void* buffer, std::size_t size, std::int64_t offset);
std::int64_t SharedMemorySize_nid_no_patch(int descriptor);
void ForgetSharedMemory_nid_no_patch(int descriptor);
void DuplicateSharedMemory_nid_no_patch(int from, int to);
#endif
#ifndef _WIN32
std::int64_t WritevSharedMemory_nid_no_patch(int descriptor, const struct iovec* vectors, int count);
std::int64_t PwritevSharedMemory_nid_no_patch(int descriptor, const struct iovec* vectors, int count, std::int64_t offset);
#endif

}

#endif
