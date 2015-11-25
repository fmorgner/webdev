

# Install Guide Arch Linux

    sudo pacman -S hiredis libev cmake boost git jsoncpp
    yaourt -S aur/libhttpserver-git
    git clone --recursive https://github.com/fmorgner/webdev.git
    cd webdev
    cmake ./cpp/build/
    ./cpp/build/build -r

# Startup Guide

    redis-server &
    cpp/build/products/Release/bin/webdev

Connect to localhost:8080
