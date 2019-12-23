#include "mainwindow.h"
#include "imageselector.h"
#include <QApplication>
#include <iostream>
#include <sys/file.h>
#include <errno.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void usage(std::string programName) {
    std::cerr << "Usage: " << programName << " [-t rotation_seconds] [-o background_opacity(0..255)] [-b blur_radius] -p image_folder -r" << std::endl;
}

int main(int argc, char *argv[])
{
    unsigned int rotationSeconds = 30;
    std::string path = "";

    QApplication a(argc, argv);

    MainWindow w;
    int opt;
    bool recursive = false;
    while ((opt = getopt(argc, argv, "b:p:t:o:r")) != -1) {
        switch (opt) {
        case 'p':
            path = optarg;
            break;
        case 't':
            rotationSeconds = atoi(optarg);
            break;
        case 'b':
            w.setBlurRadius(atoi(optarg));
            break;
        case 'o':
            w.setBackgroundOpacity(atoi(optarg));
            break;
        case 'r':
            recursive = true;
            break;
        default: /* '?' */
            usage(argv[0]);
            return 1;
        }
    }

    if (path.empty()) {
        std::cout << "Error: Path expected." << std::endl;
        usage(argv[0]);
        return 1;
    }
    w.show();

    ImageSelector is(w, rotationSeconds * 1000, path, recursive);
    is.start();
    return a.exec();
}
