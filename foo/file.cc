#include "foo/file.h"

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "absl/cleanup/cleanup.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

namespace oepd::file {

auto ReadFile(absl::string_view path) -> absl::StatusOr<std::vector<uint8_t>> {
  FILE* f = fopen(std::string(path).c_str(), "r");
  if (f == nullptr) {
    return absl::NotFoundError(
        absl::StrCat("failed to open file ", path, ": ", strerror(errno)));
  }
  auto file_closer = absl::MakeCleanup([f]() -> void { fclose(f); });

  int ret = fseek(f, 0, SEEK_END);
  if (ret != 0) {
    return absl::UnknownError(
        absl::StrCat("failed to seek file ", path, ": ", strerror(errno)));
  }
  size_t size = ftell(f);
  rewind(f);

  std::vector<uint8_t> buf(size);
  size_t bytes_read = fread(buf.data(), sizeof(unsigned char), size, f);
  if (bytes_read != size) {
    return absl::DataLossError(
        absl::StrCat("read ", bytes_read, " bytes from file ", path,
                     " but expected to read ", size, " bytes."));
  }

  return buf;
}

}  // namespace oepd::file
