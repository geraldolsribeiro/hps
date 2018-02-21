#pragma once

#include <iostream>
#include <memory>
#include "../serializer.h"

namespace hps {

template <class T, class B>
class Serializer<std::unique_ptr<T>, B> {
 public:
  static void serialize(const std::unique_ptr<T>& container, OutputBuffer<B>& ob) {
    if (container) {
      ob.write_char(1);
      Serializer<T, B>::serialize(*container, ob);
    } else {
      ob.write_char(0);
    }
  }

  static void parse(std::unique_ptr<T>& container, InputBuffer<B>& ib) {
    if (ib.read_char()) {
      if (!container) {
        container.reset(new T());
      }
      Serializer<T, B>::parse(*container, ib);
    } else {
      container.reset(nullptr);
    }
  }
};

}  // namespace hps
