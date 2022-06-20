#include <hello/hello.hpp>
#include <hello_header/hello_header.hpp>
#include <hello_object/hello_object.hpp>

int main(int, char **){
  hello::Hello hello("Jane Doe");
  hello.greet();
  hello_header::print_hello("John Doe");
  hello_object::HelloObject hello_obj("Arul");
  hello_obj.greet();
  return 0;
}
