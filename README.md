# Space Shooter

This is a C-based game/application that uses the Allegro 5 library for graphics, input, and other multimedia functions. This project demonstrates how to build a simple application that runs on Linux systems and makes use of Allegro 5.

## Features

- **Graphics Rendering**: Uses Allegro 5 for 2D graphics.
- **Input Handling**: Processes keyboard inputs.
- **Asset Management**: Assets are loaded from an `assets` directory.

## Building

### Prerequisites

Make sure you have the following installed on your system:

- GCC (GNU Compiler Collection)
- Allegro 5 library (liballegro5-dev)
- Make

### Allegro

You need to install the Allegro 5 library. You can install Allegro 5 on Ubuntu using the following command:

```bash
sudo apt-get install liballegro*5.2 liballegro*5-dev
```

### Build

After cloning, build with make.

```bash
make
```

The binary will be generated in the project root directory inside `release`.

### Run

After building the application, you can run it using the following command:

```bash
./release/Asteroids
```

### AppImage

To build an AppImage, run:

```bash
make AppImage
```

This will create a portable AppImage in the project root called `Asteroids.AppImage`. This is how release packages are published.

### Install

To install the application (binary and assets) to the `/opt/asteroids` directory, run:

```bash
sudo make install
```

This will:

1. Install the binary to `/opt/asteroids`
2. Copy the assets directory to `/opt/asteroids/assets`
3. Install a desktop launcher.

### Uninstall

To uninstall the application, use:

```bash
sudo make uninstall
```

This will remove the binary, assets, and the installed desktop launcher.

### Clean

To clean all the build files created, run:

```bash
make clean
```

This will remove the compiled binary and object files from the project directory.

## License

This project is open-sourced software licensed under the [MIT License](https://opensource.org/licenses/MIT).

## Credits

This project includes third-party assets. See [ATTRIBUTIONS.md](./ATTRIBUTIONS.md) for details on asset usage and licensing.
