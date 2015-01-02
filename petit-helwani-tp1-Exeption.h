#ifndef EXEPTION
#define EXEPTION
#include <stdexcept>
#include <algorithm>
/**
 * @brief The Exception class : CLASSE QUI PERMET DE GERER LES EXEPTIONS
 */
class Exception: public std::runtime_error{
public:
  inline Exception(const std::string& msg, const std::string& file, const std::string& function,int line)
    : std::runtime_error(msg), m_file(file), m_function(function), m_line(line)
  {
  }
  inline virtual ~Exception() throw() {}

  inline const std::string& getFile( ) const { return m_file; }
  inline const std::string& getFunction( ) const { return m_function; }
  inline int getLine( ) const { return m_line; }

private:
  std::string m_file;
  std::string m_function;
  int m_line;
};

#define THROW_EXEPTION(msg) throw Exception(msg, __FILE__,__FUNCTION__, __LINE__)
#endif // EXEPTION

