#pragma once

#include <core/events/event.h>
#include <core/typedefs.h>

#include <set>

namespace bones
{
  class EventHandler
  {
  protected:
    EventHandler* parent = nullptr;
    std::set<EventHandler*> children;
    
  public:
    ~EventHandler();
    
    virtual void add_handler(EventHandler* handler);
    virtual void remove_handler(EventHandler* handler);
    virtual void handle_event(const Event& event);
  };
}