#include "Classes/Extractor.h"
#include "Classes/App.h"

using namespace std;

int main() {
    Extractor information;
    App app(information);
    app.run();
    return 0;
}