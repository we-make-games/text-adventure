#ifndef TEXT_HPP
#define TEXT_HPP

#include "Entity.hpp"

namespace adventure {

  class Text: public Entity {
  public:
    std::string text;
    int size;
  };
} 

#endif
