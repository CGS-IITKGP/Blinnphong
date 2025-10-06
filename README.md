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
<div align="center">
  <a href="https://github.com/Jasz-rgb/Blinnphong">
     <img width="340" alt="Blinn-Phong Screenshot" src="https://github.com/CGS-IITKGP/Blinnphong/blob/30a6937532a03b68edf5d6b664aedade6ee0435c/Screenshot%202025-08-10%20231816.png">
  </a>

  <h3 align="center">Blinn–Phong Lighting with OpenGL + ImGui</h3>

  <p align="center">
    <i>Interactive real-time lighting control for imported Blender 3D models</i>
  </p>
</div>

---

<details>
<summary>Table of Contents</summary>

- [About The Project](#about-the-project)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
- [Contact](#contact)
  - [Maintainer(s)](#maintainers)
  - [Creator(s)](#creators)
- [Additional Documentation](#additional-documentation)

</details>

---

## About The Project

<div align="center">
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="80%" alt="Preview" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20234838.png">
  </a>
</div>

This project demonstrates **interactive Blinn–Phong lighting** in OpenGL, featuring **real-time ImGui controls** for lighting parameters, material properties, and model selection.  
It provides a fully **dependency-free experience** — all required headers and libraries are already integrated.  

### ✨ Key Features
- Pure **C++ + OpenGL** implementation — *no external installations required*  
- **ImGui-powered controls** for real-time tweaking of light color, position, and shininess  
- **WASD-controlled light movement** to observe reflections from multiple angles  
- **Multiple imported Blender models** (Castle, House, etc.) for lighting visualization  
- Organized CMake-based build system  
- Clean structure for extension into advanced shading models  

<p align="right">(<a href="#top">back to top</a>)</p>

---

## Getting Started

This project is now **completely dependency-free** — all the required third-party libraries (GLFW, GLAD, GLM, stb_image, Assimp, ImGui) are already configured in the repository.  
You just need to build and run the executable.

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/Jasz-rgb/Blinnphong.git
   ```
2. **Build the Project**
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. **Run the script**
   ```sh
   ./Blinnphong
   ```

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage
<!-- UPDATE -->

<div align="center">
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/CGS-IITKGP/Blinnphong/blob/dfbc74495e7caf232fdde55ebeffdabd9906af4b/Screenshot%202025-08-10%20231154.png">
  </a>
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20231232.png">
  </a>
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20232840.png">
  </a>
  <a href="https://github.com/Jasz-rgb/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/CGS-IITKGP/Blinnphong/blob/3777b0c51a75ba2eb1b683737d13de1c2a8ebd3a/Screenshot%202025-08-11%20091051.png">
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
