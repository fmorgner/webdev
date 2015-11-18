

# Install Guide Arch Linux

    sudo pacman -S hiredis libev cmake boost git jsoncpp
    git clone --recursive https://github.com/fmorgner/webdev.git
    cd webdev
    cmake ./cpp/build/
    ./cpp/build/build -r
