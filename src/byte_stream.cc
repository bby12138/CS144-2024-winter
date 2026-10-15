#include "byte_stream.hh"

ByteStream::ByteStream(uint64_t capacity)
    : capacity_(capacity), amount_(capacity) {}

bool Writer::is_closed() const {
  // Your code here.
  return closed_;
}

void Writer::push(std::string data) {
  if (data.empty()) return;
  if (!closed_ && amount_ != 0) {
    if (amount_ >= data.size()) {
      buffer_.append(data);
      amount_ -= data.size();
      total_pushed_ += data.size();
    } else {
      buffer_.append(data, 0, amount_);
      total_pushed_ += amount_;
      amount_ = 0;
    }
  }
}

void Writer::close() { closed_ = true; }

uint64_t Writer::available_capacity() const {
  // Your code here.
  return amount_;
}

uint64_t Writer::bytes_pushed() const {
  // Your code here.
  return total_pushed_;
}

bool Reader::is_finished() const { return closed_ && buffer_.empty(); }

uint64_t Reader::bytes_popped() const {
  // Your code here.
  return total_poped_;
}

std::string_view Reader::peek() const {
  // Your code here.
  return buffer_;
}

void Reader::pop(uint64_t len) {
  if (len > buffer_.size()) {
    set_error();
    return;
  } else {
    buffer_.erase(0, len);
    total_poped_ += len;
    amount_ += len;
  }
}

uint64_t Reader::bytes_buffered() const { return buffer_.size(); }
