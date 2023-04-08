<h1 align="center">
cs2-sdk
</h1>

<p align="center">
  <img src="https://img.shields.io/badge/game-CS2-yellow" />
  <img src="https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg" />
</p>

## What's this?
Plain SDK that has basic functionality such as: hooking, interface getter, schema manager, basic math and basic ESP for demonstration purposes.

## How has it been modified?
I have added two major components, label creation and screen grabbing. A `dumps` folder will be created within the CS2 folder (specifically in the `win64` folder), and this will contain all of the images and label data gathered while you play the game. It captures an image/label pair once every second. You can view the changes from the original project [here](https://github.com/bruhmoment21/cs2-sdk/compare/main...SpikeHD:cs2-data-dumper:main). This has been used in tandem with my project [CSMLC](https://github.com/SpikeHD/CSMLC)

Tested on:
- Windows
## Media
![image](https://user-images.githubusercontent.com/53657322/227977558-0b3f22dc-f225-4f19-adbd-f14d5af8e1f6.png)
## Dependencies
- [funchook + distorm](https://github.com/kubo/funchook/releases/tag/v1.1.2) - hooking
- [imgui](https://github.com/ocornut/imgui) - gui
- [STB](https://github.com/cristeigabriel/STB) - signatures
- [Vulkan](https://vulkan.lunarg.com/) - [defines.hpp](https://github.com/bruhmoment21/cs2-sdk/blob/main/cs2cheat/src/defines.hpp#L5-L7)
