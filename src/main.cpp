#include <string>
#include <vector>

#include <mesos/resources.hpp>
#include <mesos/scheduler.hpp>
#include <mesos/type_utils.hpp>

#include <stout/exit.hpp>
#include <stout/flags.hpp>
#include <stout/foreach.hpp>
#include <stout/hashset.hpp>
#include <stout/option.hpp>
#include <stout/stringify.hpp>
#include <stout/try.hpp>

#include<glog/logging.h>

using namespace mesos;
using namespace mesos::internal;

using std::string;
using std::vector;

using mesos::Resources;

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);
    google::LogToStderr();
    LOG(INFO) <<"my first info";
    return 0;
}
