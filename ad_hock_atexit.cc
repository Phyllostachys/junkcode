// found in the comments here: https://www.reddit.com/r/programming/comments/13ppm1/ds_scopeexit_in_c11/

#include <iostream>
#include <string>
#include <vector>

#define SCOPE_EXIT(code)                   \
  struct ScopeExitType##__LINE__           \
  {                                        \
      ~ScopeExitType##__LINE__() { code; } \
  } ScopeExit##__LINE__

std::FILE* fp;

int main()
{
    fp = std::fopen("test.out", "wb");
    SCOPE_EXIT(std::fclose(fp); std::printf("Closed"););
}
