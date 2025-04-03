/*
** EPITECH PROJECT, 2025
** Error
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(const std::string &message, const std::string &component) : _message(message), _component(component)
{
}

const char *Error::what() const noexcept
{
    return _message.c_str();
}
