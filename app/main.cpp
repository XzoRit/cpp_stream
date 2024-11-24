#include <lib/lib.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

using namespace std::string_literals;
using namespace std::string_view_literals;
namespace po = boost::program_options;

int main(int ac, char* av[])
{
    std::cout << "Hello app\n";

    try
    {
        po::options_description desc("Allowed options");
        desc.add_options()("help", "produce help message");

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << "\n";
        }

        const auto* a{"Hello string lit\n"};
        const auto b{"Hello string std.string\n"s};
        const auto c{"Hello string std.string_view\n"sv};
        const auto* d{"Hello chars\n"};

        auto s{::xzr::lib::stream{}};
        s << a << b << c;
        for (const auto ch : "Hello chars\n")
            s << ch;
        std::cout << s.str();

        auto os{std::ostringstream{}};
        os << a << b << c;
        for (const auto ch : "Hello chars\n")
            os << ch;
        std::cout << os.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}
