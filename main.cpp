#include <caf/all.hpp>
#include <algorithm>
#include <iterator>
#include <string>

caf::behavior test_actor_function() {
  return {[](std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) {
      const unsigned char res{static_cast<unsigned char>(c)};
      return res
             & ~0b0010'0000U; // Uppercase it by turning the 3rd highest bit off
    });
    return s;
  }};
}

void test_actor_buddy_function(caf::event_based_actor* self,
                               const caf::actor& buddy) {
  using namespace std::string_literals;
  self->request(buddy, caf::infinite, "HiTheRe"s)
    .then([self](const std::string& result_string) {
      caf::aout(self) << "test_actor_buddy_function: Got \"" << result_string << "\" from remote actor\n";
    });
}

void caf_main(caf::actor_system& sys)
{
    auto test_actor = sys.spawn(test_actor_function);
    sys.spawn(test_actor_buddy_function, test_actor);
}

CAF_MAIN()

