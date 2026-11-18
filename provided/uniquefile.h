#pragma once

#include <string>

// Owns a log file descriptor. The descriptor may be borrowed with get().
class UniqueFile {
public:
    // Open filename for writing, creating it if necessary and replacing any
    // existing contents. If opening fails, get() must return -1.
    explicit UniqueFile(const std::string& filename);

    // Release the owned descriptor, if any. Must not throw.
    ~UniqueFile() noexcept;

    // This project does not require copying or transferring ownership.
    UniqueFile(const UniqueFile&) = delete;
    UniqueFile& operator=(const UniqueFile&) = delete;
    UniqueFile(UniqueFile&&) = delete;
    UniqueFile& operator=(UniqueFile&&) = delete;

    // Borrow the descriptor; ownership remains with this object.
    int get() const { return m_fd; }

private:
    int m_fd = -1;
};
