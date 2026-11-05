#!/bin/sh
if [ -d "$HOME/Fantasyos" ]; then
    rm -rf "$HOME/Fantasyos"
fi
if [ -f "$HOME/myos" ]; then
    rm "$HOME/myos"
fi
if [ -f "$HOME/.bashrc" ]; then
    sed -i '/\.\/myos/d' ~/.bashrc
    sed -i '/\.\/Fantasyos\/fantasyos/d' ~/.bashrc
fi
