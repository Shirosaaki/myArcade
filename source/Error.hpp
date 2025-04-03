/*
** EPITECH PROJECT, 2025
** error
** File description:
** error
*/
#ifndef ERROR_HPP_
    #define ERROR_HPP_
    #include <iostream>
    #include <string>
    #include <exception>

class Error : public std::exception {
    public:
        Error(const std::string &message, const std::string &component = "Unknown");
        const char *what() const noexcept override;

    protected:
    private:
        std::string _message;
        std::string _component;
};

#endif /* !ERROR_HPP_ */
