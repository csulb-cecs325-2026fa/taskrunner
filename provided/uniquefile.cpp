#include "uniquefile.h"

#include <fcntl.h>
#include <unistd.h>

UniqueFile::UniqueFile(const std::string& filename) {
    // TODO: Open the log as described in uniquefile.h and store its descriptor.
    // Keep fd_ equal to -1 if opening fails.

}

UniqueFile::~UniqueFile() noexcept {
    // TODO: Release the descriptor if this object owns an open file.
}
