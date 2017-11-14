#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem::v1;
using namespace std;

int main(int argc, char * argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <brightness>" << endl;
        return 1;
    }

    for(auto& p: fs::directory_iterator("/sys/class/backlight")) {
        // Read the max brightness
        ifstream i(p / "max_brightness");
        int max_brightness;
        i >> max_brightness;
        i.close();

        cout << "Maximum brightness: \t" << max_brightness << endl;

        string arg(argv[1]);
        float wanted;
        int brightness;

        try {
            wanted = stof(arg);
        } catch(...) {
            cerr << "Invalid argument." << endl;
            return 3;
        }

        if ((arg.back()) == '%') {
            brightness = (wanted * max_brightness)/100;
        } else if (wanted < 1 && wanted >= 0) {
            brightness = static_cast<int>(wanted * max_brightness);
        } else {
            brightness = static_cast<int>(wanted);
        }

        cout << "Target brightness: \t" << brightness << endl;

        if (brightness > max_brightness) {
            std::cerr << "Too much light!" << endl;
            return 2;
        } else if (brightness < 0) {
            std::cerr << "Too much darkness!" << endl;
        }

        ofstream o(p / "brightness");
        o << brightness;
        o.close();

        // Only change the first result
        break;
    }
}
