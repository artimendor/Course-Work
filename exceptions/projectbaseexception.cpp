#include "projectbaseexception.h"

ProjectBaseException::ProjectBaseException(const char* msg, QWidget* parent)
    : std::logic_error (msg), parent(parent)
{

}
