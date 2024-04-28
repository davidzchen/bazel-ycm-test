#ifndef OEPD_COMMON_FILE_H_
#define OEPD_COMMON_FILE_H_

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace oepd::file {

auto ReadFile(absl::string_view path) -> absl::StatusOr<std::vector<uint8_t>>;

}  // namespace oepd::file

#endif  // OEPD_COMMON_FILE_H_
