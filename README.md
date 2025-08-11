<div id="top"></div>

<!-- PROJECT SHIELDS -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links-->
<div align="center">

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

</div>

<!-- PROJECT LOGO -->
<br />
<!-- UPDATE -->
<div align="center">
  <a href="https://github.com/Jasz-rgb/Blinnphong">
     <img width="340" alt="image" src="https://github.com/CGS-IITKGP/Blinnphong/blob/30a6937532a03b68edf5d6b664aedade6ee0435c/Screenshot%202025-08-10%20231816.png">
  </a>

  <h3 align="center">Blinn–Phong Lighting with OpenGL + ImGui</h3>

  <p align="center">
  <!-- UPDATE -->
    <i>Interactive real-time lighting control for imported Blender 3D models</i>
  </p>
</div>


<!-- TABLE OF CONTENTS -->
<details>
<summary>Table of Contents</summary>

- [About The Project](#about-the-project)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Contact](#contact)
  - [Maintainer(s)](#maintainers)
  - [creators(s)](#creators)
- [Additional documentation](#additional-documentation)

</details>


<!-- ABOUT THE PROJECT -->
## About The Project
<!-- UPDATE -->
<div align="center">
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="80%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20234838.png">
  </a>
</div>

This project demonstrates **user-interactive Blinn–Phong lighting** in OpenGL with **ImGui-based controls** for real-time tweaking of light type, lighting parameters, and model selection.  It supports **WASD-controlled light movement** for dynamic inspection of lighting effects and renders Blender-imported 3D models (e.g., `Castle` and `House` models).  Integrated ImGui for real-time tweaking of light type, lighting parameters, and model selection.

<p align="right">(<a href="#top">back to top</a>)</p>

## Getting Started

To set up a local instance of the application, follow the steps below.

### Prerequisites
* Install [GLFW](https://www.glfw.org/download.html)
* Install [GLAD](https://glad.dav1d.de/)
* Install [glm](https://github.com/g-truc/glm)
* Install [Assimp](https://github.com/assimp/assimp)
* Install [stb_image.h](https://github.com/nothings/stb)
* Install [ImGui](https://github.com/ocornut/imgui)

The following dependencies are required to be installed for the project to function properly:
<!-- UPDATE -->
* npm
  ```sh
  npm install npm@latest -g
  ```

<p align="right">(<a href="#top">back to top</a>)</p>

### Installation

_Now that the environment has been set up and configured to properly compile and run the project, the next step is to install and configure the project locally on your system._
<!-- UPDATE -->
1. Clone the repository
   ```sh
   git clone https://github.com/Jasz-rgb/Blinnphong.git
   ```
2. Make the script executable
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Execute the script
   ```sh
   ./Blinnphong
   ```

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage
<!-- UPDATE -->

<div align="center">
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="50%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20231816.png">
  </a>
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="50%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20231232.png">
  </a>
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="50%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20232840.png">
  </a>
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="50%" alt="image" src="https://github.com/CGS-IITKGP/Blinnphong/blob/3777b0c51a75ba2eb1b683737d13de1c2a8ebd3a/Screenshot%202025-08-11%20091051.png">
  </a>
</div> 

<p align="right">(<a href="#top">back to top</a>)</p>

## Contact

### Maintainer(s)

The currently active maintainer(s) of this project.

<!-- UPDATE -->
- [Jasmine](https://github.com/Jasz-rgb)

### Creator(s)

Honoring the original creator(s) and ideator(s) of this project.

<!-- UPDATE -->
- [Jasmine](https://github.com/Jasz-rgb)

<p align="right">(<a href="#top">back to top</a>)</p>

## Additional documentation

  - [License](/LICENSE)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[contributors-url]: https://github.com/Jasz-rgb/Blinnphong/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[forks-url]: https://github.com/Jasz-rgb/Blinnphong/network/members
[stars-shield]: https://img.shields.io/github/stars/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[stars-url]: https://github.com/Jasz-rgb/Blinnphong/stargazers
[issues-shield]: https://img.shields.io/github/issues/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[issues-url]: https://github.com/Jasz-rgb/Blinnphong/issues
[license-shield]: https://img.shields.io/github/license/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[license-url]: https://github.com/Jasz-rgb/Blinnphong/blob/master/LICENSE
