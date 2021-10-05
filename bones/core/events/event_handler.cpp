#include <core/debug/log.h>
#include <core/events/event_handler.h>

namespace bones
{
  EventHandler::~EventHandler()
  {
    if (parent != nullptr)
    {
      parent->remove_handler(this);
    }
  }

  void EventHandler::add_handler(EventHandler* handler)
  {
    if (handler->parent == nullptr)
    {
      handler->parent = this;
      children.insert(handler);
    }
    else
    {
      logerror << "EventHandler not added: Parent instance detected" << logendl;
    }
  }

  void EventHandler::remove_handler(EventHandler* handler)
  {
    handler->parent = nullptr;
    children.erase(handler);
  }

  void EventHandler::handle_event(const Event& event)
  {
    for (EventHandler* handler : children)
    {
      handler->handle_event(event);
    }
  }
}