if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/libs/
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$dirname
./bin/main
